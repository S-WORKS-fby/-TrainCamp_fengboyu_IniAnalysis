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
void My_Ini_Analysis_GetSectionNames(LPCTSTR filePath);

void My_Ini_Analysis_GetSection(char *targetSection, LPCTSTR filePath);

void My_Ini_Analysis_GetString(LPCTSTR sectionName, LPCTSTR keyName, LPCTSTR valueDefault, LPTSTR stringBuffer, DWORD nSize, LPCTSTR filePath);

void My_Ini_Analysis_GetInt(LPCTSTR sectionName, LPCTSTR keyName, int valueDefault, int *intBuffer, LPCTSTR filePath);

bool Judge_File_Status(FILE *file);

void RemoveCh(char *arrP);

void Find_File_Section(char *arrP);

void Judge_Section(char *secP, char *arrP, int *stIndex, int *opIndex);

#endif /*_MY_INI_ANALYSIS_H_*/