
//
// Created by marya on 4/22/2021.
//

#ifndef PS5_STACK_H
#define PS5_STACK_H
#include <stdbool.h>
#include "node.h"

bool isEmpty(node* head);
void push(node* newNode, node** head);
node* pop(node** head);
node* peek(node** head);
void clearStack(node** head);


#endif //PS5_STACK_H
