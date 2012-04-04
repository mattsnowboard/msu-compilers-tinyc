#ifndef _DECLSTMT_H
#define _DECLSTMT_H

#include "Statement.h"
#include "Expr.h"

class DeclStmt : public Statement
{
public:

    DeclStmt(const std::string &name) :
        _name(name)
    {}

    virtual DeclStmt* Clone()
    {
        DeclStmt *d = new DeclStmt(_name);
        return d;
    }

    virtual void Accept(StatementVisitor &v) const
    {
        v.Visit(*this);
    }

    const std::string& GetName() const
    {
        return _name;
    }

    ~DeclStmt()
    {
    }

protected:
    std::string _name;
};

#endif
