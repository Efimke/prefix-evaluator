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
    new->link = NULL;
    return new;
}

/*
 Stack block
 */
struct Stack {
    struct Node *top;
};

struct Stack *create_stack() {
    struct Stack *new = (struct Stack *) malloc(sizeof(struct Stack));
    new->top = NULL;
    return new;
}

int pop(struct Stack *stack) {
    struct Node *node = stack->top;
    int value = node->value;
    stack->top = node->link;
    free(node);
    return value;
}

int is_empty(struct Stack *stack) {
    return stack->top == NULL;
}

int peek(struct Stack *stack) {
    return stack->top->value;
}

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

char *reverse_string(char *string) {
    int len = (int) strlen(string);
    char *new_string = (char *) malloc(sizeof(char) * len);
    int i = len - 1, j = 0;
    for (; i >= 0; i--, j++) {
        new_string[j] = string[i];
    }
    free(string);
    new_string[j] = '\0';
    return new_string;
}


int evaluate_prefix(char *prefix) {
    struct Stack *stack = create_stack();
    char symb;
    int value, oprnd1, oprnd2;
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
    return pop(stack);
}


char *infix_to_prefix(char *infix) {
    char symb;
    struct Stack *stack = create_stack();
    int infix_len = (int) strlen(infix);
    char *output = (char *) malloc(sizeof(char) * infix_len);
    int output_index = 0;
    int i;
    for (i = infix_len - 1; i >= 0; i--) {
        symb = infix[i];
        if (isdigit(symb)) {
            output[output_index] = symb;
            output_index++;
        } else if (symb == ')') {
            push(stack, symb);
        } else if (is_operator(symb)) {
            if (is_empty(stack) || (char) peek(stack) == ')') {
                push(stack, symb);
            } else if (precedence((char) peek(stack)) <= precedence(symb)) {
                push(stack, symb);
            } else {
                output[output_index] = (char) pop(stack);
                output_index++;
                push(stack, symb);
            }
        } else if (symb == '(') {
            while (1) {
                char operator = (char) pop(stack);
                if (operator == ')') break;
                output[output_index] = operator;
                output_index++;
            }
        }
    }
    while (!is_empty(stack)) {
        char operator = (char) pop(stack);
        output[output_index] = operator;
        output_index++;
    }
    output[output_index] = '\0';
    return reverse_string(output);
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

    char test_infix1[] = "1+2";
    printf("Result: %s, expected %s \n", infix_to_prefix(test_infix1), "+12");

    char test_infix2[] = "3*(1+1)";
    printf("Result: %s, expected %s \n", infix_to_prefix(test_infix2), "*3+11");

    char test_infix3[] = "2*3/(2-1)+5*(4-1)";
    printf("Result: %s, expected %s \n", infix_to_prefix(test_infix3), "+/*23-21*5-41");
}
