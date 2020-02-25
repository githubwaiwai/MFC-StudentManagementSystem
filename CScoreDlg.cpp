// CScoreDlg.cpp: 实现文件
//

#include "pch.h"
#include "StudentManagementSystem.h"
#include "CScoreDlg.h"
#include "afxdialogex.h"
#include "mysql.h"
#include <string>
#include "MysqlManagement.h"
#include "CScorInsertDlg.h"
#include "CScoreChangeDlg.h"
#include "CScoreQueryDlg.h"

//全局变量
static CString CHANGE_ID, CHANGE_NAME, CHANGE_CLASS;

using namespace std;


// CScoreDlg 对话框

IMPLEMENT_DYNAMIC(CScoreDlg, CDialogEx)

CScoreDlg::CScoreDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SCORE, pParent)
	, m_Scor_Average(0)
{

}

CScoreDlg::~CScoreDlg()
{
}

void CScoreDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_cbx_scor);
	DDX_Control(pDX, IDC_LIST1, m_list_scor);
	DDX_Control(pDX, IDC_COMBO2, m_cbx_scor_select);
	DDX_Text(pDX, IDC_EDIT1, m_Scor_Average);
}


BEGIN_MESSAGE_MAP(CScoreDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CScoreDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &CScoreDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CScoreDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CScoreDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &CScoreDlg::OnBnClickedButton3)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST1, &CScoreDlg::OnLvnColumnclickList1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CScoreDlg::OnCbnSelchangeCombo2)
END_MESSAGE_MAP()


// CScoreDlg 消息处理程序


BOOL CScoreDlg::OnInitDialog()
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
					CString str = CString(row[i]);
					m_cbx_scor.AddString(str);//班级下拉框
				}
				//取下一行
				row = mysql_fetch_row(result);
			}
		}
		//课程名称插入平均分下拉框
		string cour = "SELECT cname FROM tb_course";
		MYSQL_RES* result_cour = NULL;
		if (0 == mysql_query(&m_sqlCon, cour.c_str()))
		{
			//AfxMessageBox(_T("数据库连接成功!"));
			 //一次性取得数据集
			result_cour = mysql_store_result(&m_sqlCon);
			//取得字段数
			unsigned int fieldcount_cour = mysql_num_fields(result_cour);
			//生成行数组
			MYSQL_ROW row_cour = NULL;
			row_cour = mysql_fetch_row(result_cour);
			while (NULL != row_cour)
			{
				//插入下拉框
				for (int i = 0; i < fieldcount_cour; i++)
				{
					CString str = CString(row_cour[i]);
					m_cbx_scor_select.AddString(str);//平均分下拉框
				}
				//取下一行
				row_cour = mysql_fetch_row(result_cour);
			}
		}
		mysql_close(&m_sqlCon);//断开连接
	}
	//设置下拉框默认显示选项
	m_cbx_scor.SetCurSel(0);

	//设置列表框
	CString str1[8] = { TEXT("学号"),TEXT("姓名"),TEXT("C++ 程序设计"),TEXT("多媒体技术"),TEXT("大学英语"),TEXT("高等数学"),TEXT("大学体育"),TEXT("马克思主义政治经济学") };
	//设置表头 参数1索引 2内容 3对齐方式 4列宽度
	for (int i = 0; i < 8; i++)
	{
		m_list_scor.InsertColumn(i, str1[i], LVFIF_TEXT, 100);
	}
	//设置列表框属性  整行选中状态 显示网格 复选框
	m_list_scor.SetExtendedStyle(m_list_scor.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	//显示当前下拉框的数据
	OnCbnSelchangeCombo1();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CScoreDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码

	//切换班级触发事件  显示学生信息
	//切换班级，清空表的上个班级内容
	m_list_scor.DeleteAllItems();

	CString CNAME;
	//获取当前下拉框班级索引
	int index = m_cbx_scor.GetCurSel();
	//根据索引获取班级名称
	m_cbx_scor.GetLBText(index, CNAME);
	//全局变量赋值
	CHANGE_CLASS = CNAME;

	MysqlManagement mysql_opera;
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

		//插入学号 姓名
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
						if (CNAME == row[j]&&mysql_opera.StuidAtMarkIsExist(row[j+1]))//取当前下拉框班级的行且有成绩
						{
							// 插入列表框
							CString str1;
							str1 = CString(row[j + 1]);
							m_list_scor.InsertItem(m, str1);//插入学号
							CString str2;
							str2 = CString(row[j + 2]);
							m_list_scor.SetItemText(m, n, str2);	//插入姓名
							m_list_scor.SetItemText(m, n+1, mysql_opera.QueryCjjAtStuid(row[j+1]));	//插入C++成绩
							m_list_scor.SetItemText(m, n + 2, mysql_opera.QueryMediaAtStuid(row[j + 1]));	//插入多媒体技术成绩
							m_list_scor.SetItemText(m, n + 3, mysql_opera.QueryEglishAtStuid(row[j + 1]));	//插入英语成绩
							m_list_scor.SetItemText(m, n + 4, mysql_opera.QueryMathAtStuid(row[j + 1]));	//插入数学成绩
							m_list_scor.SetItemText(m, n + 5, mysql_opera.QueryPEAtStuid(row[j + 1]));	//插入体育成绩
							m_list_scor.SetItemText(m, n + 6, mysql_opera.QueryMarixAtStuid(row[j + 1]));	//插入马克思成绩
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


void CScoreDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	//弹出录入窗口
	CScorInsertDlg dlg;
	dlg.DoModal();
}



void CScoreDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	//弹出更改界面
	CScoreChangeDlg dlg;
	bool flag = 0;//标记是否选取列表项
		UINT i, uSelectedCount = m_list_scor.GetSelectedCount();//选定项数目
		int  nItem = -1;
		if (uSelectedCount > 0)
		{
			for (i = 0; i < uSelectedCount; i++)
			{
				nItem = m_list_scor.GetNextItem(nItem, LVNI_SELECTED);//取得鼠标选定项的索引
				/*ASSERT(nItem != -1);
				m_list_infor.Update(nItem);*/
				/*CString str;
				str.Format(TEXT("%d"), nItem);
				MessageBox(str);*/

				//全局变量static CString CHANGR_ID, CHANGE_NAME;
				CHANGE_ID = m_list_scor.GetItemText(nItem, 0);//获得nitem行第1列的内容  学号
				CHANGE_NAME = m_list_scor.GetItemText(nItem, 1);//获得nitem行第2列的内容  姓名
				//MessageBox(CHANGE_NAME);
				flag = 1;//已选取
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
CString getscor_name()
{
	return CHANGE_NAME;
}
//要更改的学号
CString getscor_id()
{
	return CHANGE_ID;
}
//要更改的班级
CString getscor_class()
{
	return CHANGE_CLASS;
}


void CScoreDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	//删除按钮
	bool flag = 0;//标记是否选取列表项
	UINT i, uSelectedCount = m_list_scor.GetSelectedCount();//选定项数目
	int  nItem = -1;
	if (uSelectedCount > 0)
	{
		for (i = 0; i < uSelectedCount; i++)
		{
			nItem = m_list_scor.GetNextItem(nItem, LVNI_SELECTED);//取得鼠标选定项的索引
			/*ASSERT(nItem != -1);
			m_list_infor.Update(nItem);*/
			/*CString str;
			str.Format(TEXT("%d"), nItem);
			MessageBox(str);*/

			//全局变量static CString CHANGR_ID, CHANGE_NAME;
			CHANGE_ID = m_list_scor.GetItemText(nItem, 0);//获得nitem行第1列的内容  学号
			CHANGE_NAME = m_list_scor.GetItemText(nItem, 1);//获得nitem行第2列的内容  姓名
			//MessageBox(CHANGE_NAME);
			flag = 1;//已选取
		}
	}
	if (flag)
	{
		MysqlManagement mysql_opera;
		string Sstuid = CT2A(CHANGE_ID.GetString());//CString -> string
		mysql_opera.DeleteScore(Sstuid);//删除成绩
	}
	else
	{
		MessageBox(TEXT("请选择要删除的项"));
	}
}


void CScoreDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	//弹出查询框
	CScoreQueryDlg dlg;
	dlg.DoModal();
}


DWORD  dwSelColID = 0; //选择的列
BOOL   bASC = FALSE;     //是否升序

void CScoreDlg::OnLvnColumnclickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	//点击列表头响应函数

	//点击列表框表头进行升序排序
	if (dwSelColID != pNMLV->iSubItem)//iSubItem 列标号  第二次点击时相等
	{
		dwSelColID = pNMLV->iSubItem;
		bASC = bASC;
	}
	else
		bASC = !bASC;
	int count = m_list_scor.GetItemCount();//列表行数
	for (int i = 0; i < count; i++)
		m_list_scor.SetItemData(i, i);//关联指定项 SetItemData（ int nItem, DWORD dwData ） 参数2 传给回调函数的形参1、形参2
	//排序函数  参数1 比较函数 参数2 输入给这个回调函数的一个参数,一般都是对应CListCtrl对象的指针
	//参数1 比较函数的地址 参数2 要传入比较函数的应用程序的值
	m_list_scor.SortItems(CompareFunc, (LPARAM)(&m_list_scor));

	*pResult = 0;

}

//回调函数  这里必须为一个独立的函数 或者类中的静态函数；
//参数1、参数2 都是系统传给这个回调函数的，具体数值就是上面SetItemData函数中的dwData
//参数3 是输入给这个回调函数的一个参数,一般都是对应CListCtrl对象的指针
static int CALLBACK CompareFunc(LPARAM   lParam1, LPARAM   lParam2, LPARAM   lParamSort)
{
	CListCtrl* pListCtrl = (CListCtrl*) lParamSort;//{这里面都是固定语法,适当了解
	LVFINDINFO findInfo;//LVFINDINFO 结构体 
	findInfo.flags = LVFI_PARAM;
	findInfo.lParam = lParam1;
	int iItem1 = pListCtrl->FindItem(&findInfo, -1);//参数1 包含要搜索的信息 参数2  -1从开头开始
	findInfo.lParam = lParam2;
	int iItem2 = pListCtrl->FindItem(&findInfo, -1);//这里面都是固定语法,适当了解}

	CString strItem1 = pListCtrl->GetItemText(iItem1, dwSelColID);   //需要研究  参数1 获得文本的索引 行 参数2 列
	CString strItem2 = pListCtrl->GetItemText(iItem2, dwSelColID);   //需要研究
	char* str1 = (char*)strItem1.GetBuffer(strItem1.GetLength());  //需要研究  GetLength 获得字符串字符数
	char* str2 = (char*)strItem2.GetBuffer(strItem1.GetLength());  //需要研究   int - > char * 


	if (bASC)
		return strcmp(str1, str2);
	else
		return strcmp(str2, str1);

}




void CScoreDlg::OnCbnSelchangeCombo2()
{
	// TODO: 在此添加控件通知处理程序代码
	//平均分下拉框切换
	MysqlManagement mysql_opera;
	CString cname;
	//获取当前下拉框索引
	int index = m_cbx_scor_select.GetCurSel();
	//根据索引获取名称
	m_cbx_scor_select.GetLBText(index, cname);
	//MessageBox(name);
	CString clname = CHANGE_CLASS;
	//mysql_opera.QueryCidAtCname(cname); //返回课程编号
	//mysql_opera.QueryClidAtClname(clname); //返回班级编号

	
	string Scid = CT2A(mysql_opera.QueryCidAtCname(cname).GetString());//CString -> string  课程编号
	string Sclid = CT2A(mysql_opera.QueryClidAtClname(clname).GetString());//班级编号

	if (mysql_opera.ClassAverAtCourse(Scid, Sclid) != NULL)
	{
		m_Scor_Average = mysql_opera.ClassAverAtCourse(Scid, Sclid);//平均分
	}
	else
	{
		m_Scor_Average = 0;
	}
	UpdateData(false);
}
