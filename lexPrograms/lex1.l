
%{

%}

%%
if|else|void|struct|double|int|float {printf("\n%s is a keyword",yytext);}
[0-9]+ {printf("\n%s is a number",yytext);}
[A-Za-z]+ {printf("\n%s is a word",yytext);}
. | \n {ECHO;} ;
%%

int main(){
    printf("Enter a string\n");
    yylex();
    return 0;
}

int yywrap()
{
    return 1;
}