template<typename T>
inline T* ResourceManager::Get(const std::string& filePath)
{
    auto it = resources.end();
    if (resources.size() > 0) 
    {
        it = resources.find(filePath);
    }
    if (it == resources.end())
    {
        return Create<T>(filePath);
    }

    return static_cast<T*>(it->second.get());
}

template <typename T>
inline T* ResourceManager::Create(const std::string& filePath)
{
    if (!std::is_base_of_v<IResource, T>)
    {
        std::cout << "T is not a child of IResources" << std::endl;
        return nullptr;
    }

    std::future<T*> futureResource = threadPool.Enqueue([filePath]()
        {
            return new T(filePath);
        });

    futureResource.wait();

    T* resource = futureResource.get();

    resources[filePath] = std::unique_ptr<IResource>(resource);
    resource->Init();
    return resource;
}