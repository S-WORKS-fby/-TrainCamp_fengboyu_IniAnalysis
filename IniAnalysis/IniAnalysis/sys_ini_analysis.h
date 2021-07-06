/***************************sys_ini_analysis.h文件说明****************************
* Descript	:调用系统解析函数的头文件
* Author    :fengboyu
* Date      :2021_07_06
*******************************************************************************/

#ifndef _SYS_INI_ANALYSIS_H_
#define _SYS_INI_ANALYSIS_H_

/***********************************头文件****************************************/
#include "config.h"

/************************************** 全局函数声明 *************************************/
void Sys_Ini_Analysis_GetSectionNames(LPCTSTR filePath);

void Sys_Ini_Analysis_GetSection(LPCTSTR sectionName, LPCTSTR filePath);

void Sys_Ini_Analysis_GetString(LPCTSTR sectionName, LPCTSTR keyName, LPCTSTR valueDefault, LPTSTR stringBuffer, DWORD nSize, LPCTSTR filePath);

void Sys_Ini_Analysis_GetInt(LPCTSTR sectionName, LPCTSTR keyName, int valueDefault, int *intBuffer, LPCTSTR filePath);

#endif /*_SYS_INI_ANALYSIS_H_*/
