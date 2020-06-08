#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include "exp_stress_gpu.h"
#include "kernel_exp.h"

using namespace std;



int exp_stress_gpu(cl_device_id device_id) {

    unsigned int array_dimension = 4096;
    float* A = new float[array_dimension];
    //float* B = new float[array_dimension];
    float* C = new float[array_dimension];

    for (int i = 0; i < array_dimension; i++) {
        A[i] = (float)i * 2. / array_dimension;
        //B[i] = (float)(array_dimension - i)/array_dimension/2.;
    }

    cl_int ret;
    cl_context context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);
    if (DEBUG) {
        if (ret == CL_SUCCESS) {
            if (DEBUG_SUCCESS) cout << "success" << endl;
        }
        else {
            if (DEBUG_ERROR) {
                if (ret == CL_INVALID_PROGRAM_EXECUTABLE) {
                    cout << "invalid program executable ";
                }
                else if (ret == CL_INVALID_COMMAND_QUEUE) {
                    cout << "invalid command queue ";
                }
                cout << "error" << endl;
            }
            exit(1);
        }
    }

    cl_command_queue command_queue = clCreateCommandQueue(context, device_id, 0, &ret);
    if (DEBUG) {
        if (ret == CL_SUCCESS) {
            if (DEBUG_SUCCESS) cout << "success" << endl;
        }
        else {
            if (DEBUG_ERROR) {
                if (ret == CL_INVALID_PROGRAM_EXECUTABLE) {
                    cout << "invalid program executable ";
                }
                else if (ret == CL_INVALID_COMMAND_QUEUE) {
                    cout << "invalid command queue ";
                }
                cout << "error" << endl;
            }
            exit(1);
        }
    }


    cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_WRITE, array_dimension * sizeof(float), NULL, &ret);
    if (DEBUG) {
        if (ret == CL_SUCCESS) {
            if (DEBUG_SUCCESS) cout << "success" << endl;
        }
        else {
            if (DEBUG_ERROR) {
                if (ret == CL_INVALID_PROGRAM_EXECUTABLE) {
                    cout << "invalid program executable ";
                }
                else if (ret == CL_INVALID_COMMAND_QUEUE) {
                    cout << "invalid command queue ";
                }
                cout << "error" << endl;
            }
            exit(1);
        }
    }/*
    cl_mem b_mem_obj = clCreateBuffer(context, CL_MEM_READ_WRITE, array_dimension * sizeof(float), NULL, &ret);
    if (DEBUG) {
        if (ret == CL_SUCCESS) {
            if (DEBUG_SUCCESS) cout << "success" << endl;
        }
        else {
            if (DEBUG_ERROR) {
                if (ret == CL_INVALID_PROGRAM_EXECUTABLE) {
                    cout << "invalid program executable ";
                }
                else if (ret == CL_INVALID_COMMAND_QUEUE) {
                    cout << "invalid command queue ";
                }
                cout << "error" << endl;
            }
            exit(1);
        }
    }*/
    cl_mem c_mem_obj = clCreateBuffer(context, CL_MEM_READ_WRITE, array_dimension * sizeof(float), NULL, &ret);
    if (DEBUG) {
        if (ret == CL_SUCCESS) {
            if (DEBUG_SUCCESS) cout << "success" << endl;
        }
        else {
            if (DEBUG_ERROR) {
                if (ret == CL_INVALID_PROGRAM_EXECUTABLE) {
                    cout << "invalid program executable ";
                }
                else if (ret == CL_INVALID_COMMAND_QUEUE) {
                    cout << "invalid command queue ";
                }
                cout << "error" << endl;
            }
            exit(1);
        }
    }

    ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0, array_dimension * sizeof(float), A, 0, NULL, NULL);
    if (DEBUG) {
        if (ret == CL_SUCCESS) {
            if (DEBUG_SUCCESS) cout << "success" << endl;
        }
        else {
            if (DEBUG_ERROR) {
                if (ret == CL_INVALID_PROGRAM_EXECUTABLE) {
                    cout << "invalid program executable ";
                }
                else if (ret == CL_INVALID_COMMAND_QUEUE) {
                    cout << "invalid command queue ";
                }
                cout << "error" << endl;
            }
            exit(1);
        }
    }
    /*ret = clEnqueueWriteBuffer(command_queue, b_mem_obj, CL_TRUE, 0, array_dimension * sizeof(float), B, 0, NULL, NULL);
    if (DEBUG) {
        if (ret == CL_SUCCESS) {
            if (DEBUG_SUCCESS) cout << "success" << endl;
        }
        else {
            if (DEBUG_ERROR) {
                if (ret == CL_INVALID_PROGRAM_EXECUTABLE) {
                    cout << "invalid program executable ";
                }
                else if (ret == CL_INVALID_COMMAND_QUEUE) {
                    cout << "invalid command queue ";
                }
                cout << "error" << endl;
            }
            exit(1);
        }
    }*/

    //cl_program program = clCreateProgramWithSource(context, 1, (const char **)&source_str, (const size_t *)&source_size, &ret);
    cl_program program = clCreateProgramWithSource(context, 1, (const char**)&kernel_exp, NULL, &ret);
    if (DEBUG) {
        if (ret == CL_SUCCESS) {
            if (DEBUG_SUCCESS) cout << "success" << endl;
        }
        else {
            if (DEBUG_ERROR) {
                if (ret == CL_INVALID_PROGRAM_EXECUTABLE) {
                    cout << "invalid program executable ";
                }
                else if (ret == CL_INVALID_COMMAND_QUEUE) {
                    cout << "invalid command queue ";
                }
                cout << "error" << endl;
            }
            exit(1);
        }
    }
    ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
    if (DEBUG) {
        if (ret == CL_SUCCESS) {
            if (DEBUG_SUCCESS) cout << "success" << endl;
        }
        else {
            if (DEBUG_ERROR) {
                if (ret == CL_INVALID_PROGRAM) {
                    cout << "invalid program ";
                }
                else if (ret == CL_INVALID_VALUE) {
                    cout << "invalid value ";
                }
                else if (ret == CL_INVALID_DEVICE) {
                    cout << "invalid device ";
                }
                else if (ret == CL_INVALID_BINARY) {
                    cout << "invalid binary ";
                }
                else if (ret == CL_INVALID_BUILD_OPTIONS) {
                    cout << "invalid build options ";
                }
                else if (ret == CL_COMPILER_NOT_AVAILABLE) {
                    cout << "compiler not available ";
                }
                else if (ret == CL_BUILD_PROGRAM_FAILURE) {
                    cout << "build program failure ";
                }
                cout << "error" << endl;
            }
            exit(1);
        }
    }
    cl_kernel kernel = clCreateKernel(program, "vector_add", &ret);
    if (DEBUG) {
        if (ret == CL_SUCCESS) {
            if (DEBUG_SUCCESS) cout << "success" << endl;
        }
        else {
            if (DEBUG_ERROR) {
                if (ret == CL_INVALID_PROGRAM_EXECUTABLE) {
                    cout << "invalid program executable ";
                }
                else if (ret == CL_INVALID_COMMAND_QUEUE) {
                    cout << "invalid command queue ";
                }
                cout << "error" << endl;
            }
            exit(1);
        }
    }

    ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&a_mem_obj);
    //ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&b_mem_obj);
    ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*)&c_mem_obj);


    size_t global_item_size = array_dimension;
    size_t local_item_size = 32;
    ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_item_size, &local_item_size, 0, NULL, NULL);

    if (DEBUG) {
        if (ret == CL_SUCCESS) {
            if (DEBUG_SUCCESS) cout << "success" << endl;
        }
        else {
            if (DEBUG_ERROR) {
                if (ret == CL_INVALID_PROGRAM_EXECUTABLE) {
                    cout << "invalid program executable ";
                }
                else if (ret == CL_INVALID_COMMAND_QUEUE) {
                    cout << "invalid command queue ";
                }
                else if (ret == CL_INVALID_KERNEL) {
                    cout << "invalid kernel ";
                }
                else if (ret == CL_INVALID_CONTEXT) {
                    cout << "invalid context ";
                }
                else if (ret == CL_INVALID_KERNEL_ARGS) {
                    cout << "invalid kernel args ";
                }
                else if (ret == CL_INVALID_WORK_DIMENSION) {
                    cout << "invalid work dimension ";
                }
                else if (ret == CL_INVALID_GLOBAL_WORK_SIZE) {
                    cout << "invalid global work size ";
                }
                else if (ret == CL_INVALID_GLOBAL_OFFSET) {
                    cout << "invalid global offset ";
                }
                else if (ret == CL_INVALID_WORK_GROUP_SIZE) {
                    cout << "invalid work group size ";
                }
                cout << "error" << endl;
            }
            exit(1);
        }
    }
    ret = clEnqueueReadBuffer(command_queue, c_mem_obj, CL_TRUE, 0, array_dimension * sizeof(float), C, 0, NULL, NULL);

    //cout << "A[i]" << "\t"  << "C[i]" << endl;
    //for(int i = 0; i < array_dimension; i++) cout << A[i] << "\t"  << C[i] << endl;

    ret = clFlush(command_queue);
    ret = clFinish(command_queue);
    ret = clReleaseKernel(kernel);
    ret = clReleaseProgram(program);
    ret = clReleaseMemObject(a_mem_obj);
    //ret = clReleaseMemObject(b_mem_obj);
    ret = clReleaseMemObject(c_mem_obj);
    ret = clReleaseCommandQueue(command_queue);
    ret = clReleaseContext(context);

    delete[] A;
    //delete[] B;
    delete[] C;

    return 0;
}

