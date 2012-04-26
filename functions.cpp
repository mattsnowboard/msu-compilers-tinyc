
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
#include "IfStmt.h"
#include "WhileStmt.h"
#include "SymbolTable.h"
#include "AssignStmt.h"
#include "DecAssignStmt.h"
#include "WriteStmt.h"

#include "AssemblyVisitor.h"
#include "DeclStmt.h"
#include "ExprList.h"
#include "FuncCall.h"
#include "FunctionBlock.h"
#include "ParamDefList.h"
#include "ReturnStatement.h"
#include "Modulus.h"
#include <iostream>

extern "C" {
#include "functions.h"    
}

Program program;

extern "C" void * CreateNegate(void *expr, int lineno)
{
    Negate *node = new Negate((Expr *)expr, lineno);
    return node;
}

extern "C" void * CreateAdd(void *left, void *right, int lineno)
{
    Add *node = new Add((Expr *)left, (Expr *)right, lineno);
    return node;
}

extern "C" void * CreateSubtract(void *left, void *right, int lineno)
{
    Subtract *node = new Subtract((Expr *)left, (Expr *)right, lineno);
    return node;
}

extern "C" void * CreateDivide(void *left, void *right, int lineno)
{
    Divide *node = new Divide((Expr *)left, (Expr *)right, lineno);
    return node;
}

extern "C" void * CreateMultiply(void *left, void *right, int lineno)
{
    Multiply *node = new Multiply((Expr *)left, (Expr *)right, lineno);
    return node;
}

extern "C" void * CreateNumber(int i, int lineno)
{
    Value *node = new Value(i, lineno);
    return node;
}

extern "C" void * CreateVariable(const char *name, int lineno)
{
    Variable *node = new Variable(name, lineno);
    return node;
}

extern "C" void * CreateStatementList(void *stmt)
{
    StatementList* s = new StatementList;
    if (stmt != NULL) {
        s->AddItem((Statement*)stmt);
    }
    return s;
}

extern "C" void * AddStatementToList(void *stmtlist, void *stmt)
{
    StatementList* s = (StatementList*)stmtlist;
    s->AddItem((Statement*)stmt);
    return s;
}


extern "C" void * CreateWriteStmt(void *expr, int lineno)
{
    WriteStmt* wst = new WriteStmt((Expr*) expr, lineno);
    return wst;
}

extern "C" void * CreateAssignStatement(const char *name, void *expr, int lineno)
{
    AssignStmt* asn = new AssignStmt(name, (Expr*)expr, lineno);
    return asn;
}

extern "C" void * CreateDecAssignStatement(const char *name, void *expr, int lineno)
{
    DecAssignStmt* asn = new DecAssignStmt(name, (Expr*)expr, lineno);
    return asn;
}

/**
 * Everything below added on or after Tue, Apr 3, 2012 
 */


extern "C" void * CreateIfStmt(void *cond, void *stmtlist, int lineno)
{
    IfStmt* ifst = new IfStmt((Expr*)cond, (StatementList*) stmtlist, lineno);
    return ifst;
}

extern "C" void * CreateWhileStmt(void *cond, void *stmtlist, int lineno)
{
    WhileStmt* wst = new WhileStmt((Expr*)cond, (StatementList*)stmtlist, lineno);
    return wst;
}

extern "C" void * CreateReturn(void *expr, int lineno)
{
    ReturnStmt * rtns = new ReturnStmt( (Expr*)expr, lineno);
    return rtns;
}


extern "C" void * CreateDeclaration(const char *name, int lineno)
{
    DeclStmt * dcls = new DeclStmt( name, lineno);
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

extern "C" void * CreateExprList( void * expr)
{
    ExprList * theList = new ExprList();
    if (expr != NULL) {
        theList->AddItem((Expr*) expr);
    }
    return theList;    
}

extern "C" void * AddExprToList(void *exprList, void *expr)
{
    ExprList *el = (ExprList *)exprList;
    el->AddItem((Expr*) expr);
    return el;
}


extern "C" void * CreateFunctionBlock(const char *name,void *paramList, int lineno)
{
    FunctionBlock * fb = new FunctionBlock(name, (ParamDefList*) paramList, lineno);
    return fb;
}

extern "C" void * AddToFunctionBlock(void * fb, void * stmtlist)
{
    FunctionBlock *funcblock = (FunctionBlock*) fb;
    StatementList *sl = (StatementList*) stmtlist;
    funcblock->SetStatementList(sl);
    return funcblock;
}


extern "C" void * CreateFunctionCall(const char *name, void *paramlist, int lineno)
{
    FuncCall * theCall = new FuncCall(name, (ExprList*) paramlist, lineno);
    return theCall;
}

extern "C" void * CreateModulus(void * left, void * right, int lineno)
{
    Modulus * mod = new Modulus((Expr*) left, (Expr*) right, lineno);
    return mod;
}

extern "C" void * CreateInt(int num, int lineno)
{
    Value * val = new Value(num, lineno);
    return val;
}

extern "C" void * AddFunctionToProgram(void * func)
{
    program.AddFunction((FunctionBlock*) func);
    return NULL;
}

extern "C" void * CreateGreaterThan(void * left, void * right, int lineno)
{
    GreaterThan * g = new GreaterThan((Expr*)left,(Expr*) right, lineno);
    return g;
}

extern "C" void * CreateLessThan(void * left, void* right, int lineno)
{
    LessThan * l = new LessThan((Expr*) left, (Expr*) right, lineno);
    return l;
}