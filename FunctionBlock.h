#ifndef _FUNCTION_BLOCK_H
#define _FUNCTION_BLOCK_H

#include "ParamDefList.h"
#include "StatementList.h"
#include "SymbolTable.h"
#include "StatementVisitor.h"
#include "DeclStmt.h"
#include <string>

class FunctionBlock
{
public:
    FunctionBlock(const std::string name, ParamDefList *params) :
        _name(name), _params(params), _statements(NULL)
    {
        
    }

    virtual ~FunctionBlock()
    {
        if (_params) {
            delete _params;
        }
        if (_statements) {
            delete _statements;
        }
        if (_decls) {
            delete _decls;
        }
    }

    void SetDeclarationList(StatementList *sl)
    {
        if (_decls != NULL) {
            delete _decls;
        }
        _decls = sl;
        int localCnt = -4;
        StatementList::ListT stmts = sl->GetStatements();
        for (StatementList::ListT::const_iterator it = stmts.begin();
             it != stmts.end();
             ++it) {
            DeclStmt const* d = dynamic_cast<DeclStmt const*>(*it);
            _table.AddVar(d->GetName(), localCnt);
            localCnt -= 4;
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

    SymbolTable const& GetSymbolTable() const
    {
        return _table;
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
    StatementList *_decls;
    SymbolTable _table;
};

#endif
