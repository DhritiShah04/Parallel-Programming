#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

int main() {
    long long N = 100000000; // 100 million elements
    vector<double> A(N, 1.0), B(N, 2.0);
    double dot_seq = 0.0, dot_par = 0.0;

    // Sequential dot product
    double start_seq = omp_get_wtime();
    for(long long i=0;i<N;i++)
        dot_seq += A[i]*B[i];
    double end_seq = omp_get_wtime();
    double time_seq = end_seq - start_seq;

    // Parallel dot product using reduction
    double start_par = omp_get_wtime();
    #pragma omp parallel for reduction(+:dot_par)
    for(long long i=0;i<N;i++)
        dot_par += A[i]*B[i];
    double end_par = omp_get_wtime();
    double time_par = end_par - start_par;

    cout << "Sequential Dot Product: " << dot_seq << ", Time: " << time_seq << " s\n";
    cout << "Parallel Dot Product: " << dot_par << ", Time: " << time_par << " s\n";
    cout << "Speedup: " << time_seq / time_par << endl;

    return 0;
}
