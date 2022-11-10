include <stdlib.h>
#include <stdio.h>
#include "node.h"

node* createNode(int type, double value)
{
    node* new_node = (node*)malloc(sizeof(node));

    if(new_node != NULL)
    {
        new_node->type = type;
        new_node->contents.value = value;
        new_node->next = NULL;
    }
    else
    {
        printf("Error: Unable to create a node\n");
    }

    return new_node;
}

node * createNumberNode(double value)
{
    node* new_node = (node*)malloc(sizeof(node));

    if(new_node != NULL)
    {
        new_node->type = NUMBER;
        new_node->contents.value = value;
        new_node->next = NULL;
    }
    else
    {
        printf("Error: Unable to create a node\n");
    }

    return new_node;
}

node *createOperatorNode(char operator)
{
    node* new_node = (node*)malloc(sizeof(node));

    if(new_node != NULL)
    {
        new_node->type = OPERATOR;
        new_node->contents.operator = operator;
        switch(operator)
        {
            case '+':
            case '-':
                new_node->precedence = 0;
                break;
            case '*':
            case '/':
                new_node->precedence = 1;
                break;
            case '^':
                new_node->precedence = 2;
                break;
            case '(':
            case ')':
                new_node->precedence = 3;
                break;

        }
        new_node->next = NULL;
    }
    else
    {
        printf("Error: Unable to create a node\n");
    }

    return new_node;
}

void destroyNode(node* myNode)
{
    free(myNode);
}
