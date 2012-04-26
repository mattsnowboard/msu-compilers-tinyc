#ifndef _IFSTMT_H
#define _IFSTMT_H

#include "Conditional.h"

class IfStmt : public Conditional
{
public:

    IfStmt(Expr *cond, StatementList *stmts, int lineNum) :
        Conditional(cond, stmts, lineNum)
    {}

    virtual IfStmt* Clone()
    {
        Expr *c = (_cond) ? _cond->Clone() : NULL;
        StatementList *s = (_stmts) ? _stmts->Clone() : NULL;
        IfStmt *ifstmt = new IfStmt(c, s, _line);
        return ifstmt;
    }

    virtual void Accept(StatementVisitor &v) const
    {
        v.Visit(*this);
    }
};

#endif
