//==========================================================
//
// �G�̏o���Ǘ����� [enemy_manager.h]
// Author : Ibuki Okusada
//
//==========================================================
#include "enemy_manager.h"
#include "manager.h"
#include "object.h"
#include "time.h"
#include "enemy.h"
#include "meshfield.h"

// �}�N����`
#define NEXTWAVECNT	(20)	// �ewave�J�n�J�E���g

//==========================================================
// �R���X�g���N�^
//==========================================================
CEnemyManager::CEnemyManager()
{
	// �l�̃N���A
	m_nMaxEnemy = 0;
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CEnemyManager::~CEnemyManager()
{

}

//==========================================================
// ����������
//==========================================================
HRESULT CEnemyManager::Init(void)
{
	// ���݂̍ő�l�����o����
	m_nMaxEnemy = CObject::GetNumEnemAll();

	return true;
}

//==========================================================
// �I������
//==========================================================
void CEnemyManager::Uninit(void)
{

}

//==========================================================
// �X�V����
//==========================================================
void CEnemyManager::Update(void)
{
	CTime *pTime = CManager::GetScene()->GetTime();

	if (pTime == NULL)
	{
		return;
	}

	if (pTime->GetAnim() == 0 && pTime->GetNum() % NEXTWAVECNT == 0 && pTime->GetNum() < pTime->GetStartNum() && pTime->GetNum() > 0)
	{// ���̃E�F�[�u
		// �o��
		int NextNumEnemy = (int)(CObject::GetNumEnemAll() * 1.3f);
		Spawn(NextNumEnemy);
	}
}

//==========================================================
// �o������
//==========================================================
void CEnemyManager::Spawn(int nSetNum)
{
	int nSetArea = rand() % NUM_AREA;	// �z�u�ꏊ�������_���Ŏw��
	D3DXVECTOR3 SetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �z�u�ꏊ���w�肳�ꂽ�G���A�ɐݒ�
	{
		int nCnt = 0;

		// ���̕`��
		CMeshField *pMesh = CMeshField::GetTop();	// �擪���擾
		CMeshField *pArea = NULL;;

		while (pMesh != NULL)
		{// �g�p����Ă���ԌJ��Ԃ�
			CMeshField *pMeshNext = pMesh->GetNext();	// ����ێ�

			if (nCnt == nSetArea)
			{// �ݒu�G���A
				pArea = pMesh;
			}

			pMesh->SetHot(false);
			pMesh = pMeshNext;	// ���Ɉړ�
			nCnt++;

			if (nCnt >= NUM_AREA)
			{
				break;
			}
		}

		SetPos = pArea->GetPosition();
		pArea->SetHot(true);
	}

	// �G�̔z�u
	while (1)
	{
		if (CObject::GetNumEnemAll() < nSetNum)
		{
			int nRand = rand() % 201 - 100;
			float fRot = D3DX_PI * ((float)nRand * 0.01f);

			CEnemy::Create(D3DXVECTOR3(SetPos.x + rand() % 300 - 150, 0.0f, SetPos.z + rand() % 300 - 150), D3DXVECTOR3(0.0f, fRot, 0.0f),
				D3DXVECTOR3(-sinf(fRot) * 4.0f, 0.0f, -cosf(fRot) * 4.0f), "data\\TXT\\motion_murabito.txt");
		}
		else
		{
			break;
		}
	}
}