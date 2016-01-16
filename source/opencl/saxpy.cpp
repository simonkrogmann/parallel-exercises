#include <iostream>

#include <CL/cl.h>

#include "cl_util.h"

const char *source =
    "__kernel void saxpy(float a, __global float *x, __global float *y)"
    "{"
    "   uint id = get_global_id(0);"
    "   y[id] = a * x[id] + y[id];"
    "}";

void errorCallback(const char *errinfo, const void *private_info, size_t cb,
                   void *user_data)
{
    std::cout << "ContextError: " << errinfo << std::endl;
}

int main()
{
    // input data
    const size_t inputSize = 100000000;
    float a = 7;
    std::vector<float> x(inputSize, 4);
    std::vector<float> y(inputSize, 5);

    const auto device =
        cl::chooseDevice(cl::allDevices(), CL_DEVICE_MAX_COMPUTE_UNITS);
    cl::printDeviceInfo(device);
    cl_int error = 0;

    cl_context context =
        clCreateContext(nullptr, 1, &device, errorCallback, nullptr, &error);
    cl_command_queue queue = clCreateCommandQueue(context, device, 0, &error);
    cl_program program =
        clCreateProgramWithSource(context, 1, &source, nullptr, &error);
    clBuildProgram(program, 1, &device, nullptr, nullptr, nullptr);

    size_t logSize;
    clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0, nullptr,
                          &logSize);
    std::vector<char> infoLog(logSize);
    clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, logSize,
                          infoLog.data(), nullptr);
    std::cout << std::string{infoLog.begin(), infoLog.end()} << std::endl;

    cl_kernel kernel = clCreateKernel(program, "saxpy", nullptr);
    cl_mem bufferX =
        clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                       sizeof(float) * x.size(), x.data(), &error);
    cl_mem bufferY =
        clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
                       sizeof(float) * y.size(), y.data(), &error);

    clSetKernelArg(kernel, 0, sizeof(a), static_cast<void *>(&a));
    clSetKernelArg(kernel, 1, sizeof(bufferX), static_cast<void *>(&bufferX));
    clSetKernelArg(kernel, 2, sizeof(bufferY), static_cast<void *>(&bufferY));

    clEnqueueNDRangeKernel(queue, kernel, 1, nullptr, &inputSize, nullptr, 0,
                           nullptr, nullptr);
    clFinish(queue);

    auto data = static_cast<cl_float *>(clEnqueueMapBuffer(
        queue, bufferY, CL_TRUE, CL_MAP_READ, 0, sizeof(float) * inputSize, 0,
        nullptr, nullptr, &error));

    for (int i = 0; i < 20; ++i)
    {
        std::cout << data[i] << std::endl;
    }
}
