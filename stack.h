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

    if(is_empty(stack)){printf("Stack is empty!\n"); return;}

    int N = stack->size;
    struct Node* current_node = stack->head;
    for(int i=0; i<N; i++){
        printf("Node val: %d\n", current_node->node_num);
        current_node = current_node->previous_node;
    } 
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