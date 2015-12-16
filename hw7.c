#include <stdio.h>
#include <math.h>
#include "recur.c"
#include <gsl/gsl_integration.h>
#include "gsl_integration.c"

#include "timer.h"
#include "timer.c"
#include "adjust.c"

#define NMAX 100

int main (void)
{
    double vals1[NMAX+1];
    double vals2[NMAX+1];
    double timea;
    double timea1;
    double timeb;
    double timeb1;
    double tmin = 1.;
    double tmax = 2.;
    
    int nmin =0;
    int nmax = NMAX;
    int count1 = 1000;
    int count2 = 800
;
    integral_recur (nmin ,nmax, vals1);
    integral_gen (nmin ,nmax, vals1);

    printf("        n        Recur            GSL Integrator        Absolute ErrorE9\n");
    int i;

    for (i=0; i<101; i++)
    {
         printf("     %6d     %15.15f     %15.15f     %15.15f\n", i, vals1[i], vals2[i], fabs(0.000000001*(vals1[i]-vals2[i])));
    }
    int j;

    printf("\n\nRecurrence Function Timing\n\nTime Per Call (usec) Total Time (sec)    Count\n");
    do
    {
        timer_start ();
        for (j = 0; j < count1; j++)
        {
            integral_recur (nmin, nmax, vals1);
        }
        timea = timer_stop ();
        timea1 = timea/count1;
        printf(" %10.2f usec    %10.6f sec    %10d\n", timea1 * 0.000001,  timea, count1);
        count1 = adjust_rep_count (count1, timea, tmin, tmax);
    }

    while ((timea > tmax) || (timea < tmin));
    printf ("Time of Recurance Function Call: %f usec\n", timea1 * 0.000001);
    printf("\n\nGSL Integration Function Timing\n\nTime Per Call (usec) Total Time (sec)    Count\n");

    do
    {
        timer_start();
        for (j=0; j < count2; j++)
        {
            integral_gen (nmin, nmax, vals2);
        }
        timeb = timer_stop();
        timeb1 = timeb/count2;
        printf(" %10.2f usec    %10.6f sec    %10d\n", timeb1*0.000001, timeb, count2);
        count2=adjust_rep_count (count2, timeb1, tmin, tmax);
    }
    while ((timeb > tmax) || (timeb < tmin));
    printf("GSL Integration Call Time: %f usec\n", timeb1*0.000001);
    printf(" %10.6f    %10.6f\n\n", timeb1, timea1);
    printf("GSL Integration Time Ratio / Recursion Formula = %f\n", timeb1/timea1);
    return 0;
}
