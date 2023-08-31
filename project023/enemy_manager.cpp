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
	// �o��

}

//==========================================================
// �o������
//==========================================================
void CEnemyManager::Spawn(void)
{
	//if (m_pTime == NULL)
	//{
	//	return;
	//}

	//if (m_pTime->GetAnim() == 0 && m_pTime->GetNum() % NEXTWAVECNT == 0 && m_pTime->GetNum() < START_TIME)
	//{// ���̃E�F�[�u
	//	int NextNumEnemy = (int)(CObject::GetNumEnemAll() * 1.3f);

	//	// �G�̔z�u
	//	while (1)
	//	{
	//		if (CObject::GetNumEnemAll() < NextNumEnemy)
	//		{
	//			int nRand = rand() % 201 - 100;
	//			float fRot = D3DX_PI * ((float)nRand * 0.01f);

	//			CEnemy::Create(D3DXVECTOR3(0.0f + rand() % 300 - 150, 0.0f, 0.0f + rand() % 300 - 150), D3DXVECTOR3(0.0f, fRot, 0.0f),
	//				D3DXVECTOR3(-sinf(fRot) * 4.0f, 0.0f, -cosf(fRot) * 4.0f), "data\\TXT\\motion_murabito.txt");
	//		}
	//		else
	//		{
	//			break;
	//		}
	//	}
	//}
}