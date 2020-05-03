#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <omp.h>
#include <sys/time.h>
#include <time.h>
#include "stack.h"

//------- GLOBAL VARIABLES --------//
struct Graph graph;
struct Stack* S;
struct Stack* L;
//--------------------------------//


struct Graph {
	int num_nodes;
	int num_edges;
	int **matrix;
};

struct Graph get_matrix(FILE *fp) {
	
	// Create graph struct
	struct Graph graph;

	// Vars for holding rows and cols
	int value1;
	int value2;

	// Get number of nodes and edges
	fscanf(fp, "%*d %d %d", &graph.num_nodes, &graph.num_edges);
	//printf("%d %d\n", graph.num_nodes, graph.num_edges);

	// Allocate memory for matrix 2d array
	graph.matrix = (int **)malloc(graph.num_nodes * sizeof(int *)); 
    for (int i=0; i<graph.num_nodes; i++) 
         graph.matrix[i] = (int *)malloc(graph.num_nodes * sizeof(int));

    // Intialize matrix array with 0;
	for(int i = 0; i < graph.num_nodes; i++) {
		for(int j = 0; j < graph.num_nodes; j++) {
			graph.matrix[i][j] = 0;
		}
	}

	// Fill matrix
	while(fscanf(fp, "%d %d", &value1, &value2) != EOF) {
		graph.matrix[value1-1][value2-1] = 1;
	}

	return graph;
}

// Check
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

bool kahn_algorithm() {
	
	double start, end;
	
	// Initialize node degrees
	int *degree = set_node_degree(graph);


	// Initialize S
	for (int i = 0; i < graph.num_nodes; ++i) {
		if (degree[i] == 0)
		{
			push(S , i);
		}		
	}

	// Time only the parallel region for testing
	start = clock();

	//while S is not empty
	while(is_empty(S)==false){
		//remove a node n from S
		int node_n =  pop(S);

		//add n to tail of L
		push(L, node_n);	
				
		//for each i with an edge e from n to i do
		for(int i = 0; i < graph.num_nodes; i++){
			if(graph.matrix[node_n][i] == 1){

				degree[i]--;

				if(degree[i] == 0) {	
					push(S, i);	
				}
						
			}
		}


	}

	end = clock();

	printf("Time elapsed: %f\n", (double)(end-start)/CLOCKS_PER_SEC);
	
	// Check if graph has remaining edges 
	for(int i = 0; i < graph.num_nodes; i++) {
		if(degree[i] > 0) { 
			return false;

		}
	}
	return true;
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
		printf("\nPlease type the path to the graph file\n");
		return 1;
	}	

	// If file does not exists
	if((fp = fopen(file, "r")) == NULL) {
		printf("\nThe file you specified does not exist\n");
		return 1;
	}
		
	// Create new graph
	graph = get_matrix(fp);
		
	// Close file
	fclose(fp);

	// Initialize the S Stack
	S =  init_stack();
	// Initialize the L S
	L  =  init_stack();

	//Run the Glorious Algorithm
	if (kahn_algorithm() == false) {
		red();
		printf("Graph has at least one cycle\n");
		reset();
		//print_stack_bot_to_top(L);
		exit(0);
	}
	else {
		green();
		printf("The following is in a topologically correct order.\n");
		reset();
		//print_stack_bot_to_top(L);
	}

	return 0;
}
