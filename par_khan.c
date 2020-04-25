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

//When an array is returned from a function the meta data of its size is lost(because of the holly pointers).
//Thats why i implemented a struct Array to hold the size data.
struct Array{
	int* array;
	int size;
};



//------- GLOBAL VARIABLES --------//
struct Graph graph;
struct Array* degree;
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

	// Here we return the graph struct that we loaded from the file. This is very important and not self explanetory, dont forget what we do here.
	return graph;

}

//Fills the degree array with the amount of incomming edges if each node a.k.a. degree.
struct Array* get_node_degree(struct Graph graph) {

	int set_degree[graph.num_nodes];

	for(int i = 0; i < graph.num_nodes; i++) {
		set_degree[i] = 0;
		for (int j = 0; j < graph.num_nodes; j++)
		{
			if(graph.matrix[j][i] == 1) {
				set_degree[i]++;
			}
		}
	}


	//Return an Array object and allocate space for the global degree.array array.
	struct Array* degree_array = (struct Array*) malloc(sizeof(set_degree));
	degree_array->array = malloc(sizeof(set_degree));
	//fill the new array
	for(int i = 0; i < graph.num_nodes; i++) {
		degree_array->array[i] = set_degree[i];
	}
	degree_array->size = graph.num_nodes;
	return degree_array;

}

//function that returns the nodes where the ouτ edges of requested node go.
//Take this simple graph for example Example: (2)->(7) , if we run the function on node 2 we will get an array [7,4] of size two.
//                                             └──>(4)
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
//This function is DEPRICATED
int get_num_of_in_edges_from_graph(struct Graph graph, int node){
	//nodes start from number one but matrix starts from 0,0
	node--;
	//compute number of IN edges
	int count_in_edges = 0;
	for(int i=0; i<graph.num_nodes; i++){
		if(graph.matrix[i][node]==1) count_in_edges++;
	}
	
	return count_in_edges;
}


//function that computes the degree of incoming edges of specified node
int get_num_of_in_edges(struct Array* degree, int node){
	//nodes start from number one but matrix starts from 0,0
	node--;
	return degree->array[node];
}


//S <- Set of all nodes with no incoming edge
void fill_S_stack(struct Array* array, struct Stack* stack){
	for(int i=1; i<graph.num_nodes+1; i++){
		if(get_num_of_in_edges(degree, i)==0){
			push( stack , i);
			//printf("PUSH");
		}
	}
}

//remove edge from n to m
//this function only works if the graph and degree are declared globally
void remove_edge(int n, int m){
	degree->array[m-1]--;
	graph.matrix[n-1][m-1] = 0;
}

//Checks if the graph has edges. 
bool graph_has_edges(struct Array* degree){
	for(int i = 0; i < degree->size; i++) {
		if(degree->array[i] > 0) return true;
	}
	return false;
}


//Print array
void print_int_array(int* array, int size){
	//printf("\nNumber of out edges: %d \n",size);
	for(int i=0; i<size;i++){
		printf("%d--", array[i]);
	}
	printf("\n");
}

//Print Matrix
void print_matrix(struct Graph graph){
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
			//remove edge e from the array and graph
			remove_edge(node_n, nodes_m.array[i]);
			//if m has no other incoming edges then
			if( get_num_of_in_edges(degree, nodes_m.array[i])==0){
				//insert m into S
				push(stack, nodes_m.array[i]);
			}
		} 
	}
	//if graph has edges then print "graph has at least one cycle"
	if(graph_has_edges(degree)==true){
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

	// file 
	FILE *fp;

	// check number of arguments
	if(argc == 2) {
		strcpy(file, argv[1]);
	}
	else {
		printf("Please type the path to the graph file\n");
		return 1;
	}	

	//if file does not exists
	if((fp = fopen(file, "r")) == NULL) {
		printf("The file you specified does not exist\n");
		return 1;
	}
		
		// create new graph
		graph = get_matrix(fp);
		// close file
		fclose(fp);



		print_matrix(graph);

		//Initialize the S Stack
		stack =  init_stack();
		//Initialize the L stack
		sorted  =  init_stack();

		//Fill the degree array with the amount of incomming edges if each node a.k.a. degree.
		degree = get_node_degree(graph);

		print_int_array(degree->array, degree->size);

		
		//Fill with all nodes with no incoming edge
		fill_S_stack(degree, stack);

		print_stack(stack);

		//Run the Glorious Algorithm
		kahn_algorithm();

		print_int_array(degree->array, degree->size);
		//print_matrix(graph);
		//print_matrix(graph);

		return 0;
}
