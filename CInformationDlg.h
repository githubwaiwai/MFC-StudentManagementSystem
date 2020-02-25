#pragma once


// CInformationDlg 对话框

class CInformationDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInformationDlg)

public:
	CInformationDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CInformationDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_INFORMATION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
//	CString m_cbx_infor;
public:
	virtual BOOL OnInitDialog();
private:
	CComboBox m_cbx_infor;
	CListCtrl m_list_infor;

	

public:
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();
};

//全局变量传值
CString getname();//获得列表框要更改的姓名
CString getid();//获得列表框要更改的学号
CString getclass();//获得列表框要更改的班级
