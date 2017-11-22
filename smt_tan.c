#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/sysctl.h>
//#include <sys/vmmeter.h>
#include <math.h>
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
		
    		for(i=0;i<ram_size;i++)
		{
			printf("%d:%d\n",i,arr[i]);
	
		}
		


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

}
