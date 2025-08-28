#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

int main() {
    long long N = 1000; // large matrix size
    vector<vector<double>> A(N, vector<double>(N, 1.0));
    vector<vector<double>> B(N, vector<double>(N, 2.0));
    vector<vector<double>> C(N, vector<double>(N, 0.0));

    // Sequential matrix multiplication
    double start_seq = omp_get_wtime();
    for(long long i=0;i<N;i++)
        for(long long j=0;j<N;j++)
            for(long long k=0;k<N;k++)
                C[i][j] += A[i][k]*B[k][j];
    double end_seq = omp_get_wtime();
    double time_seq = end_seq - start_seq;

    // Parallel matrix multiplication using collapse
    vector<vector<double>> C_par(N, vector<double>(N, 0.0));
    double start_par = omp_get_wtime();
    #pragma omp parallel for collapse(2)
    for(long long i=0;i<N;i++)
        for(long long j=0;j<N;j++)
            for(long long k=0;k<N;k++)
                C_par[i][j] += A[i][k]*B[k][j];
    double end_par = omp_get_wtime();
    double time_par = end_par - start_par;

    cout << "Sequential Time: " << time_seq << " s\n";
    cout << "Parallel Time (collapse): " << time_par << " s\n";
    cout << "Speedup: " << time_seq / time_par << endl;

    return 0;
}