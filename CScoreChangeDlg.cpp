// CScoreChangeDlg.cpp: 实现文件
//

#include "pch.h"
#include "StudentManagementSystem.h"
#include "CScoreChangeDlg.h"
#include "afxdialogex.h"
#include "CScoreDlg.h"
#include "MysqlManagement.h"

// CScoreChangeDlg 对话框

IMPLEMENT_DYNAMIC(CScoreChangeDlg, CDialogEx)

CScoreChangeDlg::CScoreChangeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SCORE_CHANGE, pParent)
	, m_ScorChangeCjj(0)
	, m_ScorChangeMedia(0)
	, m_ScorChangeEnglish(0)
	, m_ScorChangeMath(0)
	, m_ScorChangePE(0)
	, m_ScorChangeMarix(0)
	, m_ScorChangeClass(_T(""))
	, m_ScorChangeName(_T(""))
	, m_ScorChangeId(0)
{

}

CScoreChangeDlg::~CScoreChangeDlg()
{
}

void CScoreChangeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT9, m_ScorChangeCjj);
	DDX_Text(pDX, IDC_EDIT12, m_ScorChangeMedia);
	DDX_Text(pDX, IDC_EDIT10, m_ScorChangeEnglish);
	DDX_Text(pDX, IDC_EDIT13, m_ScorChangeMath);
	DDX_Text(pDX, IDC_EDIT11, m_ScorChangePE);
	DDX_Text(pDX, IDC_EDIT14, m_ScorChangeMarix);
	DDX_Text(pDX, IDC_EDIT2, m_ScorChangeClass);
	DDX_Text(pDX, IDC_EDIT8, m_ScorChangeName);
	DDX_Text(pDX, IDC_EDIT1, m_ScorChangeId);
}


BEGIN_MESSAGE_MAP(CScoreChangeDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CScoreChangeDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CScoreChangeDlg 消息处理程序


void CScoreChangeDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();//取消enter功能
}


BOOL CScoreChangeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//学号
	m_ScorChangeId = _ttoi(getscor_id()); //CString -> int 
	//姓名
	m_ScorChangeName = getscor_name();
	//MessageBox(m_ScorChangeName);
	//班级
	m_ScorChangeClass = getscor_class();
	//MessageBox(m_ScorChangeClass);
	MysqlManagement mysql_opera;
	string Sstuid=CT2A(getscor_id().GetString());//CString -> string
	//成绩  CString -> double
	m_ScorChangeCjj= _wtof(mysql_opera.QueryCjjAtStuid(Sstuid));//根据学号查询C++成绩
	m_ScorChangeMedia = _wtof( mysql_opera.QueryMediaAtStuid(Sstuid));//根据学号查询多媒体技术成绩
	m_ScorChangeEnglish = _wtof(mysql_opera.QueryEglishAtStuid(Sstuid));//根据学号查询英语成绩
	m_ScorChangeMath = _wtof(mysql_opera.QueryMathAtStuid(Sstuid));//根据学号查询数学成绩
	m_ScorChangePE = _wtof(mysql_opera.QueryPEAtStuid(Sstuid));//根据学号查询体育成绩
	m_ScorChangeMarix = _wtof(mysql_opera.QueryMarixAtStuid(Sstuid));//根据学号查询马克思成绩
	//同步到控件
	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CScoreChangeDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//确定按钮
	UpdateData(true);//输入值同步到变量
	/*CString str;
	str.Format(TEXT("%.1f"), m_ScorInsertCjj);
	MessageBox(str);*/
	MysqlManagement mysql_opera;
	char Cstuid[10];
	snprintf(Cstuid, sizeof(Cstuid), "%d", m_ScorChangeId);//int -> char* 编辑框学号
	CString clid = mysql_opera.QueryClidAtClname(m_ScorChangeClass);//编辑框班级编号
	string CSclid = CT2A(clid.GetString());//CString -> string 
	//修改成绩
	char Cjj[10];
	snprintf(Cjj, sizeof(Cjj), "%.1f", m_ScorChangeCjj);//保留一位小数double -> char* 编辑框C++成绩
	mysql_opera.UpdateCjj(CSclid,Cjj, Cstuid);

	char Media[10];
	snprintf(Media, sizeof(Media), "%.1f", m_ScorChangeMedia);
	mysql_opera.UpdateMedia(CSclid, Media, Cstuid);

	char English[10];
	snprintf(English, sizeof(English), "%.1f", m_ScorChangeEnglish);
	mysql_opera.UpdateEnglish(CSclid, English, Cstuid);

	char Math[10];
	snprintf(Math, sizeof(Math), "%.1f", m_ScorChangeMath);
	mysql_opera.UpdateMath(CSclid, Math, Cstuid);

	char PE[10];
	snprintf(PE, sizeof(PE), "%.1f", m_ScorChangePE);
	mysql_opera.UpdatePE(CSclid, PE, Cstuid);

	char Marix[10];
	snprintf(Marix, sizeof(Marix), "%.1f", m_ScorChangeMarix);
	mysql_opera.UpdateMarix(CSclid, Marix, Cstuid);
	CDialogEx::OnOK();
}
