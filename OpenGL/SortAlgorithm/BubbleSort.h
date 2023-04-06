#pragma once
#include "SortAlgorithm.h"
#include <iostream>
#include <cmath>

class BubbleSort final : public SortAlgorithm
{
public:
	BubbleSort(BarChart& barChart);

private:
	size_t sortIterator = 0, currentVertex = 1;
	bool swapOccurred = false;

	void sort() override;
};