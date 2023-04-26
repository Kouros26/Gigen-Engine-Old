#pragma once
#include "IResource.h"
#include "ThreadPool.h"
class ResourceManager
{
public:
    ResourceManager();
    ~ResourceManager();

    template <typename T>
    static T* Get(const std::string& filePath);

    static void DeleteResource(const std::string& filePath);

private:
    template <typename T>
    static T* Create(const std::string& filePath);

    static ThreadPool threadPool;
    inline static std::unordered_map<std::string, std::unique_ptr<IResource>> resources;
};

#include "ResourceManager.inl"