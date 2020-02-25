#pragma once


// CScoreQueryDlg 对话框

class CScoreQueryDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CScoreQueryDlg)

public:
	CScoreQueryDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CScoreQueryDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SCORE_QUERY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	int m_ScorQueryId;
	CString m_ScorQueryName;
	CString m_ScorQueryClass;
	double m_ScorQueryCjj;
	double m_ScorQueryMedia;
	double m_ScorQueryEnglish;
	double m_ScorQueryMath;
	double m_ScorQueryPE;
	double m_ScorQueryMarix;
	virtual void OnOK();
public:
	afx_msg void OnBnClickedButton1();
};
