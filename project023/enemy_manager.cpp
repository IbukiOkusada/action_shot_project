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
#define NEXTWAVECNT	(12)	// �ewave�J�n�J�E���g

const char *CEnemyManager::m_apEnemyFileName[ENEMY_MAX] =
{
	"data\\TXT\\motion_society.txt",
	"data\\TXT\\motion_society_yellow.txt",
	"data\\TXT\\motion_kidsboy.txt",
	"data\\TXT\\motion_kidsgirl.txt",
};

//==========================================================
// �R���X�g���N�^
//==========================================================
CEnemyManager::CEnemyManager()
{
	// �l�̃N���A
	m_nMaxEnemy = 0;
	m_nTimer = 0;
	m_nDeadCounter = 0;
	m_nSetTimer = 0;
	m_nSuvCounter = 0;
	m_nRouteSetPlus = 0;
	m_nSetNum = 0;
	m_nRouteRandRange = 0;
	m_nTypeSetPlus = 0;
	m_nTypeRandRange = 0;
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
	CEnemy::Create("data\\TXT\\motion_society_yellow.txt");
	m_nSetNum = 3;
	m_nSetTimer = NEXTWAVECNT;
	m_nRouteRandRange = NUM_ROUTE;
	m_nTypeRandRange = ENEMY_MAX;

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

	if (pTime->GetAnim() == 0 && pTime->GetNum() % m_nSetTimer == 0 && pTime->GetNum() > pTime->GetStartNum() && pTime->GetNum() > 0)
	{// ���̃E�F�[�u
		// �o��
		int nNextNumEnemy = CObject::GetNumEnemAll() + m_nSetNum;
		Spawn(nNextNumEnemy);
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
			if (CManager::GetMode() != CScene::MODE_TUTORIAL)
			{
				CEnemy *pEnemy = CEnemy::Create(m_apEnemyFileName[rand() % m_nTypeRandRange + m_nTypeSetPlus]);
				pEnemy->SetRoute(rand() % m_nRouteRandRange + m_nRouteSetPlus);
			}
			else
			{
				CEnemy::Create("data\\TXT\\motion_murabito.txt");
			}
		}
		else
		{
			break;
		}
	}
}

//==========================================================
// �`���[�g���A���o������
//==========================================================
void CEnemyManager::UpdateTutorial(void)
{
	m_nFrameTimer++;

	if (m_nFrameTimer % 60 == 0)
	{
		m_nFrameTimer = 0;
		m_nTimer++;
	}

	if (m_nTimer % (int)(NEXTWAVECNT * 0.25f) == 0 && m_nFrameTimer == 0)
	{// ���̃E�F�[�u
		m_nTimer = 0;
		// �o��
		int NextNumEnemy = CObject::GetNumEnemAll() + 1;
		Spawn(NextNumEnemy);
	}
}

//==========================================================
// ���[�g�����_���͈͐ݒ�
//==========================================================
void CEnemyManager::SetRouteRange(int nRange, int nSetPlus)
{
	m_nRouteRandRange = nRange;
	m_nRouteSetPlus = nSetPlus;
}

//==========================================================
// ��ރ����_���ݒ�
//==========================================================
void CEnemyManager::SetTypeRange(int nRange, int nSetPlus)
{
	m_nTypeRandRange = nRange;
	m_nTypeSetPlus = nSetPlus;
}

//==========================================================
// �z�u���ݒ�
//==========================================================
void CEnemyManager::SetNum(int nNum)
{
	m_nSetNum = nNum;
}