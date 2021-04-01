#pragma once

#include "Triangle.h"
// Histogram 对话框

class Histogram : public CDialogEx
{
	DECLARE_DYNAMIC(Histogram)

public:
	Histogram(CWnd* pParent = nullptr);   // 标准构造函数
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

private:
	Triangle leftTriangel;
	Triangle rightTriangel;
	CPoint   posStart;
	bool     isMoveTriangle = false;
	int      triangleFlag;
	
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
