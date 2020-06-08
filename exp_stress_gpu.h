#ifndef __EXP_STRESS_GPU_H
#define __EXP_STRESS_GPU_H

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

#include "options.h"

int exp_stress_gpu(cl_device_id);

#endif
