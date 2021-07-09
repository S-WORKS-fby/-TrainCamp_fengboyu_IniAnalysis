/***************************my_ini_analysis.h�ļ�˵��****************************
* Descript	:�Ա����������ͷ�ļ�
* Author    :fengboyu
* Date      :2021_07_07
*******************************************************************************/

#ifndef _MY_INI_ANALYSIS_H_
#define _MY_INI_ANALYSIS_H_

/***********************************ͷ�ļ�****************************************/
#include "config.h"

/************************************** ȫ�ֺ������� *************************************/
int My_Ini_Analysis_GetSectionNames(LPCTSTR filePath);

int My_Ini_Analysis_GetSection(LPCTSTR targetSection, LPCTSTR filePath);

int My_Ini_Analysis_GetString(LPCTSTR targetSection, LPCTSTR targetKeyName, LPCTSTR  valueDefault, LPTSTR stringBuffer, DWORD nSize, LPCTSTR filePath);

int My_Ini_Analysis_GetInt(LPCTSTR targetSection, LPCTSTR targetKeyName, int *valueDefault, LPCTSTR filePath);

#endif /*_MY_INI_ANALYSIS_H_*/