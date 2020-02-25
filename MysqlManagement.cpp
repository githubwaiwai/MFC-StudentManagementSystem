#include "pch.h"
#include "MysqlManagement.h"
#include "mysql.h"

//创建表
void MysqlManagement::CreateDatabase()
{
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
	else
	{
		//班级表
		string tb_class = "create table tb_class(clid int not null comment '班级编号',clname varchar(20) not null comment '班级名称',primary key(clid));";
		mysql_query(&m_sqlCon, tb_class.c_str());
		//学生表
		string tb_student = "create table tb_student(stuid int not null,stuname varchar(4) not null,clid int not null comment '班级编号', primary key(stuid));";
		mysql_query(&m_sqlCon, tb_student.c_str());
		//课程表
		string tb_course = "create table tb_course(cid int not null comment '课程编号',cname varchar(20) not null comment '课程名称',primary key(cid)); ";
		mysql_query(&m_sqlCon, tb_course.c_str());
		//成绩表
		string tb_mark = "create table tb_mark(mid int not null,clid int not null comment '班级编号',stuid int not null,cid int not null comment '课程编号',score decimal(4, 1) comment '成绩',primary key(mid)); ";
		mysql_query(&m_sqlCon, tb_mark.c_str());
		//设置
		string set1 = "alter table tb_student add constraint uni_id unique(stuid);";
		mysql_query(&m_sqlCon, set1.c_str());

		string set2 = "alter table tb_student add constraint fk_student_clid foreign key(clid) references tb_class(clid);";
		mysql_query(&m_sqlCon, set2.c_str());

		string set3 = "alter table tb_mark add constraint fk_mark_clid foreign key(clid) references tb_class(clid); ";
		mysql_query(&m_sqlCon, set3.c_str());

		string set4 = "alter table tb_mark add constraint fk_mark_stuid foreign key(stuid) references tb_student(stuid); ";
		mysql_query(&m_sqlCon, set4.c_str());

		string set5 = "alter table tb_mark add constraint fk_mark_cid foreign key(cid) references tb_course(cid); ";
		mysql_query(&m_sqlCon, set5.c_str());

		string set6 = "alter table tb_mark change mid mid int not null auto_increment; ";
		mysql_query(&m_sqlCon, set6.c_str());
		
		//插入班级表
		string insert_class = "insert into tb_class(clid,clname)values(1, '一班'),(2, '二班'),(3, '三班'),(4, '四班'),(5, '五班'),(6, '六班'),(7, '七班'),(8, '八班'),(9, '九班'),(10, '十班') ";
		mysql_query(&m_sqlCon, insert_class.c_str());

		//插入课程表
		string insert_course = "insert into tb_course(cid,cname)values(1, 'C++程序设计'),(2, '多媒体技术'),(3, '大学英语'),(4, '高等数学'),(5, '大学体育'),(6, '马克思主义政治经济学'); ";
		mysql_query(&m_sqlCon, insert_course.c_str());

		mysql_close(&m_sqlCon);//断开连接
	}
}

//查找班级
CString MysqlManagement::QueryClass(CString classname)
{
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
	else
	{
		//查找 
		string name = "SELECT clid, clname FROM tb_class  ORDER BY clid";
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
			MYSQL_FIELD* field_class = NULL;
			for (int j = 0; j < fieldcount; j++)//遍历列
			{
				field_class = mysql_fetch_field_direct(result, j);//第j列字段
				if (strcmp(field_class->name, "clname") == 0)//取班级名称字段列
				{
					while (row != NULL)//行数组不空
					{
						if (classname == row[j])//找到并返回
						{
							mysql_close(&m_sqlCon);//断开连接
							return classname;
						}
						row = mysql_fetch_row(result);//取下一行
					}
				}
			}
		}
		mysql_close(&m_sqlCon);//断开连接
		CString str = TEXT("该班级不存在");//找不到
		return str;
	}
}

//根据班级名称查找班级编号
CString MysqlManagement::QueryClidAtClname(CString classname)
{
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
	else
	{
		//查找 班级编号，班级名称，学号，学生姓名，按班级编号升序排序生成表
		string name = "SELECT clid,clname FROM tb_class  ORDER BY clid";
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
			MYSQL_FIELD* field_class = NULL;
			for (int j = 0; j < fieldcount; j++)//遍历列
			{
				field_class = mysql_fetch_field_direct(result, j);//第j列字段
				if (strcmp(field_class->name, "clname") == 0)//取班级名称字段列
				{
					while (row != NULL)//行数组不空
					{
						if (classname == row[j])//找到当前班级
						{
							mysql_close(&m_sqlCon);//断开连接
							return CString(row[j-1]);//返回班级编号   char* -> CString
						}
						row = mysql_fetch_row(result);//取下一行
					}
				}
			}
		}
		mysql_close(&m_sqlCon);//断开连接
		CString str = TEXT("该班级不存在");//找不到
		return str;
	}

}

//根据课程名称查找课程编号
CString MysqlManagement::QueryCidAtCname(CString cname)
{
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
	else
	{
		//查找 班级编号，班级名称，学号，学生姓名，按班级编号升序排序生成表
		string name = "SELECT cid,cname FROM tb_course  ORDER BY cid";
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
			MYSQL_FIELD* field_class = NULL;
			for (int j = 0; j < fieldcount; j++)//遍历列
			{
				field_class = mysql_fetch_field_direct(result, j);//第j列字段
				if (strcmp(field_class->name, "cname") == 0)//取课程名称字段列
				{
					while (row != NULL)//行数组不空
					{
						if (cname == row[j])//找到当前课程名称
						{
							mysql_close(&m_sqlCon);//断开连接
							return CString(row[j - 1]);//返回课程编号   char* -> CString
						}
						row = mysql_fetch_row(result);//取下一行
					}
				}
			}
		}
		mysql_close(&m_sqlCon);//断开连接
		CString str = TEXT("该课程不存在");//找不到
		return str;
	}
}

//根据学号查找班级名称
CString MysqlManagement::QueryClnameAtStuid(string stuid)
{
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
	else
	{
		string name = "SELECT tb_class.clid,tb_class.clname,tb_student.stuid,tb_student.stuname FROM tb_class, tb_student WHERE tb_student.clid = tb_class.clid ORDER BY clid; ";
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
			MYSQL_FIELD* field_class = NULL;
			for (int j = 0; j < fieldcount; j++)//遍历列
			{
				field_class = mysql_fetch_field_direct(result, j);//第j列字段
				if (strcmp(field_class->name, "stuid") == 0)//取学号字段列
				{
					while (row != NULL)//行数组不空
					{
						if (stuid == row[j])//找到当前学号
						{
							mysql_close(&m_sqlCon);//断开连接
							return CString(row[j - 1]);//返回班级名称   char* -> CString
						}
						row = mysql_fetch_row(result);//取下一行
					}
				}
			}
		}
		mysql_close(&m_sqlCon);//断开连接
		CString str = TEXT("查找失败");//找不到
		return str;
	}
}

//根据学号查找姓名
CString MysqlManagement::QueryStunameAtStuid(string stuid)
{
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
	else
	{
		string name = "SELECT tb_class.clid,tb_class.clname,tb_student.stuid,tb_student.stuname FROM tb_class, tb_student WHERE tb_student.clid = tb_class.clid ORDER BY clid; ";
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
			MYSQL_FIELD* field_class = NULL;
			for (int j = 0; j < fieldcount; j++)//遍历列
			{
				field_class = mysql_fetch_field_direct(result, j);//第j列字段
				if (strcmp(field_class->name, "stuid") == 0)//取学号字段列
				{
					while (row != NULL)//行数组不空
					{
						if (stuid == row[j])//找到当前学号
						{
							mysql_close(&m_sqlCon);//断开连接
							return CString(row[j + 1]);//返回姓名   char* -> CString
						}
						row = mysql_fetch_row(result);//取下一行
					}
				}
			}
		}
		mysql_close(&m_sqlCon);//断开连接
		CString str = TEXT("查找失败");//找不到
		return str;
	}
}


//根据学号修改姓名
void MysqlManagement::UpdateStunameAtStuid(string stuname, string stuid)
{
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
	else
	{
		//修改学号为 stuid 的姓名为 stuname
		string str = " update tb_student set stuname='"+ stuname + "'where stuid='"+stuid+"';";
		mysql_query(&m_sqlCon, str.c_str());
		mysql_close(&m_sqlCon);//断开连接
	}
}

//根据学号修改班级
void MysqlManagement::UpdateClidAtStuid(string clid, string stuid)
{
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
	else
	{
		//修改学号为 stuid 的姓名为 stuname
		string str = " update tb_student set clid='" + clid + "'where stuid='" + stuid + "';";
		mysql_query(&m_sqlCon, str.c_str());
		mysql_close(&m_sqlCon);//断开连接
	}
}

//修改学号
void MysqlManagement::UpdateStuid(string stuid, string new_stuid)
{
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
	else
	{
		//修改学号为 stuid 的学号为 new_stuid
		string str = " update tb_student set stuid='" + new_stuid + "'where stuid='" + stuid + "';";
		mysql_query(&m_sqlCon, str.c_str());
		mysql_close(&m_sqlCon);//断开连接
	}
}

//学生表中学号是否存在
bool MysqlManagement::StuidAtStudentIsExist(string stuid)
{
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
	else
	{
		//查找 班级编号，班级名称，学号，学生姓名，按班级编号升序排序生成表
		string name = "SELECT stuid FROM tb_student ; ";
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
			MYSQL_FIELD* field_class = NULL;
			for (int j = 0; j < fieldcount; j++)//遍历列
			{
				field_class = mysql_fetch_field_direct(result, j);//第j列字段
				if (strcmp(field_class->name, "stuid") == 0)//取学号字段列
				{
					while (row != NULL)//行数组不空
					{
						if (stuid == row[j])//找到当前学号
						{
							mysql_close(&m_sqlCon);//断开连接
							return true;//学号已存在
						}
						row = mysql_fetch_row(result);//取下一行
					}
				}
			}
		}
		mysql_close(&m_sqlCon);//断开连接
		return false;
	}
}

//成绩表中学号是否存在
bool MysqlManagement::StuidAtMarkIsExist(string stuid)
{
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
	else
	{
		//查找 班级编号，班级名称，学号，学生姓名，按班级编号升序排序生成表
		string name = "SELECT stuid FROM tb_mark ; ";
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
			MYSQL_FIELD* field_class = NULL;
			for (int j = 0; j < fieldcount; j++)//遍历列
			{
				field_class = mysql_fetch_field_direct(result, j);//第j列字段
				if (strcmp(field_class->name, "stuid") == 0)//取学号字段列
				{
					while (row != NULL)//行数组不空
					{
						if (stuid == row[j])//找到当前学号
						{
							mysql_close(&m_sqlCon);//断开连接
							return true;//学号已存在
						}
						row = mysql_fetch_row(result);//取下一行
					}
				}
			}
		}
		mysql_close(&m_sqlCon);//断开连接
		return false;
	}
}

//判断成绩表是否空
bool MysqlManagement::MarkIsEmpty()
{
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
	else
	{
		//查找 成绩表行数
		string name = "SELECT count(*) FROM tb_mark; ";
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
			MYSQL_FIELD* field_class = NULL;
			string str = "0";
			for (int j = 0; j < fieldcount; j++)//遍历列
			{

				while (row != NULL)//行数组不空
				{
					if (str == row[j])//行数为零
					{
						mysql_close(&m_sqlCon);//断开连接
						return true;//成绩表空
					}
					row = mysql_fetch_row(result);//取下一行
				}
			}
		}
		mysql_close(&m_sqlCon);//断开连接
		return false;
	}
}


//删除学号为stuid的信息
void MysqlManagement::DeleteStudent(string stuid)
{
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
	else
	{
		string set0 = "SET FOREIGN_KEY_CHECKS=0;";//取消外键约束
		mysql_query(&m_sqlCon, set0.c_str());

		//删除学生表中学号为 stuid 的学生信息
		string str1 = " delete from tb_student where stuid='" + stuid + "';";
		mysql_query(&m_sqlCon, str1.c_str());
		//成绩表中也要删除
		string str2 = " delete from tb_mark where stuid='" + stuid + "';";
		mysql_query(&m_sqlCon, str2.c_str());
		
		string set1 = "SET FOREIGN_KEY_CHECKS=1;";//增加外键约束
		mysql_query(&m_sqlCon, set1.c_str());
		mysql_close(&m_sqlCon);//断开连接
	}
}

//查询C++成绩
CString MysqlManagement::QueryCjjAtStuid(string stuid)
{
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
	else
	{
		//查找 班级编号，学号，课程编号，成绩  按班级编学号升序排序生成表
		string name = "SELECT clid,stuid,cid,score FROM tb_mark  ORDER BY stuid";
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
			MYSQL_FIELD* field_class = NULL;
			for (int j = 0; j < fieldcount; j++)//遍历列
			{
				field_class = mysql_fetch_field_direct(result, j);//第j列字段
				if (strcmp(field_class->name, "stuid") == 0)//取学号字段列
				{
					while (row != NULL)//行数组不空
					{
						if (stuid == row[j])//找到该学号
						{
							string str = "1";//C++课程编号
							if (str == row[j + 1])//找到C++的课程编号
							{
								mysql_close(&m_sqlCon);//断开连接
								return CString(row[j +2]);//返回成绩   char* -> CString
							}
						}
						row = mysql_fetch_row(result);//取下一行
					}
				}
			}
		}
		mysql_close(&m_sqlCon);//断开连接
		CString str = TEXT(" ");
		return str;//找不到返回空
	}
}

//查询多媒体技术成绩
CString MysqlManagement::QueryMediaAtStuid(string stuid)
{
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
	else
	{
		//查找 班级编号，学号，课程编号，成绩  按班级编学号升序排序生成表
		string name = "SELECT clid,stuid,cid,score FROM tb_mark  ORDER BY stuid";
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
			MYSQL_FIELD* field_class = NULL;
			for (int j = 0; j < fieldcount; j++)//遍历列
			{
				field_class = mysql_fetch_field_direct(result, j);//第j列字段
				if (strcmp(field_class->name, "stuid") == 0)//取学号字段列
				{
					while (row != NULL)//行数组不空
					{
						if (stuid == row[j])//找到该学号
						{
							string str = "2";//课程编号
							if (str == row[j + 1])//找到课程编号
							{
								mysql_close(&m_sqlCon);//断开连接
								return CString(row[j + 2]);//返回成绩   char* -> CString
							}
						}
						row = mysql_fetch_row(result);//取下一行
					}
				}
			}
		}
		mysql_close(&m_sqlCon);//断开连接
		CString str = TEXT(" ");
		return str;//找不到返回空
	}
}

//查询英语成绩
CString MysqlManagement::QueryEglishAtStuid(string stuid)
{
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
	else
	{
		//查找 班级编号，学号，课程编号，成绩  按班级编学号升序排序生成表
		string name = "SELECT clid,stuid,cid,score FROM tb_mark  ORDER BY stuid";
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
			MYSQL_FIELD* field_class = NULL;
			for (int j = 0; j < fieldcount; j++)//遍历列
			{
				field_class = mysql_fetch_field_direct(result, j);//第j列字段
				if (strcmp(field_class->name, "stuid") == 0)//取学号字段列
				{
					while (row != NULL)//行数组不空
					{
						if (stuid == row[j])//找到该学号
						{
							string str = "3";//课程编号
							if (str == row[j + 1])//找到课程编号
							{
								mysql_close(&m_sqlCon);//断开连接
								return CString(row[j + 2]);//返回成绩   char* -> CString
							}
						}
						row = mysql_fetch_row(result);//取下一行
					}
				}
			}
		}
		mysql_close(&m_sqlCon);//断开连接
		CString str = TEXT(" ");
		return str;//找不到返回空
	}
}

//查询数学成绩
CString MysqlManagement::QueryMathAtStuid(string stuid)
{
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
	else
	{
		//查找 班级编号，学号，课程编号，成绩  按班级编学号升序排序生成表
		string name = "SELECT clid,stuid,cid,score FROM tb_mark  ORDER BY stuid";
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
			MYSQL_FIELD* field_class = NULL;
			for (int j = 0; j < fieldcount; j++)//遍历列
			{
				field_class = mysql_fetch_field_direct(result, j);//第j列字段
				if (strcmp(field_class->name, "stuid") == 0)//取学号字段列
				{
					while (row != NULL)//行数组不空
					{
						if (stuid == row[j])//找到该学号
						{
							string str = "4";//课程编号
							if (str == row[j + 1])//找到课程编号
							{
								mysql_close(&m_sqlCon);//断开连接
								return CString(row[j + 2]);//返回成绩   char* -> CString
							}
						}
						row = mysql_fetch_row(result);//取下一行
					}
				}
			}
		}
		mysql_close(&m_sqlCon);//断开连接
		CString str = TEXT(" ");
		return str;//找不到返回空
	}
}

//查询体育成绩
CString MysqlManagement::QueryPEAtStuid(string stuid)
{
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
	else
	{
		//查找 班级编号，学号，课程编号，成绩  按班级编学号升序排序生成表
		string name = "SELECT clid,stuid,cid,score FROM tb_mark  ORDER BY stuid";
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
			MYSQL_FIELD* field_class = NULL;
			for (int j = 0; j < fieldcount; j++)//遍历列
			{
				field_class = mysql_fetch_field_direct(result, j);//第j列字段
				if (strcmp(field_class->name, "stuid") == 0)//取学号字段列
				{
					while (row != NULL)//行数组不空
					{
						if (stuid == row[j])//找到该学号
						{
							string str = "5";//课程编号
							if (str == row[j + 1])//找到课程编号
							{
								mysql_close(&m_sqlCon);//断开连接
								return CString(row[j + 2]);//返回成绩   char* -> CString
							}
						}
						row = mysql_fetch_row(result);//取下一行
					}
				}
			}
		}
		mysql_close(&m_sqlCon);//断开连接
		CString str = TEXT(" ");
		return str;//找不到返回空
	}
}

//查询马克思成绩
CString MysqlManagement::QueryMarixAtStuid(string stuid)
{
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
	else
	{
		//查找 班级编号，学号，课程编号，成绩  按班级编学号升序排序生成表
		string name = "SELECT clid,stuid,cid,score FROM tb_mark  ORDER BY stuid";
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
			MYSQL_FIELD* field_class = NULL;
			for (int j = 0; j < fieldcount; j++)//遍历列
			{
				field_class = mysql_fetch_field_direct(result, j);//第j列字段
				if (strcmp(field_class->name, "stuid") == 0)//取学号字段列
				{
					while (row != NULL)//行数组不空
					{
						if (stuid == row[j])//找到该学号
						{
							string str = "6";//课程编号
							if (str == row[j + 1])//找到课程编号
							{
								mysql_close(&m_sqlCon);//断开连接
								return CString(row[j + 2]);//返回成绩   char* -> CString
							}
						}
						row = mysql_fetch_row(result);//取下一行
					}
				}
			}
		}
		mysql_close(&m_sqlCon);//断开连接
		CString str = TEXT(" ");
		return str;//找不到返回空
	}
}

//根据学号插入C++成绩
void MysqlManagement::InsertCjj(string clid,string score, string stuid)
{
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
	else
	{
		string name = "insert into tb_mark(clid,stuid,cid,score)values('" + clid + "','" + stuid + "',1,'" + score + "'); ";
		mysql_query(&m_sqlCon, name.c_str());
		
		mysql_close(&m_sqlCon);//断开连接
	}
}

//根据学号插入多媒体技术成绩
void MysqlManagement::InsertMedia(string clid,string score, string stuid)
{
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
	else
	{
		string name = "insert into tb_mark(clid,stuid,cid,score)values('" + clid + "','" + stuid + "',2,'" + score + "'); ";
		mysql_query(&m_sqlCon, name.c_str());

		mysql_close(&m_sqlCon);//断开连接
	}
}

//根据学号插入英语成绩
void MysqlManagement::InsertEnglish(string clid,string score, string stuid)
{
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
	else
	{
		string name = "insert into tb_mark(clid,stuid,cid,score)values('" + clid + "','" + stuid + "',3,'" + score + "'); ";
		mysql_query(&m_sqlCon, name.c_str());

		mysql_close(&m_sqlCon);//断开连接
	}
}

//根据学号插入数学成绩
void MysqlManagement::InsertMath(string clid,string score, string stuid)
{
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
	else
	{
		string name = "insert into tb_mark(clid,stuid,cid,score)values('" + clid + "','" + stuid + "',4,'" + score + "'); ";
		mysql_query(&m_sqlCon, name.c_str());

		mysql_close(&m_sqlCon);//断开连接
	}
}

//根据学号插入体育成绩
void MysqlManagement::InsertPE(string clid,string score, string stuid)
{
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
	else
	{
		string name = "insert into tb_mark(clid,stuid,cid,score)values('" + clid + "','" + stuid + "',5,'" + score + "'); ";
		mysql_query(&m_sqlCon, name.c_str());

		mysql_close(&m_sqlCon);//断开连接
	}
}

//根据学号插入马克思成绩
void MysqlManagement::InsertMarix(string clid, string score, string stuid)
{
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
	else
	{
		string name = "insert into tb_mark(clid,stuid,cid,score)values('" + clid + "','" + stuid + "',6,'" + score + "'); ";
		mysql_query(&m_sqlCon, name.c_str());

		mysql_close(&m_sqlCon);//断开连接
	}
}

//根据学号班级修改C++成绩
void MysqlManagement::UpdateCjj(string clid, string score, string stuid)
{
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
	else
	{
		string name = "update tb_mark set score='" + score + "' where clid='" + clid + "' and stuid='" + stuid + "'and cid=1; ";
		mysql_query(&m_sqlCon, name.c_str());

		mysql_close(&m_sqlCon);//断开连接
	}
}

//根据学号班级修改多媒体技术成绩
void MysqlManagement::UpdateMedia(string clid, string score, string stuid)
{
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
	else
	{
		string name = "update tb_mark set score='" + score + "' where clid='" + clid + "' and stuid='" + stuid + "'and cid=2; ";
		mysql_query(&m_sqlCon, name.c_str());

		mysql_close(&m_sqlCon);//断开连接
	}
}

//根据学号班级修改英语成绩
void MysqlManagement::UpdateEnglish(string clid, string score, string stuid)
{
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
	else
	{
		string name = "update tb_mark set score='" + score + "' where clid='" + clid + "' and stuid='" + stuid + "'and cid=3; ";
		mysql_query(&m_sqlCon, name.c_str());

		mysql_close(&m_sqlCon);//断开连接
	}
}

//根据学号班级修改数学成绩
void MysqlManagement::UpdateMath(string clid, string score, string stuid)
{
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
	else
	{
		string name = "update tb_mark set score='" + score + "' where clid='" + clid + "' and stuid='" + stuid + "'and cid=4; ";
		mysql_query(&m_sqlCon, name.c_str());

		mysql_close(&m_sqlCon);//断开连接
	}
}

//根据学号班级修改体育成绩
void MysqlManagement::UpdatePE(string clid, string score, string stuid)
{
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
	else
	{
		string name = "update tb_mark set score='" + score + "' where clid='" + clid + "' and stuid='" + stuid + "'and cid=5; ";
		mysql_query(&m_sqlCon, name.c_str());

		mysql_close(&m_sqlCon);//断开连接
	}
}

//根据学号班级修改马克思成绩
void MysqlManagement::UpdateMarix(string clid, string score, string stuid)
{
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
	else
	{
		string name = "update tb_mark set score='" + score + "' where clid='" + clid + "' and stuid='" + stuid + "'and cid=6; ";
		mysql_query(&m_sqlCon, name.c_str());

		mysql_close(&m_sqlCon);//断开连接
	}
}

void MysqlManagement::DeleteScore(string stuid)
{
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
	else
	{
		//删除学生表中学号为 stuid 的成绩
		string str2 = " delete from tb_mark where stuid='" + stuid + "';";
		mysql_query(&m_sqlCon, str2.c_str());

		mysql_close(&m_sqlCon);//断开连接
	}
}

//按班级、科目求平均分
double MysqlManagement::ClassAverAtCourse(string cid, string clid)
{
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
	else
	{
		//aa.cc除以bb.dd 保留一位小数；
		//其中（cc是分数表中学号为clid,班级编号为cid的分数的和）作为aa；
		//其中(dd为学生表中班级编号为clid的行数）作为bb；
		string name = "select TRUNCATE( aa.cc/bb.dd,1 ) from (select sum(score) cc from tb_mark where clid='"+clid+"' and cid='" + cid + "') as aa,(select count(*)  dd from tb_student where clid='" + clid + "') as bb;";
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
			MYSQL_FIELD* field_class = NULL;
			char *str = NULL;
			for (int j = 0; j < fieldcount; j++)//遍历列
			{
				//mysql_close(&m_sqlCon);//断开连接
				//AfxMessageBox(CString(row[j]));
				mysql_close(&m_sqlCon);//断开连接
				if (row[j] == str)
				{
					AfxMessageBox(TEXT("成绩为空"));
					return 0;
				}
				else 
					return  atof(row[j]);//返回成绩   char* -> CString
				
			}
		}
		mysql_close(&m_sqlCon);//断开连接
	}
}

