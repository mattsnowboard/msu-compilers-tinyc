
#include "SymbolTable.h"
//
#include "Expr.h"
#include <map>
#include <string>
#include "Expr.h"

void SymbolTable::AddVar(std::string Var, Expr* exprssn )
{
    std::pair<std::map<std::string, Expr*>::iterator, bool> ret
        = _VarMap.insert(std::make_pair(Var, exprssn));
    if (ret.second == false) {
        // we are overwriting, that is fine as long as we clean it up
        Expr *cleanMe = _VarMap[Var];
        _VarMap[Var] = exprssn;
        delete cleanMe;
    }

}

Expr* SymbolTable::GetVal( std::string Var )
{
    return _VarMap[Var];
}

bool SymbolTable::DoesExist( std::string Var )
{
    return (_VarMap.find(Var) != _VarMap.end());
}

void SymbolTable::Clear()
{
    Cleanup();
}

SymbolTable::~SymbolTable()
{
    Cleanup();
}

void SymbolTable::Cleanup()
{
    for (std::map<std::string, Expr*>::iterator it = _VarMap.begin();
         it != _VarMap.end();
         ++it) {
        if (it->second != NULL) {
            delete it->second;
        }
    }
    _VarMap.clear();
}
