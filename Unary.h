#ifndef _UNARY_H
#define _UNARY_H

#include "Expr.h"

class Unary : public Expr
{
public:
    explicit Unary(Expr *child, int lineNum) : Expr(lineNum), _child(child)
    {
    }
    
    virtual ~Unary()
    {
        if (_child != NULL) {
            delete _child;
        }
    }

    Expr const* GetChild() const
    {
        return _child;
    }

protected:
    Expr *_child;
};

#endif
