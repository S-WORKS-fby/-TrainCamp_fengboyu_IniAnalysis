/*************************sys_ini_analysis.cpp文件说明***************************
* Descript	:源文件，包含使用系统解析函数的函数定义
* Author    :fengboyu
* Date      :2021_07_06
*******************************************************************************/

/***********************************头文件****************************************/
#include "config.h"
#include "sys_ini_analysis.h"

/*************************************************************
Function    :Sys_Ini_Analysis_GetSectionName系统解析函数--节名
Description :使用系统解析函数导出配置文件包含的节数和节名
Input       :配置文件路径
Output      :输出指定配置文件里的所有节名
Return      :空
Note        :
*************************************************************/
void Sys_Ini_Analysis_GetSectionNames(LPCTSTR filePath)
{
	cout << endl;

	const short int sectionNameMaxByteNum = 1024;

	char sectionNamesBuffer[sectionNameMaxByteNum] = { 0 };//总的提出来的字符串容器

	int sectionNameByteNum = 0;
	sectionNameByteNum = GetPrivateProfileSectionNames(sectionNamesBuffer, sectionNameMaxByteNum, filePath);//获取ini文件Section个数和数据
	cout << "系统解析函数分析配置文件" << filePath << "包含的节:" << endl;

	int i = 0;
	int pos = 0;
	int m = 0;
	for (i = 0; i <= sectionNameByteNum; i++)//循环得到Section节名
	{
		if (sectionNamesBuffer[i] != 0 && sectionNamesBuffer[i + 1] == 0)//判断Section节名位置
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
Function    :Sys_Ini_Analysis_GetSection系统解析函数--节包含的键名键值
Description :使用系统解析函数导出配置文件包含的节数和节名
Input       :节名、文件路径
Output      :输出指定配置文件里的指定节名下的所有键名键值
Return      :空
Note        :
*********************************************************************/
void Sys_Ini_Analysis_GetSection(LPCTSTR sectionName, LPCTSTR filePath)
{
	cout << endl;

	const short int keyValueMaxByteNum = 1024;
	char keyValueBuffer[keyValueMaxByteNum] = { 0 }; //键值容器
	int key_ValuebyteNum = 0;//保存节中的字节数

	key_ValuebyteNum = GetPrivateProfileSection(sectionName, keyValueBuffer, keyValueMaxByteNum, filePath);
	cout << "系统解析函数分析配置文件" << filePath << "中节名为:" << sectionName << "中包含的键名和键值为:" << endl;

	int i = 0;
	int pos = 0;
	int m = 0;
	for (i = 0; i <= key_ValuebyteNum; i++)//循环得到Section节名
	{
		if (keyValueBuffer[i] != 0 && keyValueBuffer[i + 1] == 0)//判断key=value的位置
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
Function    :Sys_Ini_Analysis_GetString系统解析函数--读取字符串
Description :使用系统解析函数导出配置文件包含的节数和节名
Input       :节名、键名、默认值、字符串容器指针、容器大小、文件路径
Output      :查找的节下键名的字符串型键值
Return      :空
Note        :
*******************************************************************/
void Sys_Ini_Analysis_GetString(LPCTSTR sectionName, LPCTSTR keyName, LPCTSTR valueDefault, LPTSTR stringBuffer, DWORD nSize, LPCTSTR filePath)
{
	cout << endl;
	GetPrivateProfileString(sectionName, keyName, valueDefault, stringBuffer, nSize, filePath);
	cout << "系统解析函数得到节名:" << sectionName << "中键名为" << keyName << "的键值为:";
}

/*********************************************************
Function    :Sys_Ini_Analysis_GetInt系统解析函数--读取整形
Description :使用系统解析函数导出配置文件包含的节数和节名
Input       :节名、键名、默认值、整形容器指针、文件路径
Output      :查找的节下键名的整形键值
Return      :空
Note        :
*********************************************************/
void Sys_Ini_Analysis_GetInt(LPCTSTR sectionName, LPCTSTR keyName, int valueDefault, int *intBuffer, LPCTSTR filePath)
{
	cout << endl;
	*intBuffer = GetPrivateProfileInt(sectionName, keyName, valueDefault, filePath);
	cout << "系统解析函数得到节名:" << sectionName << "中键名为" << keyName << "的键值为:";
}