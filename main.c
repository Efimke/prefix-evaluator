#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <math.h>

/*
 Linked list block
 */
struct Node {
    int value;
    struct Node *link;
};

struct Node *create_node(int value) {
    struct Node *new = (struct Node *) malloc(sizeof(struct Node));
    new->value = value;
    return new;
}

//void delete_last(struct Node *node) {
//    if (node->link == NULL) {
//        free(node);
//    } else {
//        delete_last(node->link);
//    }
//}
//
//struct Node *get_last_node(struct Node *node) {
//    if (node->link == NULL) {
//        return node;
//    } else {
//        get_last_node(node->link);
//    }
//}
//
//void add_an_last_position(char value, struct Node *node) {
//    if (node != NULL) {
//        get_last_node(node)->value = value;
//    }
//}

/*
 Stack block
 */
struct Stack {
    struct Node *top;
};

struct Stack *create_stack() {
    struct Stack *new = (struct Stack *) malloc(sizeof(struct Stack));
    return new;
}

int pop(struct Stack *stack) {
    struct Node *node = stack->top;
    int value = node->value;
    stack->top = node->link;
    free(node);
    return value;
}

//char peek(struct Stack *stack) {
//    if (stack->top != NULL) {
//        return stack->top->value;
//    }
//}

void push(struct Stack *stack, int value) {
    struct Node *new = create_node(value);
    if (stack->top != NULL) {
        new->link = stack->top;
    }
    stack->top = new;
}

/*
 * -------------------------------------------------------
 */
int is_operator(char value) {
    if (value == '^' || value == '*' || value == '/' || value == '+' || value == '-') {
        return 1;
    } else {
        return 0;
    }
}

int precedence(char value) {
    if (value == '^')
        return 3;
    else if (value == '*' || value == '/')
        return 2;
    else if (value == '+' || value == '-')
        return 1;
    else
        return 0;
}

int evaluate_prefix(char *prefix) {
    struct Stack *stack = create_stack();
    char symb;
    int value, oprnd1, oprnd2, num;
    int i = 0;
    for (i = (int) strlen(prefix) - 1; i >= 0; i--) {
        symb = prefix[i];
        if (isdigit(symb)) {
            push(stack, atoi(&symb));
        } else {
            oprnd1 = pop(stack);
            oprnd2 = pop(stack);
            switch (symb) {
                case '+':
                    value = oprnd1 + oprnd2;
                    break;
                case '-':
                    value = oprnd1 - oprnd2;
                    break;
                case '*':
                    value = oprnd1 * oprnd2;
                    break;
                case '/':
                    value = oprnd1 / oprnd2;
                    break;
                case '^':
//                    value = pow(oprnd1, oprnd2);
                    break;
            }
            push(stack, value);
        }
    }
    return value;
}

/*
 * ------------------------
 */

int main() {
    char test_prefix_exp1[] = "+12";
    printf("Result: %d, expected %d \n", evaluate_prefix(test_prefix_exp1), 3);

    char test_prefix_exp2[] = "*3+11";
    printf("Result: %d, expected %d \n", evaluate_prefix(test_prefix_exp2), 6);

    char test_prefix_exp3[] = "+/*23-21*5-41";
    printf("Result: %d, expected %d \n", evaluate_prefix(test_prefix_exp3), 21);
}
