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
#define NEXTWAVECNT	(2)	// �ewave�J�n�J�E���g

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
	CEnemy::Create("data\\TXT\\motion_murabito.txt");

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
		int NextNumEnemy = CObject::GetNumEnemAll() + 6;
		Spawn(NextNumEnemy);
	}
}

//==========================================================
// �o������
//==========================================================
void CEnemyManager::Spawn(int nSetNum)
{
	// �G�̔z�u
	while (1)
	{
		if (CObject::GetNumEnemAll() < nSetNum)
		{
			CEnemy::Create("data\\TXT\\motion_murabito.txt");
		}
		else
		{
			break;
		}
	}
}