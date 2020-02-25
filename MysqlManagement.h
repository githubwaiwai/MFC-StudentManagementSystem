#pragma once
#include <string>

using namespace std;


class MysqlManagement
{
public:
	//初始化
	void CreateDatabase();//创建数据表




	//信息
	CString QueryClass(CString classname);//查找班级
	CString QueryClidAtClname(CString classname);//根据班级名称查找班级编号
	CString QueryCidAtCname(CString cname);//根据课程名称查找课程编号
	CString QueryClnameAtStuid(string stuid);//根据学号查找班级名称
	CString QueryStunameAtStuid(string stuid);//根据学号查找姓名
	void UpdateStunameAtStuid(string stuname,string stuid);//根据学号修改姓名
	void UpdateClidAtStuid(string clid, string stuid);//根据学号修改班级
	void UpdateStuid(string stuid,string new_stuid);//修改学号
	bool StuidAtStudentIsExist(string stuid);//判断学生表中学号是否已存在
	bool StuidAtMarkIsExist(string stuid);//判断成绩表中学号是否已存在
	bool MarkIsEmpty();//判断成绩表是否空
	void DeleteStudent(string stuid);//删除学号为stuid的学生信息

	//成绩
	CString QueryCjjAtStuid(string stuid);//根据学号查询C++成绩
	CString QueryMediaAtStuid(string stuid);//根据学号查询多媒体技术成绩
	CString QueryEglishAtStuid(string stuid);//根据学号查询英语成绩
	CString QueryMathAtStuid(string stuid);//根据学号查询数学成绩
	CString QueryPEAtStuid(string stuid);//根据学号查询体育成绩
	CString QueryMarixAtStuid(string stuid);//根据学号查询马克思成绩

	void InsertCjj(string clid,string score,string stuid);//根据学号班级插入C++成绩
	void InsertMedia(string clid, string score, string stuid);//根据学号班级插入多媒体技术成绩
	void InsertEnglish(string clid, string score, string stuid);//根据学号班级插入英语成绩
	void InsertMath(string clid, string score, string stuid);//根据学号班级插入数学成绩
	void InsertPE(string clid, string score, string stuid);//根据学号班级插入体育成绩
	void InsertMarix(string clid, string score, string stuid);//根据学号班级插入马克思成绩

	void UpdateCjj(string clid, string score, string stuid);//根据学号班级修改C++成绩
	void UpdateMedia(string clid, string score, string stuid);//根据学号班级修改多媒体技术成绩
	void UpdateEnglish(string clid, string score, string stuid);//根据学号班级修改英语成绩
	void UpdateMath(string clid, string score, string stuid);//根据学号班级修改数学成绩
	void UpdatePE(string clid, string score, string stuid);//根据学号班级修改体育成绩
	void UpdateMarix(string clid, string score, string stuid);//根据学号班级修改马克思成绩
	void DeleteScore(string stuid);//删除学号为stuid的成绩
	double ClassAverAtCourse(string cid, string clid);//按班级、科目求平均分
};