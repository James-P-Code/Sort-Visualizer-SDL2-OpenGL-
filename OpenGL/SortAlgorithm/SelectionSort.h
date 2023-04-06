#pragma once
#include "SortAlgorithm.h"
#include <iostream>

class SelectionSort :public SortAlgorithm
{
public:
	SelectionSort(BarChart& barChart);

private:
	void sort() override;

	static constexpr int numberOfRectangles = 100;
	size_t sortIterator = 0, currentRectangle = 1, indexOfMinimum = 0;
};

