#pragma once
#include "../BarChart/BarChart.h"
#include <vector>

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
	const std::pair<size_t, size_t>& getSwapIndices() const; // indices of the swapped rectangles.  used to update the vertex buffer
	void setRectangleToHighlight(const GLint vertexIndexToHighlight);
	const GLint getRectangleToHighlight() const;

	enum class SortType
	{
		None, BubbleSort, SelectionSort
	};

protected:
	static constexpr size_t floatsPerRectangles = 8;
	BarChart& barChart;
	const std::vector<GLfloat>& rectangleVertices;
	std::pair<size_t, size_t> swapIndices;
	GLint rectangleToHighlight;
};