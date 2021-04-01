
// HistogramMFCDlg.h: 头文件
//

#pragma once

#include "Histogram.h"


// CHistogramMFCDlg 对话框
class CHistogramMFCDlg : public CDialogEx
{
// 构造
public:
	CHistogramMFCDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HISTOGRAMMFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

private:
	Histogram* pHisto;
};
