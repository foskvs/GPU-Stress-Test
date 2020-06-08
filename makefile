ifeq ($(shell uname -s),Darwin)
    CC = clang++
    LDLIBS += -lcurl -framework OpenCL
else
    CC = g++
    LDLIBS += -lOpenCL
endif

build: GPU-Stress-Test.o exp_stress_gpu.o vec_add_stress_gpu.o
	${CC} -o GPU-Stress-Test GPU-Stress-Test.o exp_stress_gpu.o vec_add_stress_gpu.o $(LDLIBS)
GPU-Stress-Test.o: GPU-Stress-Test.cpp vec_add_stress_gpu.h exp_stress_gpu.h
	${CC} -o GPU-Stress-Test.o -c GPU-Stress-Test.cpp
exp_stress_gpu.o: exp_stress_gpu.cpp exp_stress_gpu.h kernel_exp.h
	${CC} -o exp_stress_gpu.o -c exp_stress_gpu.cpp
vec_add_stress_gpu.o: vec_add_stress_gpu.cpp vec_add_stress_gpu.h kernel_vec_add.h
	${CC} -o vec_add_stress_gpu.o -c vec_add_stress_gpu.cpp
kernel_vec_add.h: cl_to_h.sh kernel_vec_add.cl
	./cl_to_h.sh kernel_vec_add.cl kernel_vec_add.h
kernel_exp.h: cl_to_h.sh kernel_exp.cl
	./cl_to_h.sh kernel_exp.cl kernel_exp.h
clean:
	rm GPU-Stress-Test
	rm -rf *.o
