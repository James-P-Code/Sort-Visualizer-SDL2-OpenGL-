#pragma once
#include <vector>
#include "../BarChart/BarChart.h"
#include "../Constants.h"

/* Because this program is driven by a loop in main, and a state design, each sort is an iterative version of its
*  respective algorithm.  That is, each sort is designed to only do one step at a time, rather than looping through 
*  the whole sort all at once like you might normally see with a sorting algorithm.  The main loop follows pattern of
*  handle events -> update -> render -> change state (if needed).  Every sort happens during the update step, where 
*  only one step of the sort is done and then we render that one step.   */

class SortAlgorithm
{
public:
	SortAlgorithm(BarChart& barChart);
	virtual ~SortAlgorithm() {};
	virtual void sort() = 0;
	const size_t getCurrentVertex() const;
	const GLint getRectangleToHighlight() const;
	const std::pair<size_t, size_t>& getSwapIndices() const; // indices of the swapped rectangles.  used to update the vertex buffer
	const bool updateSingleRectangle() const;

	enum class SortType
	{
		None, BubbleSort, SelectionSort, InsertionSort
	};

protected:
	BarChart& barChart;
	std::pair<size_t, size_t> swapIndices;
	bool updateSingleRectangleStatus;
	size_t currentVertex, sortIterator;
	GLint rectangleToHighlight;
};