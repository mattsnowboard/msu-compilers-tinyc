#ifndef _FUNCTION_BLOCK_H
#define _FUNCTION_BLOCK_H

#include "ParamDefList.h"
#include "StatementList.h"
#include "SymbolTable.h"
#include "StatementVisitor.h"
#include "DeclStmt.h"
#include "DecAssignStmt.h"
#include "LessThan.h"
#include "GreaterThan.h"
#include <string>

class FunctionBlock : public StatementVisitor
{
public:
    FunctionBlock(const std::string name, ParamDefList *params, int lineNum) :
        _line(lineNum),
        _localCnt(0),
        _name(name),
        _params(params),
        _statements(NULL),
        _decls(NULL)
    {
        _paramCnt = 8;
        ParamDefList::ListT plist = _params->GetParams();
        for (ParamDefList::ListT::reverse_iterator it = plist.rbegin();
             it != plist.rend();
             ++it) {
            _table.AddVar(*it, _paramCnt);
            _paramCnt += 4;
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
    }

    void SetStatementList(StatementList *sl)
    {
        if (_statements != NULL) {
            throw std::runtime_error("Statement list already set!");
        }
        _statements = sl;

        // look for declarations
        _localCnt = -4;
        StatementList::ListT stmts = sl->GetStatements();
        for (StatementList::ListT::const_iterator it = stmts.begin();
             it != stmts.end();
             ++it) {
            (*it)->Accept(*this);
        }
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

    int GetVariableSpace() const
    {
        return _localCnt + 4;
    }
    
    int GetParamSpace() const
    {
        return _paramCnt - 8;
    }

    // StatementVisitor implementation
    // Used to find the declarations and add to symbol table
    virtual void Visit(const Program &p) {}
    virtual void Visit(const FunctionBlock &f) {}

    virtual void Visit(const Add &a) {}
    virtual void Visit(const Divide &d) {}
    virtual void Visit(const Multiply &m) {}
    virtual void Visit(const Negate &n) {}
    virtual void Visit(const Subtract &s) {}
    virtual void Visit(const Modulus &s) {}
    virtual void Visit(const Value &v) {}
    virtual void Visit(const Variable &v) {}

    virtual void Visit(const AssignStmt &a) {}
    virtual void Visit(const DecAssignStmt &a)
    {
        _table.AddVar(a.GetName(), _localCnt);
        _localCnt -= 4;
    }
    virtual void Visit(const WriteStmt &w) {}
    virtual void Visit(const DeclStmt &d)
    {
        _table.AddVar(d.GetName(), _localCnt);
        _localCnt -= 4;
    }
    virtual void Visit(const ReturnStmt &r) {}
    
    virtual void Visit(const FuncCall &f) {}

    virtual void Visit(const LessThan &l){}
    virtual void Visit(const GreaterThan &g){}

private:
    FunctionBlock(const FunctionBlock &s);
    FunctionBlock& operator=(const FunctionBlock &s);

    int _line;
    int _localCnt;
    int _paramCnt;
    std::string _name;
    ParamDefList *_params;
    StatementList *_statements;
    StatementList *_decls;
    SymbolTable _table;
};

#endif
