#pragma once

#ifndef ANDROID_BUILD
#include "targetver.h"
#define WIN32_LEAN_AND_MEAN
#define VK_USE_PLATFORM_WIN32_KHR
#else

#endif

#pragma warning( push, 0 )
// std lib headers
#include <chrono>
#include <codecvt>
#include <cstring>
#include <fstream>
#include <functional>
#include <locale>
#include <ostream>
#include <set>
#include <sstream>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

// Windows and graphics API headers
#ifdef USE_VULKAN_API
#pragma clang diagnostic push
// vulkan.hpp has such warnings in c++20 mode on clang
#pragma clang diagnostic ignored "-Wdefaulted-function-deleted"
#define VULKAN_HPP_TYPESAFE_CONVERSION
#define VULKAN_HPP_DISPATCH_LOADER_DYNAMIC 1
#include <vulkan/vulkan.hpp>
#pragma clang diagnostic pop
#endif

#ifndef ANDROID_BUILD
#define NOMINMAX
#include <DirectXMath.h>
#include <Windows.h>
#include <comdef.h>
#include <d3d11_3.h>
#include <d3d12.h>
#include <d3d9types.h>
#include <d3dcompiler.h>
#endif // !ANDROID_BUILD

#pragma warning( pop )
