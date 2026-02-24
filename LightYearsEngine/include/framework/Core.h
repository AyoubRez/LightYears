#pragma once

#include <cstdio>
#include <map>
#include <memory>
#include <unordered_map>
#include <vector>

namespace ly
{
    template <typename T>
    using TUniquePtr = std::unique_ptr<T>;

    template <typename T>
    using TSharedPtr = std::shared_ptr<T>;

    template <typename T>
    using TWeakPtr = std::weak_ptr<T>;

    template <typename T>
    using TArray = std::vector<T>;

    template <typename keyType, typename valType, typename Pr=std::less<keyType>>
    using TMap = std::map<keyType, valType, Pr>;
    
    template <typename keyType, typename valType, typename Hasher=std::hash<keyType>>
    using TDictionary = std::unordered_map<keyType, valType, Hasher>;

#define LY_LOG(M, ...) printf(M "\n", ##__VA_ARGS__)
}
