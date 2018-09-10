/*********************************************************
 * config.h - Configuration data for the driver.c program.
 *********************************************************/
#ifndef _CONFIG_H_
#define _CONFIG_H_

/*
 * CPEs for the baseline (naive) version of the rotate function that
 * was handed out to the students. Rd is the measured CPE for a dxd
 * image. Run the driver.c program on your system to get these
 * numbers.
 */
#define R64 2.3
#define R128 3.5
#define R256 5.4
#define R512 8.7
#define R1024 9.2
#define R2048 18.5
#define R4096 24.1

/*
 * CPEs for the baseline (naive) version of the smooth function that
 * was handed out to the students. Sd is the measure CPE for a dxd
 * image. Run the driver.c program on your system to get these
 * numbers.
 */
#define S32 46.2
#define S64 51.9
#define S128 52.2
#define S256 52.3
#define S512 52.6
#define S1024 53.2
#define S2048 55.7

#endif /* _CONFIG_H_ */
