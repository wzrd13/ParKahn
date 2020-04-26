#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]){

FILE *fp;
char* str = "string";
int x = 10;

int N = atoi(argv[1]);

fp=fopen("./graphs/b_tree.mtx", "w");
if(fp == NULL)
    exit(-1);
fprintf(fp,"%d %d %d\n", N*2+1 ,N*2+1, N*2);
for(int i=1; i<=N; i++){
    fprintf(fp,"%d %d\n", i , i*2);
    fprintf(fp,"%d %d\n", i , i*2+1);
}
    fclose(fp);
    return 0;
}







