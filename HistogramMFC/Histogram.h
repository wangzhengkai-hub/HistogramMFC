#pragma once
#include <array>

class Histograme
{
public:
	Histograme() {};
	Histograme(CRect _rect, std::array<int, 256> _histoValue);
	~Histograme();

public:
	std::array<int, 256> histoValue{};
	CRect  posRect = CRect();
	double stepX = 0;                        // X轴每个单位的数值所占的像素数
	double stepY = 0;                        // Y轴每个单位的数值所占的像素数

public:
	bool SetPara(CRect _rect, std::array<int, 256> _histoValue);                      // 使用和有参构造函数后可不执行此操作
};

