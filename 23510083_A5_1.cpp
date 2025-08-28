#include <iostream>
#include <omp.h>
using namespace std;

int main() {
    const long long N = 1000000;
    double counter = 0.0;

    // Without synchronization
    double start1 = omp_get_wtime();
    #pragma omp parallel
    {
        for(long long i=0; i<N; i++) {
            counter += 1.0; // race condition
        }
    }
    double end1 = omp_get_wtime();
    cout << "Counter without critical: " << counter << " Time: " << (end1-start1) << " s\n";

    // With critical
    counter = 0.0;
    double start2 = omp_get_wtime();
    #pragma omp parallel
    {
        for(long long i=0; i<N; i++) {
            #pragma omp critical
            counter += 1.0;
        }
    }
    double end2 = omp_get_wtime();
    cout << "Counter with critical: " << counter << " Time: " << (end2-start2) << " s\n";

    cout << "Speedup: " << (end1-start1)/(end2-start2) << endl;
    return 0;
}
