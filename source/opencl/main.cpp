#include <iostream>
#include <vector>
#include <string>

#include <CL/cl.h>

#include "cl_util.h"

int main()
{
    const auto devices = cl::allDevices();
    std::cout << "OpenCL Devices:" << std::endl;
    for (const auto& device : devices)
    {
        std::cout << "    "
                  << cl::deviceInfo<std::string>(device, CL_DEVICE_NAME)
                  << " using "
                  << cl::deviceInfo<std::string>(device, CL_DEVICE_VERSION)
                  << " with " << cl::deviceInfo<cl_uint>(
                                     device, CL_DEVICE_MAX_COMPUTE_UNITS)
                  << " computation units." << std::endl;
    }
}
