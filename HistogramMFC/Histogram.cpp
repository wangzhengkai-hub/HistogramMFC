#include "pch.h"
#include "Histogram.h"
#include <algorithm>
#include <cmath>


Histograme::Histograme(CRect _rect, std::array<int, 256> _histoValue)
{
	posRect = _rect;
	histoValue = _histoValue;
	stepX = posRect.Width() / double(_histoValue.size());
	int maxY = *(std::min_element(std::begin(histoValue), std::end(histoValue)));
	int maxHeight = (int)std::ceil((maxY * 100) / 10);
	stepY = posRect.Height() / double(maxHeight * 10);
}

Histograme::~Histograme()
{
}


bool Histograme::SetPara(CRect _rect, std::array<int, 256> _histoValue)
{
	posRect = _rect;
	histoValue = _histoValue;
	stepX = posRect.Width() / 256.0;
	int maxY = *(std::min_element(std::begin(histoValue), std::end(histoValue)));
	int maxHeight = (int)std::ceil((maxY * 100) / 10);
	stepY = posRect.Height() / double(maxHeight * 10);
	return true;
}
