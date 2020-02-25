#pragma once


// CScorInsertDlg 对话框

class CScorInsertDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CScorInsertDlg)

public:
	CScorInsertDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CScorInsertDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SCORE_INSERT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	double m_ScorInsertCjj;
	double m_ScorInsertMedia;
	double m_ScorInsertEnglish;
	double m_ScorInsertMath;
	double m_ScorInsertPE;
	double m_ScorInsertMarix;
	CComboBox m_cbx_scor_insertstudent;
	virtual void OnOK();
public:
	virtual BOOL OnInitDialog();
private:
	CComboBox m_cbx_scor_insertclass;
public:
	afx_msg void OnCbnSelchangeCombo2();
private:
	int m_ScorInsertStuid;
public:
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedOk();
};
