#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node{
    int node_num;
    struct node* previous_node;
};

struct stack{
    struct node* head;
    int size;
};

struct stack* init_stack(){
    struct stack* stack = malloc(sizeof(struct node));
    stack->head = NULL;
    stack->size = 0;
    return stack;
}

void push(struct stack* stack, int node_num){
    struct node* new_node = malloc(sizeof(struct node));
    new_node->node_num = node_num;
    new_node->previous_node = stack->head;
    stack->head = new_node; 
    stack->size++;
}


bool is_empty(struct stack* stack){
    if(stack->head == NULL){
        return true;
    }
    else return false;
}

bool pop(struct stack* stack){
    
    if(is_empty(stack)) return false;

    struct node* top = stack->head;
    stack->head = stack->head->previous_node;
    stack->size = stack->size - 1;
    free(top);
    return true;
}

int get_head_num(struct stack* stack){
    if(is_empty(stack)){
        return -1;
    }
    return stack->head->node_num;
}

int get_stack_size(struct stack* stack){
    return stack->size;
}

void print_stack(struct stack* stack){

    if(is_empty(stack)){printf("Stack is empty!\n"); return;}

    int N = stack->size;
    struct node* current_node = stack->head;
    for(int i=0; i<N; i++){
        printf("Node val: %d\n", current_node->node_num);
        current_node = current_node->previous_node;
    } 
}


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