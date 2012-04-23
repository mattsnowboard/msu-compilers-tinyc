#ifndef _CONDITIONAL_H
#define _CONDITIONAL_H

#include "Statement.h"
#include "StatementList.h"
#include <list>

class Conditional : public Statement
{
public:
    Conditional(Expr *cond, StatementList *stmts, int lineNum) :
        _cond(cond), _stmts(stmts), _value(lineNum)
    {}
    virtual ~Conditional()
    {
        if (_cond) {
            delete _cond;
            _cond = NULL;
        }
        if (_stmts) {
            delete _stmts;
            _stmts = NULL;
        }
    }
    
    virtual int Get() const { return _value; }

    Expr const* GetCondition() const {
        return _cond;
    }

    StatementList const* GetStatements() const {
        return _stmts;
    }

protected:
    Expr *_cond;
    StatementList *_stmts;
    int _value;
};

#endif
