const char* kernel_exp = "\n"\
" __kernel void vector_add(__global const float *A, __global float *C) { \n"\
"     int thread_id = get_global_id(0); \n"\
"     float a = A[thread_id]; \n"\
"     float c = 0; \n"\
"     float d = 1; \n"\
"     for (int i = 0; i < 10000000; i++) { \n"\
"         c = c + d; \n"\
"         d = (d * a)/(i + 1); \n"\
"     } \n"\
"     C[thread_id] = c; \n"\
" } \n";
