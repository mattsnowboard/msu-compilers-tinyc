#ifndef _NOTEQUALTOSTMT_H
#define _NOTEQUALTOSTMT_H

#include "Binary.h"

class NotEqualToStmt : public Binary
{
public:
    NotEqualToStmt(Expr *left, Expr *right, int lineNum) :
        Binary(left, right, lineNum) {}

    virtual NotEqualToStmt* Clone()
    {
        Expr *l = (_left) ? _left->Clone() : NULL;
        Expr *r = (_right) ? _right->Clone() : NULL;
        NotEqualToStmt *b = new NotEqualToStmt(l, r, _line);
        return b;
    }
/*
    virtual void Evaluate()
    {
        if (_left && _right) {
            _left->Evaluate();
            _right->Evaluate();
            _value = (_left->Get() > _right->Get()) ? 1 : 0;
        }
    }
*/
    virtual void Accept(StatementVisitor &v) const
    {
        v.Visit(*this);
    }
};

#endif
