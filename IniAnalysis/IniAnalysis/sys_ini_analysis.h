/***************************sys_ini_analysis.h�ļ�˵��****************************
* Descript	:����ϵͳ����������ͷ�ļ�
* Author    :fengboyu
* Date      :2021_07_06
*******************************************************************************/

#ifndef _SYS_INI_ANALYSIS_H_
#define _SYS_INI_ANALYSIS_H_

/***********************************ͷ�ļ�****************************************/
#include "config.h"

/************************************** ȫ�ֺ������� *************************************/
void Sys_Ini_Analysis_GetSectionNames(LPCTSTR filePath);

void Sys_Ini_Analysis_GetSection(LPCTSTR sectionName, LPCTSTR filePath);

void Sys_Ini_Analysis_GetString(LPCTSTR sectionName, LPCTSTR keyName, LPCTSTR valueDefault, LPTSTR stringBuffer, DWORD nSize, LPCTSTR filePath);

void Sys_Ini_Analysis_GetInt(LPCTSTR sectionName, LPCTSTR keyName, int valueDefault, int *intBuffer, LPCTSTR filePath);

#endif /*_SYS_INI_ANALYSIS_H_*/
