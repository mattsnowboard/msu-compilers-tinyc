#ifndef _PROGRAM_H
#define _PROGRAM_H

#include <list>
#include <stdexcept>
#include <iostream>
#include "FunctionBlock.h"
#include "FunctionTable.h"

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
        // add to function table
        FunctionTable &ft = FunctionTable::GetInstance();
        if (ft.DoesExist(f->GetName(), f->GetParamCount())) {
            // re-declare is an error
            std::cerr << "Function '" << f->GetName() << "' redeclared with "
                      << f->GetParamCount() << " arguments" << std::endl;
            throw std::logic_error("Function redeclared");
        }
        ft.AddDeclaration(f->GetName(), f->GetParamCount());
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
