#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

int main() {
    long long n = 1000000; // large data size
    vector<double> A(n);
    for(long long i=0;i<n;i++)
        A[i] = 1.00001 + i*0.000001; // small incremental values

    double prod_seq = 1.0, prod_critical = 1.0, prod_atomic = 1.0, prod_reduction = 1.0;

    // Sequential
    double start_seq = omp_get_wtime();
    for(long long i=0;i<n;i++)
        prod_seq *= A[i];
    double end_seq = omp_get_wtime();
    double time_seq = end_seq - start_seq;

    // Critical
    double start1 = omp_get_wtime();
    #pragma omp parallel for
    for(long long i=0;i<n;i++){
        #pragma omp critical
        prod_critical *= A[i];
    }
    double end1 = omp_get_wtime();
    double time_critical = end1 - start1;

    // Atomic (simulate with critical)
    double start2 = omp_get_wtime();
    #pragma omp parallel for
    for(long long i=0;i<n;i++){
        #pragma omp critical
        prod_atomic *= A[i];
    }
    double end2 = omp_get_wtime();
    double time_atomic = end2 - start2;

    // Reduction
    double start3 = omp_get_wtime();
    #pragma omp parallel for reduction(*:prod_reduction)
    for(long long i=0;i<n;i++)
        prod_reduction *= A[i];
    double end3 = omp_get_wtime();
    double time_reduction = end3 - start3;

    cout << "Sequential: " << time_seq << " s\n";
    cout << "Critical: " << time_critical << " s, Speedup: " << time_seq/time_critical << endl;
    cout << "Atomic: " << time_atomic << " s, Speedup: " << time_seq/time_atomic << endl;
    cout << "Reduction: " << time_reduction << " s, Speedup: " << time_seq/time_reduction << endl;

    return 0;
}
