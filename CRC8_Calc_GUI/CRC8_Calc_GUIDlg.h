
// CRC8_Calc_GUIDlg.h : header file
//

#pragma once


// CCRC8CalcGUIDlg dialog
class CCRC8CalcGUIDlg : public CDialogEx
{
// Construction
public:
	CCRC8CalcGUIDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CRC8_CALC_GUI_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
