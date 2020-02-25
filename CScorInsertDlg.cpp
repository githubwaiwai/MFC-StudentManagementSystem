// CScorInsertDlg.cpp: 实现文件
//

#include "pch.h"
#include "StudentManagementSystem.h"
#include "CScorInsertDlg.h"
#include "afxdialogex.h"
#include "CScoreDlg.h"
#include "mysql.h"
#include <string>
#include "MysqlManagement.h"
#include <vector>

//全局变量
static vector<int>stuid;//存储学号容器 
static CString INSERT_CLASS;

using namespace std;

// CScorInsertDlg 对话框

IMPLEMENT_DYNAMIC(CScorInsertDlg, CDialogEx)

CScorInsertDlg::CScorInsertDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SCORE_INSERT, pParent)
	, m_ScorInsertCjj(0)
	, m_ScorInsertMedia(0)
	, m_ScorInsertEnglish(0)
	, m_ScorInsertMath(0)
	, m_ScorInsertPE(0)
	, m_ScorInsertMarix(0)
	, m_ScorInsertStuid(0)
{

}

CScorInsertDlg::~CScorInsertDlg()
{
}

void CScorInsertDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_ScorInsertCjj);
	DDX_Text(pDX, IDC_EDIT5, m_ScorInsertMedia);
	DDX_Text(pDX, IDC_EDIT3, m_ScorInsertEnglish);
	DDX_Text(pDX, IDC_EDIT6, m_ScorInsertMath);
	DDX_Text(pDX, IDC_EDIT4, m_ScorInsertPE);
	DDX_Text(pDX, IDC_EDIT7, m_ScorInsertMarix);
	DDX_Control(pDX, IDC_COMBO1, m_cbx_scor_insertstudent);
	DDX_Control(pDX, IDC_COMBO2, m_cbx_scor_insertclass);
	DDX_Text(pDX, IDC_EDIT1, m_ScorInsertStuid);
}


BEGIN_MESSAGE_MAP(CScorInsertDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CScorInsertDlg::OnCbnSelchangeCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CScorInsertDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDOK, &CScorInsertDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CScorInsertDlg 消息处理程序


void CScorInsertDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();//取消enter功能
}


BOOL CScorInsertDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	////设置下拉框
	MYSQL m_sqlCon;
	//初始化数据库对象  
	mysql_init(&m_sqlCon);
	//设置数据库字符格式，解决中文乱码问题
	mysql_options(&m_sqlCon, MYSQL_SET_CHARSET_NAME, "GB2312");

	//localhost:服务器地址，可以直接填入IP;root:账号;  
	//2005:密码;gradesystem:数据库名;3306:网络端口    
	if (!mysql_real_connect(&m_sqlCon, "localhost", "root",
		"2005", "gradesystem", 3306, NULL, 0))
	{
		AfxMessageBox(_T("数据库连接失败!"));

	}
	else//连接成功则继续访问数据库，之后的相关操作代码基本是放在这里面的  
	{
		//AfxMessageBox(_T("数据库连接成功!"));

		//设置班级下拉框
			////显示插入的数据  clname 字段名 tb_class 表名
		string name = "SELECT clname FROM tb_class";
		MYSQL_RES* result = NULL;
		if (0 == mysql_query(&m_sqlCon, name.c_str()))
		{
			//AfxMessageBox(_T("数据库连接成功!"));
			 //一次性取得数据集
			result = mysql_store_result(&m_sqlCon);
			//取得字段数
			unsigned int fieldcount = mysql_num_fields(result);
			//生成行数组
			MYSQL_ROW row = NULL;
			row = mysql_fetch_row(result);
			while (NULL != row)
			{
				//插入班级下拉框
				for (int i = 0; i < fieldcount; i++)
				{
					CString str = CString(row[i]);
					m_cbx_scor_insertclass.AddString(str);
				}
				//取下一行
				row = mysql_fetch_row(result);
			}
		}
		mysql_close(&m_sqlCon);//断开连接
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CScorInsertDlg::OnCbnSelchangeCombo2()
{
	// TODO: 在此添加控件通知处理程序代码
	//切换班级下拉框事件
	m_cbx_scor_insertstudent.ResetContent();//清空学生下拉框
	stuid.clear();//清空学号容器
	//设置学生下拉框
	CString class_name;
	//获取当前班级下拉框班级索引
	int index = m_cbx_scor_insertclass.GetCurSel();
	//根据索引获取班级名称
	m_cbx_scor_insertclass.GetLBText(index, class_name);
	INSERT_CLASS = class_name;//全局变量赋值
	MysqlManagement mysql_opera;
	 CString class_id=mysql_opera.QueryClidAtClname(class_name);//获得班级编号
	string Sclass_id = CT2A(class_id.GetString());// CString -> string
	//MessageBox(class_id);

	MYSQL m_sqlCon;
	//初始化数据库对象  
	mysql_init(&m_sqlCon);
	//设置数据库字符格式，解决中文乱码问题
	mysql_options(&m_sqlCon, MYSQL_SET_CHARSET_NAME, "GB2312");

	//localhost:服务器地址，可以直接填入IP;root:账号;  
	//2005:密码;gradesystem:数据库名;3306:网络端口    
	if (!mysql_real_connect(&m_sqlCon, "localhost", "root",
		"2005", "gradesystem", 3306, NULL, 0))
	{
		AfxMessageBox(_T("数据库连接失败!"));

	}
	else//连接成功则继续访问数据库，之后的相关操作代码基本是放在这里面的  
	{
		//AfxMessageBox(_T("数据库连接成功!"));

		//设置学生下拉框
		string name = "SELECT stuid,stuname FROM tb_student WHERE clid='"+ Sclass_id +"'  ORDER BY stuid";
		MYSQL_RES* result = NULL;
		if (0 == mysql_query(&m_sqlCon, name.c_str()))
		{
			//AfxMessageBox(_T("数据库连接成功!"));
				//一次性取得数据集
			result = mysql_store_result(&m_sqlCon);
			//取得字段数
			unsigned int fieldcount = mysql_num_fields(result);
			//生成行数组
			MYSQL_ROW row = NULL;
			row = mysql_fetch_row(result);
			MYSQL_FIELD* field = NULL;
			////取得字段行数
			//int rowcount = mysql_num_rows(result);

			//插入学生下拉框
			for (int i=0,j = 0; i < fieldcount; i++)
			{
				field = mysql_fetch_field_direct(result, i);//第i列字段
				if (strcmp(field->name, "stuname") == 0)//取姓名字段列
				{
					while (NULL != row)
					{
						//如果学生表有学号，成绩表没有学号
						if (mysql_opera.StuidAtStudentIsExist(row[i - 1]) && !mysql_opera.StuidAtMarkIsExist(row[i - 1]))
						{
							CString str = CString(row[i]);
							m_cbx_scor_insertstudent.AddString(str);//插入下拉框
							stuid.push_back(atoi(row[i - 1]));//按插入姓名的顺序存入学号  char* -> int
						}
						j++;
						//取下一行
						row = mysql_fetch_row(result);
					}	
				}
			}
		}
		mysql_close(&m_sqlCon);//断开连接
	}
}


void CScorInsertDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	//学生下拉框切换事件
	MysqlManagement mysql_opera;
	CString student_name;
	//获取当前学生下拉框索引
	int index = m_cbx_scor_insertstudent.GetCurSel();
	////根据索引获取学生姓名
	//m_cbx_scor_insertstudent.GetLBText(index, student_name);
	//MessageBox(student_name);
	m_ScorInsertStuid = stuid[index];//显示当前学生下拉框的学号
	char Cid[10];
	snprintf(Cid, sizeof(Cid), "%d", m_ScorInsertStuid);//int -> char* 编辑框学号
	//成绩显示到编辑框
	m_ScorInsertCjj= _wtof(mysql_opera.QueryCjjAtStuid(Cid));//CString -> double 编辑框C++成绩
	m_ScorInsertMedia =_wtof(mysql_opera.QueryMediaAtStuid(Cid));
	m_ScorInsertEnglish= _wtof(mysql_opera.QueryEglishAtStuid(Cid));
	m_ScorInsertMarix = _wtof(mysql_opera.QueryMarixAtStuid(Cid));
	m_ScorInsertMath = _wtof(mysql_opera.QueryMathAtStuid(Cid));
	m_ScorInsertPE = _wtof(mysql_opera.QueryPEAtStuid(Cid));

	UpdateData(false);//同步到控件
}


void CScorInsertDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	//确定按钮
	UpdateData(true);//输入值同步到变量
	/*CString str;
	str.Format(TEXT("%.1f"), m_ScorInsertCjj);
	MessageBox(str);*/
	MysqlManagement mysql_opera;
	char Cstuid[10];
	snprintf(Cstuid, sizeof(Cstuid), "%d", m_ScorInsertStuid);//int -> char* 编辑框学号
	CString clid = mysql_opera.QueryClidAtClname(INSERT_CLASS);//下拉框班级编号
	string CSclid = CT2A(clid.GetString());//CString -> string 
	//录入成绩
	char Cjj[10];
	snprintf(Cjj, sizeof(Cjj), "%.1f", m_ScorInsertCjj);//保留一位小数double -> char* 编辑框C++成绩
	mysql_opera.InsertCjj(CSclid,Cjj, Cstuid);

	char Media[10];
	snprintf(Media, sizeof(Media), "%.1f", m_ScorInsertMedia);
	mysql_opera.InsertMedia(CSclid, Media, Cstuid);

	char English[10];
	snprintf(English, sizeof(English), "%.1f", m_ScorInsertEnglish);
	mysql_opera.InsertEnglish(CSclid, English, Cstuid);

	char Math[10];
	snprintf(Math, sizeof(Math), "%.1f", m_ScorInsertMath);
	mysql_opera.InsertMath(CSclid, Math, Cstuid);

	char PE[10];
	snprintf(PE, sizeof(PE), "%.1f", m_ScorInsertPE);
	mysql_opera.InsertPE(CSclid, PE, Cstuid);

	char Marix[10];
	snprintf(Marix, sizeof(Marix), "%.1f", m_ScorInsertMarix);
	mysql_opera.InsertMarix(CSclid, Marix, Cstuid);

	MessageBox(TEXT("录入成功！"));
	//CDialogEx::OnOK();
}
