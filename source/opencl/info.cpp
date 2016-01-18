#include <iostream>
#include <vector>
#include <string>

#include <CL/cl.h>
#include <utilgpu/cl/device.h>

int main()
{
    const auto devices = cl::allDevices();
    const auto bestDevice =
        cl::chooseDevice(devices, CL_DEVICE_MAX_COMPUTE_UNITS);
    std::cout << "OpenCL Devices:" << std::endl;
    for (const auto& device : devices)
    {
        std::cout << (device == bestDevice ? " *  " : "    ");
        cl::printDeviceInfo(device);
    }
}
