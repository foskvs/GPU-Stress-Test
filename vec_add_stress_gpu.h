#ifndef __VEC_ADD_STRESS_GPU_H
#define __VEC_ADD_STRESS_GPU_H

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#elif _WIN32
#include "C:\Program Files (x86)\IntelSWTools\system_studio_2020\OpenCL\sdk\include\CL\cl.h"
#else
#include <CL/cl.h>
#endif

#include "options.h"

int vec_add_stress_gpu(cl_device_id);

#endif
