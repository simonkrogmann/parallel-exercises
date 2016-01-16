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
}

#include "cl_util.hpp"
