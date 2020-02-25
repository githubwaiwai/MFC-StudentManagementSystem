// CScoreQueryDlg.cpp: 实现文件
//

#include "pch.h"
#include "StudentManagementSystem.h"
#include "CScoreQueryDlg.h"
#include "afxdialogex.h"
#include "MysqlManagement.h"


// CScoreQueryDlg 对话框

IMPLEMENT_DYNAMIC(CScoreQueryDlg, CDialogEx)

CScoreQueryDlg::CScoreQueryDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SCORE_QUERY, pParent)
	, m_ScorQueryId(0)
	, m_ScorQueryName(_T(""))
	, m_ScorQueryClass(_T(""))
	, m_ScorQueryCjj(0)
	, m_ScorQueryMedia(0)
	, m_ScorQueryEnglish(0)
	, m_ScorQueryMath(0)
	, m_ScorQueryPE(0)
	, m_ScorQueryMarix(0)
{

}

CScoreQueryDlg::~CScoreQueryDlg()
{
}

void CScoreQueryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_ScorQueryId);
	DDX_Text(pDX, IDC_EDIT2, m_ScorQueryName);
	DDX_Text(pDX, IDC_EDIT3, m_ScorQueryClass);
	DDX_Text(pDX, IDC_EDIT4, m_ScorQueryCjj);
	DDX_Text(pDX, IDC_EDIT7, m_ScorQueryMedia);
	DDX_Text(pDX, IDC_EDIT5, m_ScorQueryEnglish);
	DDX_Text(pDX, IDC_EDIT15, m_ScorQueryMath);
	DDX_Text(pDX, IDC_EDIT6, m_ScorQueryPE);
	DDX_Text(pDX, IDC_EDIT16, m_ScorQueryMarix);
}


BEGIN_MESSAGE_MAP(CScoreQueryDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CScoreQueryDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CScoreQueryDlg 消息处理程序


void CScoreQueryDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();取消enter功能
}


void CScoreQueryDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//查询学号 显示班级 姓名 成绩
	UpdateData(true);//输入编辑框数据同步到变量
	char Cid[10];
	snprintf(Cid, sizeof(Cid), "%d", m_ScorQueryId);//int -> char* 编辑框学号
	MysqlManagement mysql_opera;
	if (mysql_opera.StuidAtStudentIsExist(Cid))//学号存在
	{
		//查找
		m_ScorQueryName = mysql_opera.QueryStunameAtStuid(Cid);
		m_ScorQueryClass = mysql_opera.QueryClnameAtStuid(Cid);

		m_ScorQueryCjj=_wtof(mysql_opera.QueryCjjAtStuid(Cid));//根据学号查询C++成绩  CString -> double
		m_ScorQueryMedia=_wtof(mysql_opera.QueryMediaAtStuid(Cid));//根据学号查询多媒体技术成绩
		m_ScorQueryEnglish=_wtof(mysql_opera.QueryEglishAtStuid(Cid));//根据学号查询英语成绩
		m_ScorQueryMath=_wtof(mysql_opera.QueryMathAtStuid(Cid));//根据学号查询数学成绩
		m_ScorQueryPE=_wtof(mysql_opera.QueryPEAtStuid(Cid));//根据学号查询体育成绩
		m_ScorQueryMarix=_wtof(mysql_opera.QueryMarixAtStuid(Cid));//根据学号查询马克思成绩
		UpdateData(false);//同步到控件
	}
	else
	{
		MessageBox(TEXT("该学号不存在"));
	}
}
