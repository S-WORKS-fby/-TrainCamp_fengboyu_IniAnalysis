/*************************my_ini_analysis.cpp�ļ�˵��***************************
* Descript	:Դ�ļ��������Ա���������ĺ�������
* Author    :fengboyu
* Date      :2021_07_07
*******************************************************************************/


/***********************************ͷ�ļ�****************************************/
#include "config.h"
#include "my_ini_analysis.h"


/***********************************��������**************************************/
/*************************************************************
Function    :Judge_File_Status
Description :�ж��ļ���״̬
Input       :�ļ�ָ��
Output      :�ļ������
Return      :�����ʧ��Ϊmain����1
Note        :
*************************************************************/
bool Judge_File_Status(FILE *file)
{
	//�ж��ļ��Ƿ�ɹ���
	if (file)
	{
		cout << "�ļ��򿪳ɹ���" << endl << endl;
		return TRUE;
	}
	else
	{
		cout << "�ļ���ʧ�ܣ�" << endl << endl;
		return FALSE;
	}

}

/*************************************************************
Function    :RemoveCh
Description :�Ƴ��ַ����еĿո�ע�ͳ���
Input       :�ַ�����ָ��
Output      :��
Return      :��
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
Description :�ҳ������ļ��Ľ���
Input       :�ַ�����ָ��
Output      :����
Return      :��
Note        :
*************************************************************/
void Find_File_Section(char *arrP)
{
	char *pos = arrP; //��ʼ������ָ��

	if (*pos == '[')
	{
		while (*pos != '\n')
		{
			if (*pos == ']') //������ҵ������ţ���ô����м�Ľ�
			{
				vector<char> SectionBuffer; //�����洢����������

				++arrP;
				while (arrP != pos)
				{
					SectionBuffer.push_back(*arrP);  //����ȡ�Ľ�����������
					arrP++;
				}

				for (int i = 0; i < SectionBuffer.size(); i++) //ѭ����������ַ�
				{
					cout << SectionBuffer[i];
				}
				cout << endl;
				break;  //����ں�������ǰ����ѭ��
			}
			pos++;
		}
	}
}

/*************************************************************
Function    :My_Ini_Analysis_GetSectionNames�Ա��������--����
Description :ʹ���Ա�����������������ļ������Ľ�
Input       :�����ļ�·��
Output      :���ָ�������ļ�������н���
Return      :��
Note        :
*************************************************************/ 
void My_Ini_Analysis_GetSectionNames(LPCTSTR filePath)
{
	FILE *iniFile; //��ʼ���ļ�ָ��
	iniFile = fopen(filePath, "r");	
	static char intLineBuffer[LINEMAXSIZE] = { 0 }; //��ʼ���洢ini�ļ������ַ����ַ�����
	//char findBuffer[LINEMAXSIZE] = { 0 }; //��ʼ���洢�����������ַ�����
	bool JFS = TRUE; //��¼�ļ������,��ʼ��ΪTRUE��������

	JFS = Judge_File_Status(iniFile); //�ж��ļ���״̬

	//���ж�ȡ�ļ����е��ַ�������ȡ��Ϊ������к�������
	while (JFS && fgets(intLineBuffer, LINEMAXSIZE, iniFile))
	{
		RemoveCh(intLineBuffer); //����ǰ�ַ������Ƴ��ո�
		Find_File_Section(intLineBuffer); //�ҳ�������ַ�����Ľ�
	}
	cout << endl;
}

/********************************************************************
Function    :My_Ini_Analysis_GetSection�Ա��������--�ڰ����ļ�����ֵ
Description :ʹ���Ա�����������������ļ�ָ���ڵļ����ͼ�ֵ
Input       :�������ļ�·��
Output      :���ָ�������ļ����ָ�������µ����м�����ֵ
Return      :��
Note        :
********************************************************************/
void My_Ini_Analysis_GetSection(string targetSection, LPCTSTR filePath)
{

}