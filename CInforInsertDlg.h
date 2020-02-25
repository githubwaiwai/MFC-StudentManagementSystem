#pragma once

// CInforInsertDlg 对话框

class CInforInsertDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInforInsertDlg)

public:
	CInforInsertDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CInforInsertDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_INFOR_INSERT};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	virtual void OnOK();
private:
	CString m_InforInsertClass;
	int m_InforInsertId;
	CString m_InforInsertName;


};
