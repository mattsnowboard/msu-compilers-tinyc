#ifndef _BLOCK_H
#define _BLOCK_H

#include "ParamDefList.h"
#include "StatementList.h"
#include "SymbolTable.h"
#include "StatementVisitor.h"
#include "DeclStmt.h"
#include "DecAssignStmt.h"
#include "LessThan.h"
#include "GreaterThan.h"
#include "IfStmt.h"
#include "WhileStmt.h"
#include "EqualToStmt.h"
#include "NotEqualToStmt.h"
#include <string>

class Block : public Statement, StatementVisitor
{
public:
    Block(Block *parent = NULL, int lineNo = 0) :
        Statement(lineNo),
        _localCnt(0),
        _nestedLocalCnt(0),
        _nestedOffset(0),
        _statements(NULL),
        _parent(parent)
    {
    }

    virtual ~Block()
    {
        if (_statements) {
            delete _statements;
        }
        // we don't own _parent obviously
    }

    void SetParent(Block *parent)
    {
        // don't care if we overwrite, we don't own it
        _parent = parent;
    }

    void SetStatementList(StatementList *sl)
    {
        if (_statements != NULL) {
            throw std::runtime_error("Statement list already set!");
        }
        _statements = sl;

        // look for declarations
        _localCnt = 0;
        _nestedLocalCnt = 0;
        StatementList::ListT stmts = sl->GetStatements();
        for (StatementList::ListT::const_iterator it = stmts.begin();
             it != stmts.end();
             ++it) {
            (*it)->Accept(*this);
        }
    }

    StatementList const* GetStatements() const
    {
        return _statements;
    }

    SymbolTable const* GetSymbolTable() const
    {
        return &_table;
    }
    
    // figure out how much space we need in total
    int GetLocalTotal() const
    {
        return _localCnt + _nestedLocalCnt;
    }

    void SetNestedOffset(int off)
    {
        _nestedOffset = off;
    }

    // Support the Visitor Pattern
    virtual void Accept(StatementVisitor &v) const
    {
        v.Visit(*this);
    }

    // StatementVisitor implementation
    // Used to find the declarations and add to symbol table
    virtual void Visit(const Program &p) {}
    virtual void Visit(const FunctionBlock &f) {}
    virtual void Visit(const Block &b)
    {
        b.SetNestedOffset(_nestedLocalCnt);
        _nestedLocalCnt += b.GetLocalTotal();
    }

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
    virtual void Visit(const IfStmt &i){}

    virtual void Visit(const WhileStmt &i){}
    virtual void Visit(const EqualToStmt &e){}
    virtual void Visit(const NotEqualToStmt &e){}

private:
    FunctionBlock(const FunctionBlock &s);
    FunctionBlock& operator=(const FunctionBlock &s);

    int _localCnt;
    int _nestedLocalCnt;
    int _localOffset;
    StatementList *_statements;
    SymbolTable _table;
    Block *_parent;
};

#endif
