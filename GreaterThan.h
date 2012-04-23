#ifndef _GREATERTHAN_H
#define _GREATERTHAN_H

#include "Binary.h"

class GreaterThan : public Binary
{
public:
    GreaterThan(Expr *left, Expr *right, int lineNum) :
        Binary(left, right, lineNum) {}

    virtual GreaterThan* Clone()
    {
        Expr *l = (_left) ? _left->Clone() : NULL;
        Expr *r = (_right) ? _right->Clone() : NULL;
        GreaterThan *b = new GreaterThan(l, r, _line);
        return b;
    }
/*
    virtual void Evaluate()
    {
        if (_left && _right) {
            _left->Evaluate();
            _right->Evaluate();
            _value = (_left->Get() > _right->Get()) ? 1 : 0;
        }
    }
*/
    virtual void Accept(StatementVisitor &v) const
    {
        v.Visit(*this);
    }
};

#endif
