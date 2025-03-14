#include <bits/stdc++.h>
using namespace std;

void gen(int *array1, int size){
    for(int i=0; i<size; i++){
        array1[i] = rand();
        //make sure two arrays are identical
    }
}

void max_heapify(int *array1, int i, int size){
    int l = i*2 + 1;
    int r = i*2 + 2;
    int largest = i;
    if(l < size){
        if(array1[l] > array1[i]){
            largest = l;
        }
    }
    if(r < size){
        if(array1[r] > array1[largest]){
            largest = r;
        }
    }
    if(largest != i){
        int temp = array1[largest];
        array1[largest] = array1[i];
        array1[i] = temp;
        max_heapify(array1, largest, size);
    }
}

void build_max_heap(int *array1, int size){
    for(int i = (size/2)-1; i>=0; i--){
        max_heapify(array1, i, size);
    }
}

void heap_sort(int *array1, int size){
    build_max_heap(array1, size);
    for(int i=size-1; i>0; i--){
        int temp = array1[0];
        array1[0] = array1[i];
        array1[i] = temp;
        size--;
        max_heapify(array1, 0, size);
    }
}

int main()
{
    // srand(time(NULL)); // seed random number generator
    srand(time(NULL));
    int size;
    cout << "Please enter the size of the array: ";
    cin >> size;
    int * array = new int[size];
    gen(array, size);

    double heap_time, heap_time1, heap_time2;
    heap_time1 = (double)clock()/CLOCKS_PER_SEC;
    heap_sort(array, size);
    heap_time2 = (double)clock()/CLOCKS_PER_SEC;
    heap_time = heap_time2 - heap_time1;
    // for (int i = 0; i < size; i++){
    //     cout << array[i] << " ";
    // }
    // cout << endl;
    cout << "heap time: " << heap_time << endl;
    return 0;
}