#include "AssemblyVisitor.h"

#include "Program.h"
#include "FunctionBlock.h"

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
    // use a binary helper for visit left, visit right, pop, pop, add, push
}

void AssemblyVisitor::Visit(const Divide & d)
{
}

void AssemblyVisitor::Visit(const Multiply & m)
{
}

void AssemblyVisitor::Visit(const Negate & n)
{
}

void AssemblyVisitor::Visit(const Subtract & s)
{
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
