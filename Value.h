#ifndef _VALUE_H
#define _VALUE_H

#include "Expr.h"

class Value : public Expr
{
public:
    explicit Value(int v, int lineNum) : Expr(lineNum, v) {}

    virtual Value* Clone()
    {
        return new Value(_value, _line);
    }
    
    virtual void Accept(StatementVisitor &v) const
    {
        v.Visit(*this);
    }
};

#endif
