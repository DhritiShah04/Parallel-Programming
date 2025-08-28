#include <iostream>
#include <omp.h>
using namespace std;

int main(){
    int n = 20;

    cout << "With ordered:" << endl;
    double start1 = omp_get_wtime();
    #pragma omp parallel for ordered
    for(int i=1;i<=n;i++){
        #pragma omp ordered
        cout << i << " ";
    }
    double end1 = omp_get_wtime();
    double time1 = end1-start1;
    cout << "\nTime: " << end1-start1 << " s" << endl;

    cout << "\nWithout ordered:" << endl;
    double start2 = omp_get_wtime();
    #pragma omp parallel for
    for(int i=1;i<=n;i++)
        cout << i << " ";
    double end2 = omp_get_wtime();
    double time2 = end2-start2;
    cout << "\nTime: " << end2-start2 << " s" << endl;
    cout << endl;
    double speedup = time1 / time2;
    cout << "Speed-Up: " << speedup << endl;

    return 0;
}
