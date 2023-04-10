#pragma once
#include "SortAlgorithm.h"
#include <iostream>

class SelectionSort final : public SortAlgorithm
{
public:
	SelectionSort(BarChart& barChart);

private:
	void sort() override;

	size_t indexOfMinimum;
};

