__kernel void vector_add(__global const float *A, __global float *C) {
    int thread_id = get_global_id(0);
    float a = A[thread_id];
    float c = 0;
    float d = 1;
    for (int i = 0; i < 10000000; i++) {
        c = c + d;
        d = (d * a)/(i + 1);
    }
    C[thread_id] = c;
}
