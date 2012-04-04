#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

/**
 * Create a negate node
 * @param Expr*
 * @return Expr* (Negate)
 */
void * CreateNegate(void *expr);
/**
 * Create Add node
 * @param Expr* left
 * @param Expr* right
 * @return Expr* (Add)
 */
void * CreateAdd(void *left, void *right);
/**
 * Create Subtract node
 * @param Expr* left
 * @param Expr* right
 * @return Expr* (Subtract)
 */
void * CreateSubtract(void *left, void *right);
/**
 * Create Divide node
 * @param Expr* left
 * @param Expr* right
 * @return Expr* (Divide)
 */
void * CreateDivide(void *left, void *right);
/**
 * Create Multiply node
 * @param Expr* left
 * @param Expr* right
 * @return Expr* (Multiply)
 */
void * CreateMultiply(void *left, void *right);
/**
 * Create Value node
 * @param int i
 * @return Expr* (Value)
 */
void * CreateNumber(int i);
/**
 * Create Variable node
 * @param char* name
 * @return Expr* (Variable)
 */
void * CreateVariable(const char *name);
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
void * CreateWriteStmt(void *expr);
/**
 * Create Assignment Statement
 * @param char* name
 * @param Expr*
 * @return Statement* (AssignStmt)
 */
void * CreateAssignStatement(const char *name, void *expr);


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
void * CreateReturn(void *expr);

/**
 * Create a Declaration Statement
 * @param char* name
 * @return *Statement (DeclStatement)
 */
void * CreateDeclaration(const char *name);

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
void * CreateFunctionBlock(const char *name,void *paramList);

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
void * CreateFunctionCall(const char *name, void *paramlist);

/**
 * (ExprList*)
 */
void * CreateParameterList(void *paramlist, void *param);
void * CreateParameter(void *decl, void *name);

/**
 * Create a Modulus function
 * @param (Expr*) left
 * @param (Expr*) right
 * @return Modulus function
 */
void * CreateModulus(void * left, void * right);

/**
 * Create an Integer
 * @param theNumber
 * @return *value
 */
void * CreateInt(int num);
#endif
