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

%type<pval> PROGRAM FUNCDEF FUNCBODY FUNCDECL PARAMDEFLIST PARAMCALLLIST STMTLIST STMT DECLLIST ASSIGNMENT DECL OUTPUT RETURNSTMT EXPRESSION FUNCCALL EXPR TERM UNARY NUMBER TYPE

%%

PROGRAM : PROGRAM FUNCDEF { /* Add function definition to program */}
        | FUNCDEF { /* Create program, add function def to it*/}

FUNCDEF : FUNCDECL '{' FUNCBODY '}' { /* Add list of statements to func */ }

FUNCBODY : DECLLIST STMTLIST RETURNSTMT { /* add these to statement list */ }

FUNCDECL : TYPE VAR '(' PARAMDEFLIST ')' { /* create function def */ /* $$ = CreateFunctionBlock($2, $3) */}

PARAMDEFLIST : PARAMDEFLIST ',' DECL { /* add decl to list */ }
             | DECL { /* create param list, add decl */ }
             | { /* empty param list */ }
PARAMCALLLIST : PARAMCALLLIST ',' EXPR { /* add expression to list */ }
              | EXPR { /* create list, add expression */ }
              | { /* empty param list */ }

STMTLIST : STMT DELIM { /* create statement list, add statement */}
         | STMTLIST STMT DELIM { /* add new statement to list */ }
         | STMTLIST DELIM {}

STMT : ASSIGNMENT  { /* Create assignment statment */ }
     | OUTPUT { /* create a write statement */ }

DECLLIST : DECL DELIM { /* create statement list, add declaration */ }
         | DECLLIST DECL DELIM { /* add declaration */ }
         | DECLLIST DELIM {}

RETURNSTMT : RETURN EXPRESSION DELIM { /* Create a return statement */ }
           | { /* no return */}

ASSIGNMENT : VAR ASSIGN EXPRESSION  { /*$$ = CreateAssignStatement($1, $3);*/ }
DECL : TYPE VAR { /* create var declaration with type */ }
OUTPUT : WRITE EXPRESSION  { /*$$ = CreateWriteStmt($2);*/ }

EXPRESSION : EXPR  {/*$$ = $1;*/}
           | FUNCCALL { /* $$ = $1 */ }

FUNCCALL : VAR '(' PARAMCALLLIST ')' { /* create function call expr (here var is just a symbol for the function name, not a variable) */ 
                                        /*$$ = CreateFunctionCall($1, $2);*/
                                        }

EXPR : EXPR '+' TERM  {/*$$ = CreateAdd($1, $3);*/}
EXPR : EXPR '-' TERM {/*$$ = CreateSubtract($1, $3);*/}
EXPR : TERM  {/*$$ = $1;*/}

TERM : TERM '*' UNARY  {/*$$ = CreateMultiply($1, $3);*/}
TERM : TERM '/' UNARY  {/*$$ = CreateDivide($1, $3);*/}
TERM : TERM '%' UNARY {/* create mod */ }
TERM : UNARY  {/*$$ = $1;*/}

UNARY : '-' NUMBER {/*$$ = CreateNegate($2);*/}
UNARY : NUMBER {/*$$ = $1;*/}

NUMBER : '(' EXPRESSION ')'  {/*$$ = $2;*/}
NUMBER : NUM  {/*$$ = CreateDouble($1);*/}
NUMBER : VAR  {/*$$ = CreateVariable($1);*/}

TYPE : INT { /* do something? ignore since everything is an int? */ }

%%
