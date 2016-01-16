#pragma once

#include <vector>
#include <string>

#include <CL/cl.h>

namespace cl
{
template <typename T>
T deviceInfo(cl_device_id device, cl_device_info param);

std::vector<cl_platform_id> allPlatforms();
std::vector<cl_device_id> allDevices();
cl_device_id chooseDevice(const std::vector<cl_device_id>& devices,
                          const cl_device_info& param);
void printDeviceInfo(const cl_device_id& device);
}

#include "cl_util.hpp"
