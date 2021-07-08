#pragma once

/***************************my_ini_analysis.h文件说明****************************
* Descript	:自编解析函数的头文件
* Author    :fengboyu
* Date      :2021_07_07
*******************************************************************************/

#ifndef _MY_INI_ANALYSIS_H_
#define _MY_INI_ANALYSIS_H_

/***********************************头文件****************************************/
#include "config.h"

/************************************** 全局函数声明 *************************************/
__declspec(dllexport) void My_Ini_Analysis_GetSectionNames(LPCTSTR filePath);

__declspec(dllexport) void My_Ini_Analysis_GetSection(char *targetSection, LPCTSTR filePath);

__declspec(dllexport) void My_Ini_Analysis_GetString(LPCTSTR sectionName, LPCTSTR keyName, LPCTSTR valueDefault, LPTSTR stringBuffer, DWORD nSize, LPCTSTR filePath);

__declspec(dllexport) void My_Ini_Analysis_GetInt(LPCTSTR sectionName, LPCTSTR keyName, int valueDefault, int *intBuffer, LPCTSTR filePath);

__declspec(dllexport) bool Judge_File_Status(FILE *file);

__declspec(dllexport) void RemoveCh(char *arrP);

__declspec(dllexport) void Find_File_Section(char *arrP);

__declspec(dllexport) void Judge_Section(char *secP, char *arrP, int *stIndex, int *opIndex);

#endif /*_MY_INI_ANALYSIS_H_*/