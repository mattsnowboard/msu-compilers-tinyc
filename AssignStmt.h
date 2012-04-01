#ifndef _ASSIGNSTMT_H
#define _ASSIGNSTMT_H

#include "SymbolTable.h"
#include "Statement.h"
#include "Value.h"

class AssignStmt : public Statement
{
public:

    AssignStmt(const std::string &name, Expr *value) :
        _name(name), _value(value)
    {}

    virtual void Execute()
    {
       
	}

    virtual AssignStmt* Clone()
    {
        Expr *v = (_value) ? _value->Clone() : NULL;
        AssignStmt *a = new AssignStmt(_name, v);
        return a;
    }

    virtual void Accept(StatementVisitor &v) const
    {
        v.Visit(*this);
    }

    const std::string& GetName() const
    {
        return _name;
    }

    Expr const* GetValue() const
    {
        return _value;
    }

    ~AssignStmt()
    {
        if (_value) {
            delete _value;
        }
    }

protected:
    std::string _name;
    Expr* _value;
};

#endif
