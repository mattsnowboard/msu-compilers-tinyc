#ifndef _DIVIDE_H
#define _DIVIDE_H

#include "Binary.h"

class Divide : public Binary
{
public:
    Divide(Expr *left, Expr *right, int lineNum) :
        Binary(left, right, lineNum) {}

    virtual Divide* Clone()
    {
        Expr *l = (_left) ? _left->Clone() : NULL;
        Expr *r = (_right) ? _right->Clone() : NULL;
        Divide *b = new Divide(l, r);
        return b;
    }

    virtual void Accept(StatementVisitor &v) const
    {
        v.Visit(*this);
    }
};

#endif
