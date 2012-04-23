#ifndef _LESSTHAN_H
#define _LESSTHAN_H

#include "Binary.h"

class LessThan : public Binary
{
public:
    LessThan(Numerical *left, Numerical *right) :
        Binary(left, right) {}

    virtual LessThan* Clone()
    {
        Numerical *l = (_left) ? _left->Clone() : NULL;
        Numerical *r = (_right) ? _right->Clone() : NULL;
        LessThan *b = new LessThan(l, r);
        return b;
    }

    virtual void Evaluate()
    {
        if (_left && _right) {
            _left->Evaluate();
            _right->Evaluate();
            _value = (_left->Get() < _right->Get()) ? 1 : 0;
        }
    }

    virtual void Accept(StatementVisitor &v) const
    {
        v.Visit(*this);
    }
};

#endif
