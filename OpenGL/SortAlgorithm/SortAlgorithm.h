#pragma once
#include "../BarChart/BarChart.h"
#include <vector>

class SortAlgorithm
{
public:
	SortAlgorithm(BarChart& barChart);
	virtual ~SortAlgorithm() {};
	virtual void sort() = 0;
	size_t getSwapIndex();
	const size_t getFirstSwapIndex() const;
	const size_t getSecondSwapIndex() const;
	const GLint getRectangleToHighlight() const;

	enum class SortType
	{
		None, BubbleSort, SelectionSort
	};

protected:
	BarChart& barChart;
	const std::vector<GLfloat>& rectangleVertices;
	size_t swapIndex, firstSwapIndex, secondSwapIndex;
	GLint rectangleToHighlight = 0;
	static constexpr size_t floatsPerRectangles = 8;
};