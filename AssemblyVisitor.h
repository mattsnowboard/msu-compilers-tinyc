#ifndef _ASSEMBLYVISITOR_H
#define _ASSEMBLYVISITOR_H

#include "StatementVisitor.h"

#include <iostream>

class Program;
class FunctionBlock;
class SymbolTable;

class Unary;
class Binary;
class Add;
class Divide;
class Multiply;
class Modulus;
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
    virtual void Visit(const Modulus &s);
    virtual void Visit(const Value &v);
    virtual void Visit(const Variable &v);

    virtual void Visit(const AssignStmt &a);
    virtual void Visit(const WriteStmt &w);
    virtual void Visit(const DeclStmt &d);
    virtual void Visit(const ReturnStmt &r);
    
    virtual void Visit(const FuncCall &f);

private:
	void VisitBinary(const Binary &b, const std::string &op);
	void VisitUnary(const Unary &b, const std::string &op);

    std::ostream &_out;
    SymbolTable const *_currTable;
};

#endif
