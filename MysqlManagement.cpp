#include "pch.h"
#include "MysqlManagement.h"
#include "mysql.h"

//������
void MysqlManagement::CreateDatabase()
{
	MYSQL m_sqlCon;
	//��ʼ�����ݿ����  
	mysql_init(&m_sqlCon);
	//�������ݿ��ַ���ʽ�����������������
	mysql_options(&m_sqlCon, MYSQL_SET_CHARSET_NAME, "GB2312");

	//localhost:��������ַ������ֱ������IP;root:�˺�;  
	//2005:����;gradesystem:���ݿ���;3306:����˿�    
	if (!mysql_real_connect(&m_sqlCon, "localhost", "root",
		"2005", "gradesystem", 3306, NULL, 0))
	{
		AfxMessageBox(_T("���ݿ�����ʧ��!"));
	}
	else
	{
		//�༶��
		string tb_class = "create table tb_class(clid int not null comment '�༶���',clname varchar(20) not null comment '�༶����',primary key(clid));";
		mysql_query(&m_sqlCon, tb_class.c_str());
		//ѧ����
		string tb_student = "create table tb_student(stuid int not null,stuname varchar(4) not null,clid int not null comment '�༶���', primary key(stuid));";
		mysql_query(&m_sqlCon, tb_student.c_str());
		//�γ̱�
		string tb_course = "create table tb_course(cid int not null comment '�γ̱��',cname varchar(20) not null comment '�γ�����',primary key(cid)); ";
		mysql_query(&m_sqlCon, tb_course.c_str());
		//�ɼ���
		string tb_mark = "create table tb_mark(mid int not null,clid int not null comment '�༶���',stuid int not null,cid int not null comment '�γ̱��',score decimal(4, 1) comment '�ɼ�',primary key(mid)); ";
		mysql_query(&m_sqlCon, tb_mark.c_str());
		//����
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
		
		//����༶��
		string insert_class = "insert into tb_class(clid,clname)values(1, 'һ��'),(2, '����'),(3, '����'),(4, '�İ�'),(5, '���'),(6, '����'),(7, '�߰�'),(8, '�˰�'),(9, '�Ű�'),(10, 'ʮ��') ";
		mysql_query(&m_sqlCon, insert_class.c_str());

		//����γ̱�
		string insert_course = "insert into tb_course(cid,cname)values(1, 'C++�������'),(2, '��ý�弼��'),(3, '��ѧӢ��'),(4, '�ߵ���ѧ'),(5, '��ѧ����'),(6, '���˼�������ξ���ѧ'); ";
		mysql_query(&m_sqlCon, insert_course.c_str());

		mysql_close(&m_sqlCon);//�Ͽ�����
	}
}

//���Ұ༶
CString MysqlManagement::QueryClass(CString classname)
{
	MYSQL m_sqlCon;
	//��ʼ�����ݿ����  
	mysql_init(&m_sqlCon);
	//�������ݿ��ַ���ʽ�����������������
	mysql_options(&m_sqlCon, MYSQL_SET_CHARSET_NAME, "GB2312");

	//localhost:��������ַ������ֱ������IP;root:�˺�;  
	//2005:����;gradesystem:���ݿ���;3306:����˿�    
	if (!mysql_real_connect(&m_sqlCon, "localhost", "root",
		"2005", "gradesystem", 3306, NULL, 0))
	{
		AfxMessageBox(_T("���ݿ�����ʧ��!"));
	}
	else
	{
		//���� 
		string name = "SELECT clid, clname FROM tb_class  ORDER BY clid";
		MYSQL_RES* result = NULL;
		if (0 == mysql_query(&m_sqlCon, name.c_str()))
		{
			//AfxMessageBox(_T("���ݿ����ӳɹ�!"));
			 //һ����ȡ�����ݼ�
			result = mysql_store_result(&m_sqlCon);
			//ȡ���ֶ���
			unsigned int fieldcount = mysql_num_fields(result);
			//����������
			MYSQL_ROW row = NULL;
			row = mysql_fetch_row(result);
			MYSQL_FIELD* field_class = NULL;
			for (int j = 0; j < fieldcount; j++)//������
			{
				field_class = mysql_fetch_field_direct(result, j);//��j���ֶ�
				if (strcmp(field_class->name, "clname") == 0)//ȡ�༶�����ֶ���
				{
					while (row != NULL)//�����鲻��
					{
						if (classname == row[j])//�ҵ�������
						{
							mysql_close(&m_sqlCon);//�Ͽ�����
							return classname;
						}
						row = mysql_fetch_row(result);//ȡ��һ��
					}
				}
			}
		}
		mysql_close(&m_sqlCon);//�Ͽ�����
		CString str = TEXT("�ð༶������");//�Ҳ���
		return str;
	}
}

//���ݰ༶���Ʋ��Ұ༶���
CString MysqlManagement::QueryClidAtClname(CString classname)
{
	MYSQL m_sqlCon;
	//��ʼ�����ݿ����  
	mysql_init(&m_sqlCon);
	//�������ݿ��ַ���ʽ�����������������
	mysql_options(&m_sqlCon, MYSQL_SET_CHARSET_NAME, "GB2312");

	//localhost:��������ַ������ֱ������IP;root:�˺�;  
	//2005:����;gradesystem:���ݿ���;3306:����˿�    
	if (!mysql_real_connect(&m_sqlCon, "localhost", "root",
		"2005", "gradesystem", 3306, NULL, 0))
	{
		AfxMessageBox(_T("���ݿ�����ʧ��!"));
	}
	else
	{
		//���� �༶��ţ��༶���ƣ�ѧ�ţ�ѧ�����������༶��������������ɱ�
		string name = "SELECT clid,clname FROM tb_class  ORDER BY clid";
		MYSQL_RES* result = NULL;
		if (0 == mysql_query(&m_sqlCon, name.c_str()))
		{
			//AfxMessageBox(_T("���ݿ����ӳɹ�!"));
			 //һ����ȡ�����ݼ�
			result = mysql_store_result(&m_sqlCon);
			//ȡ���ֶ���
			unsigned int fieldcount = mysql_num_fields(result);
			//����������
			MYSQL_ROW row = NULL;
			row = mysql_fetch_row(result);
			MYSQL_FIELD* field_class = NULL;
			for (int j = 0; j < fieldcount; j++)//������
			{
				field_class = mysql_fetch_field_direct(result, j);//��j���ֶ�
				if (strcmp(field_class->name, "clname") == 0)//ȡ�༶�����ֶ���
				{
					while (row != NULL)//�����鲻��
					{
						if (classname == row[j])//�ҵ���ǰ�༶
						{
							mysql_close(&m_sqlCon);//�Ͽ�����
							return CString(row[j-1]);//���ذ༶���   char* -> CString
						}
						row = mysql_fetch_row(result);//ȡ��һ��
					}
				}
			}
		}
		mysql_close(&m_sqlCon);//�Ͽ�����
		CString str = TEXT("�ð༶������");//�Ҳ���
		return str;
	}

}

//���ݿγ����Ʋ��ҿγ̱��
CString MysqlManagement::QueryCidAtCname(CString cname)
{
	MYSQL m_sqlCon;
	//��ʼ�����ݿ����  
	mysql_init(&m_sqlCon);
	//�������ݿ��ַ���ʽ�����������������
	mysql_options(&m_sqlCon, MYSQL_SET_CHARSET_NAME, "GB2312");

	//localhost:��������ַ������ֱ������IP;root:�˺�;  
	//2005:����;gradesystem:���ݿ���;3306:����˿�    
	if (!mysql_real_connect(&m_sqlCon, "localhost", "root",
		"2005", "gradesystem", 3306, NULL, 0))
	{
		AfxMessageBox(_T("���ݿ�����ʧ��!"));
	}
	else
	{
		//���� �༶��ţ��༶���ƣ�ѧ�ţ�ѧ�����������༶��������������ɱ�
		string name = "SELECT cid,cname FROM tb_course  ORDER BY cid";
		MYSQL_RES* result = NULL;
		if (0 == mysql_query(&m_sqlCon, name.c_str()))
		{
			//AfxMessageBox(_T("���ݿ����ӳɹ�!"));
			 //һ����ȡ�����ݼ�
			result = mysql_store_result(&m_sqlCon);
			//ȡ���ֶ���
			unsigned int fieldcount = mysql_num_fields(result);
			//����������
			MYSQL_ROW row = NULL;
			row = mysql_fetch_row(result);
			MYSQL_FIELD* field_class = NULL;
			for (int j = 0; j < fieldcount; j++)//������
			{
				field_class = mysql_fetch_field_direct(result, j);//��j���ֶ�
				if (strcmp(field_class->name, "cname") == 0)//ȡ�γ������ֶ���
				{
					while (row != NULL)//�����鲻��
					{
						if (cname == row[j])//�ҵ���ǰ�γ�����
						{
							mysql_close(&m_sqlCon);//�Ͽ�����
							return CString(row[j - 1]);//���ؿγ̱��   char* -> CString
						}
						row = mysql_fetch_row(result);//ȡ��һ��
					}
				}
			}
		}
		mysql_close(&m_sqlCon);//�Ͽ�����
		CString str = TEXT("�ÿγ̲�����");//�Ҳ���
		return str;
	}
}

//����ѧ�Ų��Ұ༶����
CString MysqlManagement::QueryClnameAtStuid(string stuid)
{
	MYSQL m_sqlCon;
	//��ʼ�����ݿ����  
	mysql_init(&m_sqlCon);
	//�������ݿ��ַ���ʽ�����������������
	mysql_options(&m_sqlCon, MYSQL_SET_CHARSET_NAME, "GB2312");

	//localhost:��������ַ������ֱ������IP;root:�˺�;  
	//2005:����;gradesystem:���ݿ���;3306:����˿�    
	if (!mysql_real_connect(&m_sqlCon, "localhost", "root",
		"2005", "gradesystem", 3306, NULL, 0))
	{
		AfxMessageBox(_T("���ݿ�����ʧ��!"));
	}
	else
	{
		string name = "SELECT tb_class.clid,tb_class.clname,tb_student.stuid,tb_student.stuname FROM tb_class, tb_student WHERE tb_student.clid = tb_class.clid ORDER BY clid; ";
		MYSQL_RES* result = NULL;
		if (0 == mysql_query(&m_sqlCon, name.c_str()))
		{
			//AfxMessageBox(_T("���ݿ����ӳɹ�!"));
			 //һ����ȡ�����ݼ�
			result = mysql_store_result(&m_sqlCon);
			//ȡ���ֶ���
			unsigned int fieldcount = mysql_num_fields(result);
			//����������
			MYSQL_ROW row = NULL;
			row = mysql_fetch_row(result);
			MYSQL_FIELD* field_class = NULL;
			for (int j = 0; j < fieldcount; j++)//������
			{
				field_class = mysql_fetch_field_direct(result, j);//��j���ֶ�
				if (strcmp(field_class->name, "stuid") == 0)//ȡѧ���ֶ���
				{
					while (row != NULL)//�����鲻��
					{
						if (stuid == row[j])//�ҵ���ǰѧ��
						{
							mysql_close(&m_sqlCon);//�Ͽ�����
							return CString(row[j - 1]);//���ذ༶����   char* -> CString
						}
						row = mysql_fetch_row(result);//ȡ��һ��
					}
				}
			}
		}
		mysql_close(&m_sqlCon);//�Ͽ�����
		CString str = TEXT("����ʧ��");//�Ҳ���
		return str;
	}
}

//����ѧ�Ų�������
CString MysqlManagement::QueryStunameAtStuid(string stuid)
{
	MYSQL m_sqlCon;
	//��ʼ�����ݿ����  
	mysql_init(&m_sqlCon);
	//�������ݿ��ַ���ʽ�����������������
	mysql_options(&m_sqlCon, MYSQL_SET_CHARSET_NAME, "GB2312");

	//localhost:��������ַ������ֱ������IP;root:�˺�;  
	//2005:����;gradesystem:���ݿ���;3306:����˿�    
	if (!mysql_real_connect(&m_sqlCon, "localhost", "root",
		"2005", "gradesystem", 3306, NULL, 0))
	{
		AfxMessageBox(_T("���ݿ�����ʧ��!"));
	}
	else
	{
		string name = "SELECT tb_class.clid,tb_class.clname,tb_student.stuid,tb_student.stuname FROM tb_class, tb_student WHERE tb_student.clid = tb_class.clid ORDER BY clid; ";
		MYSQL_RES* result = NULL;
		if (0 == mysql_query(&m_sqlCon, name.c_str()))
		{
			//AfxMessageBox(_T("���ݿ����ӳɹ�!"));
			 //һ����ȡ�����ݼ�
			result = mysql_store_result(&m_sqlCon);
			//ȡ���ֶ���
			unsigned int fieldcount = mysql_num_fields(result);
			//����������
			MYSQL_ROW row = NULL;
			row = mysql_fetch_row(result);
			MYSQL_FIELD* field_class = NULL;
			for (int j = 0; j < fieldcount; j++)//������
			{
				field_class = mysql_fetch_field_direct(result, j);//��j���ֶ�
				if (strcmp(field_class->name, "stuid") == 0)//ȡѧ���ֶ���
				{
					while (row != NULL)//�����鲻��
					{
						if (stuid == row[j])//�ҵ���ǰѧ��
						{
							mysql_close(&m_sqlCon);//�Ͽ�����
							return CString(row[j + 1]);//��������   char* -> CString
						}
						row = mysql_fetch_row(result);//ȡ��һ��
					}
				}
			}
		}
		mysql_close(&m_sqlCon);//�Ͽ�����
		CString str = TEXT("����ʧ��");//�Ҳ���
		return str;
	}
}


//����ѧ���޸�����
void MysqlManagement::UpdateStunameAtStuid(string stuname, string stuid)
{
	MYSQL m_sqlCon;
	//��ʼ�����ݿ����  
	mysql_init(&m_sqlCon);
	//�������ݿ��ַ���ʽ�����������������
	mysql_options(&m_sqlCon, MYSQL_SET_CHARSET_NAME, "GB2312");

	//localhost:��������ַ������ֱ������IP;root:�˺�;  
	//2005:����;gradesystem:���ݿ���;3306:����˿�    
	if (!mysql_real_connect(&m_sqlCon, "localhost", "root",
		"2005", "gradesystem", 3306, NULL, 0))
	{
		AfxMessageBox(_T("���ݿ�����ʧ��!"));
	}
	else
	{
		//�޸�ѧ��Ϊ stuid ������Ϊ stuname
		string str = " update tb_student set stuname='"+ stuname + "'where stuid='"+stuid+"';";
		mysql_query(&m_sqlCon, str.c_str());
		mysql_close(&m_sqlCon);//�Ͽ�����
	}
}

//����ѧ���޸İ༶
void MysqlManagement::UpdateClidAtStuid(string clid, string stuid)
{
	MYSQL m_sqlCon;
	//��ʼ�����ݿ����  
	mysql_init(&m_sqlCon);
	//�������ݿ��ַ���ʽ�����������������
	mysql_options(&m_sqlCon, MYSQL_SET_CHARSET_NAME, "GB2312");

	//localhost:��������ַ������ֱ������IP;root:�˺�;  
	//2005:����;gradesystem:���ݿ���;3306:����˿�    
	if (!mysql_real_connect(&m_sqlCon, "localhost", "root",
		"2005", "gradesystem", 3306, NULL, 0))
	{
		AfxMessageBox(_T("���ݿ�����ʧ��!"));
	}
	else
	{
		//�޸�ѧ��Ϊ stuid ������Ϊ stuname
		string str = " update tb_student set clid='" + clid + "'where stuid='" + stuid + "';";
		mysql_query(&m_sqlCon, str.c_str());
		mysql_close(&m_sqlCon);//�Ͽ�����
	}
}

//�޸�ѧ��
void MysqlManagement::UpdateStuid(string stuid, string new_stuid)
{
	MYSQL m_sqlCon;
	//��ʼ�����ݿ����  
	mysql_init(&m_sqlCon);
	//�������ݿ��ַ���ʽ�����������������
	mysql_options(&m_sqlCon, MYSQL_SET_CHARSET_NAME, "GB2312");

	//localhost:��������ַ������ֱ������IP;root:�˺�;  
	//2005:����;gradesystem:���ݿ���;3306:����˿�    
	if (!mysql_real_connect(&m_sqlCon, "localhost", "root",
		"2005", "gradesystem", 3306, NULL, 0))
	{
		AfxMessageBox(_T("���ݿ�����ʧ��!"));
	}
	else
	{
		//�޸�ѧ��Ϊ stuid ��ѧ��Ϊ new_stuid
		string str = " update tb_student set stuid='" + new_stuid + "'where stuid='" + stuid + "';";
		mysql_query(&m_sqlCon, str.c_str());
		mysql_close(&m_sqlCon);//�Ͽ�����
	}
}

//ѧ������ѧ���Ƿ����
bool MysqlManagement::StuidAtStudentIsExist(string stuid)
{
	MYSQL m_sqlCon;
	//��ʼ�����ݿ����  
	mysql_init(&m_sqlCon);
	//�������ݿ��ַ���ʽ�����������������
	mysql_options(&m_sqlCon, MYSQL_SET_CHARSET_NAME, "GB2312");

	//localhost:��������ַ������ֱ������IP;root:�˺�;  
	//2005:����;gradesystem:���ݿ���;3306:����˿�    
	if (!mysql_real_connect(&m_sqlCon, "localhost", "root",
		"2005", "gradesystem", 3306, NULL, 0))
	{
		AfxMessageBox(_T("���ݿ�����ʧ��!"));
	}
	else
	{
		//���� �༶��ţ��༶���ƣ�ѧ�ţ�ѧ�����������༶��������������ɱ�
		string name = "SELECT stuid FROM tb_student ; ";
		MYSQL_RES* result = NULL;
		if (0 == mysql_query(&m_sqlCon, name.c_str()))
		{
			//AfxMessageBox(_T("���ݿ����ӳɹ�!"));
			 //һ����ȡ�����ݼ�
			result = mysql_store_result(&m_sqlCon);
			//ȡ���ֶ���
			unsigned int fieldcount = mysql_num_fields(result);
			//����������
			MYSQL_ROW row = NULL;
			row = mysql_fetch_row(result);
			MYSQL_FIELD* field_class = NULL;
			for (int j = 0; j < fieldcount; j++)//������
			{
				field_class = mysql_fetch_field_direct(result, j);//��j���ֶ�
				if (strcmp(field_class->name, "stuid") == 0)//ȡѧ���ֶ���
				{
					while (row != NULL)//�����鲻��
					{
						if (stuid == row[j])//�ҵ���ǰѧ��
						{
							mysql_close(&m_sqlCon);//�Ͽ�����
							return true;//ѧ���Ѵ���
						}
						row = mysql_fetch_row(result);//ȡ��һ��
					}
				}
			}
		}
		mysql_close(&m_sqlCon);//�Ͽ�����
		return false;
	}
}

//�ɼ�����ѧ���Ƿ����
bool MysqlManagement::StuidAtMarkIsExist(string stuid)
{
	MYSQL m_sqlCon;
	//��ʼ�����ݿ����  
	mysql_init(&m_sqlCon);
	//�������ݿ��ַ���ʽ�����������������
	mysql_options(&m_sqlCon, MYSQL_SET_CHARSET_NAME, "GB2312");

	//localhost:��������ַ������ֱ������IP;root:�˺�;  
	//2005:����;gradesystem:���ݿ���;3306:����˿�    
	if (!mysql_real_connect(&m_sqlCon, "localhost", "root",
		"2005", "gradesystem", 3306, NULL, 0))
	{
		AfxMessageBox(_T("���ݿ�����ʧ��!"));
	}
	else
	{
		//���� �༶��ţ��༶���ƣ�ѧ�ţ�ѧ�����������༶��������������ɱ�
		string name = "SELECT stuid FROM tb_mark ; ";
		MYSQL_RES* result = NULL;
		if (0 == mysql_query(&m_sqlCon, name.c_str()))
		{
			//AfxMessageBox(_T("���ݿ����ӳɹ�!"));
			 //һ����ȡ�����ݼ�
			result = mysql_store_result(&m_sqlCon);
			//ȡ���ֶ���
			unsigned int fieldcount = mysql_num_fields(result);
			//����������
			MYSQL_ROW row = NULL;
			row = mysql_fetch_row(result);
			MYSQL_FIELD* field_class = NULL;
			for (int j = 0; j < fieldcount; j++)//������
			{
				field_class = mysql_fetch_field_direct(result, j);//��j���ֶ�
				if (strcmp(field_class->name, "stuid") == 0)//ȡѧ���ֶ���
				{
					while (row != NULL)//�����鲻��
					{
						if (stuid == row[j])//�ҵ���ǰѧ��
						{
							mysql_close(&m_sqlCon);//�Ͽ�����
							return true;//ѧ���Ѵ���
						}
						row = mysql_fetch_row(result);//ȡ��һ��
					}
				}
			}
		}
		mysql_close(&m_sqlCon);//�Ͽ�����
		return false;
	}
}

//�жϳɼ����Ƿ��
bool MysqlManagement::MarkIsEmpty()
{
	MYSQL m_sqlCon;
	//��ʼ�����ݿ����  
	mysql_init(&m_sqlCon);
	//�������ݿ��ַ���ʽ�����������������
	mysql_options(&m_sqlCon, MYSQL_SET_CHARSET_NAME, "GB2312");

	//localhost:��������ַ������ֱ������IP;root:�˺�;  
	//2005:����;gradesystem:���ݿ���;3306:����˿�    
	if (!mysql_real_connect(&m_sqlCon, "localhost", "root",
		"2005", "gradesystem", 3306, NULL, 0))
	{
		AfxMessageBox(_T("���ݿ�����ʧ��!"));
	}
	else
	{
		//���� �ɼ�������
		string name = "SELECT count(*) FROM tb_mark; ";
		MYSQL_RES* result = NULL;
		if (0 == mysql_query(&m_sqlCon, name.c_str()))
		{
			//AfxMessageBox(_T("���ݿ����ӳɹ�!"));
			 //һ����ȡ�����ݼ�
			result = mysql_store_result(&m_sqlCon);
			//ȡ���ֶ���
			unsigned int fieldcount = mysql_num_fields(result);
			//����������
			MYSQL_ROW row = NULL;
			row = mysql_fetch_row(result);
			MYSQL_FIELD* field_class = NULL;
			string str = "0";
			for (int j = 0; j < fieldcount; j++)//������
			{

				while (row != NULL)//�����鲻��
				{
					if (str == row[j])//����Ϊ��
					{
						mysql_close(&m_sqlCon);//�Ͽ�����
						return true;//�ɼ����
					}
					row = mysql_fetch_row(result);//ȡ��һ��
				}
			}
		}
		mysql_close(&m_sqlCon);//�Ͽ�����
		return false;
	}
}


//ɾ��ѧ��Ϊstuid����Ϣ
void MysqlManagement::DeleteStudent(string stuid)
{
	MYSQL m_sqlCon;
	//��ʼ�����ݿ����  
	mysql_init(&m_sqlCon);
	//�������ݿ��ַ���ʽ�����������������
	mysql_options(&m_sqlCon, MYSQL_SET_CHARSET_NAME, "GB2312");

	//localhost:��������ַ������ֱ������IP;root:�˺�;  
	//2005:����;gradesystem:���ݿ���;3306:����˿�    
	if (!mysql_real_connect(&m_sqlCon, "localhost", "root",
		"2005", "gradesystem", 3306, NULL, 0))
	{
		AfxMessageBox(_T("���ݿ�����ʧ��!"));
	}
	else
	{
		string set0 = "SET FOREIGN_KEY_CHECKS=0;";//ȡ�����Լ��
		mysql_query(&m_sqlCon, set0.c_str());

		//ɾ��ѧ������ѧ��Ϊ stuid ��ѧ����Ϣ
		string str1 = " delete from tb_student where stuid='" + stuid + "';";
		mysql_query(&m_sqlCon, str1.c_str());
		//�ɼ�����ҲҪɾ��
		string str2 = " delete from tb_mark where stuid='" + stuid + "';";
		mysql_query(&m_sqlCon, str2.c_str());
		
		string set1 = "SET FOREIGN_KEY_CHECKS=1;";//�������Լ��
		mysql_query(&m_sqlCon, set1.c_str());
		mysql_close(&m_sqlCon);//�Ͽ�����
	}
}

//��ѯC++�ɼ�
CString MysqlManagement::QueryCjjAtStuid(string stuid)
{
	MYSQL m_sqlCon;
	//��ʼ�����ݿ����  
	mysql_init(&m_sqlCon);
	//�������ݿ��ַ���ʽ�����������������
	mysql_options(&m_sqlCon, MYSQL_SET_CHARSET_NAME, "GB2312");

	//localhost:��������ַ������ֱ������IP;root:�˺�;  
	//2005:����;gradesystem:���ݿ���;3306:����˿�    
	if (!mysql_real_connect(&m_sqlCon, "localhost", "root",
		"2005", "gradesystem", 3306, NULL, 0))
	{
		AfxMessageBox(_T("���ݿ�����ʧ��!"));
	}
	else
	{
		//���� �༶��ţ�ѧ�ţ��γ̱�ţ��ɼ�  ���༶��ѧ�������������ɱ�
		string name = "SELECT clid,stuid,cid,score FROM tb_mark  ORDER BY stuid";
		MYSQL_RES* result = NULL;
		if (0 == mysql_query(&m_sqlCon, name.c_str()))
		{
			//AfxMessageBox(_T("���ݿ����ӳɹ�!"));
			 //һ����ȡ�����ݼ�
			result = mysql_store_result(&m_sqlCon);
			//ȡ���ֶ���
			unsigned int fieldcount = mysql_num_fields(result);
			//����������
			MYSQL_ROW row = NULL;
			row = mysql_fetch_row(result);
			MYSQL_FIELD* field_class = NULL;
			for (int j = 0; j < fieldcount; j++)//������
			{
				field_class = mysql_fetch_field_direct(result, j);//��j���ֶ�
				if (strcmp(field_class->name, "stuid") == 0)//ȡѧ���ֶ���
				{
					while (row != NULL)//�����鲻��
					{
						if (stuid == row[j])//�ҵ���ѧ��
						{
							string str = "1";//C++�γ̱��
							if (str == row[j + 1])//�ҵ�C++�Ŀγ̱��
							{
								mysql_close(&m_sqlCon);//�Ͽ�����
								return CString(row[j +2]);//���سɼ�   char* -> CString
							}
						}
						row = mysql_fetch_row(result);//ȡ��һ��
					}
				}
			}
		}
		mysql_close(&m_sqlCon);//�Ͽ�����
		CString str = TEXT(" ");
		return str;//�Ҳ������ؿ�
	}
}

//��ѯ��ý�弼���ɼ�
CString MysqlManagement::QueryMediaAtStuid(string stuid)
{
	MYSQL m_sqlCon;
	//��ʼ�����ݿ����  
	mysql_init(&m_sqlCon);
	//�������ݿ��ַ���ʽ�����������������
	mysql_options(&m_sqlCon, MYSQL_SET_CHARSET_NAME, "GB2312");

	//localhost:��������ַ������ֱ������IP;root:�˺�;  
	//2005:����;gradesystem:���ݿ���;3306:����˿�    
	if (!mysql_real_connect(&m_sqlCon, "localhost", "root",
		"2005", "gradesystem", 3306, NULL, 0))
	{
		AfxMessageBox(_T("���ݿ�����ʧ��!"));
	}
	else
	{
		//���� �༶��ţ�ѧ�ţ��γ̱�ţ��ɼ�  ���༶��ѧ�������������ɱ�
		string name = "SELECT clid,stuid,cid,score FROM tb_mark  ORDER BY stuid";
		MYSQL_RES* result = NULL;
		if (0 == mysql_query(&m_sqlCon, name.c_str()))
		{
			//AfxMessageBox(_T("���ݿ����ӳɹ�!"));
			 //һ����ȡ�����ݼ�
			result = mysql_store_result(&m_sqlCon);
			//ȡ���ֶ���
			unsigned int fieldcount = mysql_num_fields(result);
			//����������
			MYSQL_ROW row = NULL;
			row = mysql_fetch_row(result);
			MYSQL_FIELD* field_class = NULL;
			for (int j = 0; j < fieldcount; j++)//������
			{
				field_class = mysql_fetch_field_direct(result, j);//��j���ֶ�
				if (strcmp(field_class->name, "stuid") == 0)//ȡѧ���ֶ���
				{
					while (row != NULL)//�����鲻��
					{
						if (stuid == row[j])//�ҵ���ѧ��
						{
							string str = "2";//�γ̱��
							if (str == row[j + 1])//�ҵ��γ̱��
							{
								mysql_close(&m_sqlCon);//�Ͽ�����
								return CString(row[j + 2]);//���سɼ�   char* -> CString
							}
						}
						row = mysql_fetch_row(result);//ȡ��һ��
					}
				}
			}
		}
		mysql_close(&m_sqlCon);//�Ͽ�����
		CString str = TEXT(" ");
		return str;//�Ҳ������ؿ�
	}
}

//��ѯӢ��ɼ�
CString MysqlManagement::QueryEglishAtStuid(string stuid)
{
	MYSQL m_sqlCon;
	//��ʼ�����ݿ����  
	mysql_init(&m_sqlCon);
	//�������ݿ��ַ���ʽ�����������������
	mysql_options(&m_sqlCon, MYSQL_SET_CHARSET_NAME, "GB2312");

	//localhost:��������ַ������ֱ������IP;root:�˺�;  
	//2005:����;gradesystem:���ݿ���;3306:����˿�    
	if (!mysql_real_connect(&m_sqlCon, "localhost", "root",
		"2005", "gradesystem", 3306, NULL, 0))
	{
		AfxMessageBox(_T("���ݿ�����ʧ��!"));
	}
	else
	{
		//���� �༶��ţ�ѧ�ţ��γ̱�ţ��ɼ�  ���༶��ѧ�������������ɱ�
		string name = "SELECT clid,stuid,cid,score FROM tb_mark  ORDER BY stuid";
		MYSQL_RES* result = NULL;
		if (0 == mysql_query(&m_sqlCon, name.c_str()))
		{
			//AfxMessageBox(_T("���ݿ����ӳɹ�!"));
			 //һ����ȡ�����ݼ�
			result = mysql_store_result(&m_sqlCon);
			//ȡ���ֶ���
			unsigned int fieldcount = mysql_num_fields(result);
			//����������
			MYSQL_ROW row = NULL;
			row = mysql_fetch_row(result);
			MYSQL_FIELD* field_class = NULL;
			for (int j = 0; j < fieldcount; j++)//������
			{
				field_class = mysql_fetch_field_direct(result, j);//��j���ֶ�
				if (strcmp(field_class->name, "stuid") == 0)//ȡѧ���ֶ���
				{
					while (row != NULL)//�����鲻��
					{
						if (stuid == row[j])//�ҵ���ѧ��
						{
							string str = "3";//�γ̱��
							if (str == row[j + 1])//�ҵ��γ̱��
							{
								mysql_close(&m_sqlCon);//�Ͽ�����
								return CString(row[j + 2]);//���سɼ�   char* -> CString
							}
						}
						row = mysql_fetch_row(result);//ȡ��һ��
					}
				}
			}
		}
		mysql_close(&m_sqlCon);//�Ͽ�����
		CString str = TEXT(" ");
		return str;//�Ҳ������ؿ�
	}
}

//��ѯ��ѧ�ɼ�
CString MysqlManagement::QueryMathAtStuid(string stuid)
{
	MYSQL m_sqlCon;
	//��ʼ�����ݿ����  
	mysql_init(&m_sqlCon);
	//�������ݿ��ַ���ʽ�����������������
	mysql_options(&m_sqlCon, MYSQL_SET_CHARSET_NAME, "GB2312");

	//localhost:��������ַ������ֱ������IP;root:�˺�;  
	//2005:����;gradesystem:���ݿ���;3306:����˿�    
	if (!mysql_real_connect(&m_sqlCon, "localhost", "root",
		"2005", "gradesystem", 3306, NULL, 0))
	{
		AfxMessageBox(_T("���ݿ�����ʧ��!"));
	}
	else
	{
		//���� �༶��ţ�ѧ�ţ��γ̱�ţ��ɼ�  ���༶��ѧ�������������ɱ�
		string name = "SELECT clid,stuid,cid,score FROM tb_mark  ORDER BY stuid";
		MYSQL_RES* result = NULL;
		if (0 == mysql_query(&m_sqlCon, name.c_str()))
		{
			//AfxMessageBox(_T("���ݿ����ӳɹ�!"));
			 //һ����ȡ�����ݼ�
			result = mysql_store_result(&m_sqlCon);
			//ȡ���ֶ���
			unsigned int fieldcount = mysql_num_fields(result);
			//����������
			MYSQL_ROW row = NULL;
			row = mysql_fetch_row(result);
			MYSQL_FIELD* field_class = NULL;
			for (int j = 0; j < fieldcount; j++)//������
			{
				field_class = mysql_fetch_field_direct(result, j);//��j���ֶ�
				if (strcmp(field_class->name, "stuid") == 0)//ȡѧ���ֶ���
				{
					while (row != NULL)//�����鲻��
					{
						if (stuid == row[j])//�ҵ���ѧ��
						{
							string str = "4";//�γ̱��
							if (str == row[j + 1])//�ҵ��γ̱��
							{
								mysql_close(&m_sqlCon);//�Ͽ�����
								return CString(row[j + 2]);//���سɼ�   char* -> CString
							}
						}
						row = mysql_fetch_row(result);//ȡ��һ��
					}
				}
			}
		}
		mysql_close(&m_sqlCon);//�Ͽ�����
		CString str = TEXT(" ");
		return str;//�Ҳ������ؿ�
	}
}

//��ѯ�����ɼ�
CString MysqlManagement::QueryPEAtStuid(string stuid)
{
	MYSQL m_sqlCon;
	//��ʼ�����ݿ����  
	mysql_init(&m_sqlCon);
	//�������ݿ��ַ���ʽ�����������������
	mysql_options(&m_sqlCon, MYSQL_SET_CHARSET_NAME, "GB2312");

	//localhost:��������ַ������ֱ������IP;root:�˺�;  
	//2005:����;gradesystem:���ݿ���;3306:����˿�    
	if (!mysql_real_connect(&m_sqlCon, "localhost", "root",
		"2005", "gradesystem", 3306, NULL, 0))
	{
		AfxMessageBox(_T("���ݿ�����ʧ��!"));
	}
	else
	{
		//���� �༶��ţ�ѧ�ţ��γ̱�ţ��ɼ�  ���༶��ѧ�������������ɱ�
		string name = "SELECT clid,stuid,cid,score FROM tb_mark  ORDER BY stuid";
		MYSQL_RES* result = NULL;
		if (0 == mysql_query(&m_sqlCon, name.c_str()))
		{
			//AfxMessageBox(_T("���ݿ����ӳɹ�!"));
			 //һ����ȡ�����ݼ�
			result = mysql_store_result(&m_sqlCon);
			//ȡ���ֶ���
			unsigned int fieldcount = mysql_num_fields(result);
			//����������
			MYSQL_ROW row = NULL;
			row = mysql_fetch_row(result);
			MYSQL_FIELD* field_class = NULL;
			for (int j = 0; j < fieldcount; j++)//������
			{
				field_class = mysql_fetch_field_direct(result, j);//��j���ֶ�
				if (strcmp(field_class->name, "stuid") == 0)//ȡѧ���ֶ���
				{
					while (row != NULL)//�����鲻��
					{
						if (stuid == row[j])//�ҵ���ѧ��
						{
							string str = "5";//�γ̱��
							if (str == row[j + 1])//�ҵ��γ̱��
							{
								mysql_close(&m_sqlCon);//�Ͽ�����
								return CString(row[j + 2]);//���سɼ�   char* -> CString
							}
						}
						row = mysql_fetch_row(result);//ȡ��һ��
					}
				}
			}
		}
		mysql_close(&m_sqlCon);//�Ͽ�����
		CString str = TEXT(" ");
		return str;//�Ҳ������ؿ�
	}
}

//��ѯ���˼�ɼ�
CString MysqlManagement::QueryMarixAtStuid(string stuid)
{
	MYSQL m_sqlCon;
	//��ʼ�����ݿ����  
	mysql_init(&m_sqlCon);
	//�������ݿ��ַ���ʽ�����������������
	mysql_options(&m_sqlCon, MYSQL_SET_CHARSET_NAME, "GB2312");

	//localhost:��������ַ������ֱ������IP;root:�˺�;  
	//2005:����;gradesystem:���ݿ���;3306:����˿�    
	if (!mysql_real_connect(&m_sqlCon, "localhost", "root",
		"2005", "gradesystem", 3306, NULL, 0))
	{
		AfxMessageBox(_T("���ݿ�����ʧ��!"));
	}
	else
	{
		//���� �༶��ţ�ѧ�ţ��γ̱�ţ��ɼ�  ���༶��ѧ�������������ɱ�
		string name = "SELECT clid,stuid,cid,score FROM tb_mark  ORDER BY stuid";
		MYSQL_RES* result = NULL;
		if (0 == mysql_query(&m_sqlCon, name.c_str()))
		{
			//AfxMessageBox(_T("���ݿ����ӳɹ�!"));
			 //һ����ȡ�����ݼ�
			result = mysql_store_result(&m_sqlCon);
			//ȡ���ֶ���
			unsigned int fieldcount = mysql_num_fields(result);
			//����������
			MYSQL_ROW row = NULL;
			row = mysql_fetch_row(result);
			MYSQL_FIELD* field_class = NULL;
			for (int j = 0; j < fieldcount; j++)//������
			{
				field_class = mysql_fetch_field_direct(result, j);//��j���ֶ�
				if (strcmp(field_class->name, "stuid") == 0)//ȡѧ���ֶ���
				{
					while (row != NULL)//�����鲻��
					{
						if (stuid == row[j])//�ҵ���ѧ��
						{
							string str = "6";//�γ̱��
							if (str == row[j + 1])//�ҵ��γ̱��
							{
								mysql_close(&m_sqlCon);//�Ͽ�����
								return CString(row[j + 2]);//���سɼ�   char* -> CString
							}
						}
						row = mysql_fetch_row(result);//ȡ��һ��
					}
				}
			}
		}
		mysql_close(&m_sqlCon);//�Ͽ�����
		CString str = TEXT(" ");
		return str;//�Ҳ������ؿ�
	}
}

//����ѧ�Ų���C++�ɼ�
void MysqlManagement::InsertCjj(string clid,string score, string stuid)
{
	MYSQL m_sqlCon;
	//��ʼ�����ݿ����  
	mysql_init(&m_sqlCon);
	//�������ݿ��ַ���ʽ�����������������
	mysql_options(&m_sqlCon, MYSQL_SET_CHARSET_NAME, "GB2312");

	//localhost:��������ַ������ֱ������IP;root:�˺�;  
	//2005:����;gradesystem:���ݿ���;3306:����˿�    
	if (!mysql_real_connect(&m_sqlCon, "localhost", "root",
		"2005", "gradesystem", 3306, NULL, 0))
	{
		AfxMessageBox(_T("���ݿ�����ʧ��!"));
	}
	else
	{
		string name = "insert into tb_mark(clid,stuid,cid,score)values('" + clid + "','" + stuid + "',1,'" + score + "'); ";
		mysql_query(&m_sqlCon, name.c_str());
		
		mysql_close(&m_sqlCon);//�Ͽ�����
	}
}

//����ѧ�Ų����ý�弼���ɼ�
void MysqlManagement::InsertMedia(string clid,string score, string stuid)
{
	MYSQL m_sqlCon;
	//��ʼ�����ݿ����  
	mysql_init(&m_sqlCon);
	//�������ݿ��ַ���ʽ�����������������
	mysql_options(&m_sqlCon, MYSQL_SET_CHARSET_NAME, "GB2312");

	//localhost:��������ַ������ֱ������IP;root:�˺�;  
	//2005:����;gradesystem:���ݿ���;3306:����˿�    
	if (!mysql_real_connect(&m_sqlCon, "localhost", "root",
		"2005", "gradesystem", 3306, NULL, 0))
	{
		AfxMessageBox(_T("���ݿ�����ʧ��!"));
	}
	else
	{
		string name = "insert into tb_mark(clid,stuid,cid,score)values('" + clid + "','" + stuid + "',2,'" + score + "'); ";
		mysql_query(&m_sqlCon, name.c_str());

		mysql_close(&m_sqlCon);//�Ͽ�����
	}
}

//����ѧ�Ų���Ӣ��ɼ�
void MysqlManagement::InsertEnglish(string clid,string score, string stuid)
{
	MYSQL m_sqlCon;
	//��ʼ�����ݿ����  
	mysql_init(&m_sqlCon);
	//�������ݿ��ַ���ʽ�����������������
	mysql_options(&m_sqlCon, MYSQL_SET_CHARSET_NAME, "GB2312");

	//localhost:��������ַ������ֱ������IP;root:�˺�;  
	//2005:����;gradesystem:���ݿ���;3306:����˿�    
	if (!mysql_real_connect(&m_sqlCon, "localhost", "root",
		"2005", "gradesystem", 3306, NULL, 0))
	{
		AfxMessageBox(_T("���ݿ�����ʧ��!"));
	}
	else
	{
		string name = "insert into tb_mark(clid,stuid,cid,score)values('" + clid + "','" + stuid + "',3,'" + score + "'); ";
		mysql_query(&m_sqlCon, name.c_str());

		mysql_close(&m_sqlCon);//�Ͽ�����
	}
}

//����ѧ�Ų�����ѧ�ɼ�
void MysqlManagement::InsertMath(string clid,string score, string stuid)
{
	MYSQL m_sqlCon;
	//��ʼ�����ݿ����  
	mysql_init(&m_sqlCon);
	//�������ݿ��ַ���ʽ�����������������
	mysql_options(&m_sqlCon, MYSQL_SET_CHARSET_NAME, "GB2312");

	//localhost:��������ַ������ֱ������IP;root:�˺�;  
	//2005:����;gradesystem:���ݿ���;3306:����˿�    
	if (!mysql_real_connect(&m_sqlCon, "localhost", "root",
		"2005", "gradesystem", 3306, NULL, 0))
	{
		AfxMessageBox(_T("���ݿ�����ʧ��!"));
	}
	else
	{
		string name = "insert into tb_mark(clid,stuid,cid,score)values('" + clid + "','" + stuid + "',4,'" + score + "'); ";
		mysql_query(&m_sqlCon, name.c_str());

		mysql_close(&m_sqlCon);//�Ͽ�����
	}
}

//����ѧ�Ų��������ɼ�
void MysqlManagement::InsertPE(string clid,string score, string stuid)
{
	MYSQL m_sqlCon;
	//��ʼ�����ݿ����  
	mysql_init(&m_sqlCon);
	//�������ݿ��ַ���ʽ�����������������
	mysql_options(&m_sqlCon, MYSQL_SET_CHARSET_NAME, "GB2312");

	//localhost:��������ַ������ֱ������IP;root:�˺�;  
	//2005:����;gradesystem:���ݿ���;3306:����˿�    
	if (!mysql_real_connect(&m_sqlCon, "localhost", "root",
		"2005", "gradesystem", 3306, NULL, 0))
	{
		AfxMessageBox(_T("���ݿ�����ʧ��!"));
	}
	else
	{
		string name = "insert into tb_mark(clid,stuid,cid,score)values('" + clid + "','" + stuid + "',5,'" + score + "'); ";
		mysql_query(&m_sqlCon, name.c_str());

		mysql_close(&m_sqlCon);//�Ͽ�����
	}
}

//����ѧ�Ų������˼�ɼ�
void MysqlManagement::InsertMarix(string clid, string score, string stuid)
{
	MYSQL m_sqlCon;
	//��ʼ�����ݿ����  
	mysql_init(&m_sqlCon);
	//�������ݿ��ַ���ʽ�����������������
	mysql_options(&m_sqlCon, MYSQL_SET_CHARSET_NAME, "GB2312");

	//localhost:��������ַ������ֱ������IP;root:�˺�;  
	//2005:����;gradesystem:���ݿ���;3306:����˿�    
	if (!mysql_real_connect(&m_sqlCon, "localhost", "root",
		"2005", "gradesystem", 3306, NULL, 0))
	{
		AfxMessageBox(_T("���ݿ�����ʧ��!"));
	}
	else
	{
		string name = "insert into tb_mark(clid,stuid,cid,score)values('" + clid + "','" + stuid + "',6,'" + score + "'); ";
		mysql_query(&m_sqlCon, name.c_str());

		mysql_close(&m_sqlCon);//�Ͽ�����
	}
}

//����ѧ�Ű༶�޸�C++�ɼ�
void MysqlManagement::UpdateCjj(string clid, string score, string stuid)
{
	MYSQL m_sqlCon;
	//��ʼ�����ݿ����  
	mysql_init(&m_sqlCon);
	//�������ݿ��ַ���ʽ�����������������
	mysql_options(&m_sqlCon, MYSQL_SET_CHARSET_NAME, "GB2312");

	//localhost:��������ַ������ֱ������IP;root:�˺�;  
	//2005:����;gradesystem:���ݿ���;3306:����˿�    
	if (!mysql_real_connect(&m_sqlCon, "localhost", "root",
		"2005", "gradesystem", 3306, NULL, 0))
	{
		AfxMessageBox(_T("���ݿ�����ʧ��!"));
	}
	else
	{
		string name = "update tb_mark set score='" + score + "' where clid='" + clid + "' and stuid='" + stuid + "'and cid=1; ";
		mysql_query(&m_sqlCon, name.c_str());

		mysql_close(&m_sqlCon);//�Ͽ�����
	}
}

//����ѧ�Ű༶�޸Ķ�ý�弼���ɼ�
void MysqlManagement::UpdateMedia(string clid, string score, string stuid)
{
	MYSQL m_sqlCon;
	//��ʼ�����ݿ����  
	mysql_init(&m_sqlCon);
	//�������ݿ��ַ���ʽ�����������������
	mysql_options(&m_sqlCon, MYSQL_SET_CHARSET_NAME, "GB2312");

	//localhost:��������ַ������ֱ������IP;root:�˺�;  
	//2005:����;gradesystem:���ݿ���;3306:����˿�    
	if (!mysql_real_connect(&m_sqlCon, "localhost", "root",
		"2005", "gradesystem", 3306, NULL, 0))
	{
		AfxMessageBox(_T("���ݿ�����ʧ��!"));
	}
	else
	{
		string name = "update tb_mark set score='" + score + "' where clid='" + clid + "' and stuid='" + stuid + "'and cid=2; ";
		mysql_query(&m_sqlCon, name.c_str());

		mysql_close(&m_sqlCon);//�Ͽ�����
	}
}

//����ѧ�Ű༶�޸�Ӣ��ɼ�
void MysqlManagement::UpdateEnglish(string clid, string score, string stuid)
{
	MYSQL m_sqlCon;
	//��ʼ�����ݿ����  
	mysql_init(&m_sqlCon);
	//�������ݿ��ַ���ʽ�����������������
	mysql_options(&m_sqlCon, MYSQL_SET_CHARSET_NAME, "GB2312");

	//localhost:��������ַ������ֱ������IP;root:�˺�;  
	//2005:����;gradesystem:���ݿ���;3306:����˿�    
	if (!mysql_real_connect(&m_sqlCon, "localhost", "root",
		"2005", "gradesystem", 3306, NULL, 0))
	{
		AfxMessageBox(_T("���ݿ�����ʧ��!"));
	}
	else
	{
		string name = "update tb_mark set score='" + score + "' where clid='" + clid + "' and stuid='" + stuid + "'and cid=3; ";
		mysql_query(&m_sqlCon, name.c_str());

		mysql_close(&m_sqlCon);//�Ͽ�����
	}
}

//����ѧ�Ű༶�޸���ѧ�ɼ�
void MysqlManagement::UpdateMath(string clid, string score, string stuid)
{
	MYSQL m_sqlCon;
	//��ʼ�����ݿ����  
	mysql_init(&m_sqlCon);
	//�������ݿ��ַ���ʽ�����������������
	mysql_options(&m_sqlCon, MYSQL_SET_CHARSET_NAME, "GB2312");

	//localhost:��������ַ������ֱ������IP;root:�˺�;  
	//2005:����;gradesystem:���ݿ���;3306:����˿�    
	if (!mysql_real_connect(&m_sqlCon, "localhost", "root",
		"2005", "gradesystem", 3306, NULL, 0))
	{
		AfxMessageBox(_T("���ݿ�����ʧ��!"));
	}
	else
	{
		string name = "update tb_mark set score='" + score + "' where clid='" + clid + "' and stuid='" + stuid + "'and cid=4; ";
		mysql_query(&m_sqlCon, name.c_str());

		mysql_close(&m_sqlCon);//�Ͽ�����
	}
}

//����ѧ�Ű༶�޸������ɼ�
void MysqlManagement::UpdatePE(string clid, string score, string stuid)
{
	MYSQL m_sqlCon;
	//��ʼ�����ݿ����  
	mysql_init(&m_sqlCon);
	//�������ݿ��ַ���ʽ�����������������
	mysql_options(&m_sqlCon, MYSQL_SET_CHARSET_NAME, "GB2312");

	//localhost:��������ַ������ֱ������IP;root:�˺�;  
	//2005:����;gradesystem:���ݿ���;3306:����˿�    
	if (!mysql_real_connect(&m_sqlCon, "localhost", "root",
		"2005", "gradesystem", 3306, NULL, 0))
	{
		AfxMessageBox(_T("���ݿ�����ʧ��!"));
	}
	else
	{
		string name = "update tb_mark set score='" + score + "' where clid='" + clid + "' and stuid='" + stuid + "'and cid=5; ";
		mysql_query(&m_sqlCon, name.c_str());

		mysql_close(&m_sqlCon);//�Ͽ�����
	}
}

//����ѧ�Ű༶�޸����˼�ɼ�
void MysqlManagement::UpdateMarix(string clid, string score, string stuid)
{
	MYSQL m_sqlCon;
	//��ʼ�����ݿ����  
	mysql_init(&m_sqlCon);
	//�������ݿ��ַ���ʽ�����������������
	mysql_options(&m_sqlCon, MYSQL_SET_CHARSET_NAME, "GB2312");

	//localhost:��������ַ������ֱ������IP;root:�˺�;  
	//2005:����;gradesystem:���ݿ���;3306:����˿�    
	if (!mysql_real_connect(&m_sqlCon, "localhost", "root",
		"2005", "gradesystem", 3306, NULL, 0))
	{
		AfxMessageBox(_T("���ݿ�����ʧ��!"));
	}
	else
	{
		string name = "update tb_mark set score='" + score + "' where clid='" + clid + "' and stuid='" + stuid + "'and cid=6; ";
		mysql_query(&m_sqlCon, name.c_str());

		mysql_close(&m_sqlCon);//�Ͽ�����
	}
}

void MysqlManagement::DeleteScore(string stuid)
{
	MYSQL m_sqlCon;
	//��ʼ�����ݿ����  
	mysql_init(&m_sqlCon);
	//�������ݿ��ַ���ʽ�����������������
	mysql_options(&m_sqlCon, MYSQL_SET_CHARSET_NAME, "GB2312");

	//localhost:��������ַ������ֱ������IP;root:�˺�;  
	//2005:����;gradesystem:���ݿ���;3306:����˿�    
	if (!mysql_real_connect(&m_sqlCon, "localhost", "root",
		"2005", "gradesystem", 3306, NULL, 0))
	{
		AfxMessageBox(_T("���ݿ�����ʧ��!"));
	}
	else
	{
		//ɾ��ѧ������ѧ��Ϊ stuid �ĳɼ�
		string str2 = " delete from tb_mark where stuid='" + stuid + "';";
		mysql_query(&m_sqlCon, str2.c_str());

		mysql_close(&m_sqlCon);//�Ͽ�����
	}
}

//���༶����Ŀ��ƽ����
double MysqlManagement::ClassAverAtCourse(string cid, string clid)
{
	MYSQL m_sqlCon;
	//��ʼ�����ݿ����  
	mysql_init(&m_sqlCon);
	//�������ݿ��ַ���ʽ�����������������
	mysql_options(&m_sqlCon, MYSQL_SET_CHARSET_NAME, "GB2312");

	//localhost:��������ַ������ֱ������IP;root:�˺�;  
	//2005:����;gradesystem:���ݿ���;3306:����˿�    
	if (!mysql_real_connect(&m_sqlCon, "localhost", "root",
		"2005", "gradesystem", 3306, NULL, 0))
	{
		AfxMessageBox(_T("���ݿ�����ʧ��!"));
	}
	else
	{
		//aa.cc����bb.dd ����һλС����
		//���У�cc�Ƿ�������ѧ��Ϊclid,�༶���Ϊcid�ķ����ĺͣ���Ϊaa��
		//����(ddΪѧ�����а༶���Ϊclid����������Ϊbb��
		string name = "select TRUNCATE( aa.cc/bb.dd,1 ) from (select sum(score) cc from tb_mark where clid='"+clid+"' and cid='" + cid + "') as aa,(select count(*)  dd from tb_student where clid='" + clid + "') as bb;";
		MYSQL_RES* result = NULL;
		if (0 == mysql_query(&m_sqlCon, name.c_str()))
		{
			//AfxMessageBox(_T("���ݿ����ӳɹ�!"));
			 //һ����ȡ�����ݼ�
			result = mysql_store_result(&m_sqlCon);
			//ȡ���ֶ���
			unsigned int fieldcount = mysql_num_fields(result);
			//����������
			MYSQL_ROW row = NULL;
			row = mysql_fetch_row(result);
			MYSQL_FIELD* field_class = NULL;
			char *str = NULL;
			for (int j = 0; j < fieldcount; j++)//������
			{
				//mysql_close(&m_sqlCon);//�Ͽ�����
				//AfxMessageBox(CString(row[j]));
				mysql_close(&m_sqlCon);//�Ͽ�����
				if (row[j] == str)
				{
					AfxMessageBox(TEXT("�ɼ�Ϊ��"));
					return 0;
				}
				else 
					return  atof(row[j]);//���سɼ�   char* -> CString
				
			}
		}
		mysql_close(&m_sqlCon);//�Ͽ�����
	}
}

