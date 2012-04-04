#ifndef _EXPR_H
#define _EXPR_H

#include <iostream>
#include <stdexcept>
#include "Statement.h"

class Expr : public Statement
{
public:
    explicit Expr(int v = 0) : _value(v)
    {}
    virtual ~Expr() {}

    virtual int Get() const { return _value; }

    virtual Expr* Clone() = 0;

    /**
     * Print an arbitrary expression to a stream
     */
    friend std::ostream& operator<<(std::ostream &out, const Expr& e)
    {
        e.Print(out);
        return out;
    }
protected:
    int _value;

private:

    virtual void Print(std::ostream &out) const
    {
        out << Get();
    }
};

#endif
