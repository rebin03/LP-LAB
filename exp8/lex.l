%{
    int count=0;
    void printToken(const char* tokenType) {
        printf("%s  => %s\n", yytext, tokenType);
}
%}

directive #.*
keyword int|float|char|double|while|for|do|if|break|continue|void|switch|case|long|struct|const|typedef|return|else|goto|union
identifier [a-zA-Z][a-zA-Z0-9]*
invalidtokens [0-9]+[a-zA-Z]+
separator [;,()\{\}]
string \"{identifier}[^\"]*\"
argument \"[^\"]*\"
number [0-9]+
operator \|\||\&\&|\+|\-|\*|\/|\%|\=|\=\=|\!\=|\<|\<=|\>|>=
multiLine_comments "/*"([^*]|\*+[^*/])*"*+/" 
singleLine_coments "//".* 
space [ \t\n]
%%

{directive} { printToken("preprocessor directive"); }
{keyword} { printToken("keyword"); }
{separator} { printToken("separator"); }
{identifier} { printToken("identifier");  count++;}
{invalidtokens} { printToken("invalid token"); }
{string} { printToken("string"); }
{argument} { printToken("argument"); }
{number} { printToken("number"); }
{operator} { printToken("operator"); }
{singleLine_coments} 
{multiLine_comments}
{space}

%%

int main() {
    FILE *file;
    file = fopen("input.c", "r");
    if (!file) {
        printf("unable to open file");
        exit(0);
    }
    yyin = file;
    yylex();
    printf("\nNumber of identifiers: %d\n", count);
    return 0;
}

int yywrap() {
    fclose(yyin);
    return 1;
}