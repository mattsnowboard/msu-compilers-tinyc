#ifndef _ADD_H
#define _ADD_H

#include "Binary.h"

class Add : public Binary
{
public:
    Add(Expr *left, Expr *right, int lineNum) :
        Binary(left, right, lineNum) {}

    virtual Add* Clone()
    {
        Expr *l = (_left) ? _left->Clone() : NULL;
        Expr *r = (_right) ? _right->Clone() : NULL;
        Add *b = new Add(l, r);
        return b;
    }

    virtual void Accept(StatementVisitor &v) const
    {
        v.Visit(*this);
    }
};

#endif
