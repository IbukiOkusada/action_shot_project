//==========================================================
//
// �G�̏��H�Ǘ����� [enemy_route.h]
// Author : Ibuki Okusada
//
//==========================================================
#include "enemy_route.h"
#include <stdio.h>

// �}�N����`
#define NEXTWAVECNT	(20)	// �ewave�J�n�J�E���g

//==========================================================
// �R���X�g���N�^
//==========================================================
CEnemyRoute::CEnemyRoute()
{
	for (int nCnt = 0; nCnt < MAX_ROUTE; nCnt++)
	{
		m_apRoute[nCnt] = NULL;
	}

	m_nNumAll = 0;
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CEnemyRoute::~CEnemyRoute()
{

}

//==========================================================
// ����������
//==========================================================
HRESULT CEnemyRoute::Init(void)
{

	return true;
}

//==========================================================
// �I������
//==========================================================
void CEnemyRoute::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_ROUTE; nCnt++)
	{
		if (m_apRoute[nCnt] == NULL)
		{
			continue;
		}

		if (m_apRoute[nCnt]->route.pPoint != NULL)
		{// �o�^����Ă���
			delete m_apRoute[nCnt]->route.pPoint;
			m_apRoute[nCnt]->route.pPoint = NULL;
		}

		delete m_apRoute[nCnt];
		m_apRoute[nCnt] = NULL;
		m_nNumAll--;	// �������J�E���g�_�E��
	}
}

//===============================================
// �w��t�@�C���̏����擾
//===============================================
CEnemyRoute::Route *CEnemyRoute::SetAddress(const char *pFileName)
{
	for (int nCnt = 0; nCnt < MAX_ROUTE; nCnt++)
	{
		if (m_apRoute[nCnt] == NULL)
		{// �g�p����Ă��Ȃ��ꍇ

			m_apRoute[nCnt] = new RouteData;

			// �t�@�C�������擾
			strcpy(&m_apRoute[nCnt]->aName[0], pFileName);

			if (Load(&m_apRoute[nCnt]->route, pFileName) == true)
			{
				return &m_apRoute[nCnt]->route;
			}
			else
			{
				delete m_apRoute[nCnt];
				m_apRoute[nCnt] = NULL;
			}
		}
		else
		{// �g�p����Ă���ꍇ
			if (strstr(&m_apRoute[nCnt]->aName[0], pFileName) != NULL)
			{// �t�@�C��������v���Ă���ꍇ
				return &m_apRoute[nCnt]->route;
				break;
			}
		}
	}

	return NULL;
}

//===============================================
// �w��A�h���X�̏����擾
//===============================================
CEnemyRoute::Route *CEnemyRoute::SetAddress(const int nIdx)
{
	if (nIdx > m_nNumAll || nIdx < 0)
	{// �ǂݍ��ݔ͈͊O�̏ꍇ
		return NULL;
	}
	else if (m_apRoute[nIdx] == NULL)
	{
		return NULL;
	}

	return &m_apRoute[nIdx]->route;
}

//===============================================
// �w��t�@�C���̃A�h���X���擾
//===============================================
int CEnemyRoute::Regist(const char *pFileName)
{
	int nIdx = -1;	// �ԍ�

	for (int nCnt = 0; nCnt < MAX_ROUTE; nCnt++)
	{
		if (m_apRoute[nCnt] == NULL)
		{// �g�p����Ă��Ȃ��ꍇ

			m_apRoute[nCnt] = new RouteData;
			// �t�@�C�������擾
			strcpy(&m_apRoute[nCnt]->aName[0], pFileName);

			if (Load(&m_apRoute[nCnt]->route, pFileName) == true)
			{
				nIdx = nCnt;	// �e�N�X�`���ԍ���ݒ�
				break;
			}
			else
			{
				delete m_apRoute[nCnt];
				m_apRoute[nCnt] = NULL;
			}
		}
		else
		{// �g�p����Ă���ꍇ
			if (strstr(&m_apRoute[nCnt]->aName[0], pFileName) != NULL)
			{// �t�@�C��������v���Ă���ꍇ
				nIdx = nCnt;	// �e�N�X�`���ԍ���ݒ�
				break;
			}
		}
	}

	return nIdx;	// �e�N�X�`���ԍ���Ԃ�
}

//===============================================
// �t�@�C���ǂݍ���
//===============================================
bool CEnemyRoute::Load(Route *pRoute, const char *pFileName)
{
	pRoute->nNumPoint = 0;
	pRoute->pPoint = NULL;
	pRoute->StartPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pRoute->StartRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	FILE *pFile = fopen(pFileName, "r");	// �t�@�C�����J��

	if (pFile == NULL)
	{// �J���Ȃ�����
		return false;
	}

	char aStr[128] = {};

	// �Ō�܂ŌJ��Ԃ��ǂݍ���
	while (fscanf(pFile, "%s", &aStr[0]) != EOF)
	{
		if (strcmp(&aStr[0], "SCRIPT") == 0)
		{//�X�N���v�g�J�n�̕������m�F�ł����ꍇ
			int nPoint = 0;	// �m�F����|�C���g��
			// �I�������܂�
			while (strcmp(&aStr[0], "END_SCRIPT") != 0)
			{
				int nResult = fscanf(pFile, "%s", &aStr[0]);

				if (nResult == EOF)
				{// �I��
					break;
				}
				else if (pRoute->nNumPoint != 0 && nPoint >= pRoute->nNumPoint)
				{// �S�ēǂݍ���
					break;
				}

				// �m�F
				if (strcmp(&aStr[0], "NUM_POINT") == 0)
				{// ����
					fscanf(pFile, "%s", &aStr[0]);			
					fscanf(pFile, "%d", &pRoute->nNumPoint);
					pRoute->pPoint = new D3DXVECTOR3[pRoute->nNumPoint];

					for (int nCnt = 0; nCnt < pRoute->nNumPoint; nCnt++)
					{
						pRoute->pPoint[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					}
				}
				else if (strcmp(&aStr[0], "POS") == 0)
				{// �J�n�n�_
					fscanf(pFile, "%s", &aStr[0]);
					fscanf(pFile, "%f", &pRoute->StartPos.x);
					fscanf(pFile, "%f", &pRoute->StartPos.y);
					fscanf(pFile, "%f", &pRoute->StartPos.z);
				}
				else if (strcmp(&aStr[0], "ROT") == 0)
				{// �J�n�n�_
					fscanf(pFile, "%s", &aStr[0]);
					fscanf(pFile, "%f", &pRoute->StartRot.x);
					fscanf(pFile, "%f", &pRoute->StartRot.y);
					fscanf(pFile, "%f", &pRoute->StartRot.z);
				}
				else if (strcmp(&aStr[0], "MOVE") == 0)
				{// �ړ���
					fscanf(pFile, "%s", &aStr[0]);
					fscanf(pFile, "%f", &pRoute->fMove);
				}
				else if (strcmp(&aStr[0], "POINT") == 0)
				{// �J�n�n�_
					fscanf(pFile, "%s", &aStr[0]);
					fscanf(pFile, "%f", &pRoute->pPoint[nPoint].x);
					fscanf(pFile, "%f", &pRoute->pPoint[nPoint].y);
					fscanf(pFile, "%f", &pRoute->pPoint[nPoint].z);
					nPoint++;
				}

			}
			//�e�f�[�^�̓ǂݍ��݊J�n
			break;
		}
	}

	// �t�@�C�������
	fclose(pFile);

	if (pRoute->nNumPoint == 0)
	{// �ǂݍ��ݎ��s
		if (pRoute->pPoint != NULL)
		{
			delete[] pRoute->pPoint;
			pRoute->pPoint = NULL;
		}
		return false;
	}

	m_nNumAll++;	// �������J�E���g�A�b�v

	return true;
}