#ifndef _SYMBOLTABLE_H
#define _SYMBOLTABLE_H

#include <map>
#include <string>

class SymbolTable 
{
public:
    SymbolTable() : _parent(NULL), _off(0) {}

	bool DoesExist(const std::string&) const;
    int GetOffset(const std::string&) const;
	void AddVar(const std::string&, int offset);

	void Clear();

    void SetParent(SymbolTable *parent)
    {
        _parent = parent;
    }

    int SetOffset(int off)
    {
        _off = off;
    }

    int GetOffset() const
    {
        return _off;
    }

    ~SymbolTable();

private:
    void Cleanup();

    SymbolTable(const SymbolTable &);
    SymbolTable& operator=(const SymbolTable &);

	std::map<std::string, int> _VarMap;	

    SymbolTable *_parent;
    // each table may have an offset for nesting
    int _off
};

#endif
