
//
// Created by marya on 4/22/2021.
//

#ifndef PS5_NODE_H
#define PS5_NODE_H
typedef enum ExpressionTypes{OPERATOR, NUMBER} Type;
typedef struct node node;
struct node
{
    union
    {
        double value;
        char operator;
    } contents;
    Type type;
    int precedence;
    node* next;
};
node* createNode(int type, double value);
node* createOperatorNode(char operator);
node* createNumberNode(double value);
void destroyNode(node* myNode);





#endif //PS5_NODE_H
