#pragma once
#include <string>

using namespace std;


class MysqlManagement
{
public:
	//��ʼ��
	void CreateDatabase();//�������ݱ�




	//��Ϣ
	CString QueryClass(CString classname);//���Ұ༶
	CString QueryClidAtClname(CString classname);//���ݰ༶���Ʋ��Ұ༶���
	CString QueryCidAtCname(CString cname);//���ݿγ����Ʋ��ҿγ̱��
	CString QueryClnameAtStuid(string stuid);//����ѧ�Ų��Ұ༶����
	CString QueryStunameAtStuid(string stuid);//����ѧ�Ų�������
	void UpdateStunameAtStuid(string stuname,string stuid);//����ѧ���޸�����
	void UpdateClidAtStuid(string clid, string stuid);//����ѧ���޸İ༶
	void UpdateStuid(string stuid,string new_stuid);//�޸�ѧ��
	bool StuidAtStudentIsExist(string stuid);//�ж�ѧ������ѧ���Ƿ��Ѵ���
	bool StuidAtMarkIsExist(string stuid);//�жϳɼ�����ѧ���Ƿ��Ѵ���
	bool MarkIsEmpty();//�жϳɼ����Ƿ��
	void DeleteStudent(string stuid);//ɾ��ѧ��Ϊstuid��ѧ����Ϣ

	//�ɼ�
	CString QueryCjjAtStuid(string stuid);//����ѧ�Ų�ѯC++�ɼ�
	CString QueryMediaAtStuid(string stuid);//����ѧ�Ų�ѯ��ý�弼���ɼ�
	CString QueryEglishAtStuid(string stuid);//����ѧ�Ų�ѯӢ��ɼ�
	CString QueryMathAtStuid(string stuid);//����ѧ�Ų�ѯ��ѧ�ɼ�
	CString QueryPEAtStuid(string stuid);//����ѧ�Ų�ѯ�����ɼ�
	CString QueryMarixAtStuid(string stuid);//����ѧ�Ų�ѯ���˼�ɼ�

	void InsertCjj(string clid,string score,string stuid);//����ѧ�Ű༶����C++�ɼ�
	void InsertMedia(string clid, string score, string stuid);//����ѧ�Ű༶�����ý�弼���ɼ�
	void InsertEnglish(string clid, string score, string stuid);//����ѧ�Ű༶����Ӣ��ɼ�
	void InsertMath(string clid, string score, string stuid);//����ѧ�Ű༶������ѧ�ɼ�
	void InsertPE(string clid, string score, string stuid);//����ѧ�Ű༶���������ɼ�
	void InsertMarix(string clid, string score, string stuid);//����ѧ�Ű༶�������˼�ɼ�

	void UpdateCjj(string clid, string score, string stuid);//����ѧ�Ű༶�޸�C++�ɼ�
	void UpdateMedia(string clid, string score, string stuid);//����ѧ�Ű༶�޸Ķ�ý�弼���ɼ�
	void UpdateEnglish(string clid, string score, string stuid);//����ѧ�Ű༶�޸�Ӣ��ɼ�
	void UpdateMath(string clid, string score, string stuid);//����ѧ�Ű༶�޸���ѧ�ɼ�
	void UpdatePE(string clid, string score, string stuid);//����ѧ�Ű༶�޸������ɼ�
	void UpdateMarix(string clid, string score, string stuid);//����ѧ�Ű༶�޸����˼�ɼ�
	void DeleteScore(string stuid);//ɾ��ѧ��Ϊstuid�ĳɼ�
	double ClassAverAtCourse(string cid, string clid);//���༶����Ŀ��ƽ����
};