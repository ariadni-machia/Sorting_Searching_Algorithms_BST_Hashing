#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int n = 100000;

int main()
{
	int c, d, swap;
	float cb=0;
	clock_t time;
	double bstime;  
  
  	char line[10];
	int i=0;
	FILE *fptr; 
	// Open file for reading 
	fptr = fopen ("integers.txt", "r"); //C:\\Users\\Ariadni\\Desktop\\integers.txt
	if (fptr == NULL) 
	{ 
	    fprintf(stderr, "\nError opening file\n"); 
	    return -1; 
	} 
	int *array = malloc(sizeof(int)*n); 	// n= total
	
	for(i=0;i<n;i++){
		fgets(line,10,fptr);
		array[i]=atoi(line);
		//printf("%d) %d\n", i, list[i]); //check   
	}

	time= clock(); // begin time
	printf("The progress for %d elements has started.\nPlease wait :) \n..........\n", n);
	
  for (c = 0 ; c < ( n - 1 ); c++)
  {
    for (d = 0 ; d < n - c - 1; d++)
    {
      if (array[d] > array[d+1]) /* For decreasing order use < */
      {
        swap       = array[d];
        array[d]   = array[d+1];
        array[d+1] = swap;
        cb++;
      }
    }
  }
  time= clock()-time;
  printf("The measurement of Bubble Sort has been completed.\n..........\n");
	bstime = ((double)time)/CLOCKS_PER_SEC; // end time
  printf("Bubble Sort Counter= %f\n", cb);
  printf("----- TIMES (Seconds) -----\nBubble Sort= %lf\n", bstime);

/*
  printf("Sorted list in ascending order:\n");

  for ( c = 0 ; c < n ; c++ )
     printf("%d\n", array[c]);
*/
	free(array);
  return 0;
}
