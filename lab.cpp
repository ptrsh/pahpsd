#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char** argv)
{
    const long int count = 1500000000;     ///< Number of array elements
    const int seeds[] = {11047, 15583, 19997, 24019, 29927, 31231, 33427, 37607, 44053, 54419};
    const int attempts = 10;
    const int threads = 4;

    int* array = 0;                 ///< The array we need to find the max in
    int  max;                       ///< The maximal element
    int  operations = 0;

    /* Allocate memory */
    array = (int*)malloc(count*sizeof(int));
    
    double start_time, end_time, total;

    total = 0;
    for(int j=0; j < attempts; j++){
        srand(seeds[j]);
        max = -1;
        for(int i = 0; i < count; i++) { array[i] = rand(); }
        start_time = omp_get_wtime();
        #pragma omp parallel num_threads(threads) shared(array, count) reduction(max: max) default(none)
        {
            #pragma omp for
            for(int i = 0; i < count; i++){            
                if (array[i] > max){
                    max = array[i];
                } 
            }
        }
        end_time = omp_get_wtime();
        total += end_time - start_time;
    }
    printf("The program worked for %.2f seconds\n", total / (double)attempts);
    
    free(array);    
    return(0);
}