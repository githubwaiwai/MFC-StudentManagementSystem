// CInforQuery.cpp: 实现文件
//

#include "pch.h"
#include "StudentManagementSystem.h"
#include "CInforQuery.h"
#include "afxdialogex.h"
#include "mysql.h"
#include <string>

using namespace std;


// CInforQuery 对话框

IMPLEMENT_DYNAMIC(CInforQueryDlg, CDialogEx)

CInforQueryDlg::CInforQueryDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_INFOR_QUERY, pParent)
	, m_InforQueryId(0)
	, m_InforQueryClass(_T(""))
	, m_InforQueryName(_T(""))
{

}

CInforQueryDlg::~CInforQueryDlg()
{
}

void CInforQueryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_InforQueryId);
	DDX_Text(pDX, IDC_EDIT2, m_InforQueryClass);
	DDX_Text(pDX, IDC_EDIT4, m_InforQueryName);
}


BEGIN_MESSAGE_MAP(CInforQueryDlg, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &CInforQueryDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON2, &CInforQueryDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CInforQuery 消息处理程序


void CInforQueryDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();//取消ENTER退出对话框
}





void CInforQueryDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CInforQueryDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码

	//查询学号显示班级、姓名
	UpdateData(true);//输入编辑框数据同步到变量
	CString str_id,str_class,str_name;
	bool flag=1;//标记找到学号
	str_id.Format(TEXT("%d"), m_InforQueryId);//int -> CString
	//MessageBox(str_id);
	/*m_InforQueryClass = TEXT("一班");
	UpdateData(false);*/
	MYSQL m_sqlCon;
	//初始化数据库对象  
	mysql_init(&m_sqlCon);
	//设置数据库字符格式，解决中文乱码问题
	mysql_options(&m_sqlCon, MYSQL_SET_CHARSET_NAME, "GB2312");
	if (!mysql_real_connect(&m_sqlCon, "localhost", "root",
		"2005", "gradesystem", 3306, NULL, 0))
	{
		AfxMessageBox(_T("数据库连接失败!"));

	}
	else
	{
		//查询 班级表_班级编号，班级表_班级名称，学生表_学号，学生表_姓名，按班级编号排序显示
		string str = "SELECT tb_class.clid,tb_class.clname,tb_student.stuid,tb_student.stuname FROM tb_class, tb_student WHERE tb_student.clid = tb_class.clid ORDER BY clid ";
		MYSQL_RES* result = NULL;
		if (0 == mysql_query(&m_sqlCon, str.c_str()))
		{
			//MessageBox(TEXT("连接成功"));
			//一次性取得数据集
			result = mysql_store_result(&m_sqlCon);
			//取得字段列数
			unsigned int fieldcount = mysql_num_fields(result);
			//生成行数组
			MYSQL_ROW row = NULL;
			row = mysql_fetch_row(result);
			MYSQL_FIELD* field_class = NULL;
			for (int j = 0; j < fieldcount; j++)//遍历列
			{
				field_class = mysql_fetch_field_direct(result, j);//第j列字段
				if (strcmp(field_class->name, "stuid") == 0)//取学号字段列
				{
					while (row != NULL)//行数组不空
					{
						if (str_id == row[j])//找到编辑框相同学号的行
						{
							str_class = row[j - 1];//取得班级名称
							str_name = row[j + 1];//取得姓名
							flag = 0;

							break;
						}
						else
						{
							flag = 1;
						}
						row = mysql_fetch_row(result);//取下一行
					}
				}
			}



		}
		mysql_close(&m_sqlCon);//断开连接
	}
	if (flag)
	{
		MessageBox(TEXT("该学号不存在"));
	}
	else
	{
	m_InforQueryClass = str_class;
	m_InforQueryName = str_name;
	UpdateData(false);//变量同步到编辑框显示
	}

}
