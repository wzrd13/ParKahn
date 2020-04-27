#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node{
    int node_num;
    struct Node* previous_node;
};

struct Stack{
    struct Node* head;
    int size;
};


void red(){ printf("\033[0;31m"); }
void green(){ printf("\033[0;32m");}
void yellow(){ printf("\033[0;33m");}
void reset(){ printf("\033[0m");}

struct Stack* init_stack(){
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Node));
    stack->head = NULL;
    stack->size = 0;
    return stack;
}

void push(struct Stack* stack, int node_num){
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->node_num = node_num;
    new_node->previous_node = stack->head;
    stack->head = new_node; 
    stack->size++;
}


bool is_empty(struct Stack* stack){
    if(stack->head == NULL){
        return true;
    }
    else return false;
}

bool pop(struct Stack* stack){
    
    if(is_empty(stack)) return false;

    struct Node* top = stack->head;
    stack->head = stack->head->previous_node;
    stack->size = stack->size - 1;
    free(top);
    return true;
}

int get_head_num(struct Stack* stack){
    if(is_empty(stack)){
        return -1;
    }
    return stack->head->node_num;
}

int return_and_remove_head(struct Stack* stack){
    int node_num = get_head_num(stack);
    pop(stack);
    return node_num;
}

int get_stack_size(struct Stack* stack){
    return stack->size;
}

void print_stack(struct Stack* stack){

    if(is_empty(stack)){ red();printf("Stack is empty!\n");reset(); return;}

    int N = stack->size;
    struct Node* current_node = stack->head;
    for(int i=0; i<N; i++){
        yellow();
        printf("Stack value: %d\n", current_node->node_num);
        reset();
        current_node = current_node->previous_node;
    } 
}

void print_stack_bot_to_top(struct Stack* stack){
    yellow();
    printf("Order: ");
    int* array = (int*)malloc(sizeof(int)*stack->size);
    struct Node* node = stack->head;
    for(int i=stack->size-1; i>=0; i--){
        array[i] = node->node_num;
        node = node->previous_node;
    }
    for(int i=0;i<stack->size; i++){
        printf("%d , ", array[i]+1);
    }
    printf("\n");
    reset();
}

/*
//STACK PLAYGROUND
int main(){

    struct stack* stack =  init_stack();

    print_stack(stack);


    push(stack ,1);
    push(stack ,2);
    push(stack ,3);
    push(stack ,4);
    push(stack ,5);

    print_stack(stack);

    pop(stack);
    
    printf("\n-----\n %d", is_empty(stack));

    print_stack(stack);

    pop(stack);

    printf("\nHead value: %d: \n Stack size: %d \n", get_head_num(stack), get_stack_size(stack));
    return 0;
}
*/