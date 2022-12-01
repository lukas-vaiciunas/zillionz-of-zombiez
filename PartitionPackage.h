#pragma once

#include "GridPartition.h"

template<typename T>
class PartitionPackage
{
public:
	PartitionPackage(
		typename GridPartition<T>::GridSize numCols,
		typename GridPartition<T>::GridSize numRows,
		typename GridPartition<T>::GridSize cellSizeTiles);

	void updateVisibility(float x, float y);
	void updateVisibleItems();

	GridPartition<T> &getPartition();
	const GridPartition<T> &getPartition() const;

	std::vector<T *> &getVisibleItems();
	const std::vector<T *> &getVisibleItems() const;
private:
	GridPartition<T> partition_;
	std::vector<T *> visibleItems_;
	typename GridPartition<T>::Coords partitionCoords_;
};

template<typename T>
PartitionPackage<T>::PartitionPackage(
	typename GridPartition<T>::GridSize numCols,
	typename GridPartition<T>::GridSize numRows,
	typename GridPartition<T>::GridSize cellSizeTiles)
	:
	partition_(numCols, numRows, cellSizeTiles),
	visibleItems_(),
	partitionCoords_(-1, -1)
{}

template<typename T>
void PartitionPackage<T>::updateVisibility(float x, float y)
{
	typename GridPartition<T>::Coords newCoords = std::move(partition_.posToCoords(x, y));

	if (partitionCoords_ == newCoords)
		return;

	partitionCoords_ = newCoords;

	this->updateVisibleItems();
}

template<typename T>
void PartitionPackage<T>::updateVisibleItems()
{
	visibleItems_ = std::move(partition_.getItemsCloseToCoords(
		partitionCoords_.col,
		partitionCoords_.row));
}

template<typename T>
GridPartition<T> &PartitionPackage<T>::getPartition()
{
	return partition_;
}

template<typename T>
const GridPartition<T> &PartitionPackage<T>::getPartition() const
{
	return partition_;
}

template<typename T>
std::vector<T *> &PartitionPackage<T>::getVisibleItems()
{
	return visibleItems_;
}

template<typename T>
const std::vector<T *> &PartitionPackage<T>::getVisibleItems() const
{
	return visibleItems_;
}