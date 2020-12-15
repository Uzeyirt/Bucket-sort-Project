#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include<stdbool.h>
float *A;

/* Üzeyir Topaloglu 2079424 */

bool is_suitible_for_bucketSort(float[],int);

void bucket_sortt (float[],float[],int);

int determine_bucket_number(float,float);

int partition(int p, int r)
{
	float x, tmp;
	int i,j;
	int randind;
	/*x = A[r];*/
	randind = p+rand()%(r-p+1);

	x = A[randind];

	/* put the pivot to the end */
	tmp = A[r];
	A[r] = A[randind];
	A[randind] = tmp;

	i = p-1;

	for (j=p;j<r;j++)
	{
		if (A[j]<=x)
		{
			i++;
			tmp = A[i];
			A[i] = A[j];
			A[j] = tmp;
		}
	}

	tmp = A[i+1];
	A[i+1] = A[r];
	A[r] = tmp;

	return i+1;
}

void quickSort(int p, int r)
{
	int q;

	if (p>=r) return;

	q = partition(p,r);

	quickSort(q+1,r);
	quickSort(p,q-1);
}

struct bucket 
{
	float value;
	struct bucket *next;
	
};
int main () 
{
	FILE *file_stream;

	file_stream = fopen("input.txt","r");

	int c=0;

	int array_size;
	
	float *unsorted_array;
	
	float *sorted_array;
	
	bool is_suitible;
	


	fscanf(file_stream,"%d\n",&array_size); // i take array size as an input (first integer in input file).
	
	unsorted_array = (float*) malloc(sizeof(float)*array_size); // i allocating memory for unsorted array according to array size.
	
	sorted_array = (float*) malloc(sizeof(float)*array_size);
	
	A = (float*) malloc(sizeof(float)*array_size);
	
	for (c=0; c<array_size; c++) //here , i am filling my unsorted array with float numbers. 
	
	{
		
		fscanf(file_stream,"%f\n",&unsorted_array[c]);
		
	}
	for (c=0; c<array_size; c++) 
	{
		A[c]=unsorted_array[c];		
	}

	/*	it is working without any error
		for (c=0; c<array_size; c++) 

	{
		
		printf("%f\n",unsorted_array[c]);
		
	}
*/
	
	is_suitible = is_suitible_for_bucketSort(unsorted_array,array_size);
	
	printf("Will we use bucket sort or quicksort (1:bucket,0:quick):%d\n",is_suitible);
	
	if (is_suitible==1) 
	{		
		bucket_sortt(unsorted_array,sorted_array,array_size);			
	}
	else if (is_suitible==0) 
	{
		
		quickSort(0,array_size-1);	
		for (c=0; c<array_size; c++) 
		{
			sorted_array[c] = A[c];		
		}
	}

	file_stream = fopen("output.txt","w"); 

	for (c=0; c<array_size; c++) 
	{
		fprintf(file_stream,"%f\n",sorted_array[c]);
	}
	
	
	fclose(file_stream);
	


	return 0;
}

void bucket_sortt (float u_l[],float s_l[],int array_size) //first argument is unsorted array ,second argument is sorted array(actually this function sorts it itself)
{ 

	int c=0,c1=0;
	
	struct bucket *Bucket;
	
	struct bucket *inserting_node;
	
	Bucket = (struct bucket*)malloc(sizeof(struct bucket)*array_size);
	
	float bucket_range = 1.00000000000000000000/array_size;
	
	for (c=0; c<array_size; c++) 
	{
				
		Bucket[c].next=NULL;
		
	}
	for (c=0; c<array_size; c++) 
	{

		int bucketno;
		bucketno = determine_bucket_number(u_l[c],bucket_range) - 1;

		if (Bucket[bucketno].next == NULL) //adding first element for a bucket
		{

			Bucket[bucketno].next =(struct bucket*)malloc(sizeof(struct bucket));
			Bucket[bucketno].next->value=u_l[c];
			Bucket[bucketno].next->next=NULL;			
		}
		else//inserting an element for a not empty bucket 
		{

			inserting_node = (struct bucket*)malloc(sizeof(struct bucket));
			inserting_node->value = u_l[c]; 
			struct bucket *temp;
			temp = &Bucket[bucketno];
			while ( ( temp->next->value < inserting_node->value ) && (temp->next!=NULL) ) 
			{
				
				temp=temp->next;	
				
			}
			if (temp->next!=NULL) 
			{
				inserting_node->next=temp->next;
				temp->next=inserting_node;
			}
			else 
			{
				temp->next=inserting_node;
				inserting_node->next=NULL;						
			}
		
		}
	}
	struct bucket *temp;
/*	for (c=0; c<array_size; c++) 
	{
	
		temp=&Bucket[c];
		while (temp->next!=NULL) 
		{
			printf ("%f -->",temp->next->value);
			temp=temp->next;
			
		}
		
	}*****it prints content of buckets*****
*/
    
	int c2=0;
	c=0;
	while (c<array_size) 
    {
    	while (Bucket[c2].next==NULL) 
		{
			c2++;
			
		}
		temp=&Bucket[c2];
		while (temp->next!=NULL) 
		{
			s_l[c] = temp->next->value;
			temp=temp->next;
			c++;
		}
		c2++;
    }
}



bool is_suitible_for_bucketSort(float array[],int a_size) 
{
	int c=0;
	int c1=0;

	int *numbers_in_buckets;

	numbers_in_buckets = (int*)malloc(sizeof(int));

	for (c=0; c<a_size; c++) 
	{
		numbers_in_buckets[c] = 0;              // i am making all integer in this array 0. This array will learn number of floats in each bucket
	}

	float bucket_range= 1.00000000000000/a_size;

	printf("bucket range is :%f\n",bucket_range);

	for (c=0; c<a_size; c++) //when this loop ends, we will have an array that shows each bucket has how many floating number.  
	{
		for (c1=1; c1<(a_size+1); c1++) 
		{
			
			if (array[c]<=c1*bucket_range) 
			{
				numbers_in_buckets[c1-1]++;
				break;
			}			
			
		}
	}
	for (c=0; c<a_size; c++) 
	{
	
		printf("Bucket %d : %d element(s)\n",c+1,numbers_in_buckets[c]);              // it is working wthout no error
	
	}		
	
	for (c=0; c<a_size; c++) //in this loop if any of them is greater than three,this function return false,Otherwise, it returns 1.
	{
		if (numbers_in_buckets[c] <= 3 ) 
		{
			
			continue;
			
		}
		else
		 {
		 	return false;	
		 }
			
	}
	return true;
	}
int determine_bucket_number(float number,float bucket_range) 
{
	
	int counter=1;
	while (number>counter*bucket_range) 
	{
		
		counter++;
		
	}
	return counter;
}
