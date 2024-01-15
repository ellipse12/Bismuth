#pragma once


typedef unsigned char ui8;
typedef unsigned int ui32;
typedef unsigned short ui16;
typedef unsigned long long ui64;
typedef ui64 isize;
typedef ui8 retval;
typedef signed char si8;
typedef signed int si32;
typedef signed short si16;
typedef signed long long si64;

typedef char i8;
typedef int i32;
typedef short i16;
typedef long long i64;

typedef float f32;
typedef double f64;

//openGL and GLFW typdefs for abstraction

typedef struct GLFWwindow GLFWwindow;
typedef unsigned int GLenum;

#define Gigabytes(count) (ui64) (count * 1024 * 1024 * 1024)
#define Megabytes(count) (ui64) (count * 1024 * 1024)
#define Kilobytes(count) (ui64) (count * 1024)
#define true 1
#define false 0

#define null 0
