#ifndef _FUNCCALL_H
#define _FUNCCALL_H

#include "Expr.h"
#include "SymbolTable.h"
#include "ExprList.h"
#include <string>

class FuncCall : public Expr
{
public:
    FuncCall(const std::string &s, ExprList *params) :
        _name(s), _params(params)
    {}

    std::string GetName() const { return _name; }

    virtual FuncCall* Clone()
    {
        ExprList *l = (_params) ? _params->Clone() : NULL;
        FuncCall *f = new FuncCall(_name, l;
        return f;
    }

    virtual void Evaluate()
    {

    }

    virtual void Accept(StatementVisitor &v) const
    {
        v.Visit(*this);
    }

    virtual ~FuncCall()
    {
        if (_params != NULL) {
            delete _params;
        }
    }

protected:
    std::string _name;
    ExprList *_params;
};

#endif