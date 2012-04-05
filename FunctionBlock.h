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
    FunctionBlock(const std::string name, ParamDefList *params, int lineNum) :
        _line(lineNum),
        _name(name),
        _params(params),
        _statements(NULL),
        _decls(NULL)
    {
        int paramCnt = 8;
        ParamDefList::ListT plist = _params->GetParams();
        for (ParamDefList::ListT::reverse_iterator it = plist.rbegin();
             it != plist.rend();
             ++it) {
            _table.AddVar(*it, paramCnt);
            paramCnt += 4;
        }
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
            throw std::runtime_error("Declaration list already set!");
        }
        _decls = sl;
        int localCnt = -4;
        StatementList::ListT stmts = sl->GetStatements();
        for (StatementList::ListT::const_iterator it = stmts.begin();
             it != stmts.end();
             ++it) {
            DeclStmt const* d = (DeclStmt const*)(*it);
            _table.AddVar(d->GetName(), localCnt);
            localCnt -= 4;
        }
    }

    void SetStatementList(StatementList *sl)
    {
        if (_statements != NULL) {
            throw std::runtime_error("Statement list already set!");
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

    StatementList const* GetDeclarations() const
    {
        return _decls;
    }

    SymbolTable const* GetSymbolTable() const
    {
        return &_table;
    }

    // Support the Visitor Pattern
    virtual void Accept(StatementVisitor &v) const
    {
        v.Visit(*this);
    }

    int GetLine() const
    {
        return _line;
    }

private:
    FunctionBlock(const FunctionBlock &s);
    FunctionBlock& operator=(const FunctionBlock &s);

    int _line;
    std::string _name;
    ParamDefList *_params;
    StatementList *_statements;
    StatementList *_decls;
    SymbolTable _table;
};

#endif
