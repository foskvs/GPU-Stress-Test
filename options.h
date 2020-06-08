#ifndef __OPTIONS_H
#define __OPTIONS_H


#define MAX_SOURCE_SIZE 0x100000
#define DEBUG 1
#define DEBUG_ERROR 1
#define DEBUG_SUCCESS 0

#ifdef __APPLE__
#define INTEL "Intel"
#else
#define INTEL "Intel(R) Corporation"
#endif

#ifdef __APPLE__
#define AMD "AMD"
#else
#define AMD "Advanced Micro Devices, Inc."
#endif

#ifdef __APPLE__
#define NVIDIA "NVIDIA"
#else
#define NVIDIA "NVIDIA Corporation"
#endif


#endif
