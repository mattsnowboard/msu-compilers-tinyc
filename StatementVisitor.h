#ifndef _STATEMENTVISITOR_H
#define _STATEMENTVISITOR_H

class Program;

class Add;
class AssignStmt;
class Divide;
class Multiply;
class Negate;
class WriteStmt;
class Subtract;
class Value;
class Variable;

class StatementVisitor
{
public:
    virtual void Visit(const Program &p) = 0;
    virtual void Visit(const Add &a) = 0;
    virtual void Visit(const AssignStmt &a) = 0;
    virtual void Visit(const Divide &d) = 0;
    virtual void Visit(const Multiply &m) = 0;
    virtual void Visit(const Negate &n) = 0;
    virtual void Visit(const Subtract &s) = 0;
    virtual void Visit(const Value &v) = 0;
    virtual void Visit(const Variable &v) = 0;
    virtual void Visit(const WriteStmt &w) = 0;
};

#endif
