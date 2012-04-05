#ifndef _Statements_H
#define _Statements_H

#include <iostream>
#include <stdexcept>

#include "StatementVisitor.h"

class Statement
{
public:
    Statement() {}

    virtual ~Statement() {}

    // Allow copying a Statement tree
    virtual Statement* Clone() = 0;

    // Support the Visitor Pattern
    virtual void Accept(StatementVisitor &v) const = 0;

private:
    Statement(const Statement &s);
    Statement& operator=(const Statement &s);
};

#endif
