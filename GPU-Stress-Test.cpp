#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include "options.h"
#include "exp_stress_gpu.h"
#include "vec_add_stress_gpu.h"

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

using namespace std;

int check_gpu();
bool check_vendor(const char*, const char*);

#define FLAG INTEL

cl_device_id device_id = NULL;



int main() {
    clock_t starting_time = clock();

    check_gpu();

    if (device_id) {
        for (int i = 0; i < 100; i++) {
            exp_stress_gpu(device_id);
        }
    }
    
    cout << "Time " << (double)(clock() - starting_time) / CLOCKS_PER_SEC << " s" << endl;
#ifdef _WIN32
    system("pause");
#endif
    return 0;
}

int check_gpu() {/*
    cl_uint platformIdCount = 0;
    clGetPlatformIDs(0, nullptr, &platformIdCount);     // count how many platforms we have
    cout << platformIdCount << " platform";
    if (platformIdCount != 1) cout << "s";
    cout << " found" << endl;


    cl_uint Max_CUs = 0;
    char* name;
    char* vendor;
    size_t size = 0;
    cl_platform_id* platformIds = (cl_platform_id*)malloc(platformIdCount);
    clGetPlatformIDs(platformIdCount, platformIds, NULL);   // read all the platforms
    for (int i = 0; i < platformIdCount; i++) {     // count how many devices we have per platform

        clGetPlatformInfo(platformIds[i], CL_PLATFORM_NAME, 0, NULL, &size);
        name = (char*)malloc(size);
        clGetPlatformInfo(platformIds[i], CL_PLATFORM_NAME, size, name, NULL);
        cout << "Platform " << i << ":" << endl;
        cout << "\tName: " << name << endl;

        clGetPlatformInfo(platformIds[i], CL_PLATFORM_VENDOR, 0, NULL, &size);
        vendor = (char*)malloc(size);
        clGetPlatformInfo(platformIds[i], CL_PLATFORM_VENDOR, size, vendor, NULL);
        cout << "\tVendor: " << vendor << endl;

        free(vendor);
        free(name);

        cl_uint deviceIdCount = 0;
        clGetDeviceIDs(platformIds[i], CL_DEVICE_TYPE_GPU, 0, NULL,
            &deviceIdCount);    // count all devices (CPU + GPU)
        cout << "\t" << deviceIdCount << " device";
        if (deviceIdCount != 1) cout << "s";
        cout << " found" << endl;

        cl_device_id* deviceIds = (cl_device_id*)malloc(deviceIdCount);
        clGetDeviceIDs(platformIds[i], CL_DEVICE_TYPE_GPU, deviceIdCount,
            deviceIds, NULL);

        for (int j = 0; j < deviceIdCount; j++) {
            clGetDeviceInfo(deviceIds[j], CL_DEVICE_NAME, 0, NULL, &size);
            name = (char*)malloc(size);
            clGetDeviceInfo(deviceIds[j], CL_DEVICE_NAME, size, name, NULL);
            clGetDeviceInfo(deviceIds[j], CL_DEVICE_VENDOR, 0, NULL, &size);
            vendor = (char*)malloc(size);
            clGetDeviceInfo(deviceIds[j], CL_DEVICE_VENDOR, size, vendor, NULL);
            //char vendor[256];
            cl_uint vid;
            clGetDeviceInfo(deviceIds[j], CL_DEVICE_VENDOR_ID, sizeof(vid), &vid, NULL);
            cout << "\t\tName: " << vendor << " " << name;
            //cout << ", vendor id: " << vid;
            cl_uint Device_CUs;
            clGetDeviceInfo(deviceIds[j], CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(Device_CUs), &Device_CUs, NULL);
            cout << "\t" << Device_CUs << " CU";
            cout << endl;

            cl_uint native_double_width;
            clGetDeviceInfo(deviceIds[j], CL_DEVICE_NATIVE_VECTOR_WIDTH_DOUBLE, sizeof(cl_uint), &native_double_width, NULL);

            if (native_double_width == 0) {
                printf("No double precision support.\n");
            }

            if (Max_CUs < Device_CUs && !strcmp(vendor, INTEL)) {
                Max_CUs = Device_CUs;
                device_id = deviceIds[j];
            }
            free(name);
            free(vendor);
        }

        free(deviceIds);
    }



    free(platformIds);

    return 0;
    */

    
    cl_uint platformIdCount = 0;
    clGetPlatformIDs(0, nullptr, &platformIdCount);
    /*cout << platformIdCount << " platform";
    if (platformIdCount != 1) cout << "s";
    cout << " found" << endl;*/

    std::vector<cl_platform_id> platformIds(platformIdCount);
    clGetPlatformIDs(platformIdCount, platformIds.data(), nullptr);
    cl_uint deviceIdCount = 0;
    clGetDeviceIDs(platformIds[0], CL_DEVICE_TYPE_ALL, 0, nullptr,
        &deviceIdCount);
    std::vector<cl_device_id> deviceIds(deviceIdCount);
    clGetDeviceIDs(platformIds[0], CL_DEVICE_TYPE_ALL, deviceIdCount,
        deviceIds.data(), nullptr);

    int i, cl_devcnt = 0;
    cl_uint n_platf, n_dev, n_entries = 16;
    cl_platform_id platf_ids[16];
    cl_device_id dev_ids[16];

    clGetPlatformIDs(n_entries, platf_ids, &n_platf);
    cout << "opencl device";
    if (platformIdCount != 1) cout << "s";
    cout << ":" << endl;
    for (i = 0; i < n_platf; i++)
    {
        if (clGetDeviceIDs(platf_ids[i], CL_DEVICE_TYPE_GPU | CL_DEVICE_TYPE_ACCELERATOR, 16, dev_ids + cl_devcnt, &n_dev))
            ;
        cl_devcnt += n_dev;
    }
    cout << cl_devcnt << " device";
    if (cl_devcnt != 1) cout << "s";
    cout << " found" << endl;
    cl_uint Max_CUs = 0;
    char* name;
    char* vendor;

    for (i = 0; i < cl_devcnt; i++)
    {
        size_t size = 0;
        //char name[256];
        clGetDeviceInfo(dev_ids[i], CL_DEVICE_NAME, 0, NULL, &size);
        name = (char*)malloc(size);
        clGetDeviceInfo(dev_ids[i], CL_DEVICE_NAME, size, name, NULL);
        clGetDeviceInfo(dev_ids[i], CL_DEVICE_VENDOR, 0, NULL, &size);
        vendor = (char*)malloc(size);
        clGetDeviceInfo(dev_ids[i], CL_DEVICE_VENDOR, size, vendor, NULL);
        //char vendor[256];
        cl_uint vid;
        clGetDeviceInfo(dev_ids[i], CL_DEVICE_VENDOR_ID, sizeof(vid), &vid, NULL);
        cout << "\tName: " << vendor << " " << name;
        //cout << endl << vendor << endl;
        //cout << ", vendor id: " << vid;
        cl_uint Device_CUs;
        clGetDeviceInfo(dev_ids[i], CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(Device_CUs), &Device_CUs, NULL);
        cout << "\t" << Device_CUs << " CU";
        cout << endl;

        cl_uint native_double_width;
        clGetDeviceInfo(device_id, CL_DEVICE_NATIVE_VECTOR_WIDTH_DOUBLE, sizeof(cl_uint), &native_double_width, NULL);

        if (native_double_width == 0) {
            printf("No double precision support.\n");
        }

        if (Max_CUs < Device_CUs && check_vendor(vendor, FLAG)) {
            Max_CUs = Device_CUs;
            device_id = dev_ids[i];
        }
        free(name);
        free(vendor);
    }
    return 0;
}

bool check_vendor(const char* vendor, const char* flag) {
    if (!flag) return true;
    return !strcmp(vendor, flag);
}
