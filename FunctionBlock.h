#ifndef _FUNCTION_BLOCK_H
#define _FUNCTION_BLOCK_H

#include "ParamDefList.h"
#include "StatementList.h"
#include "StatementVisitor.h"
#include <string>

class FunctionBlock
{
public:
    FunctionBlock(const std::string name, ParamDefList *params) :
        _name(name), _params(params), _statements(NULL)
    {}

    virtual ~FunctionBlock()
    {
        if (_params) {
            delete _params;
        }
        if (_statements) {
            delete _statements;
        }
    }

    void SetStatementList(StatementList *sl)
    {
        if (_statements != NULL) {
            delete _statements;
        }
        _statements = sl;
    }

    const std::string& GetName() const 
    {
        return _name;
    }

    ParamDefList const * GetParameters() const
    {
        return _params;
    }

    StatementList const* GetStatements() const
    {
        return _statements;
    }

    // Support the Visitor Pattern
    virtual void Accept(StatementVisitor &v) const
    {
        v.Visit(*this);
    }

private:
    FunctionBlock(const FunctionBlock &s);
    FunctionBlock& operator=(const FunctionBlock &s);

    std::string _name;
    ParamDefList *_params;
    StatementList *_statements;
};

#endif
