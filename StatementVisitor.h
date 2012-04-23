#ifndef _STATEMENTVISITOR_H
#define _STATEMENTVISITOR_H

class Program;
class FunctionBlock;

class Add;
class Divide;
class Multiply;
class Negate;
class Subtract;
class Modulus;
class Value;
class Variable;
class FuncCall;

class WriteStmt;
class AssignStmt;
class DecAssignStmt;
class DeclStmt;
class ReturnStmt;

class LessThan;
class GreaterThan;
class IfStmt;

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
    virtual void Visit(const Modulus &m) = 0;
    virtual void Visit(const Value &v) = 0;
    virtual void Visit(const Variable &v) = 0;

    virtual void Visit(const AssignStmt &a) = 0;
    virtual void Visit(const DecAssignStmt &a) = 0;
    virtual void Visit(const WriteStmt &w) = 0;
    virtual void Visit(const DeclStmt &d) = 0;
    virtual void Visit(const ReturnStmt &r) = 0;
    
    virtual void Visit(const FuncCall &f) = 0;

    virtual void Visit(const LessThan &l) = 0;
    virtual void Visit(const GreaterThan &g) = 0;

    virtual void Visit(const IfStmt &i) = 0;
};

#endif
