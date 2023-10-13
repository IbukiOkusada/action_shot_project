//==========================================================
//
// ���b�N�I���̏��� [lockon.cpp]
// Author : Ibuki Okusada
//
//==========================================================
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
#include "character.h"
#include "sound.h"

// �}�N����`
#define MULTIDEF_SIZE	(50.0f)		// �f�t�H���g�T�C�Y
#define MULTISTART_SIZE	(1000.0f)	// �\���J�n�T�C�Y
#define MULTIMINUS_SIZE	(120.0f)	// �T�C�Y�ύX
#define MULTIADD_COLA	(0.1f)		// �F
#define DEF_SIZE		(35.0f)		// �f�t�H���g�T�C�Y
#define START_SIZE		(300.0f)	// �\���J�n�T�C�Y
#define MINUS_SIZE		(30.0f)		// �T�C�Y�ύX
#define ADD_COLA		(0.1f)		// �F
#define SHOT_LENGTH		(3000.0f)

// �ÓI�����o�ϐ�
CLockOn *CLockOn::m_pTop = NULL;	// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
CLockOn *CLockOn::m_pCur = NULL;	// �Ō���̃I�u�W�F�N�g�ւ̃|�C���^

//==========================================================
// �R���X�g���N�^
//==========================================================
CLockOn::CLockOn(int nPriOrity) : CObjectBillboard(nPriOrity)
{
	// �l�̃N���A
	m_bLock = false;
	m_pMtx = NULL;
	m_bDeath = false;
	m_pNext = NULL;
	m_pPrev = NULL;

	// �������g�����X�g�ɒǉ�
	if (m_pTop != NULL)
	{// �擪�����݂��Ă���ꍇ
		m_pCur->m_pNext = this;	// ���ݍŌ���̃I�u�W�F�N�g�̃|�C���^�ɂȂ���
		m_pPrev = m_pCur;
		m_pCur = this;	// �������g���Ō���ɂȂ�
	}
	else
	{// ���݂��Ȃ��ꍇ
		m_pTop = this;	// �������g���擪�ɂȂ�
		m_pCur = this;	// �������g���Ō���ɂȂ�
	}
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CLockOn::~CLockOn()
{

}

//==========================================================
// ����������
//==========================================================
HRESULT CLockOn::Init(void)
{
	// �r���{�[�h�̏�����
	CObjectBillboard::Init();

	// �F��ύX
	SetVtx(D3DXCOLOR(1.0f, 1.0f, 0.5f, 1.0f));

	SetSize(MULTISTART_SIZE, MULTISTART_SIZE);

	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CLockOn::Uninit(void)
{
	// �I��
	CObjectBillboard::Uninit();

	m_bDeath = true;

	DeathCheck();
}

//==========================================================
// �X�V����
//==========================================================
void CLockOn::Update(void)
{
	if (m_bUse == false && m_type == TYPE_TARGET)
	{
		return;
	}
	else if (m_type != TYPE_TARGET)
	{
		SetPosition(D3DXVECTOR3(m_pObj->GetMtx()->_41, m_pObj->GetMtx()->_42 + 50.0f, m_pObj->GetMtx()->_43));

		float fSize = GetWidth();
		D3DXCOLOR col = GetCol();
		D3DXVECTOR3 rot = GetRotation();

		if (fSize > MULTIDEF_SIZE)
		{// ����̃T�C�Y���傫��
			fSize -= MULTIMINUS_SIZE;
			col.a += MULTIADD_COLA;
			rot.z += D3DX_PI * 0.025f;

			if (fSize < MULTIDEF_SIZE)
			{
				fSize = MULTIDEF_SIZE;
				rot.z = 0.0f;
			}

			if (col.a > 1.0f)
			{
				col.a = 1.0f;
			}

			if (rot.z > D3DX_PI)
			{
				rot.z += -D3DX_PI * 2;
			}

			SetRotation(rot);
			SetSize(fSize, fSize);
			SetCol(col);
		}

		return;
	}

	CCamera *pCamera = CManager::GetCamera();		// �J�����̃|�C���^
	D3DXVECTOR3 CamRot = pCamera->GetRotation();	// �J�����̊p�x

	// ���b�N�I������
	LockOn();

	float fSize = GetWidth();
	D3DXCOLOR col = GetCol();
	D3DXVECTOR3 rot = GetRotation();

	if (fSize > DEF_SIZE)
	{// ����̃T�C�Y���傫��
		fSize -= MINUS_SIZE;
		col.a += ADD_COLA;

		if (fSize < DEF_SIZE)
		{
			fSize = DEF_SIZE;
			col.a = 1.0f;
		}

		if (col.a > 1.0f)
		{
			col.a = 1.0f;
		}

		SetSize(fSize, fSize);
		SetCol(col);
	}
}

//==========================================================
// �`�揈��
//==========================================================
void CLockOn::Draw(void)
{
	if ((m_bUse == false || m_bLock == false) && m_type == TYPE_TARGET)
	{
		return;
	}

	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	//���C�e�B���O���I�t�ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//Z�e�X�g�𖳌�������
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	CObjectBillboard::RotFusionDraw();

	//���C�e�B���O���I�t�ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//Z�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

//==========================================================
// ����
//==========================================================
CLockOn *CLockOn::Create(D3DXMATRIX *pMtx, TYPE type)
{
	CLockOn *pLock = NULL;

	// ����
	pLock = new CLockOn();

	if (pLock == NULL)
	{// �m�ۂł��Ȃ������ꍇ
		return NULL;
	}

	// ����������
	pLock->Init();

	// �e�̃}�g���b�N�X�ݒ�
	pLock->SetParent(pMtx);

	// �e�N�X�`���w��
	pLock->BindTexture(CTexture::TYPE_LOCKON);

	// ��ސݒ�
	pLock->m_type = type;

	return pLock;
}

//==========================================================
// ���b�N�I���^�[�Q�b�g�ݒ�
//==========================================================
void CLockOn::LockOn(void)
{
	CObject *pOldObj = NULL;
	CEnemy *pEnemy = NULL;
	D3DXMATRIX mtxProjection;
	D3DXMATRIX mtxView;
	D3DXMATRIX mtxWorld;
	D3DXVECTOR3 EnemyPos;
	D3DXVECTOR3 ScreenPos;
	D3DVIEWPORT9 Viewport;
	float fMultiScreen = 0.3f;	// ����͈�

	if (CManager::GetSlow()->Get() != 1.0f)
	{
		fMultiScreen = 0.4f;
	}

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
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

			if(pEnemy->GetState() == CEnemy::STATE_COOL || pEnemy->GetState() == CEnemy::STATE_COOLDOWN)
			{
				pObj = pObjectNext;	// ���̃I�u�W�F�N�g�Ɉړ�
				pEnemy = NULL;
				continue;
			}

			EnemyPos.x = pEnemy->GetBody()->GetParts(0)->GetMtxWorld()->_41;
			EnemyPos.y = pEnemy->GetBody()->GetParts(0)->GetMtxWorld()->_42;
			EnemyPos.z = pEnemy->GetBody()->GetParts(0)->GetMtxWorld()->_43;

			D3DXVec3Project(&ScreenPos, &EnemyPos, &Viewport, &mtxProjection, &mtxView, &mtxWorld);

			if (ScreenPos.x < SCREEN_WIDTH * fMultiScreen || ScreenPos.x > SCREEN_WIDTH * (1.0f - fMultiScreen) ||
				ScreenPos.y < SCREEN_HEIGHT * fMultiScreen || ScreenPos.y > SCREEN_HEIGHT * (1.0f - fMultiScreen) || ScreenPos.z >= 1.0f)
			{// ��ʂɕ`�悳��Ă��Ȃ�
				pObj = pObjectNext;	// ���̃I�u�W�F�N�g�Ɉړ�
				pEnemy = NULL;
				continue;
			}

			CLockOn *pLock = m_pTop;	// �擪���擾

			while (pLock != NULL)
			{// �g�p����Ă���ԌJ��Ԃ�
				CLockOn *pLockNext = pLock->m_pNext;	// ����ێ�

				if (pLock->m_bDeath == false && pLock->m_type == TYPE_MULTI)
				{
					if (pLock->m_pObj == pEnemy)
					{// �����W�I�̏ꍇ
						pEnemy = NULL;
						pOldObj = NULL;
						break;
					}
				}

				pLock = pLockNext;	// ���Ɉړ�
			}

			if (pOldObj != NULL)
			{// ��ԋ߂��I�u�W�F�N�g������ꍇ

				D3DXVECTOR3 OldPos = pOldObj->GetPosition();

				// ��ԋ߂����f���ƃv���C���[�̋��������߂�
				float fOldObjLength =
					sqrtf((OldPos.x - m_pMtx->_41) * (OldPos.x - m_pMtx->_41)
						+ (OldPos.z - m_pMtx->_43) * (OldPos.z - m_pMtx->_43));

				// ����̃��f���ƃv���C���[�̋��������߂�
				float fObjLength =
					sqrtf((EnemyPos.x - m_pMtx->_41) * (EnemyPos.x - m_pMtx->_41)
						+ (EnemyPos.z - m_pMtx->_43) * (EnemyPos.z - m_pMtx->_43));

				if (fObjLength < fOldObjLength)
				{// ����̃��f���̕����߂��ꍇ
					pOldObj = pObj;	// ��ԋ߂����f����ύX
				}
			}
			else
			{// �O�񃂃f�����o���Ă��Ȃ��ꍇ
				if (pEnemy != NULL)
				{
					pOldObj = pObj;
				}
			}

			pObj = pObjectNext;	// ���̃I�u�W�F�N�g�Ɉړ�

			if (CManager::GetSlow()->Get() != 1.0f)
			{
				if (pOldObj != NULL)
				{
					break;
				}
			}
		}
	}

	if (pOldObj != NULL)
	{
		pEnemy = pOldObj->GetEnemy();
	}

	if (pEnemy != NULL)
	{// �g�p����Ă���ꍇ

		EnemyPos.x = pEnemy->GetBody()->GetParts(0)->GetMtxWorld()->_41;
		EnemyPos.y = pEnemy->GetBody()->GetParts(0)->GetMtxWorld()->_42;
		EnemyPos.z = pEnemy->GetBody()->GetParts(0)->GetMtxWorld()->_43;
		// ����̃��f���ƃv���C���[�̋��������߂�
		float fObjLength =
			sqrtf((EnemyPos.x - m_pMtx->_41) * (EnemyPos.x - m_pMtx->_41)
				+ (EnemyPos.z - m_pMtx->_43) * (EnemyPos.z - m_pMtx->_43));

		if (fObjLength >= SHOT_LENGTH)
		{
			m_bLock = false;
			SetSize(0.0f, 0.0f);
			m_pObj = NULL;
			return;
		}

		if (CManager::GetSlow()->Get() == 1.0f)
		{// �X���[���Ă��Ȃ�
			SetPosition(D3DXVECTOR3(pOldObj->GetPosition().x, pOldObj->GetPosition().y + 30.0f, pOldObj->GetPosition().z));
			if (m_pObj != pEnemy)
			{
				CManager::GetSound()->Play(CSound::LABEL_SE_LOCKON);
				SetSize(START_SIZE, START_SIZE);
				SetCol(D3DXCOLOR(GetCol().r, GetCol().g, GetCol().b, 0.3f));
			}

			m_bLock = true;
			m_pObj = pEnemy;
		}
		else
		{// �X���[���Ă���
			if (CManager::GetSlow()->Get() < 1.0f)
			{
				CManager::GetSound()->Play(CSound::LABEL_SE_LOCKON);
				m_bLock = false;
				SetSize(0.0f, 0.0f);
				m_pObj = NULL;

				CLockOn *pLock = CLockOn::Create(pEnemy->GetMtx(), CLockOn::TYPE_MULTI);
				pLock->SetTag(pEnemy);
				pLock->SetCol(D3DXCOLOR(0.0f, 1.0f, 0.5f, 0.3f));
			}
			else
			{
				m_bLock = false;
				SetSize(0.0f, 0.0f);
				m_pObj = NULL;
			}
		}
	}
	else
	{
		m_bLock = false;
		SetSize(0.0f, 0.0f);
		m_pObj = NULL;
	}
}

//==========================================================
// �g�p����e�}�g���b�N�X��ݒ�
//==========================================================
void CLockOn::SetParent(D3DXMATRIX *pMtx)
{
	// �e�̃}�g���b�N�X���w��
	m_pMtx = pMtx;
}

//==========================================================
// �g�p����e�}�g���b�N�X��ݒ�
//==========================================================
CObject *CLockOn::GetTag(void)
{
	if (m_pObj != NULL)
	{
		if (m_pObj->GetDeath() == false)
		{
			CObject *pObj = m_pObj;
			return pObj;
		}
	}

	return NULL;
}

//===============================================
// ���S�m�F
//===============================================
void CLockOn::DeathCheck(void)
{
	if (m_bDeath == true)
	{
		// ���X�g���玩�����g���폜����
		if (m_pTop == this)
		{// ���g���擪
			if (m_pNext != NULL)
			{// �������݂��Ă���
				m_pTop = m_pNext;	// ����擪�ɂ���
				m_pNext->m_pPrev = NULL;	// ���̑O�̃|�C���^���o���Ă��Ȃ��悤�ɂ���
			}
			else
			{// ���݂��Ă��Ȃ�
				m_pTop = NULL;	// �擪���Ȃ���Ԃɂ���
				m_pCur = NULL;	// �Ō�����Ȃ���Ԃɂ���
			}
		}
		else if (m_pCur == this)
		{// ���g���Ō��
			if (m_pPrev != NULL)
			{// �������݂��Ă���
				m_pCur = m_pPrev;	// �O���Ō���ɂ���
				m_pPrev->m_pNext = NULL;	// �O�̎��̃|�C���^���o���Ă��Ȃ��悤�ɂ���
			}
			else
			{// ���݂��Ă��Ȃ�
				m_pTop = NULL;	// �擪���Ȃ���Ԃɂ���
				m_pCur = NULL;	// �Ō�����Ȃ���Ԃɂ���
			}
		}
		else
		{
			if (m_pNext != NULL)
			{
				m_pNext->m_pPrev = m_pPrev;	// ���g�̎��ɑO�̃|�C���^���o��������
			}
			if (m_pPrev != NULL)
			{
				m_pPrev->m_pNext = m_pNext;	// ���g�̑O�Ɏ��̃|�C���^���o��������
			}
		}
	}
}

//===============================================
// ���S�m�F
//===============================================
void CLockOn::Check(CEnemy *pObject)
{
	CLockOn *pLock = m_pTop;	// �擪���擾

	while (pLock != NULL)
	{// �g�p����Ă���ԌJ��Ԃ�
		CLockOn *pLockNext = pLock->m_pNext;	// ����ێ�

		if (pLock->m_bDeath == false && pLock->m_type == TYPE_MULTI)
		{
			if (pLock->m_pObj == pObject)
			{// �����W�I�̏ꍇ
				pLock->Uninit();
			}
		}

		pLock = pLockNext;	// ���Ɉړ�
	}
}

//===============================================
// multi�^�[�Q�b�g�폜
//===============================================
void CLockOn::MultiDeath(void)
{
	CLockOn *pLock = m_pTop;	// �擪���擾

	while (pLock != NULL)
	{// �g�p����Ă���ԌJ��Ԃ�
		CLockOn *pLockNext = pLock->m_pNext;	// ����ێ�

		if (pLock->m_bDeath == false && pLock->m_type == TYPE_MULTI)
		{
			pLock->Uninit();
		}
		pLock = pLockNext;	// ���Ɉړ�
	}
}