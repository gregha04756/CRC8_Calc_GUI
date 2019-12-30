
// CRC8_Calc_GUIDlg.h : header file
//

#pragma once


// CCRC8CalcGUIDlg dialog
class CCRC8CalcGUIDlg : public CDialogEx
{
// Construction
public:
	CCRC8CalcGUIDlg(CWnd* pParent = nullptr);	// standard constructor
	CEdit m_Edit_Sequence;
	CButton m_Btn_Calculate;
	CButton m_Btn_Hex;
	CButton m_Btn_Decimal;
	afx_msg void OnChangeEditSequence();
	afx_msg void OnUpdateEditSequence();
	afx_msg void OnClickedBtnHex();
	//	afx_msg void OnBtnDecimal();
	afx_msg void OnBtnDecimal();
	afx_msg void OnClickedBtnCalc();
	CStatic m_CRC_Result;
	friend UCHAR CalculateCRC(UCHAR *Data, int DataLen);

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

private:
	int m_i_calls_ctr;
	BOOL Is_Valid_Hex(CString &str_in);
	BOOL Is_Valid_Char_Hex(CString &str_in);
	BOOL Is_Valid_Char_Decimal(CString &str_in);
	BOOL Is_Valid_Sequence(CEdit &e_in);
	CString *cvt_to_decimal(CString &str_in);
	CString *cvt_to_hexadecimal(CString &str_in);
	wchar_t const m_seps[2] = _T(" ");
	uint16_t Base16_to_Base10(wchar_t *u8_arg, int size);
	uint16_t Base10_to_Base16(wchar_t *u8_arg, int size);
	wchar_t *m_next_token = NULL;
	DECLARE_MESSAGE_MAP()

};
