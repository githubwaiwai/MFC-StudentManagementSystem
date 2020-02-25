// CInforChangeDlg.cpp: 实现文件
//

#include "pch.h"
#include "StudentManagementSystem.h"
#include "CInforChangeDlg.h"
#include "afxdialogex.h"
#include "CInformationDlg.h"
#include "MysqlManagement.h"

// CInforChangeDlg 对话框

IMPLEMENT_DYNAMIC(CInforChangeDlg, CDialogEx)

CInforChangeDlg::CInforChangeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_INFOR_CHANGE, pParent)
	, m_InforChangeId(0)
	, m_InforChangeClass(_T(""))
	, m_InforChangeName(_T(""))
{

}

CInforChangeDlg::~CInforChangeDlg()
{
}

void CInforChangeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_InforChangeId);
	DDX_Text(pDX, IDC_EDIT2, m_InforChangeClass);
	DDX_Text(pDX, IDC_EDIT3, m_InforChangeName);
}


BEGIN_MESSAGE_MAP(CInforChangeDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CInforChangeDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CInforChangeDlg 消息处理程序


void CInforChangeDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();//不接受enter退出对话框
}




BOOL CInforChangeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//学号
	m_InforChangeId = _ttoi(getid()); //CString -> int 
	//姓名
	m_InforChangeName = getname();   
	//MessageBox(m_InforChangeName);
	//班级
	m_InforChangeClass=getclass();
	//MessageBox(m_InforChangeClass);
	//同步到控件
	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CInforChangeDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//更改信息界面确定按钮
	//同步变量
	UpdateData(true);
	//MessageBox(m_InforChangeClass);
	CInformationDlg dlg;
	CString query_class, query_clid, query_name;
	string update_name,this_id,clid;
	update_name=CT2A(m_InforChangeName.GetString());//CString -> string
	this_id = to_string(m_InforChangeId);//int -> string
	MysqlManagement mysql_oper;
	//找到数据库要更改的班级
	query_class=mysql_oper.QueryClass(m_InforChangeClass);
	if (query_class == m_InforChangeClass)//班级存在
	{
		mysql_oper.UpdateStunameAtStuid(update_name, this_id);//修改学号this_id的姓名为update_name
		query_clid = mysql_oper.QueryClidAtClname(query_class);//查询班级的班级编号
		clid = CT2A(query_clid.GetString());//CString -> string
		mysql_oper.UpdateClidAtStuid(clid, this_id);//修改学号this_id的班级编号为clid
		//dlg.OnCbnSelchangeCombo1();更新列表
	}
	else
	{
		MessageBox(query_class);//找不到弹出“班级不存在”
	}
	CDialogEx::OnOK();
}
