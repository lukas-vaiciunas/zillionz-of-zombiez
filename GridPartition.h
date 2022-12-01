#pragma once

#include "GridPartitionCell.h"
#include "Constants.h"

template<typename T>
class GridPartition
{
public:
	typedef int32_t GridSize;

	struct Coords
	{
		GridSize col;
		GridSize row;

		Coords(GridSize col, GridSize row) :
			col(col),
			row(row)
		{}

		bool operator==(const Coords &other) const
		{
			return col == other.col && row == other.row;
		}

		bool operator!=(const Coords &other) const
		{
			return !this->operator==(other);
		}
	};

	GridPartition(
		GridSize numCols,
		GridSize numRows,
		GridSize cellSizeTiles);

	void add(T *object);
	void remove(T *object);

	std::vector<T *> getItemsCloseToPos(float x, float y) const;
	std::vector<T *> getItemsCloseToCoords(GridSize col, GridSize row) const;

	Coords posToCoords(float x, float y) const;
	bool areCoordsInBounds(GridSize col, GridSize row) const;
private:
	std::vector<GridPartitionCell<T>> cells_;
	GridSize numCols_;
	GridSize numRows_;
	GridSize cellSizeTiles_;

	void addToTargetIfPossible_(std::vector<T *> &target, GridSize col, GridSize row) const;

	GridSize spatialHashPos_(float x, float y) const;
	GridSize spatialHashCoords_(GridSize col, GridSize row) const;
};

template<typename T>
GridPartition<T>::GridPartition(
	GridSize numCols,
	GridSize numRows,
	GridSize cellSizeTiles)
	:
	cells_(numCols * numRows, GridPartitionCell<T>()),
	numCols_(numCols),
	numRows_(numRows),
	cellSizeTiles_(cellSizeTiles)
{}

template<typename T>
void GridPartition<T>::add(T *object)
{
	cells_[this->spatialHashPos_(object->getX(), object->getY())].add(object);
}

template<typename T>
void GridPartition<T>::remove(T *object)
{
	cells_[this->spatialHashPos_(object->getX(), object->getY())].remove(object);
}

template<typename T>
std::vector<T *> GridPartition<T>::getItemsCloseToPos(float x, float y) const
{
	Coords coords = std::move(this->posToCoords(x, y));

	return this->getItemsCloseToCoords(coords.col, coords.row);
}

template<typename T>
std::vector<T *> GridPartition<T>::getItemsCloseToCoords(GridSize col, GridSize row) const
{
	std::vector<T *> items;

	for (GridSize colIt = -1; colIt <= 1; ++colIt)
	{
		for (GridSize rowIt = -1; rowIt <= 1; ++rowIt)
		{
			this->addToTargetIfPossible_(items, col + colIt, row + rowIt);
		}
	}

	return items;
}

template<typename T>
typename GridPartition<T>::Coords GridPartition<T>::posToCoords(float x, float y) const
{
	float invCellSize = 1.0f / (cellSizeTiles_ * Constants::tileSize);

	return Coords(
		static_cast<GridSize>(x * invCellSize),
		static_cast<GridSize>(y * invCellSize));
}

template<typename T>
bool GridPartition<T>::areCoordsInBounds(GridSize col, GridSize row) const
{
	return col >= 0 && row >= 0 && col < numCols_ && row < numRows_;
}

template<typename T>
void GridPartition<T>::addToTargetIfPossible_(std::vector<T *> &target, GridSize col, GridSize row) const
{
	if (!this->areCoordsInBounds(col, row))
		return;

	std::vector<T *> items = cells_[this->spatialHashCoords_(col, row)].getItems();

	target.insert(
		target.end(),
		items.begin(), items.end());
}

template<typename T>
typename GridPartition<T>::GridSize GridPartition<T>::spatialHashPos_(float x, float y) const
{
	Coords coords = std::move(this->posToCoords(x, y));

	return this->spatialHashCoords_(coords.col, coords.row);
}

template<typename T>
typename GridPartition<T>::GridSize GridPartition<T>::spatialHashCoords_(GridSize col, GridSize row) const
{
	return col + row * numCols_;
}