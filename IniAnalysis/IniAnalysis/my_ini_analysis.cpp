/*************************my_ini_analysis.cpp文件说明***************************
* Descript	:源文件，包含自编解析函数的函数定义
* Author    :fengboyu
* Date      :2021_07_07
*******************************************************************************/


/***********************************头文件****************************************/
#include "config.h"
#include "my_ini_analysis.h"

/***********************************函数声明**************************************/
bool Judge_File_Status(FILE *file);

void RemoveCh(char *arrP);

char* FindEqual(char *arrP);

void Find_File_Section(char *arrP);

void Judge_Section(char *secP, char *arrP, int *stIndex, int *opIndex);


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
		cout << endl << "文件打开成功！" << endl;
		return TRUE;
	}
	else
	{
		cout << endl << "文件打开失败！" << endl;
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
Function    :FindEqual
Description :找到键名键值类型语句里的等号位置
Input       :字符串指针
Output      :空
Return      :指向等号的指针
Note        :
*************************************************************/
char* FindEqual(char *arrP)
{
	char *equalP = arrP; 

	while (*equalP != '\n')
	{
		if (*equalP == '=')
		{
			return equalP;
		}
		equalP++;
	}
}

/*************************************************************
Function    ::Find_File_Section
Description :找出配置文件的节名
Input       :字符数组指针
Output      :节名
Return      :空
Note        :
*************************************************************/
void Find_File_Section(char *arrP,int *indexP)
{
	char *pos = arrP; //初始化遍历指针

	if (*pos == '[')
	{
		while (*pos != '\n')
		{
			if (*pos == ']') //如果能找到右括号，那么输出中间的节
			{
				*indexP = 1; //标志找到过节名
				++arrP;
				while (arrP != pos)
				{
					cout << *arrP;
					++arrP;
				}
				cout << endl;
				break;  //输出节后跳出当前查找循环
			}
			pos++;
		}/*while (*pos != '\n')*/
	}/*if (*pos == '[')*/
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

	if (*pos != '[')
	{
		*stIndex = 2;
		return;
	}/*if (*pos != '[')*//*if执行完毕，若*index为默认值2，则该字符串不是节，若为1说明节名匹配，若为0说明不匹配*/

	while (*pos != '\n')
	{
		if (*pos != ']')
		{
			pos++;
			continue;
		}

		if (*opIndex != 0)//若之前已经找到节名，再次碰到节名则停止输出
		{
			*stIndex = 0;
			cout << endl;
			break;
		}

		char sectionBuffer[LINEMAXSIZE]; //初始化存储当前行截取的节名
		strncpy(sectionBuffer, arrP, (pos - arrP + 1)); //截取
		sectionBuffer[(pos - arrP + 1)] = '\0';

		//cout << "比对节名：" << secP << arrP << endl;

		if (!strcmp(sectionBuffer, secP)) //判断当前节和寻找节名是否相等,若相等则进入
		{
			*stIndex = 1;
			*opIndex = 1;
			//cout << "节名匹配" << endl << endl;
			break;
		}
		else
		{
			*stIndex = 0;
			//cout << "节名不匹配" << endl << endl;
			break;
		}
	}/*while (*pos != '\n')*/
}

/*************************************************************
Function    :My_Ini_Analysis_GetSectionNames自编解析函数--节名
Description :使用自编解析函数导出配置文件包含的节
Input       :配置文件路径
Output      :输出指定配置文件里的所有节名
Return      :空
Note        :
*************************************************************/ 
int My_Ini_Analysis_GetSectionNames(LPCTSTR filePath)
{
	FILE *iniFile; //初始化文件指针
	iniFile = fopen(filePath, "r");	
	static char iniLineBuffer[LINEMAXSIZE] = { 0 }; //初始化存储ini文件单行字符的字符数组
	int outputIndex = 0; //初始化输出标志，0是未找到节名，1是找到节名
	bool JFS = TRUE; //记录文件打开情况,初始化为TRUE（正常）

	JFS = Judge_File_Status(iniFile); //判断文件打开状态

	if (!JFS)
	{
		return 0;
	}

	//按行读取文件流中的字符串，读取不为空则进行后续操作
	while (JFS && fgets(iniLineBuffer, LINEMAXSIZE, iniFile))
	{
		RemoveCh(iniLineBuffer); //处理当前字符串，移除空格
		Find_File_Section(iniLineBuffer,&outputIndex); //找出处理后字符数组的节
	}
	cout << endl;

	return outputIndex;
}

/********************************************************************
Function    :My_Ini_Analysis_GetSection自编解析函数--节包含的键名键值
Description :使用自编解析函数导出配置文件指定节的键名和键值
Input       :节名、文件路径
Output      :输出指定配置文件里的指定节名下的所有键名键值
Return      :空
Note        :
********************************************************************/
int My_Ini_Analysis_GetSection(LPCTSTR targetSection, LPCTSTR filePath)
{
	FILE *iniFile; //初始化文件指针
	iniFile = fopen(filePath, "r");
	char iniLineBuffer[LINEMAXSIZE]; //初始化存储ini文件单行字符的字符数组
	char TargetSection[LINEMAXSIZE]; //初始化存储转化成规范节名的指定节名
	int sectionIndex = 2; //初始化寻找状态标志，2是默认值，1是节名匹配，0是不匹配
	int outputIndex = 0; //初始化输出标志，0是默认值，0是之前未找到节名，1是之前已经匹配到节名

	bool JFS = TRUE; //记录文件打开情况,初始化为TRUE（正常）
	JFS = Judge_File_Status(iniFile); //判断文件打开状态
	if (!JFS)
	{
		return 0;
	}

	sprintf(TargetSection, "[%s]", targetSection); //将添加括号的目标节名赋值给规范节名

	//cout << endl << "想要查找的节名：" << targetSection;
	//cout << endl << "标准化后的节名：" << TargetSection << endl;

	//按行读取文件流中的字符串，读取不为空则进行后续操作
	while (JFS && fgets(iniLineBuffer, LINEMAXSIZE, iniFile))
	{
		RemoveCh(iniLineBuffer); //处理当前字符串，移除空格

		if (outputIndex != 1) //未匹配过字节，继续匹配
		{
			Judge_Section(TargetSection, iniLineBuffer, &sectionIndex, &outputIndex); //判断当前是不是节名

			if (sectionIndex == 1)
			{
				//cout << "找到匹配的节名:" << iniLineBuffer << endl;
				//cout << "要找的键名和键值是:" << endl;
			}
			continue;
		}

		//已经匹配过节名，目前是输出键名键值状态
		Judge_Section(TargetSection, iniLineBuffer, &sectionIndex, &outputIndex); //判断当前是不是节名

		if (sectionIndex == 2) //当前不是节名
		{
			cout << iniLineBuffer << endl;
		}
		else
		{
			fclose(iniFile); //关闭文件
			break; //结束文件查找
		}
	}/*while*/
	cout << endl;

	return outputIndex;
}

/*******************************************************************************
Function    :My_Ini_Analysis_GetString自编解析函数--找出指定节指定键名的字符串值
Description :使用自编解析函数导出配置文件指定节中指定键名的键值（string类型）
Input       :节名、键名、默认值、缓冲区、缓冲区大小、文件路径
Output      :输出指定配置文件里的指定节名下指定键名的键值（string类型）
Return      :空
Note        :
********************************************************************************/
int My_Ini_Analysis_GetString(LPCTSTR targetSection, LPCTSTR targetKeyName, LPCTSTR valueDefault, LPTSTR stringBuffer, DWORD nSize, LPCTSTR filePath)
{
	FILE *iniFile; //初始化文件指针
	iniFile = fopen(filePath, "r");
	char iniLineBuffer[LINEMAXSIZE]; //初始化存储ini文件单行字符的字符数组
	char TargetSection[LINEMAXSIZE]; //初始化存储转化成规范节名的指定节名
	int sectionIndex = 2; //初始化寻找状态标志，2是默认值，1是节名匹配，0是不匹配
	int outputIndex = 0; //初始化输出标志，0是默认值，0是之前未找到节名，1是之前已经匹配到节名
	int keyFindIndex = 0; // 初始化键名查找状态标志，0是默认值，0是未找到键名，1是已找到

	bool JFS = FALSE; //记录文件打开情况,初始化为FALSE（关闭）
	JFS = Judge_File_Status(iniFile); //判断文件打开状态
	if (!JFS)
	{
		return 0;
	}

	sprintf(TargetSection, "[%s]", targetSection); //将添加括号的目标节名赋值给规范节名

	//cout << endl << "想要查找的节名：" << targetSection;
	//cout << endl << "标准化后的节名：" << TargetSection << endl;

	//按行读取文件流中的字符串，读取不为空则进行后续操作
	while (JFS && fgets(iniLineBuffer, LINEMAXSIZE, iniFile))
	{
		RemoveCh(iniLineBuffer); //处理当前字符串，移除空格

		if (outputIndex != 1) //未匹配过字节，继续匹配
		{
			Judge_Section(TargetSection, iniLineBuffer, &sectionIndex, &outputIndex); //判断当前是不是节名

			//if (sectionIndex == 1)
			//{
			//	cout << "找到匹配的节名:" << iniLineBuffer << endl;
			//}
			continue;
		}

		//已经匹配过节名，目前是输出键名键值状态
		Judge_Section(TargetSection, iniLineBuffer, &sectionIndex, &outputIndex); //判断当前是不是节名

		if (sectionIndex == 2) //当前不是节名,查找键值
		{
			char *keyEqualP = FindEqual(iniLineBuffer);  //得到当前键名键值型字符串中指向等号的指针
			
			char KeyNameBuffer[LINEMAXSIZE]; //初始化存储当前键名的缓冲区
			strncpy(KeyNameBuffer, iniLineBuffer, (keyEqualP - iniLineBuffer)); //将等号之前的键名字符串截取赋值到缓冲区
			KeyNameBuffer[(keyEqualP - iniLineBuffer)] = '\0'; //末尾添加结束符

			if (!strcmp(KeyNameBuffer,targetKeyName))
			{
				keyFindIndex = 1; //标志已经找到目标键名
				++keyEqualP;

				//将等号后的字符赋值到键值缓存区
				for (int i = 0; i <= (strlen(keyEqualP) - 1); i++)
				{
					stringBuffer[i] = keyEqualP[i];

				}
				stringBuffer[strlen(keyEqualP)] = '\0';

				break;
			}
		}
		else
		{
			//将默认字符串赋值到键值缓存区
			for (int i = 0; i <= (strlen(valueDefault) - 1); i++)
			{
				stringBuffer[i] = valueDefault[i];
			}
			stringBuffer[strlen(valueDefault)] = '\0';

			//cout << "找不到该键名！采取默认";
			fclose(iniFile); //关闭文件
			break; //结束文件查找
		}
	}/*while*/

	if (keyFindIndex == 0)
	{
		//将默认字符串赋值到键值缓存区
		for (int i = 0; i <= (strlen(valueDefault) - 1); i++)
		{
			stringBuffer[i] = valueDefault[i];
		}
		stringBuffer[strlen(valueDefault)] = '\0';

		//cout << "找不到该键名！采取默认";
		fclose(iniFile); //关闭文件
	}
	cout << endl;

	return keyFindIndex;
}

/**************************************************************************
Function    :My_Ini_Analysis_GetInt自编解析函数--找出指定节指定键名的整形值
Description :使用自编解析函数导出配置文件指定节中指定键名的键值（int类型）
Input       :节名、键名、默认值、文件路径
Output      :输出指定配置文件里的指定节名下指定键名的键值（int类型）
Return      :空
Note        :
***************************************************************************/
int My_Ini_Analysis_GetInt(LPCTSTR targetSection, LPCTSTR targetKeyName, int *valueDefault, LPCTSTR filePath)
{
	FILE *iniFile; //初始化文件指针
	iniFile = fopen(filePath, "r");
	char iniLineBuffer[LINEMAXSIZE]; //初始化存储ini文件单行字符的字符数组
	char TargetSection[LINEMAXSIZE]; //初始化存储转化成规范节名的指定节名
	char keyValueStringBuffer[LINEMAXSIZE]; //初始化存储找到的键值字符数组
	//int keyValueIntBuffer = 0; //初始化存储转化成整形的数字
	int sectionIndex = 2; //初始化寻找状态标志，2是默认值，1是节名匹配，0是不匹配
	int outputIndex = 0; //初始化输出标志，0是默认值，0是之前未找到节名，1是之前已经匹配到节名
	int keyFindIndex = 0; // 初始化键名查找状态标志，0是默认值，0是未找到键名，1是已找到

	bool JFS = FALSE; //记录文件打开情况,初始化为FALSE（关闭）
	JFS = Judge_File_Status(iniFile); //判断文件打开状态
	if (!JFS)
	{
		return 0;
	}

	sprintf(TargetSection, "[%s]", targetSection); //将添加括号的目标节名赋值给规范节名

	//cout << endl << "想要查找的节名：" << targetSection;
	//cout << endl << "标准化后的节名：" << TargetSection << endl;

	//按行读取文件流中的字符串，读取不为空则进行后续操作
	while (JFS && fgets(iniLineBuffer, LINEMAXSIZE, iniFile))
	{
		RemoveCh(iniLineBuffer); //处理当前字符串，移除空格

		if (outputIndex != 1) //未匹配过字节，继续匹配
		{
			Judge_Section(TargetSection, iniLineBuffer, &sectionIndex, &outputIndex); //判断当前是不是节名

			//if (sectionIndex == 1)
			//{
			//	cout << "找到匹配的节名:" << iniLineBuffer << endl;
			//}
			continue;
		}

		//已经匹配过节名，目前是输出键名键值状态
		Judge_Section(TargetSection, iniLineBuffer, &sectionIndex, &outputIndex); //判断当前是不是节名

		if (sectionIndex == 2) //当前不是节名,查找键值
		{
			char *keyEqualP = FindEqual(iniLineBuffer);  //得到当前键名键值型字符串中指向等号的指针

			char KeyNameBuffer[LINEMAXSIZE]; //初始化存储当前键名的缓冲区
			strncpy(KeyNameBuffer, iniLineBuffer, (keyEqualP - iniLineBuffer)); //将等号之前的键名字符串截取赋值到缓冲区
			KeyNameBuffer[(keyEqualP - iniLineBuffer)] = '\0'; //末尾添加结束符

			if (!strcmp(KeyNameBuffer, targetKeyName))
			{
				keyFindIndex = 1; //标志已经找到目标键名
				++keyEqualP;

				*valueDefault = atoi(keyEqualP); //字符串转换成整形
				break;
			}
		}
		else
		{
			//cout << "找不到该键名！采取默认";
			fclose(iniFile); //关闭文件
			break; //结束文件查找
		}
	}/*while*/

	if (keyFindIndex == 0)
	{
		//cout << "找不到该键名！采取默认";
		fclose(iniFile); //关闭文件
	}
	cout << endl;

	return keyFindIndex;
}