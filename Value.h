#ifndef _VALUE_H
#define _VALUE_H

#include "Expr.h"

class Value : public Expr
{
public:
    explicit Value(int v) : Expr(v) {}

    virtual Value* Clone()
    {
        return new Value(_value);
    }
    
    virtual void Accept(StatementVisitor &v) const
    {
        v.Visit(*this);
    }
};

#endif
