#include "AssemblyVisitor.h"

#include <stdexcept>

#include "Program.h"
#include "FunctionBlock.h"

#include "Binary.h"
#include "Unary.h"
#include "Add.h"
#include "Subtract.h"
#include "Multiply.h"
#include "Divide.h"
#include "Modulus.h"
#include "Negate.h"
#include "FuncCall.h"

#include "Variable.h"
#include "Value.h"

#include "AssignStmt.h"
#include "WriteStmt.h"
#include "ReturnStatement.h"

void AssemblyVisitor::Visit(const Program & p)
{
    _out << ".section .text" << std::endl
         << ".globl _start" << std::endl << std::endl
         << "_start:" << std::endl
         << "\tcall main" << std::endl
         << "\tjmp exit" << std::endl
         << ".include \"./x86asm/print_int.s\"" << std::endl;

    // Visit each FunctionBlock in Program
    Program::ListT funcs = p.GetFunctions();
    for (Program::ListT::const_iterator it = funcs.begin();
         it != funcs.end();
         ++it) {
        if (*it) {
            (*it)->Accept(*this);
        }
    }

    _out << ".type exit, @function" << std::endl
         << "exit:" << std::endl
         << "\tmovl $0, %ebx" << std::endl
         << "\tmovl $1, %eax" << std::endl
         << "\tint $0x80" << std::endl;
}

void AssemblyVisitor::Visit(const FunctionBlock & f)
{
    // get the current SymbolTable and store it on a stack of symbol tables?
    _currTable = f.GetSymbolTable();
    // Print prolog
    _out << ".global " << f.GetName() << std::endl
         << ".type " << f.GetName() << ", @function" << std::endl
         << f.GetName() << ":" << std::endl
         << "\tpushl %ebp /* base pointer on stack */" << std::endl
         << "\tmovl  %esp, %ebp /* change base pointer */" << std::endl;
    
    // make space for locals
    StatementList const *decls = f.GetDeclarations();
    int localCount = decls->GetStatements().size();
    _out << "\taddl $-" << (localCount * 4) << ", %esp" << std::endl;

    // visit statements
    StatementList const *stmts = f.GetStatements();
    StatementList::ListT slist = stmts->GetStatements();
    for (StatementList::ListT::const_iterator it = slist.begin();
         it != slist.end();
         ++it) {
        (*it)->Accept(*this);
    }
    
    // Print epilog
    _out << "\tmovl %ebp, %esp" << std::endl
         << "\tpopl %ebp /* restore base pointer */" << std::endl
         << "\tret" << std::endl;
}

void AssemblyVisitor::Visit(const Add & a)
{
    VisitBinary(a, "addl");
}

void AssemblyVisitor::Visit(const Divide & d)
{
    // I'm too lazy to make VisitBinary more generic...
    // get the two children results
    const Expr *l = d.GetLeft();
    const Expr *r = d.GetRight();
    if (!l || !r) {
        throw std::runtime_error("Could not evaluate binary expression");
    }
    l->Accept(*this);
    r->Accept(*this);
    // grab results into registers
	_out << "\tpopl %ebx" << std::endl; // right
	_out << "\tpopl %eax" << std::endl; // left
    // need to divide %eax by %ebx
    _out << "\tcltd" << std::endl
         << "\tidiv %ebx" << std::endl;
    // push result
	_out << "push %eax" << std::endl;
}

void AssemblyVisitor::Visit(const Modulus & d)
{
    // same as divide but return remainder
    // get the two children results
    const Expr *l = d.GetLeft();
    const Expr *r = d.GetRight();
    if (!l || !r) {
        throw std::runtime_error("Could not evaluate binary expression");
    }
    l->Accept(*this);
    r->Accept(*this);
    // grab results into registers
	_out << "\tpopl %ebx" << std::endl; // right
	_out << "\tpopl %eax" << std::endl; // left
    // need to divide %eax by %ebx
    _out << "\tcltd" << std::endl
         << "\tidiv %ebx" << std::endl;
    // push result (remainder)
	_out << "push %edx" << std::endl;
}

void AssemblyVisitor::Visit(const Multiply & m)
{
    VisitBinary(m, "imull");
}

void AssemblyVisitor::Visit(const Negate & n)
{
    VisitUnary(n, "negl");
}

void AssemblyVisitor::Visit(const Subtract & s)
{
    VisitBinary(s, "subl");
}

void AssemblyVisitor::Visit(const Value & v)
{
    // push on stack?
    _out << "\tpushl $" << v.Get() << std::endl;
}

void AssemblyVisitor::Visit(const Variable & v)
{
    // Look up in current symbol table, push some offset of ebp on stack
    if (!_currTable->DoesExist(v.GetName())) {
        std::cerr << "Undefined variable: " << v.GetName()
                  << ", on line " << v.GetLine() << std::endl;
        throw std::logic_error("Undefined variable");
    }
    int off = _currTable->GetOffset(v.GetName());
    _out << "\tpushl " << off << "(%ebp)" << std::endl;
}

void AssemblyVisitor::Visit(const AssignStmt & a)
{
    // pop something and store it in some offset to ebp depending on var
    Expr const *value = a.GetValue();
    value->Accept(*this);
    // after visiting the RHS of the assignment, the answer is on the stack
    int off = _currTable->GetOffset(a.GetName());
    _out << "\tpopl " << off << "(%ebp)" << std::endl;
}

void AssemblyVisitor::Visit(const WriteStmt & w)
{
    // may need to evaluate the RHS, then just output "write ???"
    Expr const *value = w.GetExpr();
    value->Accept(*this);
    // this will evaluate the expression with the result on the stack
    _out << "\tcall print_int" << std::endl;
}

void AssemblyVisitor::Visit(const DeclStmt & d)
{
    // allocate space on stack for local, put in current symbol table?
    // this is already done, maybe we don't need a visitor here?
}

void AssemblyVisitor::Visit(const ReturnStmt & r)
{
    // return statement means writing something to eax
    Expr const *val = r.GetExpr();
    val->Accept(*this);
    _out << "\tpopl %eax" << std::endl;
}

void AssemblyVisitor::Visit(const FuncCall & f)
{
    // visit the parameters (which will push them, then call the function
    ExprList const* params = f.GetParams();
    ExprList::ListT l = params->GetExprs();
    for (ExprList::ListT::const_iterator it = l.begin();
         it != l.end();
         ++it) {
        (*it)->Accept(*this);
    }
    // now all params are on stack
    _out << "\tcall " << f.GetName() << std::endl;
    // this is an expression so take the result from %eax and push it
    _out << "\tpushl %eax" << std::endl;
}

void AssemblyVisitor::VisitBinary(const Binary &b, const std::string &op)
{
    // get the two children results
    const Expr *l = b.GetLeft();
    const Expr *r = b.GetRight();
    if (!l || !r) {
        // WTF, exception
        throw std::runtime_error("Could not evaluate binary expression");
    }
    l->Accept(*this);
    r->Accept(*this);
    // grab results into registers
	_out << "\tpopl %edx" << std::endl; // right
	_out << "\tpopl %eax" << std::endl; // left
    // do op (example addl %edx, %eax // will do %eax = %eax + %edx)
    _out << "\t" << op << " %edx, %eax" << std::endl;
    // push result
	_out << "\tpush %eax" << std::endl;
}

void AssemblyVisitor::VisitUnary(const Unary &u, const std::string &op)
{
    // get the child result
    const Expr *c = u.GetChild();
    if (!c) {
        // WTF, exception
        throw std::runtime_error("Could not evaluate unary expression");
    }
    c->Accept(*this);
    // grab result into register
	_out << "\tpopl %eax" << std::endl;
    // do op (example negl %eax // will do %eax = - %eax)
    _out << "\t" << op << " %eax" << std::endl;
    // push result
	_out << "push %eax" << std::endl;
}
