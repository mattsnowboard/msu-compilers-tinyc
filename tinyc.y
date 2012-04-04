%{
/*
 * Expression evaluator
 */
#include "functions.h"
#include "stdio.h"

//#define YYSTYPE int

int  lineno = 1; /* number of current source line */

%}

%union {
    void *pval;		
    int ival;		
    char *sval;		
}

%token WRITE INT ASSIGN DELIM RETURN 
%token<ival> NUM
%token<sval> VAR

%type<pval> PROGRAM FUNCDEF FUNCDECL PARAMDEFLIST PARAMCALLLIST STMTLIST STMT DECLLIST ASSIGNMENT DECL OUTPUT RETURNSTMT EXPRESSION FUNCCALL EXPR TERM UNARY NUMBER TYPE

%%

PROGRAM : PROGRAM FUNCDEF { $$ = AddFunctionToProgram($2);}
        | FUNCDEF { $$ = AddFunctionToProgram($1);}

FUNCDEF : FUNCDECL '{' DECLLIST STMTLIST RETURNSTMT '}' { $$ = AddToFunctionBlock($1, $3, $4, $5); }

FUNCDECL : TYPE VAR '(' PARAMDEFLIST ')' {  $$ = CreateFunctionBlock($2, $4); }

PARAMDEFLIST : DECL { CreateParameterList($1); }
             |PARAMDEFLIST ',' DECL { $$ = AddParameterToList($1, $3);}
             | { /* empty param list */ }
PARAMCALLLIST : EXPR { $$ = CreateExprList($1);}
              |PARAMCALLLIST ',' EXPR { $$ = AddExprToList($1, $3); }
              | { /* empty param list */ }

STMTLIST : STMT DELIM { $$ = CreateStatementList($1);}
         | STMTLIST STMT DELIM { $$ = AddStatementToList($1, $2); }
         | STMTLIST DELIM {$$ = $1; }

STMT : ASSIGNMENT  { $$ = $1; }
     | OUTPUT { $$ = $1; }

DECLLIST : DECL DELIM { $$ = CreateStatementList($1); }
         | DECLLIST DECL DELIM { $$ = AddStatementToList($1, $2); }
         | DECLLIST DELIM { $$ = $1;}

RETURNSTMT : RETURN EXPRESSION DELIM { $$ = CreateReturn($2); }
           | { /* no return */}

ASSIGNMENT : VAR ASSIGN EXPRESSION  { $$ = CreateAssignStatement($1, $3); }
DECL : TYPE VAR { $$ = CreateDeclaration($2); }
OUTPUT : WRITE EXPRESSION  { $$ = CreateWriteStmt($2); }

EXPRESSION : EXPR  {$$ = $1;}
           | FUNCCALL {  $$ = $1; }

FUNCCALL : VAR '(' PARAMCALLLIST ')' { $$ = CreateFunctionCall($1, $3); }

EXPR : EXPR '+' TERM  {$$ = CreateAdd($1, $3);}
EXPR : EXPR '-' TERM {$$ = CreateSubtract($1, $3);}
EXPR : TERM  {$$ = $1;}

TERM : TERM '*' UNARY  {$$ = CreateMultiply($1, $3);}
TERM : TERM '/' UNARY  {$$ = CreateDivide($1, $3);}
TERM : UNARY  {$$ = $1;}
TERM : TERM '%' UNARY {/* create mod */ }

UNARY : '-' NUMBER {$$ = CreateNegate($2);}
UNARY : NUMBER {$$ = $1;}

NUMBER : '(' EXPRESSION ')'  {$$ = $2;}
NUMBER : NUM  {$$ = CreateInt($1);}
NUMBER : VAR  {$$ = CreateVariable($1);}

TYPE : INT { /* do something? ignore since everything is an int? */ }

%%
