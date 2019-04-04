%option nodefault yylineno

%{
#include <string.h>
#include "../inc/msg.h"
#include "../inc/label.h"
#include "../inc/global.h"
#include "../inc/output.h"
#include "../obj/asm.tab.h"

void yyerror(char *s);

union yylval {
	op_t op;
	int i;
};

%}

LABELNAME [_a-zA-Z][_a-zA-Z0-9]*

%%

\n.*  { strncpy(linebuf, yytext+1, sizeof(linebuf)); /* save the next line */
        yyless(1);      /* give back all but the \n to rescan */
        output_line(linebuf); return EOL;
      }
\r\n.* {
		strncpy(linebuf, yytext+2, sizeof(linebuf)); /* save the next line */
		yyless(2);      /* give back all but the \r\n to rescan */
		output_line(linebuf); return EOL;
       }
<<EOF>> { yyterminate(); return EOL; }

[ \t]   { /* ignore whitespace*/ }
[,]		{ return ','; }

"//".*$ { /* comment */ }

[r][0-9]+      { yylval.i = atoi(yytext+1); return REGISTER; }
(sp)           { yylval.i = 12; return REGISTER; }
(lr)           { yylval.i = 13; return REGISTER; }
(sr)           { yylval.i = 14; return REGISTER; }
(pc)           { yylval.i = 15; return REGISTER; }
[+-]?"0x"?[0-9A-F]+ { yylval.i = strtol(yytext, 0, 0); return IMMEDIATE; }

(add)     { yylval.op = op_add;  return MNEMONIC; }
(sub)     { yylval.op = op_sub;  return MNEMONIC; }
(and)     { yylval.op = op_and;  return MNEMONIC; }
(or)      { yylval.op = op_or;  return MNEMONIC; }
(xor)     { yylval.op = op_xor;  return MNEMONIC; }
(lsh)     { yylval.op = op_lsh;  return MNEMONIC; }
(rsh)     { yylval.op = op_rsh;  return MNEMONIC; }
(addi)    { yylval.op = op_addi;  return MNEMONIC; }
(cmp)     { yylval.op = op_cmp;  return MNEMONIC; }
(ssr)     { yylval.op = op_ssr;  return MNEMONIC; }

(ldr)     { yylval.op = op_ldr;  return MNEMONIC; }
(ld08)    { yylval.op = op_ld08;  return MNEMONIC; }
(ld16)    { yylval.op = op_ld16;  return MNEMONIC; }
(ld32)    { yylval.op = op_ld32;  return MNEMONIC; }
(st08)    { yylval.op = op_st08;  return MNEMONIC; }
(st16)    { yylval.op = op_st16;  return MNEMONIC; }
(st32)    { yylval.op = op_st32;  return MNEMONIC; }

(brt)     { yylval.op = op_brt; return MNEMONIC; }
(br)      { yylval.op = op_br;  return MNEMONIC; }
(call)    { yylval.op = op_call;  return MNEMONIC; }
(trap)    { yylval.op = op_trap;  return MNEMONIC; }
(reti)    { yylval.op = op_reti;  return MNEMONIC; }

(tst)     { yylval.op = op_tst; return MNEMONIC; }

(mov)     { yylval.op = op_mov;  return MNEMONIC; }
(nop)     { yylval.op = op_nop; return MNEMONIC; }
(ret)     { yylval.op = op_ret; return MNEMONIC; }
(clr)     { yylval.op = op_clr; return MNEMONIC; }

(\.word)    { yylval.op = op_word; return MNEMONIC; }
(\.address) { yylval.op = op_addr; return MNEMONIC; }
(\.align) { yylval.m = op_align; return MNEMONIC; }

(eq)      { yylval.m = mode_eq;  return MODE; }     
(neq)     { yylval.m = mode_neq;  return MODE; }    
(gg)      { yylval.m = mode_gg;  return MODE; }    
(ge)      { yylval.m = mode_ge;  return MODE; }    
(ll)      { yylval.m = mode_ll;  return MODE; }    
(le)      { yylval.m = mode_le;  return MODE; }

(true)    { yylval.m  = mode_cond_true; return MODE; }
(always)  { yylval.m  = mode_cond_unconditional; return MODE; }

{LABELNAME}  { strcpy(yylval.s, yytext); return LABEL; }
(\>{LABELNAME}) { yylval.i = label_relative(yytext+1); return IMMEDIATE; }
(\={LABELNAME}) { yylval.i = label_absolute(yytext+1); return IMMEDIATE; }


:         { return ':'; }
.		  { yyerror("unexpected input"); }

%%


int yywrap() { return 1; }

