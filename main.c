#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define PI acos(-1.0)

typedef struct layernode {
	struct layer *curr;
	struct layernode *nextnode;
} layernode;


/* layers hold weights between them and previous layer*/
typedef struct layer {
	int size;
	int prevsize;
	float *nodes;
	float **weights;
	struct layer *next;
	struct layer *input;
} layer;

/* holds linked lists of layers, activations*/
typedef struct model {
	struct layernode* layers;
	int (**activs)(int);
} model;

float* normalinit(int size, float mu, float sigma);
float** normalweights(int prevsize, int currsize, float mu, float sigma);
layer* layerinit(char *inittype, int size, int prevsize);
void layerinfo(layer *l);

int main(int argc, char *argv[])
{
	layer *l1;
	l1 = layerinit("lol", 8, 16);
	layerinfo(l1);
	free(l1);
	return 0;
}

void layerinfo(layer *l)
{
	int i = 0;
	int j = 0;
	printf("Nodes: ");
	for(i=0;i<l->size;i++)
	{
		printf("%f, ", l->nodes[i]);
	}
	printf("\n");
	
	printf("Weights:\n");
	for(i=0;i<l->prevsize;i++)
	{
		printf("%d: ", i);
		for(j=0;j<l->size;j++)
		{
			printf("%f, ", l->weights[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

layer* layerinit(char *inittype, int size, int prevsize)
{
	layer *newlayer;
	newlayer = (layer*)calloc(1, sizeof(layer));
	newlayer->size = size;
	newlayer->prevsize = prevsize;
	newlayer->nodes = normalinit(size, 0, 1);
	newlayer->weights = normalweights(prevsize, size, 0, 1);
	return newlayer;
}

float** normalweights(int prevsize, int currsize, float mu, float sigma)
{
	int i = 0;
	float **newarr;
	/* prevsize rows */
	newarr = (float**)calloc(prevsize, sizeof(float*));
	/* currsize columns */
	for(i=0;i<prevsize;i++)
	{
		newarr[i] = normalinit(currsize, mu, sigma);
	}
	return newarr;
}

float* normalinit(int size, float mu, float sigma)
{
	float *newarr;
	int i;
	newarr = (float*)calloc(size, sizeof(float));	
	for(i=0;i<size;i++)
	{
		newarr[i] = sqrt(-2 * log((float)rand()/(float)(RAND_MAX))) * cos(2 * PI * (float)rand()/(float)(RAND_MAX)) * sigma + mu;
	}
	return newarr;
}

int dotprod(float *v1, float *v2, int len)
{
	int i=0;
	int sum=0;
	for(i=0;i<len;i++)
	{
		sum+=v1[i]*v2[i];
	}
	return sum;
}
