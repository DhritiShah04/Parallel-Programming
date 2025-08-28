#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

int main(){
    long long N = 10000000;
    vector<double> A(N, 1.0);
    double sum_critical=0.0, sum_atomic=0.0, sum_seq=0.0;

    // Sequential
    double start_seq = omp_get_wtime();
    for(long long i=0;i<N;i++) sum_seq += A[i];
    double end_seq = omp_get_wtime();
    double time_seq = end_seq - start_seq;

    // Critical
    double start_c = omp_get_wtime();
    #pragma omp parallel for
    for(long long i=0;i<N;i++){
        #pragma omp critical
        sum_critical += A[i];
    }
    double end_c = omp_get_wtime();
    double time_c = end_c - start_c;

    // Atomic
    double start_a = omp_get_wtime();
    #pragma omp parallel for
    for(long long i=0;i<N;i++){
        #pragma omp atomic
        sum_atomic += A[i];
    }
    double end_a = omp_get_wtime();
    double time_a = end_a - start_a;

    cout << "Sequential: " << sum_seq << ", Time: " << time_seq << endl;
    cout << "Critical: " << sum_critical << ", Time: " << time_c << ", Speedup: " << time_seq/time_c << endl;
    cout << "Atomic: " << sum_atomic << ", Time: " << time_a << ", Speedup: " << time_seq/time_a << endl;

    return 0;
}
