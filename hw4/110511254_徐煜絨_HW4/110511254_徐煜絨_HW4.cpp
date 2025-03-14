#include <bits/stdc++.h>
using namespace std;

void gen(int *array1, int size){
    for(int i=0; i<size; i++){
        array1[i] = rand();
    }
}

int Partition(int *array1, int p, int r){
    int x = array1[r];
    int i = p-1;
    for(int j=p; j<r; j++){
        if(array1[j] <= x){
            i++;
            swap(array1[i], array1[j]);
        }
    }
    swap(array1[i+1], array1[r]);
    return i+1;
}

int RM_Partition(int *array1, int p, int r){
    int i = rand()%(r-p+1)+p;  // p~r
    swap(array1[r], array1[i]);
    return Partition(array1, p, r);
}

void RM_Quicksort(int *array1, int p, int r){
    if (p<r){
        int q = RM_Partition(array1, p, r);
        RM_Quicksort(array1, p, q-1);
        RM_Quicksort(array1, q+1, r);
    }
}

int main()
{
    // srand(30); // seed random number generator
    srand(time(NULL));
    int size;
    cout << "Please enter the size of the array: ";
    cin >> size;
    int * array_rq = new int[size];
    // cout << "before gen";
    gen(array_rq, size);

    // for(int i = 0; i < size; i++){
    //     cout << array_rq[i] << " ";
    // }

    double rq_time1, rq_time2, rq_time;

    rq_time1 = (double)clock()/CLOCKS_PER_SEC;
    RM_Quicksort(array_rq, 0, size-1);
    rq_time2 = (double)clock()/CLOCKS_PER_SEC;
    rq_time = rq_time2 - rq_time1;

    // cout << endl;
    // for(int i = 0; i < size; i++){
    //     cout << array_rq[i] << " ";
    // }
    // cout << endl;

    cout << "randomized quicksort time: " << rq_time << endl;
    return 0;
}