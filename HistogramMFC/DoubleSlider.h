#pragma once

class Slider
{
	friend class DoubleSlider;

public:
	Slider() {};
	~Slider() {};
private:
	CRect  pos = CRect();
	double center = 0;
	//double value = 0;

public:
	bool SetPosition(CRect _pos);
};



class DoubleSlider
{

public:
	DoubleSlider() {};
	DoubleSlider(CRect _pos);
	~DoubleSlider() {};

public:

	//int    leftMin = 0;
	//int    rightMax = 0;
	CRect  leftSlider;
	CRect  rightSlider;
	CRect  pos;
	double step = 0;

public:
	void SetDoubleSliderPos(int leftOffsetX, int rightOffsetX);
	void SetLeftSliderPos(int offsetX);
	void SetRightSliderPos(int offsetX);
};


