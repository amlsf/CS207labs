
#include <stdlib.h>
#include <string.h>
#include "dynamic_array.h"

int CAPACITY_INIT = 1;
int GROWTH_FACTOR = 2;

// TODO has to  be an array of ints? Can this generalize to int of other types?
int DArray_init(DArray* arr){
    arr->array = (int *) malloc(CAPACITY_INIT*sizeof(int));
    if (arr->array == NULL) {
        return -1;
    }
    arr->upto = 0;
    arr->size = CAPACITY_INIT;
    return 1;
}

int append(DArray* arr, int i){
    int *iptr;
    // TODO what is this doing: it's pulling referencing the attribute of the array
    if (arr->upto >= arr->size) {
        /* tmp pointer needed below as if allocation failed, original array would be lost */
        iptr = (int *) realloc(arr->array, arr->size*GROWTH_FACTOR*sizeof(int));
        if (iptr == NULL) {
            return -1;
        }
        
        // TODO what is this doing? allocating the new space into the array
        arr->array = iptr;
        arr->size *= GROWTH_FACTOR;
    }
    // TODO what is this doing? This is putting the element into the array at the last place
    arr->array[arr->upto] = i;
    //TODO why is this not setting upto one up, just returning it? 
    return arr->upto++;        
}

int get(DArray* arr, int index) {
    if (index >= arr->upto || index < 0) {
        return -1;
    }
    return arr->array[index];
}

int get_index(DArray* arr, int value) {
    int i;
    for (i=0; i< arr->upto; i++){
        if (arr->array[i]==value) {
            return i;
        }
    }
    return -1;
}

void DArray_free(DArray *arr) {
  free(arr->array);
}

/*your code here */

int set(DArray* arr, int index, int value){
    if (index >= arr->upto || index < 0){
        return -1;
    }
    arr->array[index] = value;
    
    // What int do I need to return? 
    return 0;
}

/* Delete the first element that matches the value in the list and shift the remaining array over */
int delete(DArray* arr, int value){
    for (int i = 0; i < arr->upto; i++){
        if (arr->array[i] == value){
            // shift everything after it over
            for (int j = i; j < arr->upto - 1; j++){
                arr->array[j] = arr->array[j+1];
                // TODO can I ignore the last item or should I clear it somehow?
            }
            // set the new length of array to be one less than before
            return arr->upto--;
        }
    }
    // TODO do I need to return something? Warn them no value matches? 
    return -1; 
}