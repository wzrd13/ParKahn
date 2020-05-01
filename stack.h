#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node{
    int node_num;
    struct Node* previous_node;
};

struct Stack{
    struct Node* head;
<<<<<<< HEAD
    struct Node* tail;
    int size;
};

=======
    int size;
};


>>>>>>> cb204fdb9c8b1c2356ee5156ea3bc254dd0109c4
void red(){ printf("\033[0;31m"); }
void green(){ printf("\033[0;32m");}
void yellow(){ printf("\033[0;33m");}
void reset(){ printf("\033[0m");}

struct Stack* init_stack(){
<<<<<<< HEAD
    
    // Create pointer to stack
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    
    // Initialize stack variables
    stack->head = NULL;
    stack->tail = NULL;
    stack->size = 0;

    // Return pointer
=======
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Node));
    stack->head = NULL;
    stack->size = 0;
>>>>>>> cb204fdb9c8b1c2356ee5156ea3bc254dd0109c4
    return stack;
}

void push(struct Stack* stack, int node_num){
<<<<<<< HEAD
    
    // Create pointer to node
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

    // Get tail
    if (stack->head == NULL)        
    {
        stack->tail = new_node;
    }

    // Initialize node values
    new_node->node_num = node_num;
    new_node->previous_node = stack->head;
    
    // Get head
    stack->head = new_node;

=======
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->node_num = node_num;
    new_node->previous_node = stack->head;
    stack->head = new_node; 
>>>>>>> cb204fdb9c8b1c2356ee5156ea3bc254dd0109c4
    stack->size++;
}


bool is_empty(struct Stack* stack){
    if(stack->head == NULL){
        return true;
    }
    else return false;
}

<<<<<<< HEAD
int peek(struct Stack* stack){
    if(is_empty(stack)){
        return -1;
    }
    return stack->head->node_num;
}

int pop(struct Stack* stack){
    
    // Check if stack is empty
    if(is_empty(stack)) return -1;
    
    // Get value
    int n = stack->head->node_num;

    // Free memory
    struct Node* top = stack->head;

    // Update stack
    stack->head = stack->head->previous_node;
    stack->size = stack->size - 1;
    
    free(top);
    return n;
}

struct Stack* concatinate(struct Stack* A, struct Stack* B) {
    
    if(is_empty(B)) return A;
    if(is_empty(A)) return B;

    B->tail->previous_node = A->head;
    A->head = B->head;
    A->size = B->size + A->size;

    return A;
}


=======
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
>>>>>>> cb204fdb9c8b1c2356ee5156ea3bc254dd0109c4

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

<<<<<<< HEAD

//STACK PLAYGROUND
int main(){

    struct Stack* S =  init_stack();
    struct Stack* C =  init_stack();

    print_stack(S);

    push(S ,1);
    push(S ,2);
    push(S ,3);
    push(S ,4);
    push(S ,5);


    push(C ,11);
    push(C ,10);
    push(C ,10);
    push(C ,10);
    push(C ,22);

    printf("stack S\n");
    print_stack(S);

    printf("stack C\n");
    print_stack(C);

    printf("stack S+C\n");
    S = concatinate(S, C);


    print_stack(S);

    // printf("%d\n", S->head->node_num);

    // printf("%d\n", S->tail->node_num);

    // printf("pop %d\n", pop(S));

    // printf("pop %d\n", pop(S));

    // printf("%d\n", S->head->node_num);

    // printf("%d\n", S->tail->node_num);

    return 0;
}
=======
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
>>>>>>> cb204fdb9c8b1c2356ee5156ea3bc254dd0109c4
