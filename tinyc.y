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

%token WRITE INT ASSIGN
%token<ival> NUM
%token<sval> VAR

%type<pval> STMT DECL EXPR STMTS UNARY TERM NUMBER OUTPUT EXPRESSION EXPRLIST

%%

PROGRAM : PROGRAM '\n' {}
| PROGRAM '\n' STMT { /*ExecuteStatement($3);*/ }
| STMT { /*ExecuteStatement($1);*/ }
        | {}

STMTS : STMTS '\n'	{ /*$$ = $1;*/ }
| STMTS '\n' STMT  { /*$$ = AddStatementToList($1, $3);*/ }
      | STMT  { /*$$ = CreateStatementList($1);*/ }
      | {}
	 
STMT : DECL  { /*$$ = $1;*/ }
| EXPRESSION { /*$$ = $1;*/ }
| OUTPUT { /*$$ = $1;*/ }

DECL : VAR ASSIGN EXPRESSION  { /*$$ = CreateAssignStatement($1, $3);*/ }

OUTPUT : WRITE EXPRESSION  { /*$$ = CreatePrintStmt($2);*/ }

EXPRLIST : EXPRESSION { /*$$ = CreateNumericalList($1);*/ }
| EXPRLIST ',' EXPRESSION { /*$$ = AddNumericalToList($1, $3);*/ }

EXPRESSION : EXPR  {/*$$ = $1;*/}

EXPR : EXPR '+' TERM  {/*$$ = CreateAdd($1, $3);*/}
EXPR : EXPR '-' TERM {/*$$ = CreateSubtract($1, $3);*/}
EXPR : TERM  {/*$$ = $1;*/}

TERM : TERM '*' UNARY  {/*$$ = CreateMultiply($1, $3);*/}
TERM : TERM '/' UNARY  {/*$$ = CreateDivide($1, $3);*/}
TERM : UNARY  {/*$$ = $1;*/}

UNARY : '-' NUMBER {/*$$ = CreateNegate($2);*/}
UNARY : NUMBER {/*$$ = $1;*/}

NUMBER : '(' EXPRESSION ')'  {/*$$ = $2;*/}
NUMBER : NUM  {/*$$ = CreateDouble($1);*/}
NUMBER : VAR  {/*$$ = CreateVariable($1);*/}

%%
