
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


void * CreateReturn(void *expr)
{
    ReturnStmt * rtns = new ReturnStmt( (Expr*)expr);
    return rtns;
}


void * CreateDeclaration(const char *name)
{
    DeclStmt * dcls = new DeclStmt( name);
    return dcls;
}

//
//@TODO
//How are parameters defined, to be added to the list
//and in the .y file?
void * CreateParameterList(void *paramlist, void *param)
{
    
  ParamDefList *s = (ParamDefList *) paramlist;
  //s->AddItem(param);
  return s;   
}

//
//@TODO 
//Should we create a special parameter class? 
//would that be easier to add to a list?
void * CreateParameter(void *decl, void *name)
{
    
}

void * AddDeclarationToList(void *type ,void *decl)
{
    
}


void * AddExprToList(void *exprList, void *expr)
{
    ExprList *el = (ExprList *)exprList;
    el->AddItem((Expr*) expr);
    return el;
}


void * CreateFunctionBlock(const char *name,void *paramList)
{
    FunctionBlock * fb = new FunctionBlock(name, (ParamDefList*) paramList);
    return fb;
}


void * CreateFunctionCall(const char *name, void *paramlist)
{
    FuncCall * theCall = new FuncCall(name, (ExprList*) paramlist);
    return theCall;
}
