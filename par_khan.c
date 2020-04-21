#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Graph
{
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

	// return graph
	return graph;

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

	if((fp = fopen(file, "r")) != NULL) {
		struct Graph graph = get_matrix(fp);

		// print matrix
		for(int i = 0; i < graph.num_nodes; i++) {
			printf("%d \t", i);
			for(int j = 0; j < graph.num_nodes; j++) {
				printf("%d--", graph.matrix[i][j]);
			}
			printf("\n");
		}
		
		fclose(fp);
	} else {
		printf("the file you specified does not exist\n");
	}
}
