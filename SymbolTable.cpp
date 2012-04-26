
#include "SymbolTable.h"

#include "Expr.h"
#include <map>
#include <string>
#include "Expr.h"

bool SymbolTable::DoesExist(const std::string &name) const
{
    bool exists = (_VarMap.find(name) != _VarMap.end());
    if (!exists && _parent) {
        // try going up the tree
        exists = _parent->DoesExist(name);
    }
    return exists;
}

int SymbolTable::GetOffset(const std::string &name) const
{
    std::map<std::string, int>::const_iterator found = _VarMap.find(name);
    if (found == _VarMap.end()) {
        // must be in a parent
        return _parent->GetOffset(name);
    }
    return (found->second) + _off;
}

void SymbolTable::AddVar(const std::string &name, int offset)
{
    std::pair<std::map<std::string, int>::iterator, bool> ret
        = _VarMap.insert(std::make_pair(name, offset));
    if (ret.second == false) {
        // we are overwriting, not sure if that matters?
    }
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
    _VarMap.clear();
}








