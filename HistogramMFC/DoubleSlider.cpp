#include "pch.h"
#include "DoubleSlider.h"

bool Slider::SetPosition(CRect _pos)
{
	pos = _pos;
	center = (pos.left + pos.right) / 2.0;
    return false;
}

DoubleSlider::DoubleSlider(CRect _pos)
{
	pos = _pos;
	leftSlider = CRect(pos.left - 5, pos.top, pos.left + 5, pos.bottom);
	rightSlider = CRect(pos.right - 5, pos.top, pos.right + 5, pos.bottom);
}

void DoubleSlider::SetDoubleSliderPos(int leftOffsetX, int rightOffsetX)
{
	int leftPos = leftOffsetX + leftSlider.CenterPoint().x;
	int rightPos = rightOffsetX + rightSlider.CenterPoint().x;

	if (leftPos >= pos.left &&
		rightPos <= pos.right &&
		leftPos <= rightPos)
	{
		leftSlider.MoveToX(leftPos);
		rightSlider.MoveToX(rightPos);
	}
}

void DoubleSlider::SetLeftSliderPos(int leftPos)
{

	//int leftPos = offsetX + leftSlider.CenterPoint().x;
	if (leftPos > pos.left &&
		leftPos <= rightSlider.CenterPoint().x)
	{
		leftSlider.OffsetRect(leftPos-leftSlider.CenterPoint().x,0);
	}
}

void DoubleSlider::SetRightSliderPos(int rightPos)
{
	//int rightPos = offsetX + rightSlider.CenterPoint().x;
	if (rightPos < pos.right &&
		rightPos >= leftSlider.CenterPoint().x)
	{
		rightSlider.OffsetRect(rightPos- rightSlider.CenterPoint().x, 0);
	}
}

