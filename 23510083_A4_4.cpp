#include <iostream>
#include <omp.h>
using namespace std;

int main() {
    int total = 0;
    int n = 20;
    int partial = 0;

    #pragma omp parallel
    {
        #pragma omp for lastprivate(partial)
        for(int i=1;i<=n;i++)
            partial += i;
        total = partial;
    }

    cout << "Total sum using lastprivate: " << total << endl;
    return 0;
}
