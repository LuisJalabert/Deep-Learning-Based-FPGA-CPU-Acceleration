%{
#include <stdio.h>
#include "../inc/msg.h"
#include "../inc/handle.h"
#include "../inc/label.h"
#include "../inc/global.h"
%}

%union {
	int i;
	op_t op;
	opmode_t m;
	char s[32];
}

%token EOL

%token <op> MNEMONIC
%token <m> MODE
%token <i> REGISTER
%token <i> IMMEDIATE
%token <s> LABEL

%%

line:
 | line lbldef
 | line r3-line EOL
 | line r2-line EOL
 | line ri-line EOL
 | line r2i-line EOL
 | line mr2-line EOL
 | line mi-line EOL
 | line mr-line EOL
 | line i-line EOL
 | line o-line EOL
 | line or-line EOL
 | line om-line EOL
 | line EOL
 | line error-line EOL
 ;
 
r3-line:  MNEMONIC REGISTER ',' REGISTER ',' REGISTER   { handle_or3($1, $2, $4, $6); }
r2-line:  MNEMONIC REGISTER ',' REGISTER                { handle_or2($1, $2, $4); }
ri-line:  MNEMONIC REGISTER ',' IMMEDIATE               { handle_ori($1, $2, $4); }
r2i-line: MNEMONIC REGISTER ',' REGISTER ',' IMMEDIATE  { handle_or2i($1, $2, $4, $6); }
mr2-line: MNEMONIC MODE         REGISTER ',' REGISTER   { handle_omr2($1, $2, $3, $5); }
mi-line:  MNEMONIC MODE         IMMEDIATE               { handle_omi($1, $2, $3); }
mr-line:  MNEMONIC MODE         REGISTER                { handle_omr($1, $2, $3); }
i-line:   MNEMONIC IMMEDIATE                            { handle_oi($1, $2); }
o-line:   MNEMONIC                                      { handle_o($1); }
or-line:  MNEMONIC REGISTER                             { handle_or($1, $2); }
om-line:  MNEMONIC MODE                                 { handle_om($1, $2); }
lbldef:   LABEL    ':'                                  { label_add($1, address); }
error-line: error                                       {  }


%%

