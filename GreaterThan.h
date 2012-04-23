#ifndef _GREATERTHAN_H
#define _GREATERTHAN_H

#include "Binary.h"

class GreaterThan : public Binary
{
public:
    GreaterThan(Numerical *left, Numerical *right) :
        Binary(left, right) {}

    virtual GreaterThan* Clone()
    {
        Numerical *l = (_left) ? _left->Clone() : NULL;
        Numerical *r = (_right) ? _right->Clone() : NULL;
        GreaterThan *b = new GreaterThan(l, r);
        return b;
    }

    virtual void Evaluate()
    {
        if (_left && _right) {
            _left->Evaluate();
            _right->Evaluate();
            _value = (_left->Get() > _right->Get()) ? 1 : 0;
        }
    }

    virtual void Accept(StatementVisitor &v) const
    {
        v.Visit(*this);
    }
};

#endif
