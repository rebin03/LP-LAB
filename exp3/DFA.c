#include <stdio.h>

// Function to simulate the DFA
int isEvenNumberOfZerosAndOnes(const char *str)
{
    int state = 0; // Initial state: q0

    for (int i = 0; str[i] != '\0'; i++)
    {
        char input = str[i];

        switch (state)
        {
        case 0: // State q0
            if (input == '0')
                state = 1;
            else if (input == '1')
                state = 2;
            else
                return 0; // Invalid input
            break;
        case 1: // State q1
            if (input == '0')
                state = 0;
            else if (input == '1')
                state = 3;
            else
                return 0; // Invalid input
            break;
        case 2: // State q2
            if (input == '0')
                state = 3;
            else if (input == '1')
                state = 0;
            else
                return 0; // Invalid input
            break;
        case 3: // State q3
            if (input == '0')
                state = 2;
            else if (input == '1')
                state = 1;
            else
                return 0; // Invalid input
            break;
        }
    }

    // After processing the entire string, check if the final state is q0
    return (state == 0);
}

int main()
{
    char str[100];
    printf("Enter a string of 0s and 1s: ");
    scanf("%s", str);

    if (isEvenNumberOfZerosAndOnes(str))
    {
        printf("Accepted: The string has an even number of 0s and 1s.\n");
    }
    else
    {
        printf("Rejected: The string does not have an even number of 0s and 1s.\n");
    }

    return 0;
}