#ifndef _PROGRAM_H
#define _PROGRAM_H

#include <list>
#include <deque>
#include "Statement.h"

#include "StatementVisitor.h"

class Program
{
public:
    Program()
    {
        _curr = _stmts.begin();
    }
    
    /**
     * Execute next Statment
     */
    void ExecuteTop()
    {
        // execute top of stack and increment the iterator
        if (_curr != _stmts.end()) {
            (*_curr++)->Execute();
        }
    }

    /**
     * Add a Statement to the Program and take ownership
     * @param Statement s
     */
    void AddStatement(Statement *s)
    {
        _stmts.push_back(s);
    }

    typedef std::list<const Statement*> ProgramListT;

    ProgramListT GetStatements() const
    {
        std::list<const Statement*> cret(_stmts.begin(), _stmts.end());
        return cret;
    }

    void Accept(StatementVisitor &v) const
    {
        v.Visit(*this);
    }

    ~Program()
    {
        while (!_stmts.empty()) {
            Statement *s = _stmts.back();
            if (s) {
                delete s;
            }
            _stmts.pop_back();
        }
    }

private:
    // treated like a stack but allow iteration
    std::deque<Statement*> _stmts;
    // current statement to execute
    std::deque<Statement*>::iterator _curr;
};

#endif
