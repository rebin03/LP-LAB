%{

%}

%%
[A-Z]+ {printf("%s\n",yytext);}
. ;
%%
int main()
{
    printf("Enter the string:\n");
    yylex();
    return 0;
}

int yywrap()
{
    return 1;

}