#ifndef _ASSEMBLYVISITOR_H
#define _ASSEMBLYVISITOR_H

#include "StatementVisitor.h"

#include <iostream>

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

class AssemblyVisitor : public StatementVisitor
{
public:
    AssemblyVisitor(std::ostream &out) :
        _out(out)
    {}

    virtual void Visit(const Program &p);
    virtual void Visit(const FunctionBlock &f);

    virtual void Visit(const Add &a);
    virtual void Visit(const Divide &d);
    virtual void Visit(const Multiply &m);
    virtual void Visit(const Negate &n);
    virtual void Visit(const Subtract &s);
    virtual void Visit(const Value &v);
    virtual void Visit(const Variable &v);

    virtual void Visit(const AssignStmt &a);
    virtual void Visit(const WriteStmt &w);
    virtual void Visit(const DeclStmt &d);
    virtual void Visit(const ReturnStmt &r);

private:
	void Visit(const Binary &b);

    std::ostream &_out;
};

#endif
