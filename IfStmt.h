#ifndef _IFSTMT_H
#define _IFSTMT_H

#include "Conditional.h"

class IfStmt : public Conditional
{
public:

    IfStmt(Expr *cond, Block *block, int lineNum) :
        Conditional(cond, block, lineNum)
    {}

    virtual IfStmt* Clone();

    virtual void Accept(StatementVisitor &v) const
    {
        v.Visit(*this);
    }
};

#endif
