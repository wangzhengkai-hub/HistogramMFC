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
	double stepX = 0;                        // X��ÿ����λ����ֵ��ռ��������
	double stepY = 0;                        // Y��ÿ����λ����ֵ��ռ��������

public:
	bool SetPara(CRect _rect, std::array<int, 256> _histoValue);                      // ʹ�ú��вι��캯����ɲ�ִ�д˲���
};

