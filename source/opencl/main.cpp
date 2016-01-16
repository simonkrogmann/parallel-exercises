#include <iostream>
#include <vector>
#include <string>

#include <CL/cl.h>

namespace cl
{
template <typename T>
T deviceInfo(cl_device_id device, cl_device_info param)
{
    T info;
    clGetDeviceInfo(device, param, sizeof(info), &info, nullptr);
    return info;
}

template <>
std::string deviceInfo<std::string>(cl_device_id device, cl_device_info param)
{
    size_t infoSize;
    clGetDeviceInfo(device, param, 0, nullptr, &infoSize);
    std::vector<char> info(infoSize);
    clGetDeviceInfo(device, param, infoSize, info.data(), nullptr);
    return {info.begin(), info.end()};
}

std::vector<cl_platform_id> allPlatforms()
{
    cl_uint platformCount;
    clGetPlatformIDs(0, nullptr, &platformCount);
    std::vector<cl_platform_id> platforms(platformCount);
    clGetPlatformIDs(platformCount, platforms.data(), nullptr);
    return platforms;
}

std::vector<cl_device_id> allDevices()
{
    const auto platforms = allPlatforms();

    std::vector<cl_device_id> devices;
    for (const auto& platform : platforms)
    {
        cl_uint deviceCount;
        clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 0, nullptr, &deviceCount);
        std::vector<cl_device_id> platformDevices(deviceCount);
        clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, deviceCount,
                       platformDevices.data(), nullptr);
        devices.insert(devices.end(), platformDevices.begin(),
                       platformDevices.end());
    }
    return devices;
}
}

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
