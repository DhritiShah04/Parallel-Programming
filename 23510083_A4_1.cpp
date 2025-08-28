#include <iostream>
#include <omp.h>
using namespace std;

int main() {
    string names[] = {"Sachin", "Bhavika", "Dhriti", "Nilay"};
    int n = 4;

    #pragma omp parallel for
    for(int i=0;i<n;i++){
        int tid = omp_get_thread_num();
        cout << "Thread " << tid << " prints: " << names[i] << endl;
    }
    return 0;
}
