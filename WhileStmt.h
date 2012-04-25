#ifndef _WHILESTMT_H
#define _WHILESTMT_H

#include "Conditional.h"

class WhileStmt : public Conditional
{
public:
    WhileStmt(Expr *cond, StatementList *stmts, int lineNum) :
        Conditional(cond, stmts, lineNum)
    {}
/*
    virtual void Execute()
    {
        if (_cond)
        {
            _cond->Evaluate();
       	    while (_cond->Get() != 0) {
                // true, execute statement list
                // hopefully this is not an infinite loop, we could implment
                // a way to break out after a very large number of iterations
                _stmts->Execute();
                // DONT FORGET TO RE-EVALUATE
                _cond->Evaluate();
            }
        }
<<<<<<< HEAD
    }*/

=======
    }
*/
>>>>>>> e8d5fdc88d2150e45f7577bb0d755b27f7da41b1
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
