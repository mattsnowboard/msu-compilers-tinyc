#ifndef _BLOCK_H
#define _BLOCK_H

#include "Statement.h"
#include "StatementList.h"
#include "SymbolTable.h"
#include "StatementVisitor.h"
#include "DecAssignStmt.h"
#include "DeclStmt.h"
#include "Conditional.h"
#include "IfStmt.h"
#include "WhileStmt.h"
#include <string>
#include <stdexcept>

class Block : public Statement, public StatementVisitor
{
public:
    Block(Block *parent = NULL, int lineNo = 0) :
        Statement(lineNo),
        _localCnt(0),
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
        _table.SetParent(_parent->GetSymbolTable());
    }

    void SetStatementList(StatementList *sl)
    {
        if (_statements != NULL) {
            throw std::runtime_error("Statement list already set!");
        }
        _statements = sl;
    }

    void ParseLocals()
    {
        // look for declarations
        StatementList::ListT stmts = _statements->GetStatements();
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

    SymbolTable * GetSymbolTable()
    {
        return &_table;
    }
    
    // figure out how much space we need in total
    int GetLocalTotal() const
    {
        return _localCnt;
    }

    void SetNestedOffset(int off)
    {
        _localCnt = off;
    }

    // Support the Visitor Pattern
    virtual void Accept(StatementVisitor &v) const
    {
        v.Visit(*this);
    }

    // I'm getting sloppy
    virtual void Accept(StatementVisitor &v)
    {
        v.Visit(*this);
    }

    virtual Block* Clone()
    {
        // this probably isn't correct
        Block *b = new Block(_parent, _line);
        StatementList *sl = (_statements) ? _statements->Clone() : NULL;
        b->SetStatementList(sl);
        return b;
    }

    // StatementVisitor implementation
    // Used to find the declarations and add to symbol table
    virtual void Visit(const Program &p) {}
    virtual void Visit(const FunctionBlock &f) {}
    virtual void Visit(const Block &b)
    {
        Block &bNC = const_cast<Block&>(b);
        VisitBlock(bNC);
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
        _table.AddVar(a.GetName(), _localCnt - 4);
        _localCnt -= 4;
    }
    virtual void Visit(const WriteStmt &w) {}
    virtual void Visit(const DeclStmt &d)
    {
        _table.AddVar(d.GetName(), _localCnt - 4);
        _localCnt -= 4;
    }
    virtual void Visit(const ReturnStmt &r) {}
    
    virtual void Visit(const FuncCall &f) {}

    virtual void Visit(const LessThan &l){}
    virtual void Visit(const GreaterThan &g){}
    virtual void Visit(const IfStmt &i)
    {
        Block *b = const_cast<Block*>(i.GetBlock());
        VisitBlock(*b);
    }

    virtual void Visit(const WhileStmt &i)
    {
        Block *b = const_cast<Block*>(i.GetBlock());
        VisitBlock(*b);
    }

    virtual void Visit(const EqualToStmt &e){}
    virtual void Visit(const NotEqualToStmt &e){}

    void VisitBlock(Block &b)
    {
        b.SetParent(this);
        b.SetNestedOffset(_localCnt);
        b.ParseLocals();
        _localCnt += b.GetLocalTotal();
    }

private:
    Block(const Block &s);
    Block& operator=(const Block &s);

    int _localCnt;
    int _nestedLocalCnt;
    int _localOffset;
    StatementList *_statements;
    SymbolTable _table;
    Block *_parent;
};

#endif
