#pragma once


// CInforQuery 对话框

class CInforQueryDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInforQueryDlg)

public:
	CInforQueryDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CInforQueryDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_INFOR_QUERY};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	int m_InforQueryId;
	CString m_InforQueryClass;
	CString m_InforQueryName;
	virtual void OnOK();

public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton2();
};
