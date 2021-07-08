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
		cout << endl << "�ļ��򿪳ɹ���" << endl << endl;
		return TRUE;
	}
	else
	{
		cout << endl << "�ļ���ʧ�ܣ�" << endl << endl;
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
Function    :Judge_Section
Description :ͨ��*index��ֵ�ж��ַ����Ƿ��ǽڣ��Ƿ�ƥ��
Input       :ָ��������ָ�룬��ǰ�ַ������ָ�룬�ж�ָ��
Output      :�ж�ָ��
Return      :��
Note        :
*************************************************************/
void Judge_Section(char *secP, char *arrP, int *stIndex,int *opIndex)
{
	char *pos = arrP; //��ʼ������ָ��


	if (*pos == '[') 
	{
		while (*pos != '\n')  //ֻ����Ĭ��״̬�²Ż����������
		{
			if (*pos == ']') //������ҵ������ţ����ҵ��˽ڣ��жϽ����Ƿ�ƥ�䣬��Ϣ��*index��ֵ
			{
				if (*opIndex == 0) //֮ǰδ�ҵ�����
				{
					char sectionBuffer[LINEMAXSIZE]; //��ʼ���洢��ǰ�н�ȡ�Ľ���
					strncpy(sectionBuffer, arrP, (pos - arrP + 1)); //��ȡ
					sectionBuffer[(pos - arrP + 1)] = '\0';

					cout << "�ȶԽ�����" << secP << arrP << endl;

					if (!strcmp(sectionBuffer, secP)) //�жϵ�ǰ�ں�Ѱ�ҽ����Ƿ����
					{
						*stIndex = 1;
						*opIndex = 1;
						cout << "����ƥ��" << endl << endl;
						break;
					}
					else
					{
						*stIndex = 0;
						cout << "������ƥ��" << endl << endl;
						break;
					}
				}
				else //��֮ǰ�Ѿ��ҵ��������ٴ�����������ֹͣ���
				{
					*stIndex = 0;
					*opIndex = 0;
					cout << "������ֵ�����ϣ�" << endl;
					break;
				}
			}/*if (*pos == ']')*/
			pos++;
		}/*while (*pos != '\n')*/
	}/*if (*pos == '[')*//*ifִ����ϣ���*indexΪĬ��ֵ2������ַ������ǽڣ���Ϊ1˵������ƥ�䣬��Ϊ0˵����ƥ��*/
	else
	{
		*stIndex = 2;
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
void My_Ini_Analysis_GetSection(char *targetSection, LPCTSTR filePath)
{
	FILE *iniFile; //��ʼ���ļ�ָ��
	iniFile = fopen(filePath, "r");
	char intLineBuffer[LINEMAXSIZE]; //��ʼ���洢ini�ļ������ַ����ַ�����
	char TargetSection[LINEMAXSIZE]; //��ʼ���洢ת���ɹ淶������ָ������
	int sectionIndex = 2; //��ʼ��Ѱ��״̬��־��2��Ĭ��ֵ��1�ǽ���ƥ�䣬0�ǲ�ƥ��
	int outputIndex = 0; //��ʼ�������־��0��Ĭ��ֵ��0�ǲ������1�����

	bool JFS = TRUE; //��¼�ļ������,��ʼ��ΪTRUE��������

	sprintf(TargetSection, "[%s]", targetSection); //��������ŵ�Ŀ�������ֵ���淶����

	cout << endl << "��Ҫ���ҵĽ�����" << targetSection;
	cout << endl << "��׼����Ľ�����" << TargetSection << endl;

	JFS = Judge_File_Status(iniFile); //�ж��ļ���״̬

	//���ж�ȡ�ļ����е��ַ�������ȡ��Ϊ������к�������
	while (JFS && fgets(intLineBuffer, LINEMAXSIZE, iniFile))
	{
		RemoveCh(intLineBuffer); //����ǰ�ַ������Ƴ��ո�

		if (outputIndex == 1) //���Ѿ�ƥ���������Ŀǰ�����������ֵ״̬
		{
			Judge_Section(TargetSection, intLineBuffer, &sectionIndex, &outputIndex); //�жϵ�ǰ�ǲ��ǽ���

			if (sectionIndex == 2) //��ǰ���ǽ���
			{
				cout << intLineBuffer << endl;
			}
			else
			{
				fclose(iniFile); //�ر��ļ�
				break; //�����ļ�����
			}
		}
		else
		{
			Judge_Section(TargetSection, intLineBuffer, &sectionIndex, &outputIndex); //�жϵ�ǰ�ǲ��ǽ���

			if (sectionIndex == 1)
			{
				cout << "�ҵ�ƥ��Ľ���:" << intLineBuffer << endl;
				cout << "���еļ����ͼ�ֵ��:" << endl;
			}
		}
	}/*while*/
	cout << endl;
}