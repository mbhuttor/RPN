
//
// Created by marya on 4/23/2021.
//


#include "error.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "stack.h"

int is_operator(char *token)
{
    int ret = 0;
    if(token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/' || token[0] == '^')
    {
        ret = 1;
    }
    return ret;
}

int is_number(char *token)
{
    int i;
    int ret = 1;

    for(i=0; i<strlen(token); i++)
    {
        if(!isdigit(token[i]))
        {
            ret = 0;
            break;
        }
    }
    return ret;
}

void infix_to_rpn(char *expression, char *outputString, int *status) {
    char *token;
    node *output = NULL;
    node *operators = NULL;
    node *number;
    node *ans = NULL;
    node *item;
    char text[80];

    node *operator;


    *status = SUCCESS; /* everything is ok */


    token = strtok(expression, " \t\n\r");
    while (token != NULL && *status == 0) {
        // Process the token

        //if the token is a number, then:
        if(is_number(token))
        {
            //    push it to the output queue.
            number = createNumberNode(atof(token));
            push(number, &output);
        }
            //else if the token is a function then:
            //    push it onto the operator stack
            //else if the token is an operator then:
        else if(is_operator(token))
        {
            //    while ((there is an operator at the top of the operator stack)
            //          and ((the operator at the top of the operator stack has greater precedence)
            //              or (the operator at the top of the operator stack has equal precedence and the token is left associative))
            //          and (the operator at the top of the operator stack is not a left parenthesis)):
            //        pop operators from the operator stack onto the output queue.
            //    push it onto the operator stack.
            operator = createOperatorNode(token[0]);
            while(!isEmpty(operators) && ((peek(&operators)->precedence > operator->precedence)||
                                          (peek(&operators)->precedence == operator->precedence && operator->contents.operator != '^'))
                  && peek(&operators)->contents.operator != '(' )
            {
                push(pop(&operators),&output);
            }
            push(operator,&operators);
        }
        else if(token[0] == '(')
        {
            //else if the token is a left parenthesis (i.e. "("), then:
            //    push it onto the operator stack.
            operator = createOperatorNode('(');
            push(operator, &operators);
        }
        else if(token[0] == ')')
        {
            //else if the token is a right parenthesis (i.e. ")"), then:
            //    while the operator at the top of the operator stack is not a left parenthesis:
            //        pop the operator from the operator stack onto the output queue.
            while(!isEmpty(operators) && peek(&operators)->contents.operator != '(')
            {
                push(pop(&operators),&output);
            }
            //    /* If the stack runs out without finding a left parenthesis, then there are mismatched parentheses. */
            if(isEmpty(operators))
            {
                *status = UNKNOWN;
                break;
            }
            else if(peek(&operators)->contents.operator == '(')
            {
                //    if there is a left parenthesis at the top of the operator stack, then:
                //        pop the operator from the operator stack and discard it
                destroyNode(pop(&operators));
            }

            //    if there is a function token at the top of the operator stack, then:
            //        pop the function from the operator stack onto the output queue.
        }

        token = strtok(NULL, " \t\n\r");
    }

///* After while loop, if operator stack not null, pop everything to output queue */
//if there are no more tokens to read then:
//    while there are still operator tokens on the stack:
//        /* If the operator token on the top of the stack is a parenthesis, then there are mismatched parentheses. */
//        pop the operator from the operator stack onto the output queue.
    while(!isEmpty(operators))
    {
        operator = pop(&operators);
        if(operator->contents.operator == '(')
        {
            *status = UNKNOWN;
            break;
        }
        push(operator, &output);
    }

    clearStack(&operators);

    // Need to reverse our stack order because output is an output queue, we want our answer to be a stack
    while(!isEmpty(output))
    {
        push(pop(&output),&ans);
    }

    outputString[0] = '\0';   // Initialize an empty string

    while(!isEmpty(ans))
    {
        item = pop(&ans);
        if(item->type == NUMBER)
        {
            sprintf(text,"%f ", item->contents.value);
            strcat(outputString,text);
        }
        else
        {
            sprintf(text,"%c ", item->contents.operator);
            strcat(outputString,text);
        }
        destroyNode(item);
    }
}
