#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

int main(){
    int n = 20;
    vector<double> arr(n);

    cout << "With nowait (incorrect):" << endl;
    #pragma omp parallel
    {
        #pragma omp for nowait
        for(int i=0;i<n;i++)
            arr[i] = i*i;

        #pragma omp for
        for(int i=0;i<n;i++)
            cout << arr[i] << " ";
    }
    cout << endl;

    cout << "\nWithout nowait (correct):" << endl;
    #pragma omp parallel
    {
        #pragma omp for
        for(int i=0;i<n;i++)
            arr[i] = i*i;

        #pragma omp for
        for(int i=0;i<n;i++)
            cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}
