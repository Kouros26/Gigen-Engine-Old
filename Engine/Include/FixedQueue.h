#pragma once
#include <queue>

template <typename T, int maxLength, typename Container = std::deque<T>>
class FixedQueue : public std::queue<T, Container>
{
public:

	void push(const T& value)
	{
		if (this->size() == maxLength)
			this->c.pop_front();

		std::queue<T, Container>::push(value);
	}
};