#pragma once
#include <vector>
#include "Histogram.h"
#include "DoubleSlider.h"
//#include "Triangle.h"
// HistogramCtrl 对话框

class HistogramCtrl : public CDialogEx
{
	DECLARE_DYNAMIC(HistogramCtrl)

public:
	HistogramCtrl(CWnd* pParent = nullptr);   // 标准构造函数
	HistogramCtrl(CRect _rect, CWnd* pParent = nullptr);
	virtual ~HistogramCtrl();

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
	//CRect    lowRect;
	//CRect    upRect;
	CPoint   posStart;
	bool     isMoveSlider = false;
	int      sliderFlag;
	Histograme*   pHisto;
	DoubleSlider* pDouSlider;
public:
	bool PaintHisto(CDC* pDC, Histograme _histo);
	bool PaintGrid(CDC* pDC, Histograme _histo);
	bool PaintHistoValue(CDC* pDC, Histograme _histo);
	bool PaintDoubleSlider(CDC* pDC);
	//bool PaintTriangle(CDC* pDC, const Triangle& _triangle, COLORREF color);
};
