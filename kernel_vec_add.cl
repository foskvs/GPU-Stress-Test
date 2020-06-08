__kernel void vector_add(__global const float *A, __global const float *B, __global float *C) {
    int thread_id = get_global_id(0);
    float a = A[thread_id];
    float b = B[thread_id];
    float c = a + b;
    C[thread_id] = c;
}
