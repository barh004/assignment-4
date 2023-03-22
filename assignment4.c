#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

void merge(int pData[], int l, int m, int r)
{
    int a = 0;
    int b = 0;
    int c = l;

    int num = m - l + 1;
    int num2 = r - m;

    int *L = (int *) malloc(num * sizeof(int));
    int *R = (int *) malloc(num2 * sizeof(int));

    extraMemoryAllocated= (num * sizeof(int)) + (num2 * sizeof(int));

    for (a = 0; a < num; a++)
        L[a] = pData[l + a];
    for (b = 0; b < num2; b++)
    {
        R[b] = pData[m + 1+ b];
    }

    a = 0;
    b = 0;
    
    while(a < num && b < num2)
    {
        if (L[a] <= R[b])
        {
            pData[c] = L[a];
            a++;
        }
        else
        {
            pData[c] = R[b];
            b++;
        }
        c++;
    }

    while( a < num)
    {
        pData[c] = L[a];
        a++;
        c++;
    }
    while( b < num2)
    {
        pData[c] = R[b];
        b++;
        c++;
    }


    free(L);
    free(R);

}

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r)
{
    if( l < r)
    {
        int m = (l + r) / 2;

        mergeSort(pData, l, m);
        mergeSort(pData, m +1, r);

        merge(pData, l, m, r);
    }

}

// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n)
{
    int y;
	for(int x = 1; x < n; x++){
        int tmp = pData[x];

        for(y = x -1; y >= 0; y--){
            if(pData[y] > tmp)
                pData[y+1]= pData[y];
            else
                break;

        }
        pData[y+1] = tmp;
    }
}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n)
{
    int tmp;
    int y;
    int x;

    for(x = 0; x < n-1; x++)
    {
        for(y= 0; y < n-x-1; y++)
        {
            if(pData[y] > pData[y+1])
            {
                tmp = pData[y];
                pData[y] = pData[y+1];
                pData[y+1] = tmp;

            }
        }
    }

	
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n)
{
    int tmp; 
    int min;
    int x;
    int y;
    for(x = 0; x < n - 1; x++)
    {
        min = x;
        for(y = x + 1; y < n; y++)
            if(pData[y]<pData[min])
                min = y;
        tmp = pData[x];
        pData[x] = pData[min];
        pData[min] = tmp;
    }
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{

	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
        for(int i = 0; i < dataSz; i++)
        {
            fscanf(inFile, "%d", &((*ppData)[i]));
        }
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};
	
	for (i=0;i<3;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n"); 
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 2; // change this?
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}