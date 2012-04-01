#ifndef _PROGRAM_H
#define _PROGRAM_H

#include <list>
#include "FunctionBlock.h"

#include "StatementVisitor.h"

class Program
{
public:
    Program()
    {
    }
    
    /**
     * Add a FunctionBlock to the Program and take ownership
     * @param FunctionBlock* f
     */
    void AddFunction(FunctionBlock *f)
    {
        _funcs.push_back(f);
    }

    typedef std::list<const FunctionBlock*> ListT;

    ListT GetFunctions() const
    {
        ListT cret(_funcs.begin(), _funcs.end());
        return cret;
    }

    void Accept(StatementVisitor &v) const
    {
        v.Visit(*this);
    }

    ~Program()
    {
        while (!_funcs.empty()) {
            FunctionBlock *f = _funcs.back();
            if (f) {
                delete f;
            }
            _funcs.pop_back();
        }
    }

private:
    std::list<FunctionBlock*> _funcs;
};

#endif
