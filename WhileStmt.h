#ifndef _WHILESTMT_H
#define _WHILESTMT_H

#include "Conditional.h"

class WhileStmt : public Conditional
{
public:
    WhileStmt(Expr *cond, StatementList *stmts, int lineNum) :
        Conditional(cond, stmts, lineNum)
    {}

    virtual WhileStmt* Clone()
    {
        Expr *c = (_cond) ? _cond->Clone() : NULL;
        StatementList *s = (_stmts) ? _stmts->Clone() : NULL;
        WhileStmt *wstmt = new WhileStmt(c, s, _line);
        return wstmt;
    }

    virtual void Accept(StatementVisitor &v) const
    {
        v.Visit(*this);
    }
};

#endif
