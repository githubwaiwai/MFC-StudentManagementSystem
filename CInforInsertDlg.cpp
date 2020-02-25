// CInforInsertDlg.cpp: 实现文件
//

#include "pch.h"
#include "StudentManagementSystem.h"
#include "CInforInsertDlg.h"
#include "afxdialogex.h"
#include <string>
#include "mysql.h"
#include "CInformationDlg.h"

using namespace std;

// CInforInsertDlg 对话框

IMPLEMENT_DYNAMIC(CInforInsertDlg, CDialogEx)

CInforInsertDlg::CInforInsertDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_INFOR_INSERT, pParent)
	, m_InforInsertClass(_T(""))
	, m_InforInsertId(0)
	, m_InforInsertName(_T(""))
{

}

CInforInsertDlg::~CInforInsertDlg()
{
}

void CInforInsertDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_InforInsertClass);
	DDX_Text(pDX, IDC_EDIT2, m_InforInsertId);
	DDX_Text(pDX, IDC_EDIT3, m_InforInsertName);
}


BEGIN_MESSAGE_MAP(CInforInsertDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON3, &CInforInsertDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CInforInsertDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CInforInsertDlg 消息处理程序


void CInforInsertDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码

	//确定按钮
	UpdateData(true);//将控件值赋给变量

	//取值标记
	bool flag_class=1,flag_stuid=0;
	//取得编辑框填入值
	CString str_class,str_stuid,str_name,clid;
	str_class = m_InforInsertClass;
	str_stuid.Format(TEXT("%d"),m_InforInsertId);//int -> CString
	str_name = m_InforInsertName;
	//MessageBox(str);

	//查询班级表 取得要写入班级id
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
		//查询输入班级是否存在
		string Cname = "SELECT clid,clname FROM tb_class  ORDER BY clid";
		MYSQL_RES* result = NULL;
		if (0 == mysql_query(&m_sqlCon, Cname.c_str()))
		{
			//AfxMessageBox(_T("数据库连接成功!"));
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
				if (strcmp(field_class->name, "clname") == 0)//取班级字段列
				{
					while (row!= NULL)//行数组不空
					{
						if (str_class == row[j])//找到编辑框相同班级的行
						{
							clid = row[j - 1];//取得班级编号
							flag_class= 1;//标记取到
							break;
						}
						else
						{
							flag_class = 0;//未取到
						}
						row = mysql_fetch_row(result);//取下一行
					}
				}
			}
		}
		//查询输入学号是否存在
		string Iname = "SELECT stuid FROM tb_student ";
		MYSQL_RES* result_stuid = NULL;
		if (0 == mysql_query(&m_sqlCon,Iname.c_str()))
		{
			//AfxMessageBox(_T("数据库连接成功!"));
			//一次性取得数据集
			result_stuid = mysql_store_result(&m_sqlCon);
			//生成行数组
			MYSQL_ROW row_stuid = NULL;
			row_stuid = mysql_fetch_row(result_stuid);
		
			while (row_stuid != NULL)//行数组不空
			{
				if (str_stuid == row_stuid[0])//存在编辑框相同的学号
				{
					flag_stuid = 1;//标记取到
					break;
				}
				else
				{
					flag_stuid = 0;//未取到
				}
				row_stuid = mysql_fetch_row(result_stuid);//取下一行
			}
		}

		if (!str_class.IsEmpty() && !str_stuid.IsEmpty() && !str_name.IsEmpty())//编辑框都输入正确
		{
			string insert_clid = CT2A(clid.GetBuffer(0));//CString -> string
			string insert_stuid = CT2A(str_stuid.GetBuffer(0));
			string insert_name = CT2A(str_name.GetBuffer(0));
			//MessageBox(TEXT("输入正确"));
			if (!flag_class)
			{
				MessageBox(TEXT("输入班级不存在"));
			}
			else if (flag_stuid)
			{
				MessageBox(TEXT("输入学号已存在"));
			}
			// 写入数据库学生表     INSERT INTO 表名(字段1, 字段2,...) VALUES (值1, 值2,....)
			string query_insert = "insert into tb_student(stuid,stuname,clid) values('" + insert_stuid + "','" + insert_name + "','" + insert_clid + "')";
			if (0 == mysql_query(&m_sqlCon, query_insert.c_str()))
			{
				//MessageBox(TEXT("连接成功"));
			}
		}
			else if (str_class.IsEmpty() )
			{
				MessageBox(TEXT("请输入班级"));
			}
			else if (str_name.IsEmpty())
			{
				MessageBox(TEXT("请输入姓名"));
			}
		mysql_close(&m_sqlCon);//断开连接
	}
	//确定按钮，关闭当前对话框
	CInforInsertDlg::OnCancel();
}


void CInforInsertDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码

	//取消按钮  关闭当前对话框
	CInforInsertDlg::OnCancel();
}


void CInforInsertDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//注释掉 以免回车关闭对话框
	//CDialogEx::OnOK();
}
