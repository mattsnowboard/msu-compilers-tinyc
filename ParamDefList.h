#ifndef _PARAMDEFLIST_H
#define _PARAMDEFLIST_H

#include <list>
#include "Expr.h"

class ParamDefList
{
public:

    ParamDefList() {}

    void AddItem(std::string type, std::string name) { _list.push_back(name); }

    virtual ~ParamDefList()
    {
    }

    ParamDefList* Clone()
    {
        ParamDefList *p = new ParamDefList;
        // simple copy
        for (std::list<std::string>::iterator it = _list.begin();
             it != _list.end();
             ++it ) {
            p->_list.push_back(*it);
        }

        return p;
    }

    typedef std::list<std::string> ListT;

    ListT GetParams() const
    {
        return _list;
    }

private:
    std::list<std::string> _list;
};

#endif
