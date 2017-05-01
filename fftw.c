#include <stdio.h>
# include <stdlib.h>
#include <time.h>
#include <sys/time.h>
# include <fftw3.h>

#define N 1024

int main ( );
void test01 ( );
double WTime ( );
//void timestamp ( );



int 
main( )
{



test01 ( );

   
  return 0;
}

void test01 ( ){

  fftw_complex *in;
  //fftw_complex *in2;
  fftw_complex *out;
  fftw_plan plan_backward;
  fftw_plan plan_forward;

  FILE *signal;
  signal = fopen("y1.txt", "r");

    //read file into array
  double vec[N];

  for (int i = 0; i < N; i++)
    {
        fscanf(signal, "%lf", &vec[i]);
    }

  in = fftw_malloc ( sizeof ( fftw_complex ) * N );

  for (int i = 0; i < N; i++ )
  {
    in[i][0] = vec[i];
    in[i][1] = 0.0;
  }
  
  out = fftw_malloc ( sizeof ( fftw_complex ) * N );
  double tbeg = WTime();
  plan_forward = fftw_plan_dft_1d ( N, in, out, FFTW_FORWARD, FFTW_ESTIMATE );

  fftw_execute ( plan_forward );

  printf ( "\n" );
  printf ( "  Output FFT Coefficients:\n" );
  printf ( "\n" );

  for (int i = 0; i < N; i++ )
  {
    printf ( "  %3d  %12f  %12f\n", i, out[i][0], out[i][1]);
    }
    
  double tend = WTime();
  printf("Computing the DFT for signal y1 took %g s\n", tend - tbeg);
  
  fftw_destroy_plan ( plan_forward );
  fftw_destroy_plan ( plan_backward );

  fftw_free ( in );
  //fftw_free ( in2 );
  fftw_free ( out );
}

double
WTime(void)
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec + tv.tv_usec / 1e6;
}
