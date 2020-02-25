// CInformationDlg.cpp: 实现文件
//

#include "pch.h"
#include "StudentManagementSystem.h"
#include "CInformationDlg.h"
#include "CInforInsertDlg.h"
#include "afxdialogex.h"
#include "mysql.h"
#include <string>
#include "MysqlManagement.h"
#include "CInforQuery.h"
#include "CInforChangeDlg.h"

using namespace std;

//全局变量
static CString str_change_id, str_change_name, str_chage_class;

// CInformationDlg 对话框

IMPLEMENT_DYNAMIC(CInformationDlg, CDialogEx)

CInformationDlg::CInformationDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_INFORMATION, pParent)
	
{

}

CInformationDlg::~CInformationDlg()
{
}

void CInformationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_COMBO1, m_cbx_infor);
	DDX_Control(pDX, IDC_LIST2, m_list_infor);
}


BEGIN_MESSAGE_MAP(CInformationDlg, CDialogEx)

	ON_CBN_SELCHANGE(IDC_COMBO1, &CInformationDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &CInformationDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CInformationDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CInformationDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CInformationDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CInformationDlg 消息处理程序


BOOL CInformationDlg::OnInitDialog()
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
				//插入下拉框
				for (int i = 0; i < fieldcount; i++) 
				{
					CString str =CString(row[i]);
					m_cbx_infor.AddString(str);
				}
				//取下一行
				row = mysql_fetch_row(result);
			}
		}
		mysql_close(&m_sqlCon);//断开连接
	}
	//设置下拉框默认显示选项
	m_cbx_infor.SetCurSel(0);
	



	//设置列表框
	CString str1[7] = { TEXT("学号"),TEXT("姓名") };
	//设置表头 参数1索引 2内容 3对齐方式 4列宽度
	for (int i = 0; i < 2; i++)
	{
		m_list_infor.InsertColumn(i, str1[i], LVFIF_TEXT, 100);
	}
	//设置列表框属性  整行选中状态 显示网格 复选框
	m_list_infor.SetExtendedStyle(m_list_infor.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );

	//显示当前下拉框的数据
	OnCbnSelchangeCombo1();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}




void CInformationDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码

	//切换班级触发事件  显示学生信息
	//切换班级，清空表的上个班级内容
		m_list_infor.DeleteAllItems();
	//先获取当前下拉框班级索引
		CString Cname;
	int index = m_cbx_infor.GetCurSel();
	//根据索引获取班级名称
	m_cbx_infor.GetLBText(index, Cname);
	//全局变量赋值
	str_chage_class = Cname;

	//关联对应数据   显示在列表框
	MYSQL m_sqlCon;
	//初始化数据库对象  
	mysql_init(&m_sqlCon);
	mysql_options(&m_sqlCon, MYSQL_SET_CHARSET_NAME, "GB2312");
  
	if (!mysql_real_connect(&m_sqlCon, "localhost", "root",
		"2005", "gradesystem", 3306, NULL, 0))
	{
		AfxMessageBox(_T("数据库连接失败!"));

	}
	else//连接成功则继续访问数据库，之后的相关操作代码基本是放在这里面的  
	{
		//AfxMessageBox(_T("数据库连接成功!"));

		//查询班级表_班级id，班级表_班级，学生表_学号，学生表_姓名 按班级编号排序
		string str = "SELECT tb_class.clid,tb_class.clname,tb_student.stuid,tb_student.stuname FROM tb_class, tb_student WHERE tb_student.clid = tb_class.clid ORDER BY clid";
		MYSQL_RES* result = NULL;
		if (0 == mysql_query(&m_sqlCon, str.c_str()))
		{
			//一次性取得数据集
			result = mysql_store_result(&m_sqlCon);
			//取得字段列数
			unsigned int fieldcount = mysql_num_fields(result);
			//取得字段行数
			int rowcount = mysql_num_rows(result);
			//生成行数组
			MYSQL_ROW row = NULL;
			row = mysql_fetch_row(result);
			MYSQL_FIELD* field_class = NULL;
			int m = 0;// 列表框第一行  索引从0开始
			int n = 1;//列表框第二列
			//数据插入列表框正文
			for (int j = 0; j < fieldcount; j++)//遍历列
			{
				field_class = mysql_fetch_field_direct(result, j);//第j列字段
				if (strcmp(field_class->name, "clname") == 0)//取班级字段列
				{
					while (row != NULL)//行数组不空
					{
						if (Cname == row[j] )//取当前下拉框班级的行
						{
							// 插入列表框
							CString str1;
							str1 = CString(row[j+1]);
							m_list_infor.InsertItem(m, str1);//插入学号
							CString str2;
							str2 = CString(row[j + 2]);
							m_list_infor.SetItemText(m,n, str2);	//插入姓名
							m++;
						}
						row = mysql_fetch_row(result);//取下一行
					}
				}
			}
		}
		mysql_close(&m_sqlCon);//断开连接
	}
}


void CInformationDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	//弹出录入界面
	CInforInsertDlg dlg;
	dlg.DoModal();
}


void CInformationDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码

	//查询按钮
	//弹出查询界面
	CInforQueryDlg dlg;
	dlg.DoModal();

}


void CInformationDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码

	//弹出更改界面
	CInforChangeDlg dlg;
	bool flag=0;//标记是否选取列表项

	MysqlManagement mysql_operat;


	{
		//for (int i = 0; i < m_list_infor.GetItemCount(); i++)
		//{
		//	BOOL check = m_list_infor.GetCheck(i);
		//	//if (check)//如果勾选该项
		//	//{
		//	//	//MessageBox(TEXT("check"));

		//	//}
		//}

		UINT i, uSelectedCount = m_list_infor.GetSelectedCount();//选定项数目
		int  nItem = -1;
		//CString str_change_id, str_change_name;
		// Update all of the selected items.
		if (uSelectedCount > 0)
		{
			for (i = 0; i < uSelectedCount; i++)
			{
				nItem = m_list_infor.GetNextItem(nItem, LVNI_SELECTED);//取得鼠标选定项的索引
				/*ASSERT(nItem != -1);
				m_list_infor.Update(nItem);*/
				/*CString str;
				str.Format(TEXT("%d"), nItem);
				MessageBox(str);*/

				//全局变量str_change_id   str_change_name
				str_change_id=m_list_infor.GetItemText(nItem, 0);//获得nitem行第1列的内容  学号
				str_change_name= m_list_infor.GetItemText(nItem, 1);//获得nitem行第2列的内容  姓名
				//MessageBox(str_change_name);
				flag = 1;//已选取
			}
		}
		
		
	}
	if (flag)
	{
		dlg.DoModal();
	}
	else 
	{
		MessageBox(TEXT("请选择要更改的项"));
	}
}

//要更改的姓名
CString getname()
{
	return str_change_name;
}
//要更改的学号
CString getid()
{
	return str_change_id;
}
//要更改的班级
CString getclass()
{
	return str_chage_class;
}



void CInformationDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	//删除按钮
	bool flag = 0;//标记是否选取列表项
	CString Cstuid;
	MysqlManagement mysql_opera;
	string Sstuid;
	UINT i, uSelectedCount = m_list_infor.GetSelectedCount();//选定项数目
	int  nItem = -1;
	if (uSelectedCount > 0)
	{
		for (i = 0; i < uSelectedCount; i++)
		{
			nItem = m_list_infor.GetNextItem(nItem, LVNI_SELECTED);//取得鼠标选定项的索引

			Cstuid = m_list_infor.GetItemText(nItem, 0);//获得nitem行第1列的内容  学号
			Sstuid = CT2A(Cstuid.GetString());// CString -> string
			flag = 1;//已选取
		}
	}

	if (flag)
	{
		mysql_opera.DeleteStudent(Sstuid);
	}
	else
	{
		MessageBox(TEXT("请选择要删除的项"));
	}

}
