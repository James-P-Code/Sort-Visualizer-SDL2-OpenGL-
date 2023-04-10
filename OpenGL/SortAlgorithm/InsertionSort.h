#pragma once
#include "SortAlgorithm.h"

class InsertionSort final : public SortAlgorithm
{
public:
	InsertionSort(BarChart& barChart);

private:
	glm::vec2 keyVertex;
	bool newIteration, resetCurrentVertex;

	void sort() override;
};