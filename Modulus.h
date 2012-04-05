#ifndef _MODULUS_H
#define _MODULUS_H

#include "Binary.h"

class Modulus : public Binary
{
public:
    Modulus(Expr *left, Expr *right) :
        Binary(left, right) {}

    virtual Modulus* Clone()
    {
        Expr *l = (_left) ? _left->Clone() : NULL;
        Expr *r = (_right) ? _right->Clone() : NULL;
        Modulus *b = new Modulus(l, r);
        return b;
    }

    virtual void Accept(StatementVisitor &v) const
    {
        v.Visit(*this);
    }
};

#endif
