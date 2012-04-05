#ifndef _STATEMENTLIST_H
#define _STATEMENTLIST_H

#include <list>
#include "Statement.h"

/**
 * This class holds a list of statements.
 * It is a helpful wrapper around std::list
 */
class StatementList
{
public:

    StatementList() {}

    void AddItem(Statement* item) { _list.push_back(item); }

    virtual ~StatementList()
    {
        for (std::list<Statement*>::iterator it = _list.begin();
             it != _list.end();
             ++it) {
            delete (*it);
        }
        _list.clear();
    }

    StatementList* Clone()
    {
        StatementList *s = new StatementList;
        // simple copy
        for (std::list<Statement*>::iterator it = _list.begin();
             it != _list.end();
             ++it ) {
            if (*it) {
                s->_list.push_back((*it)->Clone());
            }
        }

        return s;
    }

    typedef std::list<const Statement*> ListT;

    ListT GetStatements() const
    {
        ListT cret(_list.begin(), _list.end());
        return cret;
    }

private:
    std::list<Statement*> _list;
};

#endif
