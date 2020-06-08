const char* kernel_vec_add = "\n"\
" __kernel void vector_add(__global const float *A, __global const float *B, __global float *C) { \n"\
"     int thread_id = get_global_id(0); \n"\
"     float a = A[thread_id]; \n"\
"     float b = B[thread_id]; \n"\
"     float c = a + b; \n"\
"     C[thread_id] = c; \n"\
" } \n";
