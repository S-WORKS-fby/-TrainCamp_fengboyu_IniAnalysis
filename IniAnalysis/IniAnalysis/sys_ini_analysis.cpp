/*************************sys_ini_analysis.cpp�ļ�˵��***************************
* Descript	:Դ�ļ�������ʹ��ϵͳ���������ĺ�������
* Author    :fengboyu
* Date      :2021_07_06
*******************************************************************************/

/***********************************ͷ�ļ�****************************************/
#include "config.h"
#include "sys_ini_analysis.h"

/*************************************************************
Function    :Sys_Ini_Analysis_GetSectionNameϵͳ��������--����
Description :ʹ��ϵͳ�����������������ļ������Ľ����ͽ���
Input       :�����ļ�·��
Output      :���ָ�������ļ�������н���
Return      :��
Note        :
*************************************************************/
void Sys_Ini_Analysis_GetSectionNames(LPCTSTR filePath)
{
	cout << endl;

	const short int sectionNameMaxByteNum = 1024;

	char sectionNamesBuffer[sectionNameMaxByteNum] = { 0 };//�ܵ���������ַ�������

	int sectionNameByteNum = 0;
	sectionNameByteNum = GetPrivateProfileSectionNames(sectionNamesBuffer, sectionNameMaxByteNum, filePath);//��ȡini�ļ�Section����������
	cout << "ϵͳ�����������������ļ�" << filePath << "�����Ľ�:" << endl;

	int i = 0;
	int pos = 0;
	int m = 0;
	for (i = 0; i <= sectionNameByteNum; i++)//ѭ���õ�Section����
	{
		if (sectionNamesBuffer[i] != 0 && sectionNamesBuffer[i + 1] == 0)//�ж�Section����λ��
		{
			for (m = pos; m <= i; m++)
			{
				cout << sectionNamesBuffer[m];
			}
			cout << endl;
			pos = i + 2;
		}
	}
}

/*********************************************************************
Function    :Sys_Ini_Analysis_GetSectionϵͳ��������--�ڰ����ļ�����ֵ
Description :ʹ��ϵͳ�����������������ļ������Ľ����ͽ���
Input       :�������ļ�·��
Output      :���ָ�������ļ����ָ�������µ����м�����ֵ
Return      :��
Note        :
*********************************************************************/
void Sys_Ini_Analysis_GetSection(LPCTSTR sectionName, LPCTSTR filePath)
{
	cout << endl;

	const short int keyValueMaxByteNum = 1024;
	char keyValueBuffer[keyValueMaxByteNum] = { 0 }; //��ֵ����
	int key_ValuebyteNum = 0;//������е��ֽ���

	key_ValuebyteNum = GetPrivateProfileSection(sectionName, keyValueBuffer, keyValueMaxByteNum, filePath);
	cout << "ϵͳ�����������������ļ�" << filePath << "�н���Ϊ:" << sectionName << "�а����ļ����ͼ�ֵΪ:" << endl;

	int i = 0;
	int pos = 0;
	int m = 0;
	for (i = 0; i <= key_ValuebyteNum; i++)//ѭ���õ�Section����
	{
		if (keyValueBuffer[i] != 0 && keyValueBuffer[i + 1] == 0)//�ж�key=value��λ��
		{
			for (m = pos; m <= i; m++)
			{
				cout << keyValueBuffer[m];
			}
			cout << endl;
			pos = i + 2;
		}
	}
}


/******************************************************************
Function    :Sys_Ini_Analysis_GetStringϵͳ��������--��ȡ�ַ���
Description :ʹ��ϵͳ�����������������ļ������Ľ����ͽ���
Input       :������������Ĭ��ֵ���ַ�������ָ�롢������С���ļ�·��
Output      :���ҵĽ��¼������ַ����ͼ�ֵ
Return      :��
Note        :
*******************************************************************/
void Sys_Ini_Analysis_GetString(LPCTSTR sectionName, LPCTSTR keyName, LPCTSTR valueDefault, LPTSTR stringBuffer, DWORD nSize, LPCTSTR filePath)
{
	cout << endl;
	GetPrivateProfileString(sectionName, keyName, valueDefault, stringBuffer, nSize, filePath);
	cout << "ϵͳ���������õ�����:" << sectionName << "�м���Ϊ" << keyName << "�ļ�ֵΪ:";
}

/*********************************************************
Function    :Sys_Ini_Analysis_GetIntϵͳ��������--��ȡ����
Description :ʹ��ϵͳ�����������������ļ������Ľ����ͽ���
Input       :������������Ĭ��ֵ����������ָ�롢�ļ�·��
Output      :���ҵĽ��¼��������μ�ֵ
Return      :��
Note        :
*********************************************************/
void Sys_Ini_Analysis_GetInt(LPCTSTR sectionName, LPCTSTR keyName, int valueDefault, int *intBuffer, LPCTSTR filePath)
{
	cout << endl;
	*intBuffer = GetPrivateProfileInt(sectionName, keyName, valueDefault, filePath);
	cout << "ϵͳ���������õ�����:" << sectionName << "�м���Ϊ" << keyName << "�ļ�ֵΪ:";
}