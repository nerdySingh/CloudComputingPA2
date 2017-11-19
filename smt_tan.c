#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <sys/vmmeter.h>
#include <math.h>
void filegenerator(int size)
{
    FILE *f = fopen("input.txt","w");
    for(int i=0;i<size;i++)
    {
        int val = rand();
        fprintf(f,"%d\n",val);
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

int no_chunks_to_be_created(int ram_size,int file_size)
{
    int chunks = ceil(file_size/ram_size)+1;
    return chunks;
}

void externalMergeSort(int chunks_creat, int ram_size,struct stat st)
{
    
    FILE *f= fopen("input.txt","r");
    //printf("%d\n",ram_size);
    printf("%lld\n",st.st_size);
    ram_size = ram_size *(1024*1024);
    printf("%lld\n",ram_size);
    
    char *buffer =malloc(ram_size);
    
    fgets(buffer,ram_size,f);
    printf("Buffer:%lu\n",strlen(buffer));
    
    free(buffer);
    fclose(f);
    
}



int main()
{
    int size = 8*200 * 1024 *1024;
    //Size of  file to be created is 200mb
    //filegenerator(size);
    struct stat st;
    stat("input.txt",&st);
    double file_size = st.st_size/(1000*1000);
    //printf("%llu\n",st.st_size);
    //printf("%f\n",file_size);
    double ram_size = read_ram_size();  

    int chunks_create =  no_chunks_to_be_created(ram_size,file_size);
    printf("%d\n",chunks_create);
    externalMergeSort(chunks_create,ram_size, st);
    
}