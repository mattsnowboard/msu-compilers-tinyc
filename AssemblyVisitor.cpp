#include "AssemblyVisitor.h"

#include <stdexcept>

#include "Program.h"
#include "FunctionBlock.h"

#include "Binary.h"
#include "Unary.h"
#include "Add.h"
#include "Subtract.h"
#include "Multiply.h"
#include "Negate.h"

void AssemblyVisitor::Visit(const Program & p)
{
    // Visit each FunctionBlock in Program
}

void AssemblyVisitor::Visit(const FunctionBlock & f)
{
    // get the current SymbolTable and store it on a stack of symbol tables?
    // Print prolog
    _out << ".global " << f.GetName() << std::endl
         << ".type " << f.GetName() << ", @function" << std::endl
         << f.GetName() << ":" << std::endl
         << "\tpushl %ebp /* base pointer on stack */" << std::endl
         << "\tmovl  %esp, %ebp /* change base pointer */" << std::endl;
    
    /* .global #{FunctionName}
     * .type #{FunctionName}, @function
     * #{FunctionName}:
     *         pushl %ebp
     *         movl $esp, %ebp
  	 */
    // ? then visit all statements
    // Print epilog
    _out << "\tmovl %ebp, %esp" << std::endl
         << "\tpopl %ebp /* restore base pointer */" << std::endl
         << "\tret" << std::endl;
    /*
     *         movl %ebp, %esp
     *         popl %ebp
     *
     *         ret
     */
}

void AssemblyVisitor::Visit(const Add & a)
{
    VisitBinary(a, "addl");
}

void AssemblyVisitor::Visit(const Divide & d)
{
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
}

void AssemblyVisitor::Visit(const Variable & v)
{
    // Look up in current symbol table, push some offset of ebp on stack
}

void AssemblyVisitor::Visit(const AssignStmt & a)
{
    // pop something and store it in some offset to ebp depending on var
}

void AssemblyVisitor::Visit(const WriteStmt & w)
{
    // may need to evaluate the RHS, then just output "write ???"
}

void AssemblyVisitor::Visit(const DeclStmt & d)
{
    // allocate space on stack for local, put in current symbol table?
}

void AssemblyVisitor::Visit(const ReturnStmt & r)
{
    // return statement means writing something to eax
}

void AssemblyVisitor::Visit(const FuncCall & f)
{

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
	_out << "push %eax" << std::endl;
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
