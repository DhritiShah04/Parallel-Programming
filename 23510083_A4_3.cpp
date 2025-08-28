#include <iostream>
#include <omp.h>
using namespace std;

int main(){
    #pragma omp parallel
    {
        int Aryabhatta = 10; // private by default inside parallel region
        int tid = omp_get_thread_num();
        cout << "Thread " << tid << " multiplied value: " << tid * Aryabhatta << endl;
    }
    return 0;
}
