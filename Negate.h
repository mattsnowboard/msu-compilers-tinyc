#ifndef _NEGATE_H
#define _NEGATE_H

#include "Unary.h"

class Negate : public Unary
{
public:
    explicit Negate(Expr *child) : Unary(child) {}

    virtual Negate* Clone()
    {
        Expr *c = (_child) ? _child->Clone() : NULL;
        Negate *u = new Negate(c);
        return u;
    }

    virtual void Accept(StatementVisitor &v) const
    {
        v.Visit(*this);
    }
};

#endif
