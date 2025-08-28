#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

int main() {

    long long int n = 100000000;
    vector<double> A(n), B(n), C(n), D(n);

    // Initialize vectors
    for (long long int i = 0; i < n; i++) {
        A[i] = i * 0.5;
        B[i] = (n - i) * 0.5;
    }

    double start_t1 = omp_get_wtime();
    //serial
    for (long long int i = 0; i < n; i++) {
        D[i] = A[i] + B[i];
    }
    double end_t1 = omp_get_wtime();
    double time1 = (end_t1 - start_t1);

    double start_t2 = omp_get_wtime();
    // Parallel vector addition
    #pragma omp parallel for
    for (long long int i = 0; i < n; i++) {
        C[i] = A[i] + B[i];
    }
    double end_t2 = omp_get_wtime();
    double time2 = (end_t2 - start_t2);
    
    cout << "Execution Time for Sequential: " << time1 << " seconds" << endl;
    cout << "Execution Time for Parallel: " << time2 << " seconds" << endl;

    double speedup_time = time1 / time2;
    cout << "Speed-Up time is: " << speedup_time << " seconds" << endl;
    return 0;
}
