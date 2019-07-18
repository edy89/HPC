// Dartboard-Algoritkm for approximating pi
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>


using namespace std;
int main(void)
{
    long k, n, hits;
    const double factor = 1.0 / RAND_MAX;
    while (1)
    {
        cout << "Enter the no of tosses (or 0 to exit): ";
        cin >> n;
        if ( n <= 0) // input <= 0 means end-of-job
        break;
        // Initialize the random generator
        srand ((int) clock ( ) );
        // Throw n tosses
        for (k=hits=0; k < n; ++k)
        {
        // Find two random numbers within 0.. 1
        double x = rand() * factor;
        double y = rand() * factor;
        if (x*x + y*y < 1.0) // Within circle ?
        ++hits; // yes: hits += 1
        }
        double pi_approx = 4.0 * hits / n;
        cout << "Approximation of pi after"<< n << "tosses: "<< pi_approx<< " (error="<< labs (M_PI - pi_approx)*100/M_PI<< "%) \n";
    }
    return 0;
}