#include <stdio.h>
#define LENGTH 15

void insertSort(int * arr, int length) {
        int i,j;
        int tmp;
        for (i=1; i< length; i++) {
                        tmp = arr[i];
                        for(j=i-1; j>=0 && tmp > arr[j]; j--) {
                                arr[j+1] = arr[j];
                        }
                        arr[j+1] = tmp;
        }
}
void printfArr(int *arr, int length) {
        int i;
        for (i=0; i<length; i++) {
                printf("%d_", arr[i]);
        }
        printf("\n");
}
int main() {
        int arr[] = {4,5,23,34,6,77,8,8,9,9,0,0,56565,6,6767};
        insertSort(arr, LENGTH);
        printfArr(arr, LENGTH);
}
