#ifndef _NEGATE_H
#define _NEGATE_H

#include "Unary.h"

class Negate : public Unary
{
public:
    Negate(Expr *child) : Unary(child) {}

    virtual Negate* Clone()
    {
        Expr *c = (_child) ? _child->Clone() : NULL;
        Negate *u = new Negate(c);
        return u;
    }

    virtual void Evaluate()
    {
        if (_child) {
            _child->Evaluate();
            _value = -_child->Get();
        }
    }

    virtual void Accept(StatementVisitor &v) const
    {
        v.Visit(*this);
    }
};

#endif
