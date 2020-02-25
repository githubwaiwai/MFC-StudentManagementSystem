#pragma once


// CScoreDlg 对话框

class CScoreDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CScoreDlg)

public:
	CScoreDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CScoreDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SCORE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
private:
	CComboBox m_cbx_scor;
	CListCtrl m_list_scor;
public:
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnLvnColumnclickList1(NMHDR* pNMHDR, LRESULT* pResult);

	

private:
	CComboBox m_cbx_scor_select;
	double m_Scor_Average;
public:
	afx_msg void OnCbnSelchangeCombo2();
};

//全局变量传值
CString getscor_name();//获得列表框要更改的姓名
CString getscor_id();//获得列表框要更改的学号
CString getscor_class();//获得列表框要更改的班级

//回调函数  
static int CALLBACK CompareFunc(LPARAM   lParam1, LPARAM   lParam2, LPARAM   lParamSort);