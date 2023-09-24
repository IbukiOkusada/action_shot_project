//===============================================
//
// �ԑS�ʂ̊Ǘ�����(car_manager.cpp)
// Author : Ibuki Okusada
//
//===============================================
#include "car_manager.h"
#include "car.h"
#include "manager.h"
#include "slow.h"
#include "shadow.h"
#include "Xfile.h"
#include "sound.h"

// �}�N����`
#define LOAD_POSX	(-200.0f)	// ����X���W
#define LOAD_POSY	(-30.0f)	// ����Y���W
#define LOAD_POSZ	(-4200.0f)	// ����Z���W
#define MOVE_Z		(11.0f)		// Z�ړ���
#define SPAWN_DEF	(120)		// ��{�����J�E���g
#define SPAWN_RAND	(180)		// �����_���������J�E���g
#define SET_RANKNUM	(6)			// �����L���O��ʏ����z�u��

//===============================================
// �ÓI�����o�ϐ�
//===============================================
const char *CCarManager::m_apFileName[MAX_CAR] = 
{
	"data\\MODEL\\car000.x",
	"data\\MODEL\\car001.x",
	"data\\MODEL\\car002.x",
	"data\\MODEL\\car003.x",
	"data\\MODEL\\car004.x",
	"data\\MODEL\\car005.x",
};

//===============================================
// �ÓI�����o�ϐ�
//===============================================
const D3DXVECTOR2 CCarManager::m_aShadowSize[MAX_CAR] =
{
	{ 100.0f, 200.0f },
	{ 100.0f, 200.0f },
	{ 100.0f, 200.0f },
	{ 100.0f, 200.0f },
	{ 180.0f, 720.0f },
	{ 180.0f, 720.0f },
};

//===============================================
// �R���X�g���N�^
//===============================================
CCarManager::CCarManager()
{
	// �l�̃N���A
	for (int nCnt = 0; nCnt < LOAD_MAX; nCnt++)
	{
		m_aSpawn[nCnt].fCount = 0.0f;
		m_aSpawn[nCnt].fDef = 0.0f;
		m_aSpawn[nCnt].nNum = 0;
		m_apTop[nCnt] = NULL;
		m_apCur[nCnt] = NULL;
	}
}

//===============================================
// �f�X�g���N�^
//===============================================
CCarManager::~CCarManager()
{

}

//===============================================
// ����������
//===============================================
HRESULT CCarManager::Init(void)
{
	for (int nCnt = 0; nCnt < LOAD_MAX; nCnt++)
	{
		m_aSpawn[nCnt].fDef = SPAWN_DEF;
	}

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CCarManager::Uninit(void)
{

}

//===============================================
// �X�V����
//===============================================
void CCarManager::Update(void)
{
	// �����Ǘ�
	Spawn();

	// �p��
	Delete();
}

//===============================================
// �����L���O�̏����z�u
//===============================================
void CCarManager::SetRanking(void)
{
	D3DXVECTOR3 pos = D3DXVECTOR3(LOAD_POSX, LOAD_POSY, LOAD_POSZ);
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, MOVE_Z);
	float fAddPos = 1400.0f;

	// �Ԑ����J��Ԃ�
	for (int nCnt = 0; nCnt < LOAD_MAX; nCnt++)
	{
		for (int nCntSet = 0; nCntSet < SET_RANKNUM; nCntSet++)
		{
			int nRand = rand() % MAX_CAR;

			CCar *pCar = NULL;
			rot.y = D3DX_PI * nCnt;

			pCar = CCar::Create(pos, rot, m_apFileName[nRand]);
			pCar->SetMove(move);
			pCar->GetShadow()->SetpVtx(m_aShadowSize[nRand].x, m_aShadowSize[nRand].y);

			// ���X�g�ɐݒ�
			BindList(pCar, (LOAD)nCnt);

			pos.z += fAddPos;
		}

		pos = D3DXVECTOR3(LOAD_POSX, LOAD_POSY, LOAD_POSZ);
		pos.x *= -1.0f;
		pos.z *= -1.0f;
		move.z *= -1.0f;
		fAddPos *= -1.0f;
	}
}

//===============================================
// ���X�g�ɃZ�b�g
//===============================================
bool CCarManager::BindList(CCar *pCar, LOAD load)
{
	if (load >= LOAD_RIGHT && load < LOAD_MAX)
	{// �͈͓�
		// �������g�����X�g�ɒǉ�
		if (m_apTop[load] != NULL)
		{// �擪�����݂��Ă���ꍇ
			m_apCur[load]->SetNext(pCar);	// ���ݍŌ���̃I�u�W�F�N�g�̃|�C���^�ɂȂ���
			pCar->SetPrev(m_apCur[load]);
			m_apCur[load] = pCar;	// �������g���Ō���ɂȂ�
		}
		else
		{// ���݂��Ȃ��ꍇ
			m_apTop[load] = pCar;	// �������g���擪�ɂȂ�
			m_apCur[load] = pCar;	// �������g���Ō���ɂȂ�
		}
	}
	else
	{// ���X�g�ǉ����s
		return false;
	}

	// ��������
	m_aSpawn[load].nNum++;

	return true;
}

//===============================================
// ���X�g����O��
//===============================================
void CCarManager::DetachList(CCar *pCar, LOAD load)
{
	// ���X�g���玩�����g���폜����
	if (m_apTop[load] == pCar)
	{// ���g���擪
		if (m_apTop[load]->GetNext() != NULL)
		{// �������݂��Ă���
			m_apTop[load] = m_apTop[load]->GetNext();	// ����擪�ɂ���
			m_apTop[load]->SetPrev(NULL);	// ���̑O�̃|�C���^���o���Ă��Ȃ��悤�ɂ���
		}
		else
		{// ���݂��Ă��Ȃ�
			m_apTop[load] = NULL;	// �擪���Ȃ���Ԃɂ���
			m_apCur[load] = NULL;	// �Ō�����Ȃ���Ԃɂ���
		}
	}
	else if (m_apCur[load] == pCar)
	{// ���g���Ō��
		if (m_apCur[load]->GetPrev() != NULL)
		{// ��O�����݂��Ă���
			m_apCur[load] = pCar->GetPrev();	// �O���Ō���ɂ���
			m_apCur[load]->SetNext(NULL);		// �O�̎��̃|�C���^���o���Ă��Ȃ��悤�ɂ���
		}
		else
		{// ���݂��Ă��Ȃ�
			m_apTop[load] = NULL;	// �擪���Ȃ���Ԃɂ���
			m_apCur[load] = NULL;	// �Ō�����Ȃ���Ԃɂ���
		}
	}
	else
	{// ��
		if (pCar->GetNext() != NULL)
		{// �������݂��Ă���
			pCar->GetNext()->SetPrev(pCar->GetPrev());	// ���g�̎��ɑO�̃|�C���^���o��������
		}
		if (pCar->GetPrev() != NULL)
		{// ��O�����݂��Ă���
			pCar->GetPrev()->SetNext(pCar->GetNext());	// ���g�̑O�Ɏ��̃|�C���^���o��������
		}
	}

	// ��������
	m_aSpawn[load].nNum--;
}

//===============================================
// ��������
//===============================================
void CCarManager::Spawn(void)
{
	D3DXVECTOR3 pos = D3DXVECTOR3(LOAD_POSX, LOAD_POSY, LOAD_POSZ);
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, MOVE_Z);

	// �Ԑ����J��Ԃ�
	for (int nCnt = 0; nCnt < LOAD_MAX; nCnt++)
	{
		m_aSpawn[nCnt].fCount += CManager::GetSlow()->Get();

		if (m_aSpawn[nCnt].fCount < m_aSpawn[nCnt].fDef)
		{// �K��l�ɒB���Ă��Ȃ�
			pos.x *= -1.0f;
			pos.z *= -1.0f;
			move.z *= -1.0f;
			continue;
		}

		int nRand = rand() % MAX_CAR;

		CCar *pCar = NULL;
		rot.y = D3DX_PI * nCnt;
		if (CManager::GetMode() != CScene::MODE_TUTORIAL)
		{
			pCar = CCar::Create(pos, rot, m_apFileName[nRand]);
			pCar->SetMove(move);
			pCar->GetShadow()->SetpVtx(m_aShadowSize[nRand].x, m_aShadowSize[nRand].y);
		}
		else
		{
			pCar = CCar::Create(pos, rot, m_apFileName[4]);
			pCar->SetMove(move);
			pCar->GetShadow()->SetpVtx(m_aShadowSize[4].x, m_aShadowSize[4].y);
		}

		// ���X�g�ɐݒ�
		BindList(pCar, (LOAD)nCnt);
		m_aSpawn[nCnt].fCount = 0.0f;
		m_aSpawn[nCnt].fDef = SPAWN_DEF + (float)(rand() % SPAWN_RAND);

		pos.x *= -1.0f;
		pos.z *= -1.0f;
		move.z *= -1.0f;
	}
}

//===============================================
// ����
//===============================================
void CCarManager::Delete(void)
{
	// ���Ԑ�
	{
		CCar *pCar = m_apTop[LOAD_LEFT];

		while (pCar != NULL)
		{
			CCar *pCarNext = pCar->GetNext();
			float fMoveZ = pCar->GetMove().z;
			float fPosZ = pCar->GetPosition().z;

			if (fPosZ < LOAD_POSZ)
			{// �[�܂ōs����
				// �I��
				DetachList(pCar, LOAD_LEFT);
				pCar->Uninit();
			}

			pCar = pCarNext;
		}
	}

	// �E�Ԑ�
	{
		CCar *pCar = m_apTop[LOAD_RIGHT];

		while (pCar != NULL)
		{
			CCar *pCarNext = pCar->GetNext();
			float fMoveZ = pCar->GetMove().z;
			float fPosZ = pCar->GetPosition().z;

			if (fPosZ > -LOAD_POSZ)
			{// �[�܂ōs����
				// �I��
				DetachList(pCar, LOAD_RIGHT);
				pCar->Uninit();
			}

			pCar = pCarNext;
		}
	}
}

//===============================================
// �����蔻��
//===============================================
CCar *CCarManager::Collision(D3DXVECTOR3 &pos, D3DXVECTOR3 &posOld, D3DXVECTOR3 &move, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax, bool *pJump)
{
	CXFile *pFile = CManager::GetModelFile();
	bool bLand = true;	// ���n�������ۂ�
	*pJump = true;

	// �Ԑ����J��Ԃ�
	for (int nCnt = 0; nCnt < LOAD_MAX; nCnt++)
	{
		CCar *pCar = m_apTop[nCnt];

		while (pCar != NULL)
		{
			CCar *pCarNext = pCar->GetNext();
			D3DXVECTOR3 vtxObjMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			D3DXVECTOR3 vtxObjMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// �����𔽉f
			pCar->SetRotSize(vtxObjMax,
				vtxObjMin,
				pFile->GetMax(pCar->GetIdx()),
				pFile->GetMin(pCar->GetIdx()),
				pCar->GetRotation().y);

			if (pos.x + vtxMax.x > pCar->GetPosition().x + vtxObjMin.x
				&& pos.x + vtxMin.x < pCar->GetPosition().x + vtxObjMax.x
				&& pos.z + vtxMax.z > pCar->GetPosition().z + vtxObjMin.z
				&& pos.z + vtxMin.z < pCar->GetPosition().z + vtxObjMax.z)
			{//�͈͓��ɂ���
			 //�ォ��̔���
				if (posOld.y + vtxMin.y >= pCar->GetPosition().y + vtxObjMax.y
					&& pos.y + vtxMin.y < pCar->GetPosition().y + vtxObjMax.y)
				{//�ォ��߂荞��
				 //��ɂ̂���
					pos.y = pCar->GetPosition().y + vtxObjMax.y - vtxMin.y;
					pos += pCar->GetMove();
					move.y = 0.0f;
					*pJump = false;

					return pCar;
				}
			}

			if (pos.y + vtxMax.y > pCar->GetPosition().y + vtxObjMin.y
				&& pos.y + vtxMin.y <= pCar->GetPosition().y + vtxObjMax.y)
			{//�v���C���[�ƃ��f�������������ɂ���
				if (posOld.x + vtxMin.x >= pCar->GetPosition().x + vtxObjMax.x
					&& pos.x + vtxMin.x < pCar->GetPosition().x + vtxObjMax.x
					&& pos.z + vtxMax.z > pCar->GetPosition().z + vtxObjMin.z
					&& pos.z + vtxMin.z < pCar->GetPosition().z + vtxObjMax.z)
				{//�E���獶�ɂ߂荞��
					pos.x = pCar->GetPosition().x + vtxObjMax.x - vtxMin.x + 0.1f;
					move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					pos.y += 5.0f;
					move.x = rand() % 20 * 0.1f + 15.0f;
					move.y = 7.0f;
					CManager::GetSound()->Play(CSound::LABEL_SE_CARHIT);

					return NULL;
				}
				else if (posOld.x + vtxMax.x <= pCar->GetPosition().x + vtxObjMin.x
					&& pos.x + vtxMax.x > pCar->GetPosition().x + vtxObjMin.x
					&& pos.z + vtxMax.z > pCar->GetPosition().z + vtxObjMin.z
					&& pos.z + vtxMin.z < pCar->GetPosition().z + vtxObjMax.z)
				{//������E�ɂ߂荞��
				 //�ʒu��߂�
					pos.x = pCar->GetPosition().x + vtxObjMin.x - vtxMax.x - 0.1f;
					move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					pos.y += 5.0f;
					move.x = rand() % 20 * -0.1f + -15.0f;
					move.y = 7.0f;
					CManager::GetSound()->Play(CSound::LABEL_SE_CARHIT);
					return NULL;
				}
				else if (((posOld.z + vtxMin.z >= pCar->GetPosition().z + vtxObjMax.z
					&& pos.z + vtxMin.z < pCar->GetPosition().z + vtxObjMax.z) || (pos.z + vtxMin.z >= pCar->GetOldPos().z + vtxObjMax.z
						&& pos.z + vtxMin.z < pCar->GetPosition().z + vtxObjMax.z))
					&& (pos.x + vtxMax.x > pCar->GetPosition().x + vtxObjMin.x
					&& pos.x + vtxMin.x < pCar->GetPosition().x + vtxObjMax.x))
				{//�������O�ɂ߂荞��
					//�ʒu��߂�
					pos.z = pCar->GetPosition().z + vtxObjMax.z - vtxMin.z + 0.1f;
					move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					pos.y += 5.0f;
					move.y = 7.0f;
					move.x = rand() % (200 - 100) * 0.1f;
					if (pCar->GetMove().z > 0.0f)
					{
						move.z = pCar->GetMove().z;
					}
					CManager::GetSound()->Play(CSound::LABEL_SE_CARHIT);
					return NULL;
				}
				else if (((posOld.z + vtxMax.z <= pCar->GetPosition().z + vtxObjMin.z
					&& pos.z + vtxMax.z > pCar->GetPosition().z + vtxObjMin.z) || (pos.z + vtxMax.z <= pCar->GetOldPos().z + vtxObjMin.z
						&& pos.z + vtxMax.z > pCar->GetPosition().z + vtxObjMin.z))
					&& (pos.x + vtxMax.x > pCar->GetPosition().x + vtxObjMin.x
					&& pos.x + vtxMin.x < pCar->GetPosition().x + vtxObjMax.x))
				{//��O���牜�ɂ߂荞��t
					//�ʒu��߂�
					pos.z = pCar->GetPosition().z + vtxObjMin.z - vtxMax.z - 0.1f;
					move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					pos.y += 5.0f;
					move.y = 7.0f;
					move.x = rand() % (200 - 100) * 0.1f;
					if(pCar->GetMove().z < 0.0f)
					{
						move.z = pCar->GetMove().z;
					}
					CManager::GetSound()->Play(CSound::LABEL_SE_CARHIT);
					return NULL;
				}
			}

			pCar = pCarNext;
		}
	}

	return NULL;
}