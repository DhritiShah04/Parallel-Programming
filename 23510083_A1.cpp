#include <iostream>
#include <omp.h>
using namespace std;

int main() {
    int n;
    cout<<"Enter number of threads: ";
    cin>>n;
    omp_set_num_threads(n);

    //Sequential
    cout << "Threads printed Sequentially!" <<endl;
    for(int i=0;i<n;i++){
        cout << "Hello World from thread " << i << " out of " << n << " threads!" << endl;
    }

    cout << endl;
    //Parallel
    cout << "Threads printed parallelly!" <<endl;
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int total_threads = omp_get_num_threads();
        cout << "Hello World from thread " << thread_id << " out of " << total_threads << " threads!" << endl;
    }
    return 0;
}
