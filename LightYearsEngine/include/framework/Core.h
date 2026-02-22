#pragma once
#include <cstdio>

namespace ly
{
#define LY_LOG(M, ...) printf(M "\n", ##__VA_ARGS__)
}
