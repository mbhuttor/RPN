//
// Created by marya on 4/23/2021.
//

#include "rpn.h"
#include "error.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

double mypow(double base, int exponent)
{
    if(exponent == 0) // Base case
    {
        return 1.0;
    }
    return base * mypow(base, exponent - 1);
}

double evaluate(char *expression, int *status)
{
    char *token;
    node *stack = NULL;
    node *number;
    node *left, *right;
    double answer;

    *status = SUCCESS; /* everything is ok */


    token = strtok(expression," \t\n\r");
    while(token != NULL && *status == 0 )
    {
        // Process the token
        if(strlen(token) == 1)
        {
            switch(token[0])
            {
                case '+':  /*left + right*/
                    left = pop(&stack);
                    right = peek(&stack);

                    if(left != NULL && right != NULL)
                    {
                        right->contents.value = right->contents.value + left->contents.value;
                        destroyNode(left);
                    }
                    else
                    {
                        *status = NULLPTR;
                    }
                    break;
                case '-':
                    left = pop(&stack);
                    right = peek(&stack);

                    if(left != NULL && right != NULL)
                    {
                        right->contents.value = right->contents.value - left->contents.value;
                        destroyNode(left);
                    }
                    else
                    {
                        *status = NULLPTR;
                    }
                    break;
                case '*':
                    left = pop(&stack);
                    right = peek(&stack);

                    if(left != NULL && right != NULL)
                    {
                        right->contents.value = right->contents.value * left->contents.value;
                        destroyNode(left);
                    }
                    else
                    {
                        *status = NULLPTR;
                    }
                    break;
                case '/':
                    left = pop(&stack);
                    right = peek(&stack);

                    if(left != NULL && right != NULL)
                    {
                        right->contents.value = right->contents.value / left->contents.value;
                        destroyNode(left);
                    }
                    else
                    {
                        *status = NULLPTR;
                    }
                    break;

                case '^':
                    left = pop(&stack);
                    right = peek(&stack);

                    if(left != NULL && right != NULL)
                    {
                        right->contents.value = mypow(right->contents.value, (int) left->contents.value);
                        destroyNode(left);
                    }
                    else
                    {
                        *status = NULLPTR;
                    }
                    break;

                default:  /* We either have left digit or an unrecognized operator*/
                    if(isdigit(token[0]))
                    {
                        number = createNumberNode(atof(token));
                        push(number, &stack );
                    }
                    else
                    {
                        *status = UNKNOWN;
                    }
                    break;
            }
        }
        else
        {
            /* if we make it to here, we have left number */
            number = createNumberNode(atof(token));
            push(number, &stack );
        }


        token = strtok(NULL, " \t\n\r");
    }

    /* No more processing if we have an error */
    if(*status != SUCCESS)
    {
        return 0.0;
    }

    number = pop(&stack);
    if(number == NULL)
    {
        *status = NULLPTR;
        return 0.0;
    }

    answer = number->contents.value;
    destroyNode(number);

    if(peek(&stack) != NULL) /* check not enough operators */
    {
        *status = TOOFEW;
    }

    clearStack(&stack);


    return answer;

}
