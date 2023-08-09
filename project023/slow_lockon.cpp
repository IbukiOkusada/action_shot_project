//==========================================================
//
// �X���[���̃��b�N�I������ [slow_lockon.h]
// Author : Ibuki Okusada
//
//==========================================================
#include "slow_lockon.h"
#include "lockon.h"
#include "manager.h"
#include "texture.h"
#include "debugproc.h"
#include "renderer.h"
#include "objectX.h"
#include "model.h"
#include "camera.h"
#include "slow.h"
#include "enemy.h"
#include "game.h"
#include "meshfield.h"
#include "object2D.h"
#include "character.h"

#define DEF_LENGTH	(5000)	// �f�t�H���g����
#define DEF_SIZE	(70)

//==========================================================
// �R���X�g���N�^
//==========================================================
CSlowLock::CSlowLock(int nPriOrity) : CObject3D(nPriOrity)
{
	// �l�̃N���A
	m_fLength = 0.0f;
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CSlowLock::~CSlowLock()
{

}

//==========================================================
// ����������
//==========================================================
HRESULT CSlowLock::Init(void)
{
	// �r���{�[�h�̏�����
	CObject3D::Init();
	
	SetpVtx(DEF_SIZE, DEF_SIZE);
	m_fLength = DEF_SIZE;

	CObject2D *p = CObject2D::Create(7);

	p->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
	p->SetSize(SCREEN_WIDTH * 0.1f, SCREEN_HEIGHT * 0.1f);
	p->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f));

	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CSlowLock::Uninit(void)
{
	// �I��
	CObject3D::Uninit();
}

//==========================================================
// �X�V����
//==========================================================
void CSlowLock::Update(void)
{
	CCamera *pCamera = CManager::GetCamera();		// �J�����̃|�C���^
	D3DXVECTOR3 CamRot = pCamera->GetRotation();	// �J�����̊p�x

	if (CManager::GetSlow()->Get() != 1.0f)
	{
		// �p�x����
		Controller();

		// ���b�N�I������
		LockOn();
	}
}

//==========================================================
// �`�揈��
//==========================================================
void CSlowLock::Draw(void)
{
	if (CManager::GetSlow()->Get() == 1.0f)
	{
		return;
	}

	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	//CObject3D::Draw();
}

//==========================================================
// ����
//==========================================================
CSlowLock *CSlowLock::Create(void)
{
	CSlowLock *pLock = NULL;

	// ����
	pLock = new CSlowLock();

	if (pLock == NULL)
	{// �m�ۂł��Ȃ������ꍇ
		return NULL;
	}

	// ����������
	pLock->Init();

	// �e�N�X�`���w��
	pLock->BindTexture(CTexture::TYPE_SLOWLOCK);

	return pLock;
}

//==========================================================
// ���b�N�I���^�[�Q�b�g�ݒ�
//==========================================================
void CSlowLock::LockOn(void)
{
	CEnemy *pEnemy = NULL;
	int nCnt = 0;
	int nCntObj = 0;
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^
	D3DXMATRIX mtxProjection;
	D3DXMATRIX mtxView;
	D3DXMATRIX mtxWorld;
	D3DXVECTOR3 EnemyPos;
	D3DXVECTOR3 ScreenPos;
	D3DVIEWPORT9 Viewport;

	//�f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	pDevice->GetTransform(D3DTS_PROJECTION, &mtxProjection);
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);
	pDevice->GetViewport(&Viewport);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		CObject *pObj = CObject::GetTop(nCntPri);	// �擪���擾

		while (pObj != NULL)
		{// �g�p����Ă��Ȃ���Ԃ܂�

			CObject *pObjectNext = pObj->GetNext();	// ���̃I�u�W�F�N�g�ւ̃|�C���^���擾

			if (pObj == NULL)
			{// �g�p����Ă��Ȃ��ꍇ
				pObj = pObjectNext;	// ���̃I�u�W�F�N�g�Ɉړ�
				continue;
			}

			if (pObj->GetType() != CObject::TYPE_ENEMY)
			{// ��ނ����f���ł͂Ȃ��ꍇ
				pObj = pObjectNext;	// ���̃I�u�W�F�N�g�Ɉړ�
				continue;
			}

			if (pObj->GetDeath() == true)
			{
				pObj = pObjectNext;	// ���̃I�u�W�F�N�g�Ɉړ�
				continue;
			}

			pEnemy = pObj->GetEnemy();

			if (pEnemy == NULL)
			{
				pObj = pObjectNext;	// ���̃I�u�W�F�N�g�Ɉړ�
				continue;
			}

			EnemyPos.x = pEnemy->GetBody()->GetParts(0)->GetMtxWorld()->_41;
			EnemyPos.y = pEnemy->GetBody()->GetParts(0)->GetMtxWorld()->_42;
			EnemyPos.z = pEnemy->GetBody()->GetParts(0)->GetMtxWorld()->_43;

			D3DXVec3Project(&ScreenPos, &EnemyPos, &Viewport, &mtxProjection, &mtxView, &mtxWorld);

			//CManager::GetDebugProc()->Print("�G�l�~�[�̃X�N���[�����W[%f, %f, %f]\n", ScreenPos.x, ScreenPos.y, ScreenPos.z);
			//CManager::GetDebugProc()->Print("����͈�[MIN %f, %f, MAX %f, %f]\n", SCREEN_WIDTH * 0.45f, SCREEN_HEIGHT * 0.45f, SCREEN_WIDTH * 0.55f, SCREEN_HEIGHT * 0.55f);
			if (ScreenPos.x < SCREEN_WIDTH * 0.4f || ScreenPos.x > SCREEN_WIDTH * 0.6f ||
				ScreenPos.y < SCREEN_HEIGHT * 0.4f || ScreenPos.y > SCREEN_HEIGHT * 0.6f || ScreenPos.z >= 1.0f)
			{// ��ʂɕ`�悳��Ă��Ȃ�
				pObj = pObjectNext;	// ���̃I�u�W�F�N�g�Ɉړ�
				pEnemy = NULL;
				continue;
			}

			CLockOn *pLock = CLockOn::GetTop();	// �擪���擾

			while (pLock != NULL)
			{// �g�p����Ă���ԌJ��Ԃ�
				CLockOn *pLockNext = pLock->GetNext();	// ����ێ�

				if (pLock->GetDeath() == false && pLock->GetType() == CLockOn::TYPE_MULTI)
				{
					CEnemy *pLockEnemy = pLock->GetEnemy();
					if (pLockEnemy == pEnemy)
					{// �����W�I�̏ꍇ
						pEnemy = NULL;
						break;
					}
				}

				pLock = pLockNext;	// ���Ɉړ�
			}

			if (pEnemy != NULL)
			{
				break;
			}

			pObj = pObjectNext;	// ���̃I�u�W�F�N�g�Ɉړ�
		}
	}

	if (pEnemy != NULL)
	{// �g�p����Ă���ꍇ

		CLockOn *pLock = CLockOn::Create(pEnemy->GetMtx(), CLockOn::TYPE_MULTI);
		pLock->SetTag(pEnemy);
		pLock->SetCol(D3DXCOLOR(0.0f, 1.0f, 0.5f, 0.3f));
	}
}

//==========================================================
// ����֘A
//==========================================================
void CSlowLock::Controller(void)
{
	CCamera *pCamera = CManager::GetCamera();

	D3DXVECTOR3 CamRot = pCamera->GetRotation();
	D3DXVECTOR3 CamPosV = pCamera->GetPositionV();
	D3DXVECTOR3 CamPosR = pCamera->GetPositionR();
	D3DXVECTOR3 nor = (CamPosR - CamPosV);
	D3DXVECTOR3 vec;
	D3DXVec3Normalize(&vec, &nor);	// �x�N�g����ۑ�

	float fRotDiff = (float)((CamRot.z - MIN_CAMERA_ROTZ) / (MAX_CAMERA_ROTZ - MIN_CAMERA_ROTZ));

	float fPosYDiff = CamPosR.y * 0.1f;

	SetPosition(D3DXVECTOR3(CamPosR.x + (vec.x * (DEF_LENGTH + CamPosR.y * 0.5f)) * fRotDiff, 0.0f, CamPosR.z + (vec.z * (DEF_LENGTH + CamPosR.y * 0.5f)) * fRotDiff));

	D3DXVECTOR3 pos = GetPosition();

	if (pos.z + m_fLength >= 3600.0f)
	{
		pos.z = 3600.0f - m_fLength;
	}
	else if (pos.z - m_fLength <= -3600.0f)
	{
		pos.z = -3600.0f + m_fLength;
	}

	if (pos.x + m_fLength >= 3900.0f)
	{
		pos.x = 3900.0f - m_fLength;
	}
	else if (pos.x - m_fLength <= -3450.0f)
	{
		pos.x = -3450.0f + m_fLength;
	}


	if (CGame::GetMeshField() != NULL)
	{
		float fHeight = CGame::GetMeshField()->GetHeight(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		pos.y = fHeight;
	}

	SetPosition(pos);

	m_fLength = DEF_SIZE + fPosYDiff;

	SetpVtx(m_fLength, m_fLength);

	//CManager::GetDebugProc()->Print("�X���[���b�N�I���x�N�g��[%f, %f, %f]\n", nor.x, nor.y, nor.z);
	//CManager::GetDebugProc()->Print("�X���[���b�N�I�����W[%f, %f, %f]\n", GetPosition().x, GetPosition().y, GetPosition().z);
}