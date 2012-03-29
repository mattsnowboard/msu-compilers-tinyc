#ifndef _WRITESTMT_H
#define _WRITESTMT_H

#include "Statement.h"
#include "Expr.h"

class WriteStmt : public Statement
{
public:

    WriteStmt(Expr *expr) :
        _expr(expr)
    {}

    virtual void Execute()
    {
    }

    virtual WriteStmt* Clone()
    {
        Expr *n = (_expr) ? _expr->Clone() : NULL;
        WriteStmt *w = new WriteStmt(n);
        return w;
    }

    virtual void Accept(StatementVisitor &v) const
    {
        v.Visit(*this);
    }

    Expr const* GetExpr() const
    {
        return _expr;
    }

    ~WriteStmt()
    {
        if (_expr) {
            delete _expr;
        }
    }

protected:
    Expr *_expr;
};

#endif
