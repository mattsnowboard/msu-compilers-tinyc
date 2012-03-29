#ifndef _ADD_H
#define _ADD_H

#include "Binary.h"

class Add : public Binary
{
public:
    Add(Expr *left, Expr *right) :
        Binary(left, right) {}

    virtual Add* Clone()
    {
        Expr *l = (_left) ? _left->Clone() : NULL;
        Expr *r = (_right) ? _right->Clone() : NULL;
        Add *b = new Add(l, r);
        return b;
    }

    virtual void Evaluate()
    {
        if (_left && _right) {
            _left->Evaluate();
            _right->Evaluate();
            _value = _left->Get() + _right->Get();
        }
    }

    virtual void Accept(StatementVisitor &v) const
    {
        v.Visit(*this);
    }
};

#endif
