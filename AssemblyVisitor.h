#ifndef _ASSEMBLYVISITOR_H
#define _ASSEMBLYVISITOR_H

#include "StatementVisitor.h"
#include <string>

#include <iostream>

class Program;
class FunctionBlock;
class SymbolTable;
class Block;

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

class LessThan;
class GreaterThan;
class IfStmt;
class WhileStmt;
class EqualToStmt;
class NotEqualToStmt;

class AssemblyVisitor : public StatementVisitor
{
public:
    AssemblyVisitor(std::ostream &out) :
        _out(out)
    {
        _whileStmtNum = 0;
        _ifStmtNum = 0;
        _compare = "";
    }

    virtual void Visit(const Program &p);
    virtual void Visit(const FunctionBlock &f);
    virtual void Visit(const Block &b);

    virtual void Visit(const Add &a);
    virtual void Visit(const Divide &d);
    virtual void Visit(const Multiply &m);
    virtual void Visit(const Negate &n);
    virtual void Visit(const Subtract &s);
    virtual void Visit(const Modulus &s);
    virtual void Visit(const Value &v);
    virtual void Visit(const Variable &v);

    virtual void Visit(const AssignStmt &a);
    virtual void Visit(const DecAssignStmt &a);
    virtual void Visit(const WriteStmt &w);
    virtual void Visit(const DeclStmt &d);
    virtual void Visit(const ReturnStmt &r);
    
    virtual void Visit(const FuncCall &f);

    virtual void Visit(const LessThan &l);
    virtual void Visit(const GreaterThan &g);

    virtual void Visit(const IfStmt &i);
    virtual void Visit(const WhileStmt &w);

    virtual void Visit(const EqualToStmt &e);
    virtual void Visit(const NotEqualToStmt &e);

private:
	void VisitBinary(const Binary &b, const std::string &op);
	void VisitUnary(const Unary &b, const std::string &op);
    
    std::string _compare;

    int _whileStmtNum;
    int _ifStmtNum;

    std::ostream &_out;
    SymbolTable const *_currTable;
};

#endif
