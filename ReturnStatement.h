#ifndef _RETURNSTMT_H
#define _RETURNSTMT_H

#include "Statement.h"
#include "Expr.h"

class ReturnStmt : public Statement
{
public:

    ReturnStmt(Expr *expr, int lineNum) :
        Statement(lineNum), _expr(expr)
    {}

    virtual ReturnStmt* Clone()
    {
        Expr *n = (_expr) ? _expr->Clone() : NULL;
        ReturnStmt *r = new ReturnStmt(n, _line);
        return r;
    }

    virtual void Accept(StatementVisitor &v) const
    {
        v.Visit(*this);
    }

    Expr const* GetExpr() const
    {
        return _expr;
    }

    ~ReturnStmt()
    {
        if (_expr) {
            delete _expr;
        }
    }

protected:
    Expr *_expr;
};

#endif
