#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <omp.h>
#include <sys/time.h>
#include <time.h>
#include "stack.h"

//------- GLOBAL VARIABLES --------//
struct Graph graph;
struct Stack* stack;
struct Stack* sorted;
//--------------------------------//


struct Graph {
	int num_nodes;
	int num_edges;
	int **matrix;
};

struct Graph get_matrix(FILE *fp) {
	
	// create graph struct
	struct Graph graph;

	// vars for holding rows and cols
	int value1;
	int value2;

	// get number of nodes and edges
	fscanf(fp, "%*d %d %d", &graph.num_nodes, &graph.num_edges);
	//printf("%d %d\n", graph.num_nodes, graph.num_edges);

	// allocate memory for matrix 2d array
	graph.matrix = (int **)malloc(graph.num_nodes * sizeof(int *)); 
    for (int i=0; i<graph.num_nodes; i++) 
         graph.matrix[i] = (int *)malloc(graph.num_nodes * sizeof(int));

     // intialize matrix array with 0;
	for(int i = 0; i < graph.num_nodes; i++) {
		for(int j = 0; j < graph.num_nodes; j++) {
			graph.matrix[i][j] = 0;
		}
	}

	// fill matrix
	while(fscanf(fp, "%d %d", &value1, &value2) != EOF) {
		graph.matrix[value1-1][value2-1] = 1;
	}

	return graph;
}

// check
int* set_node_degree(struct Graph graph) {

	int *degree = malloc(sizeof(int)*graph.num_nodes);

	for(int i = 0; i < graph.num_nodes; i++) {
		degree[i] = 0;
		for (int j = 0; j < graph.num_nodes; j++)
		{
			if(graph.matrix[j][i] == 1) {
				degree[i]++;
			}
		}
	}
	return degree;	
}

//Checks if the graph has edges. 
bool graph_has_edges(int* degree, struct Graph graph) {
	for(int i = 0; i < graph.num_nodes; i++) {
		if(degree[i] > 0) { 
			return true;
		}
	}
	return false;
}

//Print Matrix
void print_matrix(struct Graph graph) {
		printf("%-3c", 'X');
		for(int i = 0; i < graph.num_nodes; i++) {
			printf("%3d", i+1);
		}
		printf("\n\n");

		 for(int i = 0; i < graph.num_nodes; i++) {
			
			printf("%-3d", i+1);
			for(int j = 0; j < graph.num_nodes; j++) {
					
					//COLOURS!!! XD
					if(graph.matrix[i][j]==0) printf("%3d", graph.matrix[i][j]);
					else printf("\033[0;32m%3d\033[0m", graph.matrix[i][j]);
					
				}

		 	printf("\n");
		 }
}


unsigned long get_time() {
        struct timeval tv;
        gettimeofday(&tv, NULL);
        unsigned long ret = tv.tv_usec;
        ret /= 1000;
        ret += (tv.tv_sec * 1000);
        return ret;
}


void kahn_algorithm() {
	
	// Initialize node degrees
	int *degree = set_node_degree(graph);


	// Initialize S
	for (int i = 0; i < graph.num_nodes; ++i)
	{
		if (degree[i] == 0)
		{
			push(stack , i);
			printf("PUSH: %d\n", i+1);
		}		
	}

	//while S is not empty
	while(is_empty(stack) == false){
		
		//remove a node n from S
		int node_n =  return_and_remove_head(stack);		
		//add n to tail of L								
		push(sorted, node_n);
		
		//for each node m with an edge e from n to m do
		for(int i = 0; i < graph.num_nodes; i++){
			if(graph.matrix[node_n][i] == 1){
				graph.matrix[node_n][i] = 0;
				degree[i]--;

				if(degree[i] == 0) {
					push(stack, i);
				}
			}
		}    
	}
	
	//if graph has edges then print "graph has at least one cycle"
	if(graph_has_edges(degree, graph) == true){
		red();
		printf("\nGraph has at least one cycle\n");
		reset();
	}
	else{
		green();
		printf("\nThe following is in a topologically sorted order.\n");
		reset();
		print_stack_bot_to_top(sorted);
	}
}


int main(int argc, char *argv[]) {
	
	// file name
	char file[20];

	// File 
	FILE *fp;

	// Check number of arguments
	if(argc == 2) {
		strcpy(file, argv[1]);
	}
	else {
		printf("Please type the path to the graph file\n");
		return 1;
	}	

	// If file does not exists
	if((fp = fopen(file, "r")) == NULL) {
		printf("The file you specified does not exist\n");
		return 1;
	}
		
	// Create new graph
	graph = get_matrix(fp);
		
	// Close file
	fclose(fp);

	// Initialize the S Stack
	stack =  init_stack();
	// Initialize the L stack
	sorted  =  init_stack();

	//Run the Glorious Algorithm
	kahn_algorithm();


	// long end =  get_time() - start;
	// yellow();
	// printf("\nTime: %ld \n", end);
	// reset();

	return 0;
}
