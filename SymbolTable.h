#ifndef _SYMBOLTABLE_H
#define _SYMBOLTABLE_H

#include <map>
#include <string>

class SymbolTable 
{
public:
    SymbolTable() : _parent(NULL) {}

	bool DoesExist(const std::string&) const;
    int GetOffset(const std::string&) const;
	void AddVar(const std::string&, int offset);

	void Clear();

    void SetParent(const SymbolTable *parent)
    {
        _parent = parent;
    }

    ~SymbolTable();

private:
    void Cleanup();

    SymbolTable(const SymbolTable &);
    SymbolTable& operator=(const SymbolTable &);

	std::map<std::string, int> _VarMap;	

    const SymbolTable *_parent;
};

#endif
