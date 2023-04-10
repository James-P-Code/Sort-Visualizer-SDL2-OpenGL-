#pragma once
#include "SortAlgorithm.h"
#include <iostream>
#include <cmath>

class BubbleSort final : public SortAlgorithm
{
public:
	BubbleSort(BarChart& barChart);

private:
	bool swapOccurred;

	void sort() override;
};