#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

/**
 * Create a negate node
 * @param Expr*
 * @return Expr* (Negate)
 */
void * CreateNegate(void *expr, int lineno);
/**
 * Create Add node
 * @param Expr* left
 * @param Expr* right
 * @return Expr* (Add)
 */
void * CreateAdd(void *left, void *right, int lineno);
/**
 * Create Subtract node
 * @param Expr* left
 * @param Expr* right
 * @return Expr* (Subtract)
 */
void * CreateSubtract(void *left, void *right, int lineno);
/**
 * Create Divide node
 * @param Expr* left
 * @param Expr* right
 * @return Expr* (Divide)
 */
void * CreateDivide(void *left, void *right, int lineno);
/**
 * Create Multiply node
 * @param Expr* left
 * @param Expr* right
 * @return Expr* (Multiply)
 */
void * CreateMultiply(void *left, void *right, int lineno);
/**
 * Create Value node
 * @param int i
 * @return Expr* (Value)
 */
void * CreateNumber(int i, int lineno);
/**
 * Create Variable node
 * @param char* name
 * @return Expr* (Variable)
 */
void * CreateVariable(const char *name, int lineno);
/**
 * Create a StatementList with a single statement
 * @param Statement* stmt
 * @return StatementList*
 */
void * CreateStatementList(void *stmt);
/**
 * Add a Statement to a StatementList
 * @param StatementList* stmtlist
 * @param Statement* stmt
 * @return StatementList*
 */
void * AddStatementToList(void *stmtlist, void *stmt);

/**
 * Create a Write Statement
 * @param Numerical* expr
 * @return Statement* (WriteStmt)
 */
void * CreateWhileStmt(void *cond, void *stmtlist, int lineno);

/**

 * Create a Write Statement

 * @param Numerical* expr

 * @return Statement* (WriteStmt)

 */
void * CreateWriteStmt(void *expr, int lineno);

/**
 * Create Assignment Statement
 * @param char* name
 * @param Expr*
 * @return Statement* (AssignStmt)
 */
void * CreateAssignStatement(const char *name, void *expr, int lineno);
/**
 * Create Declare and Assignment Statement
 * @param char* name
 * @param Expr*
 * @return Statement* (DecAssignStmt)
 */
void * CreateDecAssignStatement(const char *name, void *expr, int lineno);


/**
 * Functions that I've identified may need to be created.
 * 
 * Everything below added on or after Tue, Apr 3, 2012 
 * 
 */

/**
 * Create a Return Statement
 * @param Exp*
 * #reteturn Expr* (ReturnStatement)
 */
void * CreateReturn(void *expr, int lineno);

/**
 * Create a Declaration Statement
 * @param char* name
 * @return *Statement (DeclStatement)
 */
void * CreateDeclaration(const char *name, int lineno);

/**
 * Add a declaration to a declaration list
 * @param type* type (for memory size)
 * @param DeclStatement* decl
 * @return a list of declarations sharing the same type
 */
void * AddDeclarationToList(void *type ,void *decl);

/**
 * Add and expression to an expression list
 * @param *exprList (to add to)
 * @param *expr
 * @return ListT
 */
void * AddExprToList(void *exprList, void *expr);

/**
 * Create and expression list and add expr to it.
 * @param *expr
 * @return *Exprlist
 */
void * CreateExprList(void *expr);

/**
 * Create a Function Block
 * @param char* name
 * @param ParamDefList* params
 * @return *FunctionBlock
 */
void * CreateFunctionBlock(const char *name,void *paramList, int lineno);

/**
 * Add shtuff to the Function block
 * @param *FunctionBlock
 * @param *StmtList
 * @return *Functionblock
 */
void * AddToFunctionBlock(void * fb, void *stmtlist);

/**
 *
 */
void * CreateFunctionDelcartion();

/**
 *
 */
void * CreateFunction();

/**
 * Create a Function call
 * @param char* name (of function to call)
 * @param ExprList* params
 */
void * CreateFunctionCall(const char *name, void *paramlist, int lineno);

/**
 * @param *decl
 * @return *ParamDefList
 */
void * CreateParameterList(void * decl);

/**
 * Add a declaration to a parameter list
 * @param (ParamDefList*) list
 * @param (DeclStmt*) decl
 * @return *ParamDefList
 */
void * AddParameterToList(void *list, void *decl);

/**
 * Create a Modulus function
 * @param (Expr*) left
 * @param (Expr*) right
 * @return Modulus function
 */
void * CreateModulus(void * left, void * right, int lineno);

/**
 * Create an Integer
 * @param theNumber
 * @return *value
 */
void * CreateInt(int num, int lineno);

void * AddFunctionToProgram(void * func);
#endif
