#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

int main() {
    long long n = 100000000;  // Large size for performance measurement
    double scalar = 5.0;
    vector<double> A(n), B(n);

    // Initialize vector
    for (long long i = 0; i < n; i++) {
        A[i] = i * 0.5;
    }

    // Sequential execution
    double start1 = omp_get_wtime();
    for (long long i = 0; i < n; i++) {
        B[i] = A[i] + scalar;
    }
    double end1 = omp_get_wtime();
    double time_seq = end1 - start1;

    // Parallel execution (static scheduling)
    double start2 = omp_get_wtime();
    #pragma omp parallel for schedule(static)
    for (long long i = 0; i < n; i++) {
        B[i] = A[i] + scalar;
    }
    double end2 = omp_get_wtime();
    double time_par = end2 - start2;

    cout << "Sequential Time: " << time_seq << " s" << endl;
    cout << "Parallel Time (Static): " << time_par << " s" << endl;
    cout << "Speedup: " << time_seq / time_par << endl;

    return 0;
}
