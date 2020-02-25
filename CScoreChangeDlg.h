#pragma once


// CScoreChangeDlg 对话框

class CScoreChangeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CScoreChangeDlg)

public:
	CScoreChangeDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CScoreChangeDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SCORE_CHANGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
private:
	double m_ScorChangeCjj;
	double m_ScorChangeMedia;
	double m_ScorChangeEnglish;
	double m_ScorChangeMath;
	double m_ScorChangePE;
	double m_ScorChangeMarix;
	CString m_ScorChangeClass;
	CString m_ScorChangeName;
	int m_ScorChangeId;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
