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

    // Define the hardcoded production rules
    strcpy(rules[0].left, "S");
    strcpy(rules[0].right, "(L)");
    strcpy(rules[1].left, "S");
    strcpy(rules[1].right, "a");
    strcpy(rules[2].left, "L");
    strcpy(rules[2].right, "L,S");
    strcpy(rules[3].left, "L");
    strcpy(rules[3].right, "S");

    printf("\nGrammer:\nS --> (L)|a\nL --> L,S|S\n\n");

    // User input for the input string
    printf("Enter the input string: ");
    scanf("%s", input);

    i = 0;
    // print heading
    printf("Stack\t\t\tInput Buffer\t\tOperation\n");
    while (1)
    {
        //SHIFT Operation
        // If there are more characters in the input string, add the next character to the stack
        if (i < strlen(input))
        {
            ch[0] = input[i];
            ch[1] = '\0';
            i++;
            strcat(stack, ch);
            printf("%-24s%-24sShift %s\n", stack, input + i, ch);
        }

        //REDUCE Operation
        // Iterate through the production rules
        for (j = 0; j < 4; j++)
        {
            if (strcmp(stack, "S") == 0 && i == strlen(input))
                break;
            // Check if the right-hand side of the production rule matches a substring in the stack
            substring = strstr(stack, rules[j].right);
            if (substring != NULL)
            {
                // Replace the matched substring with the left-hand side of the production rule
                stack_length = strlen(stack);
                substring_length = strlen(substring);
                stack_top = stack_length - substring_length;
                stack[stack_top] = '\0';
                strcat(stack, rules[j].left);
                printf("%-24s%-24sReduce %s->%s\n", stack, input + i, rules[j].left, rules[j].right);
                j = 0; // Restart the loop to ensure immediate reduction of the newly derived production rule
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