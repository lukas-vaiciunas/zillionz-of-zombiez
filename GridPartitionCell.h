#pragma once

#include <vector>

template<typename T>
class GridPartitionCell
{
public:
	GridPartitionCell();
	~GridPartitionCell();

	void add(T *item);
	void remove(T *item);

	const std::vector<T *> &getItems() const;
private:
	std::vector<T *> items_;
};

template<typename T>
GridPartitionCell<T>::GridPartitionCell() :
	items_()
{}

template<typename T>
GridPartitionCell<T>::~GridPartitionCell()
{
	for (auto it = items_.begin(); it != items_.end(); ++it)
	{
		delete *it;
	}
}

template<typename T>
void GridPartitionCell<T>::add(T *item)
{
	items_.push_back(item);
}

template<typename T>
void GridPartitionCell<T>::remove(T *item)
{
	for (auto it = items_.begin(); it != items_.end(); ++it)
	{
		if (*it == item)
		{
			delete *it;
			items_.erase(it);
			break;
		}
	}
}

template<typename T>
const std::vector<T *> &GridPartitionCell<T>::getItems() const
{
	return items_;
}