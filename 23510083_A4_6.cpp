#include <iostream>
#include <omp.h>
using namespace std;

int main(){
    #pragma omp parallel num_threads(2)
    {
        int tid = omp_get_thread_num();
        if(tid == 0) cout << "Thread " << tid << " prints: 2" << endl;
        else if(tid == 1) cout << "Thread " << tid << " prints: 4" << endl;
    }
    return 0;
}
