#ifndef _VARIABLE_H
#define _VARIABLE_H

#include "Expr.h"
#include "SymbolTable.h"
#include <string>

class Variable : public Expr
{
public:
    explicit Variable(const std::string &s, int lineNum) :
        Expr(lineNum), _name(s) {}

    std::string GetName() const { return _name; }

    virtual Variable* Clone()
    {
        Variable *v = new Variable(_name, _line);
        return v;
    }

    virtual void Accept(StatementVisitor &v) const
    {
        v.Visit(*this);
    }

protected:
    std::string _name;
};

#endif
