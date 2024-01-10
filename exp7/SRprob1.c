#include <stdio.h>
#include <string.h>

struct ProductionRule
{
    char left[10];
    char right[10];
};

int main()
{
    char input[20], stack[50], ch[2], *substring;
    int i, j, stack_length, substring_length, stack_top;
    struct ProductionRule rules[10];

    stack[0] = '\0';

    strcpy(rules[0].left, "S");
    strcpy(rules[0].right, "id");
    strcpy(rules[1].left, "S");
    strcpy(rules[1].right, "S*S");
    strcpy(rules[2].left, "S");
    strcpy(rules[2].right, "S+S");

    printf("\nGrammer:\nE --> 2E2\nE --> 3E3\nE --> 4\n\n");

    printf("Enter the input string: ");
    scanf("%s", input);

    i = 0;

    printf("\nStack\t\t\tInput Buffer\t\tOperation\n");
    while (1)
    {
        if (i < strlen(input))
        {
            ch[0] = input[i];
            ch[1] = '\0';
            i++;
            strcat(stack, ch);
            printf("%-24s%-24sShift %s\n", stack, input + i, ch);
        }


        for (j = 0; j < 3; j++)
        {
            if (strcmp(stack, "S") == 0 && i == strlen(input))
                break;
                
            substring = strstr(stack, rules[j].right);
            if (substring != NULL)
            {
                stack_length = strlen(stack);
                substring_length = strlen(substring);
                stack_top = stack_length - substring_length;
                stack[stack_top] = '\0';
                strcat(stack, rules[j].left);
                printf("%-24s%-24sReduce %s->%s\n", stack, input + i, rules[j].left, rules[j].right);
                j = 0; 
            }
        }

        // Check if the stack contains only the start symbol and if the entire input string has been processed
        if (strcmp(stack, "S") == 0 && i == strlen(input))
        {
            printf("Accepted\n");
            break;
        }

        // Check if the entire input string has been processed but the stack doesn't match the start symbol
        if (i == strlen(input))
        {
            printf("Not Accepted\n");
            break;
        }
    }

    return 0;
}