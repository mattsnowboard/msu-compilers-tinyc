#ifndef _EXPR_H
#define _EXPR_H

#include <iostream>
#include <stdexcept>
#include "Statement.h"

class Expr : public Statement
{
public:
    Expr(int v = 0) : _value(v)
    {}
    virtual ~Expr() {}

    virtual void Execute()
    {
        // could remove this probably
        Evaluate();
        std::cout << "Answer: " << *this << std::endl;
    }

    virtual void Evaluate() = 0;

    virtual Expr* Clone() = 0;

    virtual int Get() const { return _value; }

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
