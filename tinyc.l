%{
/*
 * Lex file for tinyc
 */

#include <stdio.h>
#include "y.tab.h"

extern int lineno;  /* defined in micro.y */

%}

%%

("write") {return WRITE;}
("int")   {return INT;}

[0-9]+ { yylval.ival = atoi(yytext); return NUM; }

[a-zA-Z]+[a-zA-Z0-9]* { yylval.sval = strdup(yytext); return VAR;}

("("|")"|"*"|"-"|"+"|"/"|"}"|"{"|","|";") {return yytext[0];}
("=") {return ASSIGN;}

[ \t]* {/* ignore blank lines */}
"\n"    ++lineno; /* Keep track of line number for errors */
\r     {}

"//".*\n	{/*ignore comments*/}

. {
    fprintf(stderr,
            "Illegal character \'%s\' on line #%d\n",
            yytext, lineno);
    exit(1);
  }

%%

int yywrap()
{
    return 1;
}
