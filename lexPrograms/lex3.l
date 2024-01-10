%{
int linec=0, wordc=0, spacec=0, charc=0;    
%}

%%
[\n] {linec++; charc+=yyleng;}
[ \t] {spacec++; charc+=yyleng;}
[^\t\n ] {wordc++; charc+=yyleng;}
%%

int main()
{
    printf("Enter the sentence:\n");
    yylex();
    printf("no of line is %d\n",linec);
     printf("no of space is %d\n",spacec);
      printf("no of word is %d\n",wordc);
       printf("no of characters is %d\n",charc);
       return 0;
}

int yywrap()
{
  return 1;
}