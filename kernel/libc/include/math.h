/**
 * @file math.h
 * @author levent 
 * @brief tiny subset of C99 math.h, mostly used in gfx stuff
 * @version 0.1
 * @date 2023-11-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef _MATH_H_
#define _MATH_H_

#define PI 3.14159265358979323846
#define TWO_PI (2.0 * PI)
#define PI_OVER_2 (PI / 2.0)
#define PI_OVER_4 (PI / 4.0)

/*Returns the sine of a radian angle x.*/
double sin(double);

/*Returns the cosine of a radian angle x.*/
double cos(double);



#endif