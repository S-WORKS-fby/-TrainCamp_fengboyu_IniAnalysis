/*************************main.cpp文件说明***************************
* Descript	:源文件，主程序
* Author    :fengboyu
* Date      :2021_07_06
*******************************************************************************/

/***********************************头文件****************************************/
#include "config.h"
#include "sys_ini_analysis.h"
#include "my_ini_analysis.h"


/***********************************主程序****************************************/
int main()
{
	LPCTSTR filePath = FILEPATH; //设置文件路径
	LPTSTR strName = new char[20]; //初始化指向读取的键值指针
	LPTSTR strClass = new char[20]; //初始化指向读取的键值指针
	int studentAge = 0; //初始化学生年龄
	int *age = &studentAge; //初始化指向学生年龄指针

	///************************************系统解析文件读取*********************************/
	///*******************************读取指定配置文件中的节信息***************************/
	//Sys_Ini_Analysis_GetSectionNames(filePath);

	///*************************读取指定配置文件中指定节的所有键名键值*********************/
	//Sys_Ini_Analysis_GetSection("stu dy", filePath);

	///*************************读取指定配置文件中指定节名下指定键名的信息*****************/
	////读取字符串类型
	//Sys_Ini_Analysis_GetString("  student ", "name", "未取得名字", strName, 20, filePath);
	//cout << strName << endl;
	//Sys_Ini_Analysis_GetString("stu dy", "class", "未取得班级", strClass, 20, filePath);
	//cout << strClass << endl;

	////读取整形
	//Sys_Ini_Analysis_GetInt("student", "a g e", 0, age, filePath);
	//cout << studentAge << endl;

	/************************************自编解析文件读取*********************************/
	/*******************************读取指定配置文件中的节信息***************************/
	My_Ini_Analysis_GetSectionNames(filePath); 
	/*************************读取指定配置文件中指定节的所有键名键值*********************/
	My_Ini_Analysis_GetSection("stu dy", filePath);

	system("pause");
	return 0;
}