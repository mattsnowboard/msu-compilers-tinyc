#ifndef _SUBTRACT_H
#define _SUBTRACT_H

#include "Binary.h"

class Subtract : public Binary
{
public:
    Subtract(Expr *left, Expr *right, int lineNum) :
        Binary(left, right, lineNum) {}
        
    virtual Subtract* Clone()
    {
        Expr *l = (_left) ? _left->Clone() : NULL;
        Expr *r = (_right) ? _right->Clone() : NULL;
        Subtract *b = new Subtract(l, r);
        return b;
    }

    virtual void Accept(StatementVisitor &v) const
    {
        v.Visit(*this);
    }
};

#endif
