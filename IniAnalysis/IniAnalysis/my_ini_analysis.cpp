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
		cout << endl << "文件打开成功！" << endl << endl;
		return TRUE;
	}
	else
	{
		cout << endl << "文件打开失败！" << endl << endl;
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
Function    :Judge_Section
Description :通过*index的值判断字符串是否是节，是否匹配
Input       :指定节名的指针，当前字符数组的指针，判断指针
Output      :判断指针
Return      :空
Note        :
*************************************************************/
void Judge_Section(char *secP, char *arrP, int *stIndex,int *opIndex)
{
	char *pos = arrP; //初始化遍历指针


	if (*pos == '[') 
	{
		while (*pos != '\n')  //只有在默认状态下才会查找右括号
		{
			if (*pos == ']') //如果能找到右括号，则找到了节，判断节名是否匹配，信息看*index的值
			{
				if (*opIndex == 0) //之前未找到节名
				{
					char sectionBuffer[LINEMAXSIZE]; //初始化存储当前行截取的节名
					strncpy(sectionBuffer, arrP, (pos - arrP + 1)); //截取
					sectionBuffer[(pos - arrP + 1)] = '\0';

					cout << "比对节名：" << secP << arrP << endl;

					if (!strcmp(sectionBuffer, secP)) //判断当前节和寻找节名是否相等
					{
						*stIndex = 1;
						*opIndex = 1;
						cout << "节名匹配" << endl << endl;
						break;
					}
					else
					{
						*stIndex = 0;
						cout << "节名不匹配" << endl << endl;
						break;
					}
				}
				else //若之前已经找到节名，再次碰到节名则停止输出
				{
					*stIndex = 0;
					*opIndex = 0;
					cout << "键名键值输出完毕！" << endl;
					break;
				}
			}/*if (*pos == ']')*/
			pos++;
		}/*while (*pos != '\n')*/
	}/*if (*pos == '[')*//*if执行完毕，若*index为默认值2，则该字符串不是节，若为1说明节名匹配，若为0说明不匹配*/
	else
	{
		*stIndex = 2;
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
void My_Ini_Analysis_GetSection(char *targetSection, LPCTSTR filePath)
{
	FILE *iniFile; //初始化文件指针
	iniFile = fopen(filePath, "r");
	char intLineBuffer[LINEMAXSIZE]; //初始化存储ini文件单行字符的字符数组
	char TargetSection[LINEMAXSIZE]; //初始化存储转化成规范节名的指定节名
	int sectionIndex = 2; //初始化寻找状态标志，2是默认值，1是节名匹配，0是不匹配
	int outputIndex = 0; //初始化输出标志，0是默认值，0是不输出，1是输出

	bool JFS = TRUE; //记录文件打开情况,初始化为TRUE（正常）

	sprintf(TargetSection, "[%s]", targetSection); //将添加括号的目标节名赋值给规范节名

	cout << endl << "想要查找的节名：" << targetSection;
	cout << endl << "标准化后的节名：" << TargetSection << endl;

	JFS = Judge_File_Status(iniFile); //判断文件打开状态

	//按行读取文件流中的字符串，读取不为空则进行后续操作
	while (JFS && fgets(intLineBuffer, LINEMAXSIZE, iniFile))
	{
		RemoveCh(intLineBuffer); //处理当前字符串，移除空格

		if (outputIndex == 1) //即已经匹配过节名，目前是输出键名键值状态
		{
			Judge_Section(TargetSection, intLineBuffer, &sectionIndex, &outputIndex); //判断当前是不是节名

			if (sectionIndex == 2) //当前不是节名
			{
				cout << intLineBuffer << endl;
			}
			else
			{
				fclose(iniFile); //关闭文件
				break; //结束文件查找
			}
		}
		else
		{
			Judge_Section(TargetSection, intLineBuffer, &sectionIndex, &outputIndex); //判断当前是不是节名

			if (sectionIndex == 1)
			{
				cout << "找到匹配的节名:" << intLineBuffer << endl;
				cout << "其中的键名和键值是:" << endl;
			}
		}
	}/*while*/
	cout << endl;
}