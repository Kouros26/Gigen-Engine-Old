#pragma once
#include <string>

class Object
{
public:
	Object();
	Object(const std::string& name);

	virtual ~Object();

	[[nodiscard]] std::string GetName() const;
	void SetName(const std::string& pName);

	virtual std::string GetType();

	[[nodiscard]] unsigned int GetId() const;

	[[nodiscard]] bool IsActive() const;
	virtual void SetActive(bool b);

protected:

	bool isActive;
	std::string name{};
	unsigned int id{};

	inline static unsigned int objectIndex = 0;
};