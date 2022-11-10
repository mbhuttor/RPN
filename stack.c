
//
// Created by marya on 4/22/2021.
//

#include "stack.h"
#include <stdlib.h>



bool isEmpty(node* head)
{
    return !head;
}
void push(node* newNode, node** head)
{
    newNode->next = *head;
    *head = newNode;
}
node* pop(node** head)  //pointer to pointer
{
    if(!isEmpty(*head))
    {
        node* poppedNode = *head;
        *head = (*head)->next;    //deferenced
        return poppedNode;
    }
    else
    {
        return NULL;
    }
}
node* peek(node** head) // pointer-to-pointer not technically need, but makes calls to push, pop, peek consistent
{
    return *head;
}
void clearStack(node** head)  //pointer to pointer because we are changing head
{
    if(!isEmpty(*head))
    {
        while(*head != NULL)
        {
            node* poppedNode = *head;
            *head = (*head)->next;
            destroyNode(poppedNode);
        }
    }
}

