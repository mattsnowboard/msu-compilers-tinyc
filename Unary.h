#ifndef _UNARY_H
#define _UNARY_H

#include "Expr.h"

class Unary : public Expr
{
public:
    Unary(Expr *child) : _child(child)
    {
        if (_child) {
            _child->Evaluate();
        }
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
