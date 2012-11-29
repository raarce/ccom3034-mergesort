#include <iostream>
#include <QElapsedTimer>
#include <QDebug>

using namespace std;
void merge(int *a, int low, int mid, int high);
void merge_sort_common(int *a, int low, int high);
void testMergeSortSeq (int size);
bool verification (int *a, int low, int high);

int main(int argc, char *argv[]){
    testMergeSortSeq(700000);
    return(0);
}

//
// Creates an array of random numbers, calls on merge sort, and
// times its execution.
//
void testMergeSortSeq (int size) {
    QElapsedTimer myTimer;
    qDebug() << "Running sequential merge sort...";
    qDebug() << "================================";

    int *a = new int[size];

    // Fill array with random numbers
    srand(time(0));
    for (int i=0; i<size; i++)  a[i] = rand() % 100000  ;

    myTimer.start();
    merge_sort_common(a, 0, size-1);

    qDebug() << "Total time elapsed: "<< myTimer.elapsed() << "miliseconds";
    qDebug() << "Verification:" << (verification(a,0,size-1)?"ok":"error") << endl;

    return;
}

//
// Verifies that list is in ascending order.
//
bool verification (int *a, int low, int high) {
    for (int i=low; i<high; i++)
        if (a[i] > a[i+1]) return false;
    return true;
}

//
// Merges two ordered sublists into one list.
//
void merge(int *a, int low, int mid, int high) {
    int low_idx,b_idx,high_idx;
    int *b = new int[high-low+1];
    low_idx=low;
    b_idx=0;
    high_idx=mid+1;
    while((low_idx<=mid)&&(high_idx<=high)) {
        if(a[low_idx]<=a[high_idx]) {
            b[b_idx]=a[low_idx];
            low_idx++;
        }
        else {
            b[b_idx]=a[high_idx];
            high_idx++;
        }
        b_idx++;
    }

    if(low_idx > mid) {
        for(;high_idx<=high;high_idx++) {
            b[b_idx]=a[high_idx];
            b_idx++;
        }
    }
    else {
        for(;low_idx<=mid;low_idx++) {
            b[b_idx]=a[low_idx];
            b_idx++;
        }
    }
    for(b_idx=0;b_idx<=high-low;b_idx++) a[b_idx+low]=b[b_idx];
}

//
// Performs the recursive merge sort
//
void merge_sort_common(int *a, int low, int high) {
    if (high-low < 1) {  return;}

    int middle = (low + high) / 2;

    merge_sort_common(a, low, middle);
    merge_sort_common(a, middle+1, high);

    merge(a,low,middle,high);
    return;
}
