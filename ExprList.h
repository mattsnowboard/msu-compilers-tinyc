#ifndef _EXPRLIST_H
#define _EXPRLIST_H

#include <list>
#include "Expr.h"

class ExprList
{
public:

    ExprList() {}

    void AddItem(Expr* item) { _list.push_back(item); }

    virtual ~ExprList()
    {
        for (std::list<Expr*>::iterator it = _list.begin();
             it != _list.end();
             ++it) {
            delete (*it);
        }
        _list.clear();
    }

    void Execute()
    {
        for (std::list<Expr*>::iterator it = _list.begin();
             it != _list.end();
             ++it) {
            (*it)->Execute();
        }
    }

    ExprList* Clone()
    {
        ExprList *s = new ExprList;
        // simple copy
        for (std::list<Expr*>::iterator it = _list.begin();
             it != _list.end();
             ++it ) {
            if (*it) {
                s->_list.push_back((*it)->Clone());
            }
        }

        return s;
    }

    typedef std::list<const Expr*> ListT;

    ListT GetExprs() const
    {
        ListT cret(_list.begin(), _list.end());
        return cret;
    }

private:
    std::list<Expr*> _list;
};

#endif
