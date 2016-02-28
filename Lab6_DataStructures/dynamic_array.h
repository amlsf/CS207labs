
typedef struct DArray {
    int upto; /*keep track of how many elements*/
    int size;
    int *array; /*actual memory allocated*/
} DArray;

/* here is the interface */
int DArray_init(DArray* arr);
int append(DArray* arr, int i);
int get(DArray* arr, int index); // get a[52]
int get_index(DArray* arr, int value); // corresponds to .index
int set(DArray* arr, int index, int value); //setter a[52] = x
int delete(DArray* arr, int value);
void DArray_free(DArray* arr); // free all the memory