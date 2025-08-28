#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

int main() {
    long long N = 500; // large size
    vector<vector<double>> A(N, vector<double>(N, 1.0));
    vector<vector<double>> B(N, vector<double>(N, 2.0));
    vector<vector<double>> C(N, vector<double>(N, 0.0));

    // Sequential
    double start_seq = omp_get_wtime();
    for(long long i=0;i<N;i++)
        for(long long j=0;j<N;j++)
            for(long long k=0;k<N;k++)
                C[i][j] += A[i][k]*B[k][j];
    double end_seq = omp_get_wtime();
    double time_seq = end_seq - start_seq;

    // Parallel static
    vector<vector<double>> C_static(N, vector<double>(N, 0.0));
    double start_static = omp_get_wtime();
    #pragma omp parallel for schedule(static) collapse(2)
    for(long long i=0;i<N;i++)
        for(long long j=0;j<N;j++)
            for(long long k=0;k<N;k++)
                C_static[i][j] += A[i][k]*B[k][j];
    double end_static = omp_get_wtime();
    double time_static = end_static - start_static;

    // Parallel dynamic
    vector<vector<double>> C_dynamic(N, vector<double>(N, 0.0));
    double start_dyn = omp_get_wtime();
    #pragma omp parallel for schedule(dynamic) collapse(2)
    for(long long i=0;i<N;i++)
        for(long long j=0;j<N;j++)
            for(long long k=0;k<N;k++)
                C_dynamic[i][j] += A[i][k]*B[k][j];
    double end_dyn = omp_get_wtime();
    double time_dyn = end_dyn - start_dyn;

    cout << "Sequential Time: " << time_seq << " s\n";
    cout << "Static Schedule Time: " << time_static << " s\n";
    cout << "Dynamic Schedule Time: " << time_dyn << " s\n";
    cout << "Speedup (Static): " << time_seq / time_static << endl;
    cout << "Speedup (Dynamic): " << time_seq / time_dyn << endl;

    return 0;
}
