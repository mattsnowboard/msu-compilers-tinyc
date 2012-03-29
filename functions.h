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

#endif
