%{
int count = 0;

%}

identifier [a-zA-Z][a-zA-Z0-9_]*
invalidtoken [0-9_]+[a-zA-Z]+

%%

#.* { printf("\n%s is a preprocessor directive", yytext); }
int|float|char|while|for|do|if|break|continue|void|switch|struct|return|else {printf("\n%s is a keyword", yytext);}
[;,(){}] {  printf("\n%s is a separator", yytext); }
{identifier} {printf("\n%s is an identifier", yytext); }
{invalidtoken} { printf("\n%s is an invalid token", yytext); }
[0-9]+ {printf("\n%s is a Number", yytext); }
".*" {printf("\n%s is a string", yytext); }
([A-Za-z][A-Za-z0-9],[A-Za-z][a-zA-Z0-9]) { printf("\n%s is argument", yytext); }
\+|\-|\%|\*|\>|\<|\>=|\<=|\=|\/|\& { printf("\n%s is an operator", yytext); }
"//"[A-Za-z0-9 \t]*"\n" {printf("\n%s is a single line comment",yytext);}
"/"[A-Za-z0-9 \t\n]"*/" {printf("\n%s is a multiline comment",yytext); }
[ \t\n] ;

%%

int main() {
    FILE *file;
    file = fopen("in.c", "r");
    if (!file) {
        printf("unable to open file");
        exit(0);
    }
    yyin = file;
    yylex();

    return 0;
}

int yywrap() {
    fclose(yyin);
    return 1; 
}