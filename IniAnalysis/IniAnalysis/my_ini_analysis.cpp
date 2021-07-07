/*************************my_ini_analysis.cpp文件说明***************************
* Descript	:源文件，包含自编解析函数的函数定义
* Author    :fengboyu
* Date      :2021_07_07
*******************************************************************************/


/***********************************头文件****************************************/
#include "config.h"
#include "my_ini_analysis.h"


/***********************************函数定义**************************************/
/*************************************************************
Function    :Judge_File_Status
Description :判断文件打开状态
Input       :文件指针
Output      :文件打开情况
Return      :如果打开失败为main返回1
Note        :
*************************************************************/
bool Judge_File_Status(FILE *file)
{
	//判断文件是否成功打开
	if (file)
	{
		cout << "文件打开成功！" << endl << endl;
		return TRUE;
	}
	else
	{
		cout << "文件打开失败！" << endl << endl;
		return FALSE;
	}

}

/*************************************************************
Function    :RemoveCh
Description :移除字符串中的空格，注释除外
Input       :字符数组指针
Output      :空
Return      :空
Note        :
*************************************************************/
void RemoveCh(char *arrP)
{
	char *arrPAction = arrP; 

	while ((*arrPAction != ';') && (*arrPAction != '\n'))
	{
		if (*arrPAction != ' ')
		{
			*arrP = *arrPAction++;
			arrP++;
		}
		else
		{
			++arrPAction;
		}
	}

	if (*arrPAction == ';')
	{
		while (*arrPAction != '\n')
		{
			*arrP = *arrPAction++;
			arrP++;
		}
	}
	*arrP = '\0';
}

/*************************************************************
Function    ::Find_File_Section
Description :找出配置文件的节名
Input       :字符数组指针
Output      :节名
Return      :空
Note        :
*************************************************************/
void Find_File_Section(char *arrP)
{
	char *pos = arrP; //初始化遍历指针

	if (*pos == '[')
	{
		while (*pos != '\n')
		{
			if (*pos == ']') //如果能找到右括号，那么输出中间的节
			{
				vector<char> SectionBuffer; //声明存储节名的容器

				++arrP;
				while (arrP != pos)
				{
					SectionBuffer.push_back(*arrP);  //将读取的节名存入容器
					arrP++;
				}

				for (int i = 0; i < SectionBuffer.size(); i++) //循环输出节名字符
				{
					cout << SectionBuffer[i];
				}
				cout << endl;
				break;  //输出节后跳出当前查找循环
			}
			pos++;
		}
	}
}

/*************************************************************
Function    :My_Ini_Analysis_GetSectionNames自编解析函数--节名
Description :使用自编解析函数导出配置文件包含的节
Input       :配置文件路径
Output      :输出指定配置文件里的所有节名
Return      :空
Note        :
*************************************************************/ 
void My_Ini_Analysis_GetSectionNames(LPCTSTR filePath)
{
	FILE *iniFile; //初始化文件指针
	iniFile = fopen(filePath, "r");	
	static char intLineBuffer[LINEMAXSIZE] = { 0 }; //初始化存储ini文件单行字符的字符数组
	//char findBuffer[LINEMAXSIZE] = { 0 }; //初始化存储满足条件的字符数组
	bool JFS = TRUE; //记录文件打开情况,初始化为TRUE（正常）

	JFS = Judge_File_Status(iniFile); //判断文件打开状态

	//按行读取文件流中的字符串，读取不为空则进行后续操作
	while (JFS && fgets(intLineBuffer, LINEMAXSIZE, iniFile))
	{
		RemoveCh(intLineBuffer); //处理当前字符串，移除空格
		Find_File_Section(intLineBuffer); //找出处理后字符数组的节
	}
	cout << endl;
}

/********************************************************************
Function    :My_Ini_Analysis_GetSection自编解析函数--节包含的键名键值
Description :使用自编解析函数导出配置文件指定节的键名和键值
Input       :节名、文件路径
Output      :输出指定配置文件里的指定节名下的所有键名键值
Return      :空
Note        :
********************************************************************/
void My_Ini_Analysis_GetSection(string targetSection, LPCTSTR filePath)
{

}