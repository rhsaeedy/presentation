# include <stdlib.h>
# include <stdio.h>
#include <time.h>
#include <sys/time.h>
# include <fftw3.h>

int main ( );
void test01 ( );
double frand ( );
double WTime ( );
void timestamp ( );

/******************************************************************************/

int main ( )

/******************************************************************************/
/*
  Purpose:

    MAIN is the main program for FFTW3_PRB.

  Discussion:

    FFTW3_PRB tests the FFTW3 library.

  Licensing:

    This code is distributed under the GNU LGPL license. 

  Modified:

    05 November 2007

  Author:

    John Burkardt
*/
{
  timestamp ( );
  printf ( "\n" );
  printf ( "FFTW3_TEST\n" );
  printf ( "  C version\n" );
  printf ( "  Test the FFTW3 library.\n" );

  test01 ( );
  
/*
  Terminate.
*/
  printf ( "\n" );
  printf ( "FFTW_TEST\n" );
  printf ( "  Normal end of execution.\n" );
  printf ( "\n" );
  timestamp ( );

  return 0;
}
/******************************************************************************/

void test01 ( )

/******************************************************************************/
/*
  Purpose:

    TEST01: apply FFT to complex 1D data.

  Discussion:

    In this example, we generate N=100 random complex values stored as
    a vector of type FFTW_COMPLEX named "IN".

    We have FFTW3 compute the Fourier transform of this data named "OUT".

    We have FFTW3 compute the inverse Fourier transform of "OUT" to get
    "IN2", which should be the original input data, scaled by N.

  Licensing:

    This code is distributed under the GNU LGPL license. 

  Modified:

    04 November 2007

  Author:

    John Burkardt
*/
{
  int i;
  fftw_complex *in;
  fftw_complex *in2;
  int n = 10000;
  fftw_complex *out;
  fftw_plan plan_backward;
  fftw_plan plan_forward;
  unsigned int seed = 123456789;

  printf ( "\n" );
  printf ( "TEST01\n" );
  printf ( "  Demonstrate FFTW3 on a single vector of complex data.\n" );
  printf ( "\n" );
  printf ( "  Transform data to FFT coefficients.\n" );
  printf ( "  Backtransform FFT coefficients to recover data.\n" );
  printf ( "  Compare recovered data to original data.\n" );
/*
  Create the input array.
*/
  in = fftw_malloc ( sizeof ( fftw_complex ) * n );

  srand ( seed );
  
  double tbeg = WTime();

  for ( i = 0; i < n; i++ )
  {
    in[i][0] = rand ( );
    in[i][1] = rand ( );
  }

  printf ( "\n" );
  printf ( "  Input Data:\n" );
  printf ( "\n" );

  for ( i = 0; i < n; i++ )
  {
    printf ( "  %3d  %12f  %12f\n", i, in[i][0], in[i][1] );
  }
/*
  Create the output array.
*/
  out = fftw_malloc ( sizeof ( fftw_complex ) * n );

  plan_forward = fftw_plan_dft_1d ( n, in, out, FFTW_FORWARD, FFTW_ESTIMATE );

  fftw_execute ( plan_forward );

  printf ( "\n" );
  printf ( "  Output FFT Coefficients:\n" );
  printf ( "\n" );

  for ( i = 0; i < n; i++ )
  {
    printf ( "  %3d  %12f  %12f\n", i, out[i][0], out[i][1] );
  }
/*
  Recreate the input array.
*/
  in2 = fftw_malloc ( sizeof ( fftw_complex ) * n );

  plan_backward = fftw_plan_dft_1d ( n, out, in2, FFTW_BACKWARD, FFTW_ESTIMATE );

  fftw_execute ( plan_backward );

  printf ( "\n" );
  printf ( "  Recovered input data:\n" );
  printf ( "\n" );

  for ( i = 0; i < n; i++ )
  {
    printf ( "  %3d  %12f  %12f\n", i, in2[i][0], in2[i][1] );
  }

  printf ( "\n" );
  printf ( "  Recovered input data divided by N:\n" );
  printf ( "\n" );

  for ( i = 0; i < n; i++ )
  {
    printf ( "  %3d  %12f  %12f\n", i, 
      in2[i][0] / ( double ) ( n ), in2[i][1] / ( double ) ( n ) );
  }
  
  
/*
  Free up the allocated memory.
*/
  fftw_destroy_plan ( plan_forward );
  fftw_destroy_plan ( plan_backward );

  fftw_free ( in );
  fftw_free ( in2 );
  fftw_free ( out );
  
  double tend = WTime();
  printf("Fourier coefficient calculation took %g s\n", tend - tbeg);

  return;
}

//*****************************************************************************/

double frand ( )

//*****************************************************************************/
/*
  Purpose:

    FRAND returns random values between 0 and 1.

  Discussion:

    The random seed can be set by a call to SRAND ( unsigned int ).

    Note that Kernighan and Ritchie suggest using

      ( ( double ) rand ( ) / ( RAND_MAX + 1 ) )

    but this seems to result in integer overflow for RAND_MAX + 1,
    resulting in negative values for the random numbers.

  Licensing:

    This code is distributed under the GNU LGPL license. 

  Modified:

    23 October 2005

  Author:

    John Burkardt

  Reference:

    Brian Kernighan, Dennis Ritchie,
    The C Programming Language,
    Prentice Hall, 1988.

  Parameters:

    Output, double FRAND, a random value between 0 and 1.
*/
{
  double value;

  value = ( ( double ) rand ( ) / ( RAND_MAX ) );

  return value;
}
//*****************************************************************************/

void timestamp ( )

/******************************************************************************/
/*
  Purpose:

    TIMESTAMP prints the current YMDHMS date as a time stamp.

  Example:

    31 May 2001 09:45:54 AM

  Licensing:

    This code is distributed under the GNU LGPL license. 

  Modified:

    24 September 2003

  Author:

    John Burkardt

  Parameters:

    None
*/
{
# define TIME_SIZE 40

  static char time_buffer[TIME_SIZE];
  const struct tm *tm;
  size_t len;
  time_t now;

  now = time ( NULL );
  tm = localtime ( &now );

  len = strftime ( time_buffer, TIME_SIZE, "%d %B %Y %I:%M:%S %p", tm );

  printf ( "%s\n", time_buffer );

  return;
# undef TIME_SIZE
}


double
WTime(void)
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec + tv.tv_usec / 1e6;
}


  

