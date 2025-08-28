#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

int main() {
    const int nthreads = 8;
    vector<double> squares(nthreads);

    #pragma omp parallel num_threads(nthreads)
    {
        int tid = omp_get_thread_num();
        squares[tid] = tid * tid;

        #pragma omp barrier  // Wait for all threads
        #pragma omp master
        {
            cout << "Squares of thread IDs: ";
            for(int i=0; i<nthreads; i++)
                cout << squares[i] << " ";
            cout << endl;
        }
    }
    return 0;
}
