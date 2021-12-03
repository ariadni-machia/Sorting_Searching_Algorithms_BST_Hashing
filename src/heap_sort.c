#include<stdio.h>
#include <stdlib.h>
#include<conio.h>
#include <time.h>

void heapSort(int array[],int n);
void adjustHeap(int, int, int array[]);

int main() {

    int i,n=100000;
    int *arr_sort;
    char line[10];
    arr_sort = (int*) malloc(n*sizeof(int));

    clock_t time;
    double HStime;

    FILE *fptr;
    fptr = fopen("integers.txt","r");

    if (fptr == NULL){
        fprintf(stderr, "\n An Error occurred while opening the file \n");
        return -1;
    }
    for(i=0;i<n;i++){
		fgets(line,10,fptr);
		arr_sort[i]=atoi(line);
		//printf("%d) %d\n", i, HSlist[i]); //check
	}

    printf("The process for the HeapSort of %d numbers has started...\n", n);
    time = clock();
    heapSort(arr_sort,n);
    time = clock() - time;
    printf("The time needed for the HeapSort is: %d\n", time);
    HStime = ((double)time)/CLOCKS_PER_SEC;
	printf("The time measurement of the HeapSort has been completed. %lf\n",HStime);
  	fclose(fptr);
  	return 0;
}

void heapSort(int array[],int n) {
    int a;
    int i;
    for (i = n / 2 - 1; i >= 0; i--)
        adjustHeap(n, i, array);

    for (i = n - 1; i >= 0; i--) {
        int tmp;
    //Swapping Values
    tmp = array[0];
    array[0] = array[i];
    array[i] = tmp;
    adjustHeap(i, 0,array);
  }
}

void adjustHeap(int n, int i, int *array) {
  int tmp;
  int large = i, left = 2 * i + 1, right = 2 * i + 2;

  // adjest left child
  if (left < n && array[left] > array[large])
    large = left;

  // adjest right child
  if (right < n && array[right] > array[large])
    large = right;


  if (large != i) {
    //Swapping Values
    tmp = array[i];
    array[i] = array[large];
    array[large] = tmp;
    adjustHeap(n, large,array);
  }
}
