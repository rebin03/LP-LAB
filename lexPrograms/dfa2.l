%{ 
%} 

%s B C D E DEAD 

%% 
<INITIAL>a BEGIN B; 
<INITIAL>b BEGIN INITIAL; 
<INITIAL>[^ab\n] BEGIN DEAD; 
<INITIAL>\n BEGIN INITIAL; {printf("Accepted\n");} 

<B>a BEGIN C; 
<B>b BEGIN INITIAL; 
<B>[^ab\n] BEGIN DEAD; 
<B>\n BEGIN INITIAL; {printf("Accepted\n");} 

<C>a BEGIN C; 
<C>b BEGIN D; 
<C>[^ab\n] BEGIN DEAD; 
<C>\n BEGIN INITIAL; {printf("Accepted\n");} 

<D>a BEGIN B; 
<D>b BEGIN E; 
<D>[^ab\n] BEGIN DEAD; 
<D>\n BEGIN INITIAL; {printf("Accepted\n");} 

<E>a BEGIN E; 
<E>b BEGIN E; 
<E>[^ab\n] BEGIN DEAD; 
<E>\n BEGIN INITIAL; {printf("Not Accepted\n");} 


<DEAD>[^\n] BEGIN DEAD; 
<DEAD>\n BEGIN INITIAL; {printf("Invalid\n");} 

%% 

int main() 
{ 
	printf("Enter String\n"); 
	yylex(); 
	return 0; 
} 
int yywrap()
{
    return 1;
}