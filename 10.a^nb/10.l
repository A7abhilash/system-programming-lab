%{
	#include"an_b.tab.h"
%}

%%
[a] {return A;}
[b] {return B;}
[ \t] ; // Ignore spaces and tabs
\n {return NL;}
. {return yytext[0];}
%%

int yywrap() {return 1;}

