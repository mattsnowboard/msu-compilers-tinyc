#ifndef _MULTIPLY_H
#define _MULTIPLY_H

#include "Binary.h"

class Multiply : public Binary
{
public:
    Multiply(Expr *left, Expr *right) :
        Binary(left, right) {}

    virtual Multiply* Clone()
    {
        Expr *l = (_left) ? _left->Clone() : NULL;
        Expr *r = (_right) ? _right->Clone() : NULL;
        Multiply *b = new Multiply(l, r);
        return b;
    }

    virtual void Evaluate()
    {
        if (_left && _right) {
            _left->Evaluate();
            _right->Evaluate();
            _value = _left->Get() * _right->Get();
        }
    }

    virtual void Accept(StatementVisitor &v) const
    {
        v.Visit(*this);
    }
};

#endif
