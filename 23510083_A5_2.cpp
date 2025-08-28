#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

int main() {
    const long long N = 1000000;
    vector<double> A(N);
    double sum = 0.0;

    for(long long i=0; i<N; i++) A[i] = i * 0.5;

    // Using critical
    sum = 0.0;
    double start1 = omp_get_wtime();
    #pragma omp parallel for
    for(long long i=0; i<N; i++) {
        #pragma omp critical
        sum += A[i];
    }
    double end1 = omp_get_wtime();
    cout << "Sum using critical: " << sum << " Time: " << (end1-start1) << " s\n";

    // Using atomic
    sum = 0.0;
    double start2 = omp_get_wtime();
    #pragma omp parallel for
    for(long long i=0; i<N; i++) {
        #pragma omp atomic
        sum += A[i];
    }
    double end2 = omp_get_wtime();
    cout << "Sum using atomic: " << sum << " Time: " << (end2-start2) << " s\n";

    cout << "Speedup (atomic/critical): " << (end1-start1)/(end2-start2) << endl;

    return 0;
}
