// HistogramCtrl.cpp: 实现文件
//

#include "pch.h"
#include <algorithm>
#include <cmath>
#include "afxdialogex.h"
#include "HistogramMFC.h"
#include "HistogramCtrl.h"

#define random(a,b) (rand()%(b-a)+a)


using namespace std;

// HistogramCtrl 对话框

IMPLEMENT_DYNAMIC(HistogramCtrl, CDialogEx)

HistogramCtrl::HistogramCtrl(CWnd* pParent /*=nullptr*/)
	:CDialogEx(IDD_FORMVIEW, pParent)
{
	pHisto = nullptr;
	pDouSlider = nullptr;
	sliderFlag = -1;
	rect = CRect();
}

HistogramCtrl::HistogramCtrl(CRect _rect, CWnd* pParent)
	: CDialogEx(IDD_FORMVIEW, pParent)
{
	pHisto = nullptr;
	pDouSlider = nullptr;
	sliderFlag = -1;
	rect = _rect;

}

HistogramCtrl::~HistogramCtrl()
{
	delete pHisto;
	delete pDouSlider;
}

void HistogramCtrl::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(HistogramCtrl, CDialogEx)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// HistogramCtrl 消息处理程序


void HistogramCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (pDouSlider->leftSlider.PtInRect(point))
	{
		isMoveSlider = true;
		sliderFlag = 0;
	}

	if (pDouSlider->rightSlider.PtInRect(point))
	{
		isMoveSlider = true;
		sliderFlag = 1;
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void HistogramCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (isMoveSlider == true)
	{
		//posStart = leftTriangel.center;
		isMoveSlider = false;
		sliderFlag = -1;
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}


void HistogramCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (pDouSlider->leftSlider.PtInRect(point) || pDouSlider->rightSlider.PtInRect(point))
		SetClassLongPtr(this->GetSafeHwnd(), -12, (LONG)LoadCursorA(NULL, IDC_SIZEWE));
	else
		SetClassLongPtr(this->GetSafeHwnd(), -12, (LONG)LoadCursorA(NULL, IDC_ARROW));


	if (isMoveSlider)
	{
		switch (sliderFlag)
		{
		case 0:
			pDouSlider->SetLeftSliderPos(point.x);
			break;

		case 1:
			pDouSlider->SetRightSliderPos(point.x);
			break;

		default:
			break;
		}

		Invalidate(true);
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


BOOL HistogramCtrl::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化

	this->MoveWindow(rect);
	CRect _rect;
	this->GetClientRect(_rect);
	_rect.top += 50;
	_rect.bottom -= 50;
	_rect.left += 50;
	_rect.right -= 50;

	std::array<int, 256> histoValue{};
	for (size_t i = 0; i < histoValue.size(); i++)
	{
		int a = random(1, 60);
		histoValue[i] = a;
	}
	pHisto = new Histograme(_rect, histoValue);
	pDouSlider = new DoubleSlider(_rect);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void HistogramCtrl::OnPaint()
{

	CPaintDC dc(this);
	CDC      cacheDc;
	CBitmap  cacheCBitmap;

	CRect rc;
	GetClientRect(&rc);
	cacheDc.CreateCompatibleDC(&dc);
	cacheCBitmap.CreateCompatibleBitmap(&dc, rc.Width(), rc.Height());
	CBitmap* pOldBit = cacheDc.SelectObject(&cacheCBitmap);
	cacheDc.FillSolidRect(rc, GetSysColor(COLOR_WINDOW));

	PaintHisto(&cacheDc, *pHisto, pDouSlider->leftSlider.CenterPoint().x, pDouSlider->rightSlider.CenterPoint().x);
	PaintDoubleSlider(&cacheDc);

	dc.BitBlt(0, 0, rc.right, rc.bottom, &cacheDc, 0, 0, SRCCOPY);

	cacheCBitmap.DeleteObject();
	cacheDc.DeleteDC();
	CDialogEx::OnPaint();
}


BOOL HistogramCtrl::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return true;
}


//bool HistogramCtrl::PaintHisto(CDC* pDC, Histograme _histo, int leftValue, int rightValue);
//{
//
//}


bool HistogramCtrl::PaintHisto(CDC* pDC, Histograme _histo, int leftValue, int rightValue)
{
	CPen solidPen(PS_SOLID, 1, RGB(192, 192, 192));
	CPen dothPen(PS_DOT, 1, RGB(192, 192, 192));
	pDC->SelectObject(solidPen);
	pDC->Rectangle(_histo.posRect);
	PaintGrid(pDC, _histo);
	PaintHistoValue(pDC, _histo, leftValue, rightValue);
	return false;
}

bool HistogramCtrl::PaintGrid(CDC* pDC, Histograme _histo)
{

	size_t valueSize = _histo.histoValue.size();

	std::vector<int> scaleValueX;
	std::vector<int> scaleValueY;

	for (size_t i = 0; i < 256; i = i + 5)
		scaleValueX.push_back(int(i * _histo.stepX));

	int maxY = *(std::min_element(std::begin(_histo.histoValue), std::end(_histo.histoValue)));
	int maxHeight = (int)std::ceil((maxY * 100) / 10);

	int scaleStep = 2;
	if (maxHeight > 3)
		scaleStep = int(std::pow(2, (maxHeight / 3)));

	for (size_t i = 0; i <= maxHeight * 10; i = i + scaleStep)
		scaleValueY.push_back(int(i * _histo.stepY));

	CPen graySolidPen(PS_SOLID, 1, RGB(192, 192, 192));
	CPen grayDothPen(PS_DOT, 1, RGB(192, 192, 192));

	CPen blackThickPen(PS_SOLID, 2, RGB(0, 0, 0));
	CPen blackThinPen(PS_SOLID, 1, RGB(0, 0, 0));

	CFont font;
	font.CreateFontA(13, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("宋体"));

	// 画网格和刻度标记
	for (size_t i = 0; i < scaleValueX.size(); i++)
	{
		if (i % 5 == 0)
			pDC->SelectObject(graySolidPen);
		else
			pDC->SelectObject(grayDothPen);

		pDC->MoveTo(scaleValueX[i] + _histo.posRect.left, _histo.posRect.bottom - 1);
		pDC->LineTo(scaleValueX[i] + _histo.posRect.left, _histo.posRect.top);

		if (i % 5 == 0)
		{
			pDC->SelectObject(blackThickPen);
			pDC->MoveTo(scaleValueX[i] + _histo.posRect.left, _histo.posRect.bottom + 10);
			pDC->LineTo(scaleValueX[i] + _histo.posRect.left, _histo.posRect.bottom + 5);

			CString str;
			str.Format("%d", (int)std::round(scaleValueX[i] / _histo.stepX));
			pDC->SelectObject(font);
			pDC->TextOutA(scaleValueX[i] - 13 + _histo.posRect.left, _histo.posRect.bottom + 15, str);
		}
	}


	for (size_t i = 0; i < scaleValueY.size(); i++)
	{
		if (i % 5 == 0)
			pDC->SelectObject(graySolidPen);
		else
			pDC->SelectObject(grayDothPen);

		pDC->MoveTo(_histo.posRect.left, _histo.posRect.bottom - scaleValueY[i]);
		pDC->LineTo(_histo.posRect.right, _histo.posRect.bottom - scaleValueY[i]);

		if (i % 5 == 0)
			pDC->SelectObject(blackThickPen);
		else
			pDC->SelectObject(graySolidPen);
		pDC->MoveTo(_histo.posRect.left - 10, _histo.posRect.bottom - scaleValueY[i]);
		pDC->LineTo(_histo.posRect.left - 5, _histo.posRect.bottom - scaleValueY[i]);

		if (i % 5 == 0)
		{
			pDC->SelectObject(font);
			CString str;
			str.Format("%d", (int)std::round(scaleValueY[i] / _histo.stepY));
			pDC->TextOutA(_histo.posRect.left - 30, _histo.posRect.bottom - scaleValueY[i] - 7, str);
		}

	}
	return 0;
}

bool HistogramCtrl::PaintHistoValue(CDC* pDC, Histograme _histo, int leftValue, int rightValue)
{
	CPen blueSolidPen(PS_SOLID, (int)std::ceil(_histo.stepX), RGB(0, 0, 255));
	CPen graySolidPen(PS_SOLID, (int)std::ceil(_histo.stepX), RGB(192, 192, 192));
	for (size_t i = 0; i < _histo.histoValue.size(); i++)
	{
		if (i * _histo.stepX + _histo.posRect.left < leftValue || i * _histo.stepX + _histo.posRect.left >rightValue)
			pDC->SelectObject(graySolidPen);
		else
			pDC->SelectObject(blueSolidPen);

		if (_histo.histoValue[i] > 0)
		{
			pDC->MoveTo(int(i * _histo.stepX + _histo.posRect.left), _histo.posRect.bottom);
			pDC->LineTo(int(i * _histo.stepX + _histo.posRect.left), int(_histo.posRect.bottom - _histo.histoValue[i] * _histo.stepY));
		}

	}
	return false;
}


bool HistogramCtrl::PaintDoubleSlider(CDC* pDC)
{
	CPen greenPen(PS_SOLID, 2, RGB(0, 255, 0));
	CPen redPen(PS_SOLID, 2, RGB(255, 0, 0));

	CFont font;
	font.CreateFontA(13, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("宋体"));

	int leftCenterX = (pDouSlider->leftSlider.left + pDouSlider->leftSlider.right) / 2;
	int rightCenterX = (pDouSlider->rightSlider.left + pDouSlider->rightSlider.right) / 2;
	pDC->SelectObject(greenPen);
	pDC->MoveTo(leftCenterX, pDouSlider->leftSlider.bottom);
	pDC->LineTo(leftCenterX, pDouSlider->leftSlider.top);
	pDC->SetTextColor(RGB(0, 255, 0));
	CString str;
	str.Format("%d", (int)((leftCenterX - 50) / pHisto->stepX));
	pDC->TextOutA(leftCenterX + 10, pDouSlider->leftSlider.top + pDouSlider->leftSlider.Height() * 0.1, str);



	pDC->SelectObject(redPen);
	pDC->MoveTo(rightCenterX, pDouSlider->rightSlider.bottom);
	pDC->LineTo(rightCenterX, pDouSlider->rightSlider.top);
	pDC->SetTextColor(RGB(255, 0, 0));
	str.Format("%d", (int)((rightCenterX - 50) / pHisto->stepX));
	pDC->TextOutA(rightCenterX - 30, pDouSlider->rightSlider.top + pDouSlider->rightSlider.Height() * 0.1, str);

	// TODO: 在此处添加实现代码.
	return false;
}


//bool HistogramCtrl::PaintTriangle(CDC* pDC, const Triangle& _triangle, COLORREF color)
//{
//	CRgn rgn;
//	CBrush brush;
//	pDC->Polygon(_triangle.data, 3);
//	rgn.CreatePolygonRgn(_triangle.data, 3, ALTERNATE/*WINDING*/);
//	brush.CreateSolidBrush(color);
//	pDC->FillRgn(&rgn, &brush);
//	brush.DeleteObject();
//	rgn.DeleteObject();
//	return true;
//}
