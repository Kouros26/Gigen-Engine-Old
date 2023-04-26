#pragma once
#include <string>

class IResource
{
public:
    IResource(const std::string& filePath) : filePath(filePath) {};
    virtual ~IResource() = default;

    IResource() = default;
    IResource(const IResource& other) = default;
    IResource(IResource&& other) noexcept = default;
    IResource& operator=(const IResource& other) = default;
    IResource& operator=(IResource&& other) noexcept = default;

    virtual void Init() = 0;

    [[nodiscard]] const std::string& GetFilePath() const { return filePath; };

protected:
    std::string filePath;
};

std::string readFile(std::string const&);
