#pragma once


// CInforChangeDlg 对话框

class CInforChangeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInforChangeDlg)

public:
	CInforChangeDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CInforChangeDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_INFOR_CHANGE};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	int m_InforChangeId;
	CString m_InforChangeClass;
	CString m_InforChangeName;
	virtual void OnOK();
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
