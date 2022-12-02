#pragma once

#include <vector>

template<typename T>
class Pool
{
public:
	typedef uint32_t PoolType;

	Pool(PoolType capacity);
	virtual ~Pool();

	typename std::vector<T *>::iterator begin();
	typename std::vector<T *>::iterator end();

	void add(T *item);

	void clear();

	bool isFull() const;
	PoolType getVacancy() const;
protected:
	std::vector<T *> items_;
	PoolType capacity_;
	PoolType numLive_;

	void removeAtIndex_(PoolType index);
};

template<typename T>
Pool<T>::Pool(PoolType capacity) :
	items_(capacity, nullptr),
	capacity_(capacity),
	numLive_(0)
{}

template<typename T>
Pool<T>::~Pool()
{
	this->clear();
}

template<typename T>
typename std::vector<T *>::iterator Pool<T>::begin()
{
	return items_.begin();
}

template<typename T>
typename std::vector<T *>::iterator Pool<T>::end()
{
	return items_.begin() + numLive_;
}

template<typename T>
void Pool<T>::add(T *item)
{
	items_[numLive_++] = item;
}

template<typename T>
void Pool<T>::clear()
{
	for (PoolType i = 0; i < numLive_; ++i)
	{
		delete items_[i];
		items_[i] = nullptr;
	}

	numLive_ = 0;
}

template<typename T>
bool Pool<T>::isFull() const
{
	return numLive_ >= capacity_;
}

template<typename T>
typename Pool<T>::PoolType Pool<T>::getVacancy() const
{
	return capacity_ - numLive_;
}

template<typename T>
void Pool<T>::removeAtIndex_(PoolType index)
{
	--numLive_;
	items_[index] = items_[numLive_];
	items_[numLive_] = nullptr;
}