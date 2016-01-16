#include "cl_util.h"

namespace cl
{
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
