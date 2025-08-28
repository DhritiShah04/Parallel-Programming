#include <iostream>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
using namespace std;

int main(){
    long long int points = 100000000; // large data
    long long int count_serial = 0;
    long long int count_parallel = 0;

    // SERIAL EXECUTION
    double start_serial = omp_get_wtime();
    for(long long int i = 0; i < points; i++){
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;

        if(x*x + y*y <= 1.0) count_serial++;
    }
    double pi_serial = 4.0 * (double)count_serial / points;
    double end_serial = omp_get_wtime();

    cout << "Estimated PI (Serial): " << pi_serial << endl;
    cout << "Serial Execution Time: " << (end_serial - start_serial) << " s\n";

    // PARALLEL EXECUTION
    double start_parallel = omp_get_wtime();
    #pragma omp parallel for reduction(+:count_parallel)
    for(long long int i = 0; i < points; i++){
        unsigned int seed = (unsigned int)time(NULL) ^ (omp_get_thread_num() + i);
        double x = (double)rand_r(&seed) / RAND_MAX;
        double y = (double)rand_r(&seed) / RAND_MAX;

        if(x*x + y*y <= 1.0) count_parallel++;
    }
    double pi_parallel = 4.0 * (double)count_parallel / points;
    double end_parallel = omp_get_wtime();

    cout << "Estimated PI (Parallel): " << pi_parallel << endl;
    cout << "Parallel Execution Time: " << (end_parallel - start_parallel) << " s\n";

    // Speedup
    double speedup = (end_serial - start_serial) / (end_parallel - start_parallel);
    cout << "Speedup (Serial / Parallel): " << speedup << endl;

    return 0;
}