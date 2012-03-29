#ifndef _BINARY_H
#define _BINARY_H

#include "Expr.h"

class Binary : public Expr
{
public:
    Binary(Expr *left, Expr *right) :
        _left(left), _right(right)
    {
        if (_left) {
            _left->Evaluate();
        }
        if (_right) {
            _right->Evaluate();
        }
    }

    virtual ~Binary()
    {
        if (_left != NULL) {
            delete _left;
        }
        if (_right != NULL) {
            delete _right;
        }
    }

    Expr const* GetLeft() const
    {
        return _left;
    }

    Expr const* GetRight() const
    {
        return _right;
    }

protected:
    Expr *_left;
    Expr *_right;
};

#endif
