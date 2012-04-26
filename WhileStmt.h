#ifndef _WHILESTMT_H
#define _WHILESTMT_H

#include "Conditional.h"

class WhileStmt : public Conditional
{
public:
    WhileStmt(Expr *cond, Block *block, int lineNum) :
        Conditional(cond, block, lineNum)
    {}

    virtual WhileStmt* Clone();

    virtual void Accept(StatementVisitor &v) const
    {
        v.Visit(*this);
    }
};

#endif
