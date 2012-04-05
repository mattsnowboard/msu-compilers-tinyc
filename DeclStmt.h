#ifndef _DECLSTMT_H
#define _DECLSTMT_H

#include "Statement.h"
#include "Expr.h"

class DeclStmt : public Statement
{
public:

    DeclStmt(const std::string &name, int lineNum) :
        Statement(lineNum), _name(name)
    {}

    virtual DeclStmt* Clone()
    {
        DeclStmt *d = new DeclStmt(_name, _line);
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
