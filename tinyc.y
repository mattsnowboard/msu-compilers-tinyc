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

%token WRITE INT ASSIGN DELIM RETURN IF WHILE 
%token<ival> NUM
%token<sval> VAR

%type<pval> PROGRAM FUNCDEF FUNCDECL PARAMDEFLIST PARAMCALLLIST STMTLIST STMT ASSIGNMENT DECL OUTPUT RETURNSTMT EXPRESSION FUNCCALL EXPR TERM UNARY NUMBER TYPE DECASSIGN IFSTMT WHILESTMT BLOCK

%%

PROGRAM : PROGRAM FUNCDEF { $$ = AddFunctionToProgram($2);}
        | FUNCDEF { $$ = AddFunctionToProgram($1);}

FUNCDEF : FUNCDECL '{' STMTLIST '}' { $$ = AddToFunctionBlock($1, $3); }

FUNCDECL : TYPE VAR '(' PARAMDEFLIST ')' {  $$ = CreateFunctionBlock($2, $4, lineno); }

PARAMDEFLIST : DECL { $$ = CreateParameterList($1); }
             | PARAMDEFLIST ',' DECL { $$ = AddParameterToList($1, $3);}
             | { $$ = CreateParameterList(NULL);/* empty param list */ }
PARAMCALLLIST : EXPRESSION { $$ = CreateExprList($1);}
              | PARAMCALLLIST ',' EXPRESSION { $$ = AddExprToList($1, $3); }
              | { $$ = CreateExprList(NULL); /* empty param list */ }

BLOCK : '{' STMTLIST '}' { $$ = $2; }

STMTLIST : STMT DELIM { $$ = CreateStatementList($1);}
         | STMTLIST STMT DELIM { $$ = AddStatementToList($1, $2); }
         | STMTLIST DELIM {$$ = $1; }
         | { $$ = CreateStatementList(NULL); }


STMT : ASSIGNMENT  { $$ = $1; }
     | OUTPUT { $$ = $1; }
     | DECL { $$ = $1; }
     | DECASSIGN { $$ = $1; }
     | RETURNSTMT { $$ = $1; }
	 | IFSTMT { $$ = $1; }
	 | WHILESTMT { $$ = $1; }



IFSTMT : IF '(' EXPRESSION ')' BLOCK {
    $$ = CreateIfStmt($3, $5, lineno);
}
WHILESTMT : WHILE '(' EXPRESSION ')' BLOCK {

    $$ = CreateWhileStmt($3, $5, lineno);
}

RETURNSTMT : RETURN EXPRESSION { $$ = CreateReturn($2, lineno); }

DECASSIGN : TYPE VAR ASSIGN EXPRESSION {
    $$ = CreateDecAssignStatement($2, $4, lineno); }
ASSIGNMENT : VAR ASSIGN EXPRESSION  {
    $$ = CreateAssignStatement($1, $3, lineno); }
DECL : TYPE VAR { $$ = CreateDeclaration($2, lineno); }
OUTPUT : WRITE EXPRESSION  { $$ = CreateWriteStmt($2, lineno); }

EXPRESSION : EXPR  {$$ = $1;}
           | FUNCCALL {  $$ = $1; }

FUNCCALL : VAR '(' PARAMCALLLIST ')' { $$ = CreateFunctionCall($1, $3, lineno); }

EXPR : EXPR '+' TERM  {$$ = CreateAdd($1, $3, lineno);}
EXPR : EXPR '-' TERM {$$ = CreateSubtract($1, $3, lineno);}
EXPR : EXPR '>' TERM {$$ = CreateGreaterThan($1, $3, lineno);}
EXPR : EXPR '<' TERM {$$ = CreateLessThan($1, $3, lineno);}
EXPR : TERM  {$$ = $1;}

TERM : TERM '*' UNARY  {$$ = CreateMultiply($1, $3, lineno);}
TERM : TERM '/' UNARY  {$$ = CreateDivide($1, $3, lineno);}
TERM : UNARY  {$$ = $1;}
TERM : TERM '%' UNARY {$$ = CreateModulus($1, $3, lineno); }

UNARY : '-' NUMBER {$$ = CreateNegate($2, lineno);}
UNARY : NUMBER {$$ = $1;}

NUMBER : '(' EXPRESSION ')'  {$$ = $2;}
NUMBER : NUM  {$$ = CreateInt($1, lineno);}
NUMBER : VAR  {$$ = CreateVariable($1, lineno);}
NUMBER : FUNCCALL {$$ = $1; }

TYPE : INT { /* do something? ignore since everything is an int? */ }

%%
