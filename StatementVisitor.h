#ifndef _STATEMENTVISITOR_H
#define _STATEMENTVISITOR_H

class Program;
class FunctionBlock;

class Add;
class Divide;
class Multiply;
class Negate;
class Subtract;
class Value;
class Variable;
class FuncCall;

class WriteStmt;
class AssignStmt;
class DeclStmt;
class ReturnStmt;

class StatementVisitor
{
public:
    virtual void Visit(const Program &p) = 0;
    virtual void Visit(const FunctionBlock &f) = 0;

    virtual void Visit(const Add &a) = 0;
    virtual void Visit(const Divide &d) = 0;
    virtual void Visit(const Multiply &m) = 0;
    virtual void Visit(const Negate &n) = 0;
    virtual void Visit(const Subtract &s) = 0;
    virtual void Visit(const Value &v) = 0;
    virtual void Visit(const Variable &v) = 0;

    virtual void Visit(const AssignStmt &a) = 0;
    virtual void Visit(const WriteStmt &w) = 0;
    virtual void Visit(const DeclStmt &d) = 0;
    virtual void Visit(const ReturnStmt &r) = 0;
};

#endif
