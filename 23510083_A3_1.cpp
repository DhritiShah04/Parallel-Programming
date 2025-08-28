#include <iostream>
#include <omp.h>
using namespace std;

int main() {
    cout << "Using #pragma omp parallel:" << endl;
    double start1 = omp_get_wtime();

    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        cout << "Hello World from thread " << tid << endl;
    }
    double end1 = omp_get_wtime();
    double time1 = end1 - start1;

    cout << "\nUsing #pragma omp parallel for:" << endl;
    double start2 = omp_get_wtime();

    #pragma omp parallel for
    for (int i = 0; i < omp_get_max_threads(); i++) {
        cout << "Hello World from thread " << i << endl;
    }
    double end2 = omp_get_wtime();
    double time2 = end2 - start2;

    cout << "\nTime parallel section: " << time1 << " s" << endl;
    cout << "Time parallel for section: " << time2 << " s" << endl;
    cout << "Speedup: " << time1 / time2 << endl;

    return 0;
}
