#include <iostream>

#include <CL/cl.h>

#include "cl_util.h"

int main()
{
    const auto bestDevice =
        cl::chooseDevice(cl::allDevices(), CL_DEVICE_MAX_COMPUTE_UNITS);
    cl::printDeviceInfo(bestDevice);
}
