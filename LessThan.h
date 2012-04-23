#ifndef _LESSTHAN_H
#define _LESSTHAN_H

#include "Binary.h"

class LessThan : public Binary
{
public:
    LessThan(Expr *left, Expr *right, int lineNum) :
        Binary(left, right, lineNum) {}

    virtual LessThan* Clone()
    {
        Expr *l = (_left) ? _left->Clone() : NULL;
        Expr *r = (_right) ? _right->Clone() : NULL;
        LessThan *b = new LessThan(l, r, _line);
        return b;
    }
/*
    virtual void Evaluate()
    {
        if (_left && _right) {
            _left->Evaluate();
            _right->Evaluate();
            _value = (_left->Get() < _right->Get()) ? 1 : 0;
        }
    }
*/
    virtual void Accept(StatementVisitor &v) const
    {
        v.Visit(*this);
    }
};

#endif
