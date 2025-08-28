#include <iostream>
#include <omp.h>
using namespace std;

int main() {
    int n;
    cout<<"Enter number of threads: ";
    cin>>n;
    omp_set_num_threads(n);

    double start_t1 = omp_get_wtime();
    //Sequential
    cout << "Threads printed Sequentially!" <<endl;
    for(int i=0;i<n;i++){
        cout << "Hello World from thread " << i << " out of " << n << " threads!" << endl;
    }
    double end_t1 = omp_get_wtime();
    double time1 = (end_t1 - start_t1);
    cout << endl;

    //Parallel
    double start_t2 = omp_get_wtime();
    cout << "Threads printed parallelly!" <<endl;
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int total_threads = omp_get_num_threads();
        cout << "Hello World from thread " << thread_id << " out of " << total_threads << " threads!" << endl;
    }
    double end_t2 = omp_get_wtime();
    double time2 = (end_t2 - start_t2);
    
    cout << "Execution Time for Sequential: " << time1 << " seconds" << endl;
    cout << "Execution Time for Parallel: " << time2 << " seconds" << endl;

    double speedup_time = time1 / time2;
    cout << "Speed-Up time is: " << speedup_time << endl;

    return 0;
}
