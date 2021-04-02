#pragma once
#pragma warning(disable: 26451)
#include <iostream>
#include <array>
#include <vector>
#include "Triangle.h"
// Histogram 对话框

class Histo
{
public:
	Histo() {};
	Histo(CRect _rect);
	~Histo();

public:
	CRect positionRt;

	double showRange = 0.56;
	std::array<int, 256> histoValue;
	std::vector<int> scaleValueX;
	std::vector<int> scaleValueY;

	double stepX;
	double stepY;

	bool SetPara();
};

class Histogram : public CDialogEx
{
	DECLARE_DYNAMIC(Histogram)

public:
	Histogram(CWnd* pParent = nullptr);   // 标准构造函数
	Histogram(CRect _rect, CWnd* pParent = nullptr);
	virtual ~Histogram();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORMVIEW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

private:
	CRect    rect;
	//Triangle leftTriangel;
	//Triangle rightTriangel;

	CRect    lowRect;
	CRect    upRect;
	CPoint   posStart;
	bool     isMoveTriangle = false;
	int      triangleFlag;
	Histo    histo;
public:
	bool PaintHisto(CDC* pDC, Histo _histo);
	//bool PaintTriangle(CDC* pDC, const Triangle& _triangle, COLORREF color);
	int  PaintGrid(CDC* pDC,Histo _histo);
	bool PaintHistoValue(CDC* pDC, Histo _histo);
	bool PaintTRect(CDC* pDC);
};
