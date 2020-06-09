#include <iostream>
#include <random>
#include <ctime>
#include <omp.h>

const long long iteration = 100000000;

int main()
{
    std::default_random_engine e;
    std::uniform_real_distribution<double> u(0.0, 1.0);
    
    int maxThreads = omp_get_max_threads();
    for (int i = 1; i <= maxThreads; ++i)
    {
        long long count = 0;
        clock_t startClock = clock();
        double startWall = omp_get_wtime();
        std::cout<<"Number of threads: "<<i<<'\n';

        #pragma omp parallel for reduction(+:count) num_threads(i)
        for (int i = 0 ; i < iteration; ++i)
        {
            double x = u(e);
            double y = u(e);
            if (x * x + y * y < 1)
            {
                ++count;
            }
        }
        double endWall = omp_get_wtime();
        clock_t endClock = clock();
        std::cout<<"Time on clock: "<<(double)(endClock - startClock) / CLOCKS_PER_SEC<<'\n';
        std::cout<<"Time on wall : "<<endWall - startWall<<'\n';
        double pi = 4 * double(count) / double(iteration);
        std::cout<<"PI = "<<pi<<'\n';
    }
}