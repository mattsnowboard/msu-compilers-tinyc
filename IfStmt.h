#ifndef _IFSTMT_H
#define _IFSTMT_H

#include "Conditional.h"

class IfStmt : public Conditional
{
public:

    IfStmt(Numerical *cond, StatementList *stmts) :
        Conditional(cond, stmts)
    {}

    virtual void Execute()
    {
        if (_cond)
        {
            _cond->Evaluate();
       	    if (_cond->Get() != 0) {
                // true, execute statement list
                _stmts->Execute();
            }
        }
    }

    virtual IfStmt* Clone()
    {
        Numerical *c = (_cond) ? _cond->Clone() : NULL;
        StatementList *s = (_stmts) ? _stmts->Clone() : NULL;
        IfStmt *ifstmt = new IfStmt(c, s);
        return ifstmt;
    }

    virtual void Accept(StatementVisitor &v) const
    {
        v.Visit(*this);
    }
};

#endif
