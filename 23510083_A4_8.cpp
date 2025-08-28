#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

int main(){
    long long N = 100000000;
    vector<double> A(N, 1.0);
    double sum_seq=0.0, sum_par=0.0;

    // Sequential
    double start_seq = omp_get_wtime();
    for(long long i=0;i<N;i++) sum_seq += A[i];
    double end_seq = omp_get_wtime();
    double time_seq = end_seq - start_seq;

    // Parallel reduction
    double start_par = omp_get_wtime();
    #pragma omp parallel for reduction(+:sum_par)
    for(long long i=0;i<N;i++)
        sum_par += A[i];
    double end_par = omp_get_wtime();
    double time_par = end_par - start_par;

    cout << "Sequential Sum: " << sum_seq << ", Time: " << time_seq << endl;
    cout << "Parallel Sum: " << sum_par << ", Time: " << time_par << ", Speedup: " << time_seq/time_par << endl;

    return 0;
}
