#ifndef _VARIABLE_H
#define _VARIABLE_H

#include "Unary.h"
#include "SymbolTable.h"
#include <string>

class Variable : public Unary
{
public:
    Variable(const std::string &s) : Unary(NULL), _name(s) {}

    std::string GetName() const { return _name; }
    

    virtual Variable* Clone()
    {
        Variable *v = new Variable(_name);
        v->_child = (_child) ? _child->Clone() : NULL;
        return v;
    }

    virtual void Evaluate()
    {
        // here we want to always re-evaluate
        if (_child) {
            delete _child;
        }
        
        SymbolTable &s = SymbolTable::GetInstance();
        if (s.DoesExist(_name)) {
            Expr *temp = s.GetVal(_name);
            // Now Variable owns this
            _child = temp->Clone();
        }
        else {
            std::cout << "Variable: " << _name << " not defined." << std::endl;
            _value = 0;
        }

        if (_child) {
            _child->Evaluate();
            _value = _child->Get();
        }
    }

    virtual void Accept(StatementVisitor &v) const
    {
        v.Visit(*this);
    }

protected:
    std::string _name;
};

#endif
