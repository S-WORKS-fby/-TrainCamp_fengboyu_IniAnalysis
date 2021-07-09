/*************************my_ini_analysis.cpp�ļ�˵��***************************
* Descript	:Դ�ļ��������Ա���������ĺ�������
* Author    :fengboyu
* Date      :2021_07_07
*******************************************************************************/


/***********************************ͷ�ļ�****************************************/
#include "config.h"
#include "my_ini_analysis.h"

/***********************************��������**************************************/
bool Judge_File_Status(FILE *file);

void RemoveCh(char *arrP);

char* FindEqual(char *arrP);

void Find_File_Section(char *arrP);

void Judge_Section(char *secP, char *arrP, int *stIndex, int *opIndex);


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
		cout << endl << "�ļ��򿪳ɹ���" << endl;
		return TRUE;
	}
	else
	{
		cout << endl << "�ļ���ʧ�ܣ�" << endl;
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
Function    :FindEqual
Description :�ҵ�������ֵ���������ĵȺ�λ��
Input       :�ַ���ָ��
Output      :��
Return      :ָ��Ⱥŵ�ָ��
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
Description :�ҳ������ļ��Ľ���
Input       :�ַ�����ָ��
Output      :����
Return      :��
Note        :
*************************************************************/
void Find_File_Section(char *arrP,int *indexP)
{
	char *pos = arrP; //��ʼ������ָ��

	if (*pos == '[')
	{
		while (*pos != '\n')
		{
			if (*pos == ']') //������ҵ������ţ���ô����м�Ľ�
			{
				*indexP = 1; //��־�ҵ�������
				++arrP;
				while (arrP != pos)
				{
					cout << *arrP;
					++arrP;
				}
				cout << endl;
				break;  //����ں�������ǰ����ѭ��
			}
			pos++;
		}/*while (*pos != '\n')*/
	}/*if (*pos == '[')*/
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

	if (*pos != '[')
	{
		*stIndex = 2;
		return;
	}/*if (*pos != '[')*//*ifִ����ϣ���*indexΪĬ��ֵ2������ַ������ǽڣ���Ϊ1˵������ƥ�䣬��Ϊ0˵����ƥ��*/

	while (*pos != '\n')
	{
		if (*pos != ']')
		{
			pos++;
			continue;
		}

		if (*opIndex != 0)//��֮ǰ�Ѿ��ҵ��������ٴ�����������ֹͣ���
		{
			*stIndex = 0;
			cout << endl;
			break;
		}

		char sectionBuffer[LINEMAXSIZE]; //��ʼ���洢��ǰ�н�ȡ�Ľ���
		strncpy(sectionBuffer, arrP, (pos - arrP + 1)); //��ȡ
		sectionBuffer[(pos - arrP + 1)] = '\0';

		//cout << "�ȶԽ�����" << secP << arrP << endl;

		if (!strcmp(sectionBuffer, secP)) //�жϵ�ǰ�ں�Ѱ�ҽ����Ƿ����,����������
		{
			*stIndex = 1;
			*opIndex = 1;
			//cout << "����ƥ��" << endl << endl;
			break;
		}
		else
		{
			*stIndex = 0;
			//cout << "������ƥ��" << endl << endl;
			break;
		}
	}/*while (*pos != '\n')*/
}

/*************************************************************
Function    :My_Ini_Analysis_GetSectionNames�Ա��������--����
Description :ʹ���Ա�����������������ļ������Ľ�
Input       :�����ļ�·��
Output      :���ָ�������ļ�������н���
Return      :��
Note        :
*************************************************************/ 
int My_Ini_Analysis_GetSectionNames(LPCTSTR filePath)
{
	FILE *iniFile; //��ʼ���ļ�ָ��
	iniFile = fopen(filePath, "r");	
	static char iniLineBuffer[LINEMAXSIZE] = { 0 }; //��ʼ���洢ini�ļ������ַ����ַ�����
	int outputIndex = 0; //��ʼ�������־��0��δ�ҵ�������1���ҵ�����
	bool JFS = TRUE; //��¼�ļ������,��ʼ��ΪTRUE��������

	JFS = Judge_File_Status(iniFile); //�ж��ļ���״̬

	if (!JFS)
	{
		return 0;
	}

	//���ж�ȡ�ļ����е��ַ�������ȡ��Ϊ������к�������
	while (JFS && fgets(iniLineBuffer, LINEMAXSIZE, iniFile))
	{
		RemoveCh(iniLineBuffer); //����ǰ�ַ������Ƴ��ո�
		Find_File_Section(iniLineBuffer,&outputIndex); //�ҳ�������ַ�����Ľ�
	}
	cout << endl;

	return outputIndex;
}

/********************************************************************
Function    :My_Ini_Analysis_GetSection�Ա��������--�ڰ����ļ�����ֵ
Description :ʹ���Ա�����������������ļ�ָ���ڵļ����ͼ�ֵ
Input       :�������ļ�·��
Output      :���ָ�������ļ����ָ�������µ����м�����ֵ
Return      :��
Note        :
********************************************************************/
int My_Ini_Analysis_GetSection(LPCTSTR targetSection, LPCTSTR filePath)
{
	FILE *iniFile; //��ʼ���ļ�ָ��
	iniFile = fopen(filePath, "r");
	char iniLineBuffer[LINEMAXSIZE]; //��ʼ���洢ini�ļ������ַ����ַ�����
	char TargetSection[LINEMAXSIZE]; //��ʼ���洢ת���ɹ淶������ָ������
	int sectionIndex = 2; //��ʼ��Ѱ��״̬��־��2��Ĭ��ֵ��1�ǽ���ƥ�䣬0�ǲ�ƥ��
	int outputIndex = 0; //��ʼ�������־��0��Ĭ��ֵ��0��֮ǰδ�ҵ�������1��֮ǰ�Ѿ�ƥ�䵽����

	bool JFS = TRUE; //��¼�ļ������,��ʼ��ΪTRUE��������
	JFS = Judge_File_Status(iniFile); //�ж��ļ���״̬
	if (!JFS)
	{
		return 0;
	}

	sprintf(TargetSection, "[%s]", targetSection); //��������ŵ�Ŀ�������ֵ���淶����

	//cout << endl << "��Ҫ���ҵĽ�����" << targetSection;
	//cout << endl << "��׼����Ľ�����" << TargetSection << endl;

	//���ж�ȡ�ļ����е��ַ�������ȡ��Ϊ������к�������
	while (JFS && fgets(iniLineBuffer, LINEMAXSIZE, iniFile))
	{
		RemoveCh(iniLineBuffer); //����ǰ�ַ������Ƴ��ո�

		if (outputIndex != 1) //δƥ����ֽڣ�����ƥ��
		{
			Judge_Section(TargetSection, iniLineBuffer, &sectionIndex, &outputIndex); //�жϵ�ǰ�ǲ��ǽ���

			if (sectionIndex == 1)
			{
				//cout << "�ҵ�ƥ��Ľ���:" << iniLineBuffer << endl;
				//cout << "Ҫ�ҵļ����ͼ�ֵ��:" << endl;
			}
			continue;
		}

		//�Ѿ�ƥ���������Ŀǰ�����������ֵ״̬
		Judge_Section(TargetSection, iniLineBuffer, &sectionIndex, &outputIndex); //�жϵ�ǰ�ǲ��ǽ���

		if (sectionIndex == 2) //��ǰ���ǽ���
		{
			cout << iniLineBuffer << endl;
		}
		else
		{
			fclose(iniFile); //�ر��ļ�
			break; //�����ļ�����
		}
	}/*while*/
	cout << endl;

	return outputIndex;
}

/*******************************************************************************
Function    :My_Ini_Analysis_GetString�Ա��������--�ҳ�ָ����ָ���������ַ���ֵ
Description :ʹ���Ա�����������������ļ�ָ������ָ�������ļ�ֵ��string���ͣ�
Input       :������������Ĭ��ֵ������������������С���ļ�·��
Output      :���ָ�������ļ����ָ��������ָ�������ļ�ֵ��string���ͣ�
Return      :��
Note        :
********************************************************************************/
int My_Ini_Analysis_GetString(LPCTSTR targetSection, LPCTSTR targetKeyName, LPCTSTR valueDefault, LPTSTR stringBuffer, DWORD nSize, LPCTSTR filePath)
{
	FILE *iniFile; //��ʼ���ļ�ָ��
	iniFile = fopen(filePath, "r");
	char iniLineBuffer[LINEMAXSIZE]; //��ʼ���洢ini�ļ������ַ����ַ�����
	char TargetSection[LINEMAXSIZE]; //��ʼ���洢ת���ɹ淶������ָ������
	int sectionIndex = 2; //��ʼ��Ѱ��״̬��־��2��Ĭ��ֵ��1�ǽ���ƥ�䣬0�ǲ�ƥ��
	int outputIndex = 0; //��ʼ�������־��0��Ĭ��ֵ��0��֮ǰδ�ҵ�������1��֮ǰ�Ѿ�ƥ�䵽����
	int keyFindIndex = 0; // ��ʼ����������״̬��־��0��Ĭ��ֵ��0��δ�ҵ�������1�����ҵ�

	bool JFS = FALSE; //��¼�ļ������,��ʼ��ΪFALSE���رգ�
	JFS = Judge_File_Status(iniFile); //�ж��ļ���״̬
	if (!JFS)
	{
		return 0;
	}

	sprintf(TargetSection, "[%s]", targetSection); //��������ŵ�Ŀ�������ֵ���淶����

	//cout << endl << "��Ҫ���ҵĽ�����" << targetSection;
	//cout << endl << "��׼����Ľ�����" << TargetSection << endl;

	//���ж�ȡ�ļ����е��ַ�������ȡ��Ϊ������к�������
	while (JFS && fgets(iniLineBuffer, LINEMAXSIZE, iniFile))
	{
		RemoveCh(iniLineBuffer); //����ǰ�ַ������Ƴ��ո�

		if (outputIndex != 1) //δƥ����ֽڣ�����ƥ��
		{
			Judge_Section(TargetSection, iniLineBuffer, &sectionIndex, &outputIndex); //�жϵ�ǰ�ǲ��ǽ���

			//if (sectionIndex == 1)
			//{
			//	cout << "�ҵ�ƥ��Ľ���:" << iniLineBuffer << endl;
			//}
			continue;
		}

		//�Ѿ�ƥ���������Ŀǰ�����������ֵ״̬
		Judge_Section(TargetSection, iniLineBuffer, &sectionIndex, &outputIndex); //�жϵ�ǰ�ǲ��ǽ���

		if (sectionIndex == 2) //��ǰ���ǽ���,���Ҽ�ֵ
		{
			char *keyEqualP = FindEqual(iniLineBuffer);  //�õ���ǰ������ֵ���ַ�����ָ��Ⱥŵ�ָ��
			
			char KeyNameBuffer[LINEMAXSIZE]; //��ʼ���洢��ǰ�����Ļ�����
			strncpy(KeyNameBuffer, iniLineBuffer, (keyEqualP - iniLineBuffer)); //���Ⱥ�֮ǰ�ļ����ַ�����ȡ��ֵ��������
			KeyNameBuffer[(keyEqualP - iniLineBuffer)] = '\0'; //ĩβ��ӽ�����

			if (!strcmp(KeyNameBuffer,targetKeyName))
			{
				keyFindIndex = 1; //��־�Ѿ��ҵ�Ŀ�����
				++keyEqualP;

				//���Ⱥź���ַ���ֵ����ֵ������
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
			//��Ĭ���ַ�����ֵ����ֵ������
			for (int i = 0; i <= (strlen(valueDefault) - 1); i++)
			{
				stringBuffer[i] = valueDefault[i];
			}
			stringBuffer[strlen(valueDefault)] = '\0';

			//cout << "�Ҳ����ü�������ȡĬ��";
			fclose(iniFile); //�ر��ļ�
			break; //�����ļ�����
		}
	}/*while*/

	if (keyFindIndex == 0)
	{
		//��Ĭ���ַ�����ֵ����ֵ������
		for (int i = 0; i <= (strlen(valueDefault) - 1); i++)
		{
			stringBuffer[i] = valueDefault[i];
		}
		stringBuffer[strlen(valueDefault)] = '\0';

		//cout << "�Ҳ����ü�������ȡĬ��";
		fclose(iniFile); //�ر��ļ�
	}
	cout << endl;

	return keyFindIndex;
}

/**************************************************************************
Function    :My_Ini_Analysis_GetInt�Ա��������--�ҳ�ָ����ָ������������ֵ
Description :ʹ���Ա�����������������ļ�ָ������ָ�������ļ�ֵ��int���ͣ�
Input       :������������Ĭ��ֵ���ļ�·��
Output      :���ָ�������ļ����ָ��������ָ�������ļ�ֵ��int���ͣ�
Return      :��
Note        :
***************************************************************************/
int My_Ini_Analysis_GetInt(LPCTSTR targetSection, LPCTSTR targetKeyName, int *valueDefault, LPCTSTR filePath)
{
	FILE *iniFile; //��ʼ���ļ�ָ��
	iniFile = fopen(filePath, "r");
	char iniLineBuffer[LINEMAXSIZE]; //��ʼ���洢ini�ļ������ַ����ַ�����
	char TargetSection[LINEMAXSIZE]; //��ʼ���洢ת���ɹ淶������ָ������
	char keyValueStringBuffer[LINEMAXSIZE]; //��ʼ���洢�ҵ��ļ�ֵ�ַ�����
	//int keyValueIntBuffer = 0; //��ʼ���洢ת�������ε�����
	int sectionIndex = 2; //��ʼ��Ѱ��״̬��־��2��Ĭ��ֵ��1�ǽ���ƥ�䣬0�ǲ�ƥ��
	int outputIndex = 0; //��ʼ�������־��0��Ĭ��ֵ��0��֮ǰδ�ҵ�������1��֮ǰ�Ѿ�ƥ�䵽����
	int keyFindIndex = 0; // ��ʼ����������״̬��־��0��Ĭ��ֵ��0��δ�ҵ�������1�����ҵ�

	bool JFS = FALSE; //��¼�ļ������,��ʼ��ΪFALSE���رգ�
	JFS = Judge_File_Status(iniFile); //�ж��ļ���״̬
	if (!JFS)
	{
		return 0;
	}

	sprintf(TargetSection, "[%s]", targetSection); //��������ŵ�Ŀ�������ֵ���淶����

	//cout << endl << "��Ҫ���ҵĽ�����" << targetSection;
	//cout << endl << "��׼����Ľ�����" << TargetSection << endl;

	//���ж�ȡ�ļ����е��ַ�������ȡ��Ϊ������к�������
	while (JFS && fgets(iniLineBuffer, LINEMAXSIZE, iniFile))
	{
		RemoveCh(iniLineBuffer); //����ǰ�ַ������Ƴ��ո�

		if (outputIndex != 1) //δƥ����ֽڣ�����ƥ��
		{
			Judge_Section(TargetSection, iniLineBuffer, &sectionIndex, &outputIndex); //�жϵ�ǰ�ǲ��ǽ���

			//if (sectionIndex == 1)
			//{
			//	cout << "�ҵ�ƥ��Ľ���:" << iniLineBuffer << endl;
			//}
			continue;
		}

		//�Ѿ�ƥ���������Ŀǰ�����������ֵ״̬
		Judge_Section(TargetSection, iniLineBuffer, &sectionIndex, &outputIndex); //�жϵ�ǰ�ǲ��ǽ���

		if (sectionIndex == 2) //��ǰ���ǽ���,���Ҽ�ֵ
		{
			char *keyEqualP = FindEqual(iniLineBuffer);  //�õ���ǰ������ֵ���ַ�����ָ��Ⱥŵ�ָ��

			char KeyNameBuffer[LINEMAXSIZE]; //��ʼ���洢��ǰ�����Ļ�����
			strncpy(KeyNameBuffer, iniLineBuffer, (keyEqualP - iniLineBuffer)); //���Ⱥ�֮ǰ�ļ����ַ�����ȡ��ֵ��������
			KeyNameBuffer[(keyEqualP - iniLineBuffer)] = '\0'; //ĩβ��ӽ�����

			if (!strcmp(KeyNameBuffer, targetKeyName))
			{
				keyFindIndex = 1; //��־�Ѿ��ҵ�Ŀ�����
				++keyEqualP;

				*valueDefault = atoi(keyEqualP); //�ַ���ת��������
				break;
			}
		}
		else
		{
			//cout << "�Ҳ����ü�������ȡĬ��";
			fclose(iniFile); //�ر��ļ�
			break; //�����ļ�����
		}
	}/*while*/

	if (keyFindIndex == 0)
	{
		//cout << "�Ҳ����ü�������ȡĬ��";
		fclose(iniFile); //�ر��ļ�
	}
	cout << endl;

	return keyFindIndex;
}