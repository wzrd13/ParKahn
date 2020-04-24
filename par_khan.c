#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stack.h"

struct Graph
{
	int num_nodes;
	int num_edges;
	int **matrix;
};

//when an array is returned from a function the meta data of its size is lost(because of the holly pointers).
//Thats why i implemented a struct Array to hold the size data.
struct Array{
	int* array;
	int size;
};



//------- GLOBAL VARIABLES --------//
struct Graph graph;
struct Stack* stack;
struct Stack* sorted;
//--------------------------------//



 struct Graph get_matrix(FILE *fp) {
	
	// create graph struct
	struct Graph graph;

	// vars for holding rows and cols
	int value1;
	int value2;

	// get number of nodes and edges
	fscanf(fp, "%*d %d %d", &graph.num_nodes, &graph.num_edges);
	printf("%d %d\n", graph.num_nodes, graph.num_edges);

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

	// Here we return the graph struct that we loaded from the file. This is very important and not self explanetory, dont forget what we do here.
	return graph;

}

void get_node_degree(struct Graph graph) {

	int degree[graph.num_nodes];

	for(int i = 0; i < graph.num_nodes; i++) {
		degree[i] = 0;
		for (int j = 0; j < graph.num_nodes; j++)
		{
			if(graph.matrix[j][i] == 1) {
				degree[i]++;
			}
		}
	}

	for (int i = 0; i < graph.num_nodes; ++i)
	{
		printf("degree of node %d: \t %d\n", i+1, degree[i]);
	}
}

//function that returns the nodes where the ouτ edges of requested node go.
//Take this simple graph for example Example: (2)->(7) , if we run the function on node 2 we will get an array [7,4] of size two.
//											   └──>(4)
struct Array get_out_edges(struct Graph graph, int node){
	//nodes start from number one but matrix starts from 0,0
	node--;
	//compute number of OUT edges
	int count_out_edges = 0;
	for(int i=0; i<graph.num_nodes; i++){
		if(graph.matrix[node][i]==1) count_out_edges++;
	}
	//create array of out edges
	//The reason the Array struct was created is explained above.
	struct Array* array = malloc(sizeof(struct Array));
	array->array = malloc(sizeof(int)*count_out_edges);
	array->size = count_out_edges; 
	int index = 0;
	for(int i=0; i<graph.num_nodes; i++){
		if(graph.matrix[node][i]==1){
			array->array[index] = i+1;
			index++;
		}
	}
	return *array;
}

//function that computes the degree of incoming edges of specified node
int get_num_of_in_edges(struct Graph graph, int node){
	//nodes start from number one but matrix starts from 0,0
	node--;
	//compute number of IN edges
	int count_in_edges = 0;
	for(int i=0; i<graph.num_nodes; i++){
		if(graph.matrix[i][node]==1) count_in_edges++;
	}
	
	return count_in_edges;
}

//S <- Set of all nodes with no incoming edge
void fill_S_stack(struct Graph graph, struct Stack* stack){
	for(int i=1; i<graph.num_nodes+1; i++){
		if(get_num_of_in_edges(graph, i)==0){
			push( stack , i);
			//printf("PUSH");
		}
	}
}

//remove edge from n to m
void remove_edge(int n, int m){
	graph.matrix[n-1][m-1] = 0;
}

//Checks if the graph has edges. (checks if every cell is 0)
bool graph_has_edges(struct Graph graph){
	for(int i = 0; i < graph.num_nodes; i++) {
		for (int j = 0; j < graph.num_nodes; j++){
			if(graph.matrix[j][i] == 1) return true;
		}
	}
	return false;
}


//Print array
void print_int_array(int* array, int size){
	printf("\nNumber of out edges: %d \n",size);
	for(int i=0; i<size;i++){
		printf("%d--", array[i]);
	}
	printf("\n");
}

//Print Matrix
void print_matrix(struct Graph graph){

		 for(int i = 0; i < graph.num_nodes; i++) {
			
			printf("%d \t", i+1);
	 	for(int j = 0; j < graph.num_nodes; j++) {
				
		 		printf("%d--", graph.matrix[i][j]);
		 	}

		 	printf("\n");
		 }
}


void kahn_algorithm(){
	//while S is not empty do
	while(is_empty(stack)==false){
		//remove a node n from S
		int node_n =  return_and_remove_head(stack);
		//add n to tail of L
		push(sorted, node_n);
		//for each node m with an edge e from n to m do
		struct Array nodes_m = get_out_edges(graph, node_n);
		//print_int_array(nodes_m.array, nodes_m.size);
		for(int i=0; i<nodes_m.size; i++){
			//remove edge e from the graph
			remove_edge( node_n, nodes_m.array[i]);
			//if m has no other incoming edges then
			if( get_num_of_in_edges(graph, nodes_m.array[i])==0){
				//insert m into S
				push(stack, nodes_m.array[i]);
			}
		} 
	}
	//if graph has edges then print "graph has at least one cycle"
	if(graph_has_edges(graph)==true){
		printf("\nGraph has at least one cycle\n");
	}
	else{
		printf("\nThe following is in a topologically sorted order (printed inverted for the moment LOL)\n");
		print_stack(sorted);
	}

}




int main(int argc, char *argv[]) {
	
	// file name
	char file[20];

	// file 
	FILE *fp;

	// check number of arguments
	if(argc == 2) {
		strcpy(file, argv[1]);
	}
	else {
		printf("please type the path to the graph file\n");
		return 1;
	}	

	//if file does not exists
	if((fp = fopen(file, "r")) == NULL) {
		printf("the file you specified does not exist\n");
		return 1;
	}
		
		// create new graph
		graph = get_matrix(fp);
		// close file
		fclose(fp);


		//get_node_degree(graph);

		print_matrix(graph);

		//Initialize the S Stack
		stack =  init_stack();
		//Initialize the L stack
		sorted  =  init_stack();
		
		//Fill with all nodes with no incoming edge
		fill_S_stack(graph, stack);

		print_stack(stack);

		//Run the Glorious Algorithm
		kahn_algorithm();


		//print_matrix(graph);

		return 0;
}
