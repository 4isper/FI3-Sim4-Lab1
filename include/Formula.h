// ����, �����, ���� "��������� � ��������� ������"
//
//
//
//

#ifndef __Formula_H__
#define __Formula_H__

#define _USE_MATH_DEFINES
#include "Stack.h"
#include <iostream>
#include <string>
#include "MyString.h"
#include <math.h>

#include "IMap.h"
#include "AVLTree.h"
#include "HashTable.h"
#include "Map.h"
#include "SMap.h"

const size_t FORMULA_MAX_LENGTH = 255;
const size_t FORMULA_TABLES_ARRAY_SIZE = 4;

class TFormulaSelectTable
{
public:
	static const size_t Map = 0;
	static const size_t SMap = 1;
	static const size_t AVLTree = 2;
	static const size_t HashTable = 3;
};

template <class T>
class TFormula
{
protected:
	TString fm;
	TString postfix;
	IMap<TString, T>* tables[FORMULA_TABLES_ARRAY_SIZE];
	size_t selected_table = 0;
	T result;
	bool calculated;
	bool postfix_calculated;
	bool formula_checked;
	void TablesInit(void);
	size_t Priority(const char& c) const;
	size_t PriorityWithUnaryMinus(const char& c) const;
	bool ReservedNamesFuntions(const TString& str) const;
	bool ReservedOperations(const char& c) const;
	bool ReservedConstants(const TString& str, T& res) const;
	void HandleTempNumberOrVarOrFunction(const size_t& sz, TStack<TString>& errs, TString& tmp, const size_t& i, const bool& FirstThrow) const;
	bool GetDefinedValues(TString& str, T& res) const;
public:
	TFormula(const TString& form = "");
	TFormula(const TFormula& f);
	TFormula(TFormula&& f) noexcept;
	TFormula& operator=(const TFormula& f);
	TFormula& operator=(TFormula&& f) noexcept;
	~TFormula();

	void SelectTable(const size_t _selected_table);
	void SetFormula(const TString& form);
	TString GetFormula(void) const;
	TStack<TString> CheckFormula(bool FirstThrow = false);
	void CreatePostfixForm(void);
	TString GetPostfixForm(void);
	T Calculate(void);
	void SetDefinedValues(TString* _vars, T* _vals, const size_t sz);
	void SetDefinedValue(TString* _var, T* _val);
};

template<typename T>
inline void TFormula<T>::TablesInit()
{
	tables[TFormulaSelectTable::Map] = new TMap<TString, T>(FORMULA_MAX_LENGTH);
	tables[TFormulaSelectTable::SMap] = new TSMap<TString, T>(FORMULA_MAX_LENGTH);
	tables[TFormulaSelectTable::AVLTree] = new TAVLTree<TString, T>(FORMULA_MAX_LENGTH);
	tables[TFormulaSelectTable::HashTable] = new THashTable<TString, T>(FORMULA_MAX_LENGTH);
}

template<typename T>
inline size_t TFormula<T>::Priority(const char& c) const
{
	if (c == '^')
		return 4;
	if (c == '*' || c == '/' || c == '^')
		return 3;
	if (c == '+' || c == '-')
		return 2;
	if (c == '(')
		return 1;
	return 0;
}

template<typename T>
inline size_t TFormula<T>::PriorityWithUnaryMinus(const char& c) const
{
	if (c == '~')
		return 5;
	return Priority(c);
}

template<typename T>
inline bool TFormula<T>::ReservedNamesFuntions(const TString& str) const
{
	return (str == "sin" || str == "cos" || str == "tan" || str == "cot" || str == "log");
}

template<typename T>
inline bool TFormula<T>::ReservedOperations(const char& c) const
{
	return Priority(c) > 1;
}

template<typename T>
inline bool TFormula<T>::ReservedConstants(const TString& str, T& res) const
{
	if (str == "pi")
	{
		res = T(M_PI);
		return true;
	}
	if (str == "e")
	{
		res = T(M_E);
		return true;
	}
	return false;
}

template<typename T>
inline void TFormula<T>::HandleTempNumberOrVarOrFunction(const size_t& sz, TStack<TString>& errs, TString& tmp, const size_t& i, const bool& FirstThrow) const
{
	size_t tmp_sz = tmp.GetLen();
	if (tmp[0] == '.')
	{
		errs.Push(TString(std::to_string(i - 1).c_str()) + ": " + "Var or number can't start with '.' yet.");
		if (FirstThrow)
			throw errs.Top();
		tmp = "";
	}
	else if (tmp_sz != 0)
	{
		if (isdigit(tmp[0]))
		{
			bool found_dot = false;
			for (size_t j = 1; j < tmp_sz; j++)
			{
				if (tmp[j] == '.' && found_dot)
				{
					errs.Push(TString(std::to_string(i - 1 - tmp_sz + j).c_str()) + ": " + "Too many dots in one number.");
					if (FirstThrow)
						throw errs.Top();
					break;
				}
				else if (tmp[j] == '.' && !found_dot)
					found_dot = true;
				if (tmp[j] != '.' && !isdigit(tmp[j]))
				{
					errs.Push(TString(std::to_string(i - 1 - tmp_sz + j).c_str()) + ": " + "Var name can't start with a number.");
					if (FirstThrow)
						throw errs.Top();
					break;
				}
			}
			if (tmp[tmp_sz - 1] == '.')
			{
				errs.Push(TString(std::to_string(i - 1).c_str()) + ": " + "Autocorrection for a number that ends with '.' is not supported yet.");
				if (FirstThrow)
					throw errs.Top();
			}
		}
		else
		{
			bool is_reserved_fun_name = ReservedNamesFuntions(tmp);
			if (is_reserved_fun_name && (i == sz || fm[i] != '('))
			{
				errs.Push(TString(std::to_string(i - 1).c_str()) + ": " + "Illegal var name " + tmp + ". It's a reserved function name.");
				if (FirstThrow)
					throw errs.Top();
			}
			if (!is_reserved_fun_name && i != sz && fm[i] == '(')
			{
				errs.Push(TString(std::to_string(i - 1).c_str()) + ": " + "Var name " + tmp + " is not a function.");
				if (FirstThrow)
					throw errs.Top();
			}
		}
		tmp = "";
	}
}

template<typename T>
inline bool TFormula<T>::GetDefinedValues(TString& str, T& res) const
{
	try
	{
		res = *(tables[selected_table]->Find(&str));
		return true;
	}
	catch (const char*)
	{
		return false;
	}
}

template<typename T>
inline TFormula<T>::TFormula(const TString& form)
{
	TablesInit();
	SetFormula(form);
	//postfix = "";
	//result = 0.0;
}

template<typename T>
inline TFormula<T>::TFormula(const TFormula& f)
{
	operator=(f);
}

template<typename T>
inline TFormula<T>::TFormula(TFormula&& f) noexcept
{
	operator=(f);
}

template<typename T>
inline TFormula<T>& TFormula<T>::operator=(const TFormula& f)
{
	if (tables == f.tables)
		return *this;
	fm = f.fm;
	postfix = f.postfix;
	result = f.result;
	calculated = f.calculated;
	postfix_calculated = f.postfix_calculated;
	formula_checked = f.formula_checked;
	selected_table = f.selected_table;
	tables[TFormulaSelectTable::Map] = new TMap<TString, T>(*(static_cast<TMap<TString, T>*>(f.tables[TFormulaSelectTable::Map])));
	tables[TFormulaSelectTable::SMap] = new TSMap<TString, T>(*(static_cast<TSMap<TString, T>*>(f.tables[TFormulaSelectTable::SMap])));
	tables[TFormulaSelectTable::AVLTree] = new TAVLTree<TString, T>(*(static_cast<TAVLTree<TString, T>*>(f.tables[TFormulaSelectTable::AVLTree])));
	tables[TFormulaSelectTable::HashTable] = new THashTable<TString, T>(*(static_cast<THashTable<TString, T>*>(f.tables[TFormulaSelectTable::HashTable])));
	return *this;
}

template<typename T>
inline TFormula<T>& TFormula<T>::operator=(TFormula&& f) noexcept
{
	std::swap(fm, f.fm);
	std::swap(postfix, f.postfix);
	std::swap(tables, f.tables);
	std::swap(selected_table, f.selected_table);
	std::swap(result, f.result);
	std::swap(calculated, f.calculated);
	std::swap(postfix_calculated, f.postfix_calculated);
	std::swap(formula_checked, f.formula_checked);
	return *this;
}

template<typename T>
inline TFormula<T>::~TFormula()
{
	for (size_t i = 0; i < FORMULA_TABLES_ARRAY_SIZE; i++)
	{
		delete tables[i];
	}
	calculated = false;
	postfix_calculated = false;
	formula_checked = false;
}

template<typename T>
inline void TFormula<T>::SelectTable(const size_t _selected_table)
{
	if (_selected_table < FORMULA_TABLES_ARRAY_SIZE)
	{
		selected_table = _selected_table;
	}
	else
	{
		throw "Incorrect selected_table value: bigger than FORMULA_TABLES_ARRAY_SIZE";
	}
}

template<typename T>
inline void TFormula<T>::SetFormula(const TString& form)
{
	size_t sz = form.GetLen();
	calculated = false;
	postfix_calculated = false;
	formula_checked = false;
	fm = "";
	for (size_t i = 0; i < sz; i++)
		if (form[i] != ' ')
			fm += form[i];
}

template<typename T>
inline TString TFormula<T>::GetFormula(void) const
{
	return fm;
}

template<typename T>
inline TStack<TString> TFormula<T>::CheckFormula(bool FirstThrow)
{
	size_t sz = fm.GetLen();
	TStack<TString> errs(sz);
	if (formula_checked)
		return errs;
	if (fm == "")
	{
		errs.Push("Formula is empty.");
		if (FirstThrow)
			throw errs.Top();
		return errs;
	}

	char typo = 0;
	int brackets = 0;
	TString tmp = "";

	// First symbol check
	if (!isdigit(fm[0]) && !isalpha(fm[0]) && fm[0] != '.' && fm[0] != '_' && fm[0] != '(' && fm[0] != '-')
	{
		errs.Push(TString("0: You can't start formula with ") + fm[0] + '.');
		if (FirstThrow)
			throw errs.Top();
	}

	for (size_t i = 0; i < sz; i++)
	{
		size_t tmp_sz = tmp.GetLen();
		if (!isdigit(fm[i]) && !isalpha(fm[i]) && fm[i] != '.' && fm[i] != '_')
		{
			if (fm[i] != '(' && fm[i] != ')')
			{
				if (typo != 0 && (typo != '(' || fm[i] != '-'))
				{
					errs.Push(TString(std::to_string(i).c_str()) + ": " + "Extra operation " + fm[i] + '.');
					if (FirstThrow)
						throw errs.Top();
				}
				typo = fm[i];
				if (!ReservedOperations(fm[i]) && fm[i] != '.' && fm[i] != '_')
				{
					errs.Push(TString(std::to_string(i).c_str()) + ": " + "Illegal character " + fm[i] + '.');
					if (FirstThrow)
						throw errs.Top();
				}
			}
			else
			{
				if (fm[i] == '(')
				{
					typo = '(';
					if (brackets >= 0)
						brackets++;
				}
				else if (fm[i] == ')')
				{
					if (i > 0 && fm[i - 1] == '(')
					{
						errs.Push(TString(std::to_string(i).c_str()) + ": " + "You can't have '()' in formula.");
						if (FirstThrow)
							throw errs.Top();
					}
					typo = 0;
					if (brackets >= 0)
						brackets--;
				}
				if (brackets < 0)
				{
					errs.Push(TString(std::to_string(i).c_str()) + ": " + "Extra ')'.");
					if (FirstThrow)
						throw errs.Top();
				}
			}
			HandleTempNumberOrVarOrFunction(sz, errs, tmp, i, FirstThrow);
		}
		else
		{
			typo = 0;
			tmp += fm[i];
		}
	}
	if (brackets > 0)
	{
		errs.Push("Missing ')'.");
		if (FirstThrow)
			throw errs.Top();
	}
	HandleTempNumberOrVarOrFunction(sz, errs, tmp, sz, FirstThrow);

	formula_checked = errs.IsEmpty();
	return errs;
}

template<typename T>
inline void TFormula<T>::CreatePostfixForm(void)
{
	if (postfix_calculated)
		return;
	if (!formula_checked)
		CheckFormula(true);
	postfix = "";
	size_t sz = fm.GetLen();
	// Ïðîáëåìà óíàðíîãî ìèíóñà.
	TString _fm = fm;
	if (_fm[0] == '-')
		_fm[0] = '~';
	for (size_t i = 1; i < sz; i++)
		if (_fm[i] == '-' && _fm[i - 1] == '(')
			_fm[i] = '~';
	// Â ïîñòôèêñíîé ôîðìóëå âñž äîëæíî ðàçäåëÿòüñÿ ïðîáåëàìè!!!
	TStack<TString> opst(sz);
	bool handling_e = false;
	TString tmp = "";
	TString StackItem;
	bool is_operation;
	bool handling_function = false;

	for (size_t i = 0; i < sz; i++)
	{
		is_operation = ReservedOperations(_fm[i]) || _fm[i] == '~';
		if (!is_operation && _fm[i] != '(' && _fm[i] != ')')
		{
			tmp += _fm[i];
			handling_e = true;
		}
		else
		{
			if (handling_e)
			{
				if (ReservedNamesFuntions(tmp))
				{
					handling_function = true;
					i--;
				}
				else
				{
					handling_function = false;
					postfix += (tmp + " ");
					tmp = "";
				}
			}
			handling_e = false;
			if (_fm[i] == '(')
			{
				opst.Push(TString("("));
			}
			else if (_fm[i] == ')')
			{
				while ((tmp = opst.Pop())[0] != '(')
				{
					handling_e = !(ReservedOperations(tmp[0]) || tmp[0] == '~' || ReservedNamesFuntions(tmp));
					postfix += tmp;
					if (!handling_e)
						postfix += ' ';
				}
			}
			else
			{
				size_t prio, prio_stacki;
				if (handling_function)
					prio = 5;
				else
					prio = PriorityWithUnaryMinus(_fm[i]);
				while (!opst.IsEmpty())
				{
					StackItem = opst.Pop();
					handling_e = !(ReservedOperations(StackItem[0]) || StackItem[0] == '~' || ReservedNamesFuntions(StackItem));
					if (ReservedNamesFuntions(StackItem))
						prio_stacki = 5;
					else
						prio_stacki = PriorityWithUnaryMinus(StackItem[0]);
					if (prio <= prio_stacki)
					{
						postfix += StackItem;
						if (!handling_e)
							postfix += ' ';
					}
					else
					{
						opst.Push(StackItem);
						break;
					}
				}
				handling_e = !(is_operation || handling_function);
				if (handling_function)
					opst.Push(tmp);
				else
					opst.Push(TString(1, _fm[i]));
				handling_function = false;
				tmp = "";
			}
		}
	}
	if (handling_e)
		postfix += tmp;
	if (!opst.IsEmpty() && postfix[postfix.GetLen() - 1] != ' ')
		postfix += ' ';

	while (!opst.IsEmpty())
	{
		tmp = opst.Pop();
		handling_e = !(ReservedOperations(tmp[0]) || tmp[0] == '~' || ReservedNamesFuntions(tmp));
		postfix += tmp;
		if (!handling_e && !opst.IsEmpty())
			postfix += ' ';
	}
	postfix_calculated = true;
}

template<typename T>
inline TString TFormula<T>::GetPostfixForm(void)
{
	if (!postfix_calculated)
		CreatePostfixForm();
	return postfix;
}

template<typename T>
inline T TFormula<T>::Calculate(void)
{
	if (calculated)
		return result;
	if (!postfix_calculated)
		CreatePostfixForm();
	size_t sz = postfix.GetLen();
	TStack<T> opst(sz);
	TString tmp = "";
	for (size_t i = 0; i < sz + 1; i++)
	{
		if (postfix[i] == ' ' || i == sz)
		{
			if (Priority(tmp[0]) > 0)
			{
				T b = opst.Pop();
				T a = opst.Pop();
				switch (tmp[0])
				{
				case '+':
					opst.Push(a + b);
					break;
				case '-':
					opst.Push(a - b);
					break;
				case '*':
					opst.Push(a * b);
					break;
				case '/':
					if (std::fpclassify(b) == FP_ZERO)
						throw std::runtime_error("Division by zero.");
					opst.Push(a / b);
					break;
				case '^':
					opst.Push(std::pow(a, b));
					break;
				}
			}
			else if (tmp[0] == '~')
			{
				opst.Push(-opst.Pop());
			}
			else if (ReservedNamesFuntions(tmp))
			{
				T a = opst.Pop();
				if (tmp == "sin")
					opst.Push(std::sin(a));
				else if (tmp == "cos")
					opst.Push(std::cos(a));
				else if (tmp == "tan")
				{
					if (std::fpclassify(std::cos(a)) == FP_ZERO) // Ýòî áåñïîëåçíî, êîñèíóñ íèêîãäà íå áóäåò ðàâåí íóëþ.
						throw std::runtime_error("Division by zero.");
					opst.Push(std::tan(a));
				}
				else if (tmp == "cot")
				{
					if (std::fpclassify(std::sin(a)) == FP_ZERO) // Ýòî áåñïîëåçíî, ñèíóñ íèêîãäà íå áóäåò ðàâåí íóëþ.
						throw std::runtime_error("Division by zero.");
					opst.Push(1.0 / (std::tan(a)));
				}
				else if (tmp == "log")
					opst.Push(std::log(a));
				else
					throw "I am sorry, it seems that I forgot about some functions. Ping me pls.";
			}
			else
			{
				T a;
				if (tmp.IsNumber())
				{
					a = std::strtod(tmp.GetString(), nullptr);
					opst.Push(a);
				}
				else
				{
					if (GetDefinedValues(tmp, a))
					{
						opst.Push(a);
					}
					else if (ReservedConstants(tmp, a))
					{
						opst.Push(a);
					}
					else
					{
						throw tmp + " is not defined.";
					}
				}
				
			}
			tmp = "";
		}
		else
		{
			tmp += postfix[i];
		}
	}
	result = opst.Top();
	//calculated = true; // Sadly because tables DO NOT store values but their adresses so you can't really know if someone changed values or not. That's why it's always false;
	return result;
}

template<typename T>
inline void TFormula<T>::SetDefinedValues(TString* _vars, T* _vals, const size_t sz)
{
	if (sz <= 0)
	{
		throw "Size cannot be zero";
	}
	for (size_t i = 0; i < sz; i++)
	{
		SetDefinedValue(&(_vars[i]), &(_vals[i]));
	}
	calculated = false;
}

template<typename T>
inline void TFormula<T>::SetDefinedValue(TString* _var, T* _val)
{
/* 	bool isAdd = true;
	try
	{
		(tables[0])->Add(_var, _val);
	}
	catch (const char*)
	{
		(tables[0])->Find(_var) = _val;
		isAdd = false;
	}
	for (size_t i = 1; i < FORMULA_TABLES_ARRAY_SIZE; i++)
	{
		if (isAdd)
		{
			(tables[i])->Add(_var, _val);
		}
		else
		{
			(tables[i])->Find(_var) = _val;
		}
	} */
	for (size_t i = 0; i < FORMULA_TABLES_ARRAY_SIZE; i++)
	{
		tables[i]->Add(_var, _val);
	}
	calculated = false;
}

#endif