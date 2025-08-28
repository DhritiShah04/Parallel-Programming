#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

int main(){
    long long n = 1000000;
    vector<double> A(n);
    for(long long i=0;i<n;i++) A[i] = i+1;

    double sum_seq=0.0, sum_par=0.0;

    // Sequential execution
    double start1 = omp_get_wtime();
    for(long long i=0;i<n;i++) sum_seq += A[i]*A[i];
    double end1 = omp_get_wtime();
    double time_seq = end1 - start1;

    // Parallel using reduction
    double start2 = omp_get_wtime();
    #pragma omp parallel for reduction(+:sum_par)
    for(long long i=0;i<n;i++)
        sum_par += A[i]*A[i];
    double end2 = omp_get_wtime();
    double time_par = end2 - start2;

    cout << "Sequential Sum of Squares: " << sum_seq << ", Time: " << time_seq << " s\n";
    cout << "Parallel Sum of Squares: " << sum_par << ", Time: " << time_par << " s\n";
    cout << "Speedup: " << time_seq / time_par << endl;

    return 0;
}
