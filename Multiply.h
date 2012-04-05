#ifndef _MULTIPLY_H
#define _MULTIPLY_H

#include "Binary.h"

class Multiply : public Binary
{
public:
    Multiply(Expr *left, Expr *right, int lineNum) :
        Binary(left, right, lineNum) {}

    virtual Multiply* Clone()
    {
        Expr *l = (_left) ? _left->Clone() : NULL;
        Expr *r = (_right) ? _right->Clone() : NULL;
        Multiply *b = new Multiply(l, r);
        return b;
    }

    virtual void Accept(StatementVisitor &v) const
    {
        v.Visit(*this);
    }
};

#endif
