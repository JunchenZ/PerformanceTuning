#include "clock.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h>
#include <unistd.h>

/*
 * Routines for using the cycle counter
 */

#if 1
/* $begin x86cyclecounter */
/* Initialize the cycle counter */
static unsigned cyc_hi = 0;
static unsigned cyc_lo = 0;

/* Set *hi and *lo to the high and low order bits  of the cycle counter.
   Implementation requires assembly code to use the rdtsc instruction. */
void access_counter(unsigned *hi, unsigned *lo) {
  asm("rdtsc; movl %%edx,%0; movl %%eax,%1" /* Read cycle counter */
      : "=r"(*hi), "=r"(*lo)                /* and move results to */
      : /* No input */                      /* the two outputs */
      : "%edx", "%eax");
}

/* Record the current value of the cycle counter. */
void start_counter() { access_counter(&cyc_hi, &cyc_lo); }

/* Return the number of cycles since the last call to start_counter. */
double get_counter() {
  unsigned ncyc_hi, ncyc_lo;
  unsigned hi, lo, borrow;
  double result;

  /* Get cycle counter */
  access_counter(&ncyc_hi, &ncyc_lo);

  /* Do double precision subtraction */
  lo = ncyc_lo - cyc_lo;
  borrow = lo > ncyc_lo;
  hi = ncyc_hi - cyc_hi - borrow;
  result = (double)hi * (1 << 30) * 4 + lo;
  if (result < 0) {
    fprintf(stderr, "Error: counter returns neg value: %.0f\n", result);
  }
  return result;
}
/* $end x86cyclecounter */
#endif /* x86 */

double ovhd() {
  /* Do it twice to eliminate cache effects */
  int i;
  double result;

  for (i = 0; i < 2; i++) {
    start_counter();
    result = get_counter();
  }
  return result;
}

/* $begin mhz */
/* Estimate the clock rate by measuring the cycles that elapse */
/* while sleeping for sleeptime seconds */
double mhz_full(int verbose, int sleeptime) {
  double rate;

  start_counter();
  sleep(sleeptime);
  rate = get_counter() / (1e6 * sleeptime);
  if (verbose)
    printf("Processor clock rate ~= %.1f MHz\n", rate);
  return rate;
}
/* $end mhz */

/* Version using a default sleeptime */
double mhz(int verbose) { return mhz_full(verbose, 2); }

/** Special counters that compensate for timer interrupt overhead */

static clock_t start_tick = 0;

void start_comp_counter() {
  struct tms t;
  times(&t);
  start_tick = t.tms_utime;
  start_counter();
}

double get_comp_counter() {
  double time = get_counter();
  double ctime;
  struct tms t;
  clock_t ticks;

  times(&t);
  ticks = t.tms_utime - start_tick;
  ctime = time;
  return ctime;
}
