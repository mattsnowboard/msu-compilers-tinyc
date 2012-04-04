
#include <stack>
#include <cstring>


#include "Program.h"

#include "Add.h"
#include "Subtract.h"
#include "Multiply.h"
#include "Divide.h"
#include "Negate.h"
#include "Value.h"
#include "Variable.h"
#include "Statement.h"
#include "StatementList.h"

#include "SymbolTable.h"
#include "AssignStmt.h"
#include "WriteStmt.h"

#include "AssemblyVisitor.h"
#include "DeclStmt.h"
#include "ExprList.h"
#include "FuncCall.h"
#include "FunctionBlock.h"
#include "ParamDefList.h"
#include "ReturnStatement.h"
#include "Modulus.h"

extern "C" {
#include "functions.h"    
}

Program program;

extern "C" void * CreateNegate(void *expr)
{
    Negate *node = new Negate((Expr *)expr);
    return node;
}

extern "C" void * CreateAdd(void *left, void *right)
{
    Add *node = new Add((Expr *)left, (Expr *)right);
    return node;
}

extern "C" void * CreateSubtract(void *left, void *right)
{
    Subtract *node = new Subtract((Expr *)left, (Expr *)right);
    return node;
}

extern "C" void * CreateDivide(void *left, void *right)
{
    Divide *node = new Divide((Expr *)left, (Expr *)right);
    return node;
}

extern "C" void * CreateMultiply(void *left, void *right)
{
    Multiply *node = new Multiply((Expr *)left, (Expr *)right);
    return node;
}

extern "C" void * CreateNumber(int i)
{
    Value *node = new Value(i);
    return node;
}

extern "C" void * CreateVariable(const char *name)
{
    Variable *node = new Variable(name);
    return node;
}

extern "C" void * CreateStatementList(void *stmt)
{
    StatementList* s = new StatementList;
    s->AddItem((Statement*)stmt);
    return s;
}

extern "C" void * AddStatementToList(void *stmtlist, void *stmt)
{
    StatementList* s = (StatementList*)stmtlist;
    s->AddItem((Statement*)stmt);
    return s;
}

extern "C" void * CreateWriteStmt(void *expr)
{
    WriteStmt* wst = new WriteStmt((Expr*) expr);
    return wst;
}

extern "C" void * CreateAssignStatement(const char *name, void *expr)
{
    AssignStmt* asn = new AssignStmt(name, (Expr*)expr);
    return asn;
}

/**
 * Everything below added on or after Tue, Apr 3, 2012 
 */


extern "C" void * CreateReturn(void *expr)
{
    ReturnStmt * rtns = new ReturnStmt( (Expr*)expr);
    return rtns;
}


extern "C" void * CreateDeclaration(const char *name)
{
    DeclStmt * dcls = new DeclStmt( name);
    return dcls;
}


extern "C" void * CreateParameterList(void *decl)
{
    
  ParamDefList *s = new ParamDefList();
  if (decl != NULL) {
      s->AddItem("int", ((DeclStmt*)decl)->GetName());
  }
  return s;   
}

extern "C" void * AddParameterToList(void * list, void *decl)
{
    ParamDefList *s = (ParamDefList*) list;
    s->AddItem("int", ((DeclStmt*) decl)->GetName());
    return s;
}


extern "C" void * CreateParameter(void *decl, void *name)
{
    return NULL;
}

extern "C" void * AddDeclarationToList(void *type ,void *decl)
{
    return NULL;
}


extern "C" void * CreateExprList( void * expr)
{
    ExprList * theList = new ExprList();
    theList->AddItem((Expr*) expr);
    return theList;    
}

extern "C" void * AddExprToList(void *exprList, void *expr)
{
    ExprList *el = (ExprList *)exprList;
    el->AddItem((Expr*) exprList);
    return el;
}


extern "C" void * CreateFunctionBlock(const char *name,void *paramList)
{
    FunctionBlock * fb = new FunctionBlock(name, (ParamDefList*) paramList);
    return fb;
}

extern "C" void * AddToFunctionBlock(void * fb, void * decls, void * stmtlist, void *rstmt)
{
    FunctionBlock *funcblock = (FunctionBlock*) fb;
    StatementList *sl = (StatementList*) stmtlist;
    sl->AddItem((Statement*) rstmt);
    funcblock->SetDeclarationList((StatementList*) decls);
    funcblock->SetStatementList(sl);
    return funcblock;
}


extern "C" void * CreateFunctionCall(const char *name, void *paramlist)
{
    FuncCall * theCall = new FuncCall(name, (ExprList*) paramlist);
    return theCall;
}

extern "C" void * CreateModulus(void * left, void * right)
{
    Modulus * mod = new Modulus((Expr*) left, (Expr*) right);
    return mod;
}

extern "C" void * CreateInt(int num)
{
    Value * val = new Value( num);
    return val;
}

extern "C" void * AddFunctionToProgram(void * func)
{
    program.AddFunction((FunctionBlock*) func);
    return NULL;
}

