#include <iostream>
#include <omp.h>
using namespace std;

int main(){
    int nthreads;
    int sum_seq=0, sum_par=0;

    // Sequential sum
    double start_seq = omp_get_wtime();
    nthreads = omp_get_max_threads();
    for(int i=0;i<nthreads;i++){
        sum_seq += i*i;
        cout << "Thread " << i << " square: " << i*i << endl;
    }
    double end_seq = omp_get_wtime();
    double time_seq = end_seq - start_seq;

    // Parallel sum
    double start_par = omp_get_wtime();
    #pragma omp parallel for reduction(+:sum_par)
    for(int i=0;i<nthreads;i++){
        sum_par += i*i;
        cout << "Thread " << omp_get_thread_num() << " square: " << i*i << endl;
    }
    double end_par = omp_get_wtime();
    double time_par = end_par - start_par;

    cout << "Sequential sum: " << sum_seq << ", Parallel sum: " << sum_par << endl;
    cout << "Speedup: " << time_seq / time_par << endl;
    return 0;
}
