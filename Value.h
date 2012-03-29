#ifndef _VALUE_H
#define _VALUE_H

#include "Expr.h"

class Value : public Expr
{
public:
    Value(int v) : Expr(v) {}

    virtual Value* Clone()
    {
        return new Value(_value);
    }
    
    // NOP
    virtual void Evaluate()
    {
    }

    virtual void Accept(StatementVisitor &v) const
    {
        v.Visit(*this);
    }
};

#endif
