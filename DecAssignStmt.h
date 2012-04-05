#ifndef _DECASSIGNSTMT_H
#define _DECASSIGNSTMT_H

#include "SymbolTable.h"
#include "AssignStmt.h"

class DecAssignStmt : public AssignStmt
{
public:

    DecAssignStmt(const std::string &name, Expr *value, int lineNum) :
        AssignStmt(name, value, lineNum)
    {}

    virtual DecAssignStmt* Clone()
    {
        Expr *v = (_value) ? _value->Clone() : NULL;
        DecAssignStmt *a = new DecAssignStmt(_name, v, _line);
        return a;
    }

    virtual void Accept(StatementVisitor &v) const
    {
        v.Visit(*this);
    }
};

#endif
