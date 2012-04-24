#include "FunctionTable.h"
#include <sstream>
#include <stdexcept>

bool FunctionTable::DoesExist(const std::string &name, int argc) const
{
    NameToLabelT::const_iterator nameFound = _names.find(name);
    if (nameFound != _names.end()) {
        // special case, main function only declared once
        if (name == "main") {
            return true;
        }
        ArgsToLabelT::const_iterator argcFound = (nameFound->second).find(argc);
        if (argcFound != (nameFound->second).end()) {
            return true;
        }
    }
    return false;
}

std::string FunctionTable::GetLabel(const std::string &name, int argc) const
{
    NameToLabelT::const_iterator nameFound = _names.find(name);
    if (nameFound != _names.end()) {
        ArgsToLabelT::const_iterator argcFound = (nameFound->second).find(argc);
        if (argcFound != (nameFound->second).end()) {
            return argcFound->second;
        }
    }
    // ERROR!
    return "";
}

void FunctionTable::AddDeclaration(const std::string &name, int argc)
{
    bool isMain = (name == "main");

    std::ostringstream label;
    label << name << "__" << argc;

    NameToLabelT::iterator nameFound = _names.find(name);
    if (nameFound == _names.end()) {
        // first function of this name
        std::pair<NameToLabelT::iterator, bool> ret
            = _names.insert(std::make_pair(name, ArgsToLabelT()));
        nameFound = ret.first;
    } else if (isMain) {
        throw std::logic_error("Function main redeclared");
    }

    // special case for main
    if (isMain) {
        std::pair<ArgsToLabelT::iterator, bool> ret
            = nameFound->second.insert(std::make_pair(argc, name));
    } else {
        std::pair<ArgsToLabelT::iterator, bool> ret
            = nameFound->second.insert(std::make_pair(argc, label.str()));
        if (ret.second == false) {
            // can't redeclare
            throw std::logic_error("Function redeclared");
        }
    }
}

void FunctionTable::Clear()
{
    Cleanup();
}

FunctionTable::~FunctionTable()
{
    Cleanup();
}

void FunctionTable::Cleanup()
{
    _names.clear();
}

