#include <bits/stdc++.h>
using namespace std;

void gen(int *array1, int *array2, int size){
    for(int i=0; i<size; i++){
        array1[i] = rand();
        array2[i] = array1[i];
        //make sure two arrays are identical
    }
}

void insertion_sort(int *a, int size){
    for(int i=1; i<size; i++){
        int key = a[i];
        int j = i-1;
        while(j>=0 && a[j]>key){
            a[j+1] = a[j];
            j--;
        }
        a[j+1] = key;
    }
}

void merge(int *a, int p, int q, int r){
    int i, j, k;
    int n1 = q-p+1;
    int n2 = r-q;
    // int L[n1], R[n2];
    int * L = new int[n1];
    int * R = new int[n2];
    for(i=0; i<n1; i++){
        L[i] = a[p+i];
    }
    for(j=0; j<n2; j++){
        R[j] = a[q+1+j];
    }
    i = 0;
    j = 0;
    k = p;
    while(i<n1 && j<n2){
        if(L[i] <= R[j]){
            a[k] = L[i];
            i++;
        }
        else{
            a[k] = R[j];
            j++;
        }
        k++;
    }
    while(i<n1){
        a[k] = L[i];
        i++;
        k++;
    }
    while(j<n2){
        a[k] = R[j];
        j++;
        k++;
    }
}

void merge_sort(int *a, int p, int r){
    int q;
    if (p>=r) return;
    q = (p+r)/2;
    merge_sort(a, p, q);
    merge_sort(a, q+1, r);
    merge(a, p, q, r);
}

int main()
{
    // srand(time(NULL)); // seed random number generator
    srand(time(NULL));
    int size;
    cout << "Please enter the size of the array: ";
    cin >> size;
    int * array_ins = new int[size];
    int * array_mer = new int[size];
    // cout << "before gen";
    gen(array_ins, array_mer ,size);
    // cout << "after gen";
    // for (int i = 0; i < size; i++){
    //     cout << array_ins[i] << " ";
    // }
    // cout << endl;
    // for (int i = 0; i < size; i++){
    //     cout << array_mer[i] << " ";
    // }
    // cout << endl;
    double insert_time, insert_time1, insert_time2, merge_time, merge_time1, merge_time2;
    insert_time1 = (double)clock()/CLOCKS_PER_SEC;
    insertion_sort(array_ins, size);
    insert_time2 = (double)clock()/CLOCKS_PER_SEC;
    insert_time = insert_time2 - insert_time1;
    // for (int i = 0; i < size; i++){
    //     cout << array_ins[i] << " ";
    // }
    // cout << endl;
    merge_time1 = (double)clock()/CLOCKS_PER_SEC;
    merge_sort(array_mer, 0, size-1);
    merge_time2 = (double)clock()/CLOCKS_PER_SEC;
    merge_time = merge_time2 - merge_time1;
    // for (int i = 0; i < size; i++){
    //     cout << array_mer[i] << " ";
    // }
    // cout << endl;
    cout << "insertion time: " << insert_time << endl;
    cout << "merge time: " << merge_time << endl;
    return 0;
}