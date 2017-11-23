
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/sysctl.h>
//#include <sys/vmmeter.h>
#include <limits.h>
#include <math.h>

#define LCHILD(x) 2*x+1
#define RCHILD(x) 2*x+2
#define PARENT(x) (x-1)/2


typedef struct node {
    int data ;
    int index;
} node ;

typedef struct minHeap {
    int size ;
    node *elem ;
} minHeap ;


/*
    Function to initialize the min heap with size = 0
*/
minHeap initMinHeap(int size) {
    minHeap hp ;
    hp.size = 0 ;
    return hp ;
}


/*
    Function to swap data within two nodes of the min heap using pointers
*/
void swap(node *n1, node *n2) {
    node temp = *n1 ;
    *n1 = *n2 ;
    *n2 = temp ;
}




void heapify(minHeap *hp, int i) {
    int smallest = (LCHILD(i) < hp->size && hp->elem[LCHILD(i)].data < hp->elem[i].data) ? LCHILD(i) : i ;
    if(RCHILD(i) < hp->size && hp->elem[RCHILD(i)].data < hp->elem[smallest].data) {
        smallest = RCHILD(i) ;
    }
    if(smallest != i) {
        swap(&(hp->elem[i]), &(hp->elem[smallest])) ;
        heapify(hp, smallest) ;
    }
}


/* 
    Build a Min Heap given an array of numbers
    Instead of using insertNode() function n times for total complexity of O(nlogn),
    we can use the buildMinHeap() function to build the heap in O(n) time
*/
void buildMinHeap(minHeap *hp, int *arr, int size) {
    int i ;

    // Insertion into the heap without violating the shape property
    for(i = 0; i < size; i++) {
        if(hp->size) {
            hp->elem = realloc(hp->elem, (hp->size + 1) * sizeof(node)) ;
        } else {
            hp->elem = malloc(sizeof(node)) ;
        }
        node nd ;
        nd.data = arr[i] ;
        hp->elem[(hp->size)++] = nd ;
    }

    // Making sure that heap property is also satisfied
    for(i = (hp->size - 1) / 2; i >= 0; i--) {
        heapify(hp, i) ;
    }
}








void filegenerator(int size)
{
    FILE *f = fopen("input.txt","w");
int i;
for(i=0;i<size;i++)
    {
        int val = rand();
        fprintf(f,"%d ",val);
    }
    fclose(f);
}

double read_ram_size()
{
    FILE *f = fopen("Memory.txt","r");
    char buffer[255];
    fgets(buffer,sizeof(buffer),f);
    double ram_size = atof(buffer);
    //printf("%f\n",ram_size);
    return ram_size;
    fclose(f);	
   

}


void set_merge(int arr[],int a1_l,int a2_l, int i, int j, int k, int m, int n,int low,int mid, int high)
{
	
	int arr1[a1_l], arr2[a2_l];
	for(i = 0; i < a1_l; i++)
	{
		int temp1 =  low+i;
		arr1[i] = arr[temp1];

	}

	for(j = 0; j < a2_l; j++)
	{
		int temp2 = mid+1+j;
        	arr2[j] = arr[temp2];
	}
    
    while (m < a1_l && n < a2_l)
    {
        if (arr1[m] <= arr2[n])
	{
            arr[k] = arr1[m];
	    k+=1;
	    m+=1;
	}
        else
	{
            arr[k] = arr2[n];
	    n=n+1;
	    k=k+1;

	}
    }

    while (m < a1_l)
	{
        	arr[k] = arr1[m];
		k+=1;
		m+=1;
 	}
    while(n < a2_l)
	{
        arr[k] = arr2[n];
	k+=1;
	n+=1;
	}

}



void call_merge(int arr[], int low, int mid, int high)
{
    int i, j, k=low,m=0,n=0;
    int a1_l = mid - low + 1;
    int a2_l = high - mid;
    
    set_merge(arr,a1_l,a2_l,i,j,k,m,n,low,mid,high);
}
 


void merge_sort(int arr[], int low, int high)
{
	int mid;
    if (low < high)
    {
	int temp =  (high-low)/2;
        mid = low + temp;
        merge_sort(arr, low, mid);
        merge_sort(arr, mid + 1, high);
 
        call_merge(arr, low, mid, high);
    }
}
 








/*


*/


int no_chunks_to_be_created(double ram_size,double file_size)
{
    int chunks = (file_size/ram_size);
    return chunks;
}

void externalMergeSort(int chunks_create, int ram_size,struct stat st)
{
    
    FILE *f= fopen("input.txt","r");
    //printf("%d\n",ram_size);

	FILE *chunks[chunks_create];
    	char file_name[2];
	
	int more_input = 1;
	int counter=0;
	int* arr = (int*)malloc(ram_size*sizeof(int));
	fseek(f, 0, SEEK_SET);

	int i=0;
	int j;
	
	for(i=0;i<chunks_create;i++)
	{

		snprintf(file_name,sizeof(file_name),"%d",i);
		chunks[i] =  fopen(file_name,"w");
	
	}


	while(more_input)
	{
		for(i=0;i<ram_size;i++)
		{
			if(fscanf(f,"%d ",&arr[i])!=1)
			{
				more_input=0;
				break;
			}
		}

	   	merge_sort(arr, 0, i - 1);
		for(j=0;j<i;j++)
		{

			fprintf(chunks[counter],"%d ",arr[j]);
	
		}
		counter++;
	}
	for(i=0;i<chunks_create;i++)
	{

		fclose(chunks[i]);

	}
    free(arr);	
    fclose(f);
}


int find_index(int arr[],int l,int r,int x)
{
	if(r>=l)
	{
		int mid = l+(r-l)/2;
		if(arr[mid]==x)
		{
			return mid;
		}
	
		if(arr[mid]>x)
		{
			return find_index(arr,l,mid-1,x);

		}
		
		return find_index(arr,mid+1,r,x);

	}
return -1;
}

void  merge_files_created(int ways,int ram_size)
{
	FILE *output_file = fopen("output.txt","w");
	FILE *read_chunks[ways];
	char filename[2];
	int i=0;
	for(i=0;i<ways;i++)
	{
		snprintf(filename,sizeof(filename),"%d",i);
		//printf("%s",filename);
		read_chunks[i] = fopen(filename,"r");
	}

	// create new node .
	int* arr =(int *)malloc(ram_size*ways); 
	//node *myHeapNode= malloc(ways);
	minHeap hp = initMinHeap(0);
	for(i=0;i<ways;i++)
	{
		if(fscanf(read_chunks[i],"%d ",&arr[i])!=1)
			break;
		//hp.elem[i].index=i
		//hp.elem[i].index=i;
		//myHeapNode[i].index = i;
	}
	for(i=0;i<ways;i++)
	{
		printf("%d:%d\n",i,arr[i]);
	}
	
	buildMinHeap(&hp,arr,i);
	int sorted_array[ways];
	/*int count=0;
	int index;
	int data1;
	*/
	//fclose(output_file);
	//printf("%d\n",sizeof(hp));
	int index;
	int count=0;
	int temp=0;
	/*
	for(int j=0;j<ways;j++)
	{
		sorted_array[j]=hp.elem[j].data;
	}*/
	//int n = sizeof(sorted_array)/sizeof(sorted_array[0]);
	//printf("Length:%d\n",i);
	printf("Sorted_DATA:\n");
	while(count !=i)
	{
		int root = hp.elem[0].data ;
		printf("%d:%d\n",temp,root);
		fprintf(output_file,"%d ",root);
		for(int j=0;j<ways;j++)
	        {
                	sorted_array[j]=hp.elem[j].data;
        	}

		int n = sizeof(sorted_array)/sizeof(sorted_array[0]);

		index=find_index(sorted_array,0,n-1,root);
		//printf("%d\n",index);
		if(index!=-1)
		{
			if(fscanf(read_chunks[count],"%d ",&root)!=1)
			{

			root =INT_MAX;	
			count++;

			}

			//printf("Read_ROOT:%d\n",root);
			hp.elem[0].data = root;
			heapify(&hp,0);
			temp++;
		}
		else
		{
		break;
		}
	}//While Close.

	for(i=0;i<ways;i++)
	{
		fclose(read_chunks[i]);
	}
fclose(output_file);
//Merged All files.
}








int main()
{
    int size = 200* 1024;
    //Size of  file to be created is 200mb   
    struct stat st;
    //stat("input.txt",&st);
    //double file_size = st.st_size;
    //printf("%llu\n",st.st_size);
    //printf("%f\n",file_size);
    double ram_size = 20000;

    int chunks_create =  no_chunks_to_be_created(ram_size,size);
    printf("%d\n",chunks_create);
    filegenerator(ram_size*chunks_create);
    externalMergeSort(chunks_create,ram_size, st);
    merge_files_created(chunks_create,ram_size);
}
