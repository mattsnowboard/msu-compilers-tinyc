#ifndef _FUNCTIONTABLE_H
#define _FUNCTIONTABLE_H

#include <map>
#include <string>

/**
 * Making this a singleton for the time being
 */
class FunctionTable 
{
public:
    // Singleton pattern
    static FunctionTable& GetInstance()
    {
        static FunctionTable instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }

	bool DoesExist(const std::string&, int argc) const;
    std::string GetLabel(const std::string&, int argc) const;
	void AddDeclaration(const std::string&, int argc);

	void Clear();

    ~FunctionTable();

private:
    FunctionTable() {}
    void Cleanup();

    FunctionTable(const FunctionTable &);
    FunctionTable& operator=(const FunctionTable &);
    
    typedef std::map<int, std::string> ArgsToLabelT;
    typedef std::map<std::string, ArgsToLabelT> NameToLabelT;
	std::map<std::string, std::map<int, std::string> > _names;	
};

#endif
