/*************************main.cpp�ļ�˵��***************************
* Descript	:Դ�ļ���������
* Author    :fengboyu
* Date      :2021_07_06
*******************************************************************************/

/***********************************ͷ�ļ�****************************************/
#include "config.h"
#include "sys_ini_analysis.h"
#include "my_ini_analysis.h"


/***********************************������****************************************/
int main()
{
	LPCTSTR filePath = FILEPATH; //�����ļ�·��
	LPTSTR strName = new char[20]; //��ʼ��ָ���ȡ�ļ�ֵָ��
	LPTSTR strClass = new char[20]; //��ʼ��ָ���ȡ�ļ�ֵָ��
	int studentAge = 0; //��ʼ��ѧ������
	int *age = &studentAge; //��ʼ��ָ��ѧ������ָ��

	///************************************ϵͳ�����ļ���ȡ*********************************/
	///*******************************��ȡָ�������ļ��еĽ���Ϣ***************************/
	//Sys_Ini_Analysis_GetSectionNames(filePath);

	///*************************��ȡָ�������ļ���ָ���ڵ����м�����ֵ*********************/
	//Sys_Ini_Analysis_GetSection("stu dy", filePath);

	///*************************��ȡָ�������ļ���ָ��������ָ����������Ϣ*****************/
	////��ȡ�ַ�������
	//Sys_Ini_Analysis_GetString("  student ", "name", "δȡ������", strName, 20, filePath);
	//cout << strName << endl;
	//Sys_Ini_Analysis_GetString("stu dy", "class", "δȡ�ð༶", strClass, 20, filePath);
	//cout << strClass << endl;

	////��ȡ����
	//Sys_Ini_Analysis_GetInt("student", "a g e", 0, age, filePath);
	//cout << studentAge << endl;

	/************************************�Ա�����ļ���ȡ*********************************/
	/*******************************��ȡָ�������ļ��еĽ���Ϣ***************************/
	My_Ini_Analysis_GetSectionNames(filePath); 
	/*************************��ȡָ�������ļ���ָ���ڵ����м�����ֵ*********************/
	My_Ini_Analysis_GetSection("stu dy", filePath);

	system("pause");
	return 0;
}