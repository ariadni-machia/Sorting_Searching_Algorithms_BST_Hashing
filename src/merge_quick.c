#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<conio.h>

void Quick_sort (int list[] , int first , int last);
void part(int list[],int min,int max);
void merge(int list[],int min,int mid,int max);

const int n=100000;
int main()
{
    
    int i=0;
    clock_t time,timeQ,timeM;
    double Qstime,Mstime;

    FILE *fptr;
    fptr = fopen ("integers.txt", "r");
    if (fptr == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        return -1;
    }
    int* list=(int*) malloc(n*sizeof(int)); 
   for(i=0;i<n;i++){
        fscanf(fptr, "%d\n", &list[i]);
	}
	
    time = clock(); printf("time=%ld\t",time);
    Quick_sort(list,0,n-1);
    timeQ = clock();
    printf("timeQ=%ld\n",timeQ);

    
    printf("QS(time needed for sorting with Quick sort): %ld\n", timeQ-time);
    Qstime = (double)(timeQ-time)/CLOCKS_PER_SEC;
    
	free(list);
    list=(int*) malloc(n*sizeof(int));
    for(i=0;i<n;i++){
        fscanf(fptr, "%d", &list[i]);
	}
    
    time = clock(); printf("time=%ld\t",time);
    part(list,0,n-1);
    timeM = clock();
	printf("timeM=%ld\n",timeM);  
	
	
    printf("MS(time needed for sorting with Merge sort): %ld\n", timeM-time);
    Mstime = (double)(timeM-time)/CLOCKS_PER_SEC;
    printf("__TIME__\nQstime=%f\nMtime=%f",Qstime,Mstime);
    free(list);
    return 0;
}

void part(int list[],int min,int max) {
 int mid;
  if(min<max) {
    mid=(min+max)/2;
    part(list,min,mid);
    part(list,mid+1,max);
    merge(list,min,mid,max);
  }
}

void merge(int list[],int min,int mid,int max) {
  int i,j,k,m;
  int tmp[n];
  j=min;
  m=mid+1;

    for(i=min; j<=mid && m<=max ; i++) {
        if(list[j]<=list[m]) {
            tmp[i]=list[j];
            j++;
        }

        else {
            tmp[i]=list[m];
            m++;
        }
     }

	if(j>mid) {
	    for(k=m; k<=max; k++) {
               tmp[i]=list[k];
               i++;
        }
    }

    else {
     	for(k=j; k<=mid; k++) {
            tmp[i]=list[k];
            i++;
        }
    }

 	 for(k=min; k<=max; k++) {
     		list[k]=tmp[k];
     }
}

void Quick_sort (int list[] , int first , int last) {

    int pivot,j,temp,i;

    if(first<last) {

        pivot=first;
        i=first;
        j=last;

        while(i<j) {
            while(list[i]<=list[pivot]&&i<last)
                i++;
                while(list[j]>list[pivot])
                    j--;

                    if(i<j) {
                        temp=list[i];
                        list[i]=list[j];
                        list[j]=temp;
                    }
        }

            temp=list[pivot];
            list[pivot]=list[j];
            list[j]=temp;

            Quick_sort(list,first,j-1);
            Quick_sort(list,j+1,last);

    }
}
