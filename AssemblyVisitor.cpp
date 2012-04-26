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

#include "LessThan.h"
#include "GreaterThan.h"
#include "WhileStmt.h"
#include "EqualToStmt.h"
#include <list>

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

    // look up function in table
    FunctionTable &ft = FunctionTable::GetInstance();
    if (!ft.DoesExist(f.GetName(), f.GetParamCount())) {
        // error, undefined function
        std::cerr << "FATAL: Undefined function found: '" << f.GetName()
                  << "', with " << f.GetParamCount() << " arguments, on line "
                  << f.GetLine() << std::endl;
        throw std::logic_error("Undefined function definition");
    }
    std::string label = ft.GetLabel(f.GetName(),  f.GetParamCount());

    // Print prolog
    _out << ".global " << label << std::endl
         << ".type " << label << ", @function" << std::endl
         << label << ":" << std::endl
         << "\tpushl %ebp /* base pointer on stack */" << std::endl
         << "\tmovl  %esp, %ebp /* change base pointer */" << std::endl;
    
    // make space for locals
    int localCount = f.GetVariableSpace();
    if (localCount != 0) {
        _out << "\taddl $" << (localCount) << ", %esp" << std::endl;
    }

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
	_out << "pushl %eax" << std::endl;
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
	_out << "pushl %edx" << std::endl;
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

void AssemblyVisitor::Visit(const GreaterThan &g)
{
    //cmp arg2, arg1 does subtraction and sets flags
    VisitBinary(g, "cmp");
    _out << "" << std::endl;
        /*
    *   I'm going to use this for the if and while loops.  This is
    *   the condition they're going to want to branch on.  Note:
    *   it is the opposite of the compare.  That is, Greater Than
    *   will branch on jl (branch lesser)
    */
    _compare = "jl";

}

void AssemblyVisitor::Visit(const LessThan &l)
{

    //cmp arg2, arg1 does subtraction and sets flags
    VisitBinary(l, "cmp");
    _out << "" << std::endl;

    /*
    *   I'm going to use this for the if and while loops.  This is
    *   the condition they're going to want to branch on.  Note:
    *   it is the opposite of the compare.  That is, Less Than
    *   will branch on jg (branch greater)
    */
    _compare = "jg";
}

void AssemblyVisitor::Visit(const EqualToStmt &e)
{
    VisitBinary(e, "cmp");
    _out << "" << std::endl;

    _compare = "jne";
}

void AssemblyVisitor::Visit(const NotEqualToStmt &e)
{
    VisitBinary(e, "cmp");
    _out << "" << std::endl;

    _compare = "je";
}

void AssemblyVisitor::Visit(const IfStmt & i)
{

    /** Notes
    * jne = branch not equal
    * je = branch equal
    * jl = branch less
    * jg = branch greater
    */

    /*
    *   Plan of Attack
    *   Order in Assembly:
    *
    *
    *   Evaluate the "if"
    *   jne to ending tag
    *
    *   Put the stuff in the "if" down
    *
    *   Put ending tag at the end
    *
    */
    //@TODO figure out how the hell do to this



    const Expr *cond = i.GetCondition();
    const StatementList *block= i.GetStatements();
    StatementList::ListT blockStmts = block->GetStatements();
    int curIfNum = _ifStmtNum++;

   cond->Accept(*this);
   _out << _compare << " if_stmt_num_" << curIfNum << std::endl;

    for (StatementList::ListT::const_iterator it = blockStmts.begin();
         it != blockStmts.end();
         ++it) 
    {(*it)->Accept(*this);}

   _out << "if_stmt_num_" << curIfNum <<":" << std::endl;



}

void AssemblyVisitor::Visit(const WhileStmt& w)
{

    /*
    *   Plan of Attack
    *   Order in Assembly:
    *   Place a while_stmt_num label
    *   evaluate the condition
    *   do a jump on that condition
    *
    *   put the stuff of the while loop here
    *   
    *   jump to while_stmt_num label
    *   put while_stmt_num_end label
    *
    */

    //Set up the variables below
    const Expr *cond = w.GetCondition();
    const StatementList *block= w.GetStatements();
    StatementList::ListT blockStmts = block->GetStatements();

    int curWhileNum = _whileStmtNum++;

    //put a label to begin the while statement, we'll jump here
    //unconditionally at the end of the while loop
    _out << "while_stmt_num_begin" << curWhileNum << ":" << std::endl;

    //place the condition into the code
    cond->Accept(*this);

    //Do the proper comparison to jump to the end of the while statement.
    _out << _compare << " while_stmt_num_end" << curWhileNum << std::endl;

    //place the while statement block into assembly
    for (StatementList::ListT::const_iterator it = blockStmts.begin();
         it != blockStmts.end();
         ++it) 
    {(*it)->Accept(*this);}

    //As we are still in the "block", place an unconditional jump to
    //just above our original condition
    _out << "\tjmp while_stmt_num_begin" << curWhileNum << "/*Unconditional Jump to just above condition*/" << std::endl;
   
    //place a label at the end, we'll jump here when our condition isn't met
   _out << "while_stmt_num_end" << curWhileNum <<":" << std::endl;

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
        std::cerr << "FATAL: Undefined variable: '" << v.GetName()
                  << "', on line " << v.GetLine() << std::endl;
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
    if (!_currTable->DoesExist(a.GetName())) {
        std::cerr << "FATAL: Undefined variable: '" << a.GetName()
                  << "', on line " << a.GetLine() << std::endl;
        throw std::logic_error("Undefined variable");
    }
    int off = _currTable->GetOffset(a.GetName());
    _out << "\tpopl " << off << "(%ebp)" << std::endl;
}

void AssemblyVisitor::Visit(const DecAssignStmt & a)
{
    // pop something and store it in some offset to ebp depending on var
    Expr const *value = a.GetValue();
    value->Accept(*this);
    // after visiting the RHS of the assignment, the answer is on the stack
    if (!_currTable->DoesExist(a.GetName())) {
        std::cerr << "FATAL: Undefined variable: '" << a.GetName()
                  << "', on line " << a.GetLine() << std::endl;
        throw std::logic_error("Undefined variable");
    }
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

    // look up in table
    FunctionTable &ft = FunctionTable::GetInstance();
    if (!ft.DoesExist(f.GetName(), l.size())) {
        // error, undefined function
        std::cerr << "FATAL: Undefined function called: '" << f.GetName()
                  << "', with " << l.size() << " arguments, on line "
                  << f.GetLine() << std::endl;
        throw std::logic_error("Undefined function call");
    }
    std::string label = ft.GetLabel(f.GetName(), l.size());

    for (ExprList::ListT::const_iterator it = l.begin();
         it != l.end();
         ++it) {
        (*it)->Accept(*this);
    }
    // now all params are on stack
    _out << "\tcall " << label << std::endl;
    // BUG FIX, clean up parameters we pushed
    // @todo This hard codes the 4 here
    int paramC = 4 * l.size();
    if (paramC != 0) {
        _out << "\taddl $" << (paramC) << ", %esp" << std::endl;
    }
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
	_out << "\tpushl %eax" << std::endl;
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
	_out << "pushl %eax" << std::endl;
}
