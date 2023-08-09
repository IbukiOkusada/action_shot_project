//===============================================
//
// �e�̏��� [bullet.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "bullet.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "debugproc.h"
#include "explosion.h"
#include "enemy.h"
#include "effect.h"
#include "particle.h"
#include "sound.h"
#include "score.h"
#include "texture.h"
#include "objectX.h"
#include "Xfile.h"
#include "slow.h"
#include "meshorbit.h"
#include "meshfield.h"
#include "wet.h"
#include "game.h"

//===============================================
// �}�N����`
//===============================================
#define LIFE	(120.0f)		// ����

// �ÓI�����o�ϐ�
CBullet *CBullet::m_pTop = NULL;	// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
CBullet *CBullet::m_pCur = NULL;	// �Ō���̃I�u�W�F�N�g�ւ̃|�C���^
int CBullet::m_nNumAll = 0;

//===============================================
// �R���X�g���N�^
//===============================================
CBullet::CBullet()
{
	// �l�̃N���A
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fLife = 0.0f;
}

//===============================================
// �R���X�g���N�^(�I�[�o�[���[�h)
//===============================================
CBullet::CBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	// �l�̃N���A
	SetPosition(pos);
	m_fLife = 0.0f;
	m_move = move;
	m_Inermove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pTarget = NULL;
	m_pNext = NULL;
	m_pPrev = NULL;
	m_pOrbit = NULL;

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

	m_pOrbit2 = NULL;
}

//===============================================
// �f�X�g���N�^
//===============================================
CBullet::~CBullet()
{

}

//===============================================
// ����������
//===============================================
HRESULT CBullet::Init(void)
{
	// �I�u�W�F�N�g�̏���������
	CObject3D::Init();

	m_fLife = LIFE;
	m_nChangeTimer = 20;
	m_nType = 0;
	m_bDeath = false;

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CBullet::Uninit(void)
{
	// �I�u�W�F�N�g�̏I������
	CObject3D::Uninit();

	if (m_pTarget != NULL)
	{
		delete m_pTarget;
		m_pTarget = NULL;
	}

	if (m_pOrbit != NULL)
	{
		m_pOrbit->Uninit();
	}

	if (m_pOrbit2 != NULL)
	{
		m_pOrbit2->Uninit();
	}

	m_bDeath = true;

	DeathCheck();
}

//===============================================
// �X�V����
//===============================================
void CBullet::Update(void)
{
	D3DXVECTOR3 pos = GetPosition();

	// ���_���X�V
	//SetVtx();

	m_fLife -= CManager::GetSlow()->Get();

	if (m_fLife > 0.0f)
	{//  ����������ꍇ
		// ���W�X�V
		Controller();
		m_nChangeTimer--;

		//uCManager::GetDebugProc()->Print("���W[%f, %f, %f]\n", GetPosition().x, GetPosition().y, GetPosition().z);

		//�e�Ƃ̓����蔻��
		if (Collision(pos, CObject::TYPE_ENEMY) == true)
		{// ���������ꍇ
			//�X�R�A�̉��Z
			CManager::GetSound()->Play(CSound::LABEL_SE_BREAK);

			// ���S�m�F
			//DeathCheck();
			return;	// �I�����Ă��邽�ߕԂ�
		}
	}
	else
	{// �����؂�

		// �����̐���
		//CExplos ion::Create(GetPosition());

		// �I������
		Uninit();

		// ���S�m�F
		DeathCheck();
		return;
	}

	// �}�g���b�N�X�ݒ�
	SetMtx();
}

//===============================================
// �`�揈��
//===============================================
void CBullet::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	//���C�e�B���O���I�t�ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	
	//CObjectBillboard::Draw();

	//���C�e�B���O���I���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//===============================================
// ���_���ݒ�
//===============================================
CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, TYPE type)
{
	CBullet *pBullet = NULL;
	CTexture *pTexture = CManager::GetTexture();	// �e�N�X�`���ւ̃|�C���^

	// �I�u�W�F�N�g2D�̐���
	pBullet = new CBullet(pos, move);

	if (pBullet != NULL)
	{// �����ł����ꍇ

		// ����������
		pBullet->Init();

		// �e�̎�ސݒ�
		pBullet->m_nType = type;

		// �I�u�W�F�N�g�^�C�v�̐ݒ�
		pBullet->SetType(CObject::TYPE_BULLET);

		pBullet->BindTexture(-1);

		pBullet->SetSize(10.0f, 10.0f);

		pBullet->SetMtx();

		// �O�Ղ�
		if (type == TYPE_NONE)
		{
			pBullet->m_pOrbit = CMeshOrbit::Create(pBullet->GetMtx(), D3DXVECTOR3(0.0f, 3.0f, 0.0f), D3DXVECTOR3(0.0f, -3.0f, 0.0f), CMeshOrbit::TYPE_BULLET);
			pBullet->m_pOrbit2 = CMeshOrbit::Create(pBullet->GetMtx(), D3DXVECTOR3(0.0f, 3.0f, 0.0f), D3DXVECTOR3(0.0f, -3.0f, 0.0f), CMeshOrbit::TYPE_BULLET);
			pBullet->m_pOrbit2->BindTexture(CManager::GetTexture()->Regist("data\\TEXTURE\\water000.jpg"));
			pBullet->m_pOrbit->BindTexture(CManager::GetTexture()->Regist("data\\TEXTURE\\water001.jpg"));
		}
		else if (type == TYPE_SHOWER)
		{
			pBullet->m_pOrbit = CMeshOrbit::Create(pBullet->GetMtx(), D3DXVECTOR3(0.0f, 0.01f, 0.0f), D3DXVECTOR3(0.0f, -0.01f, 0.0f), CMeshOrbit::TYPE_BULLET);
			pBullet->m_pOrbit2 = CMeshOrbit::Create(pBullet->GetMtx(), D3DXVECTOR3(0.0f, 0.01f, 0.0f), D3DXVECTOR3(0.0f, -0.01f, 0.0f), CMeshOrbit::TYPE_BULLET);
			pBullet->m_pOrbit2->BindTexture(CManager::GetTexture()->Regist("data\\TEXTURE\\water002.jpg"));
			pBullet->m_pOrbit->BindTexture(CManager::GetTexture()->Regist("data\\TEXTURE\\water001.jpg"));
		}
		//pBullet->m_pOrbit->BindTexture(CManager::GetTexture()->Regist("data\\TEXTURE\\water000.jpg"));
	}
	else
	{// �����Ɏ��s�����ꍇ
		return NULL;
	}

	return pBullet;
}

//===============================================
// ���쏈��
//===============================================
void CBullet::Controller(void)
{
	D3DXVECTOR3 pos = GetPosition();	// ���W���擾
	CMeshField *pMesh = CGame::GetMeshField();
	D3DXVECTOR3 nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float fHeight = CGame::GetMeshField()->GetHeight(GetPosition(), nor);

	if (m_nType == TYPE_GRAVITY)
	{
		m_move.y += -0.07f * CManager::GetSlow()->Get();
	}
	else if (m_nType == TYPE_SHOWER)
	{
		m_move.y += -0.07f * CManager::GetSlow()->Get();
	}
	else
	{
		m_fParTimer += CManager::GetSlow()->Get();

		if (m_fParTimer >= 1.0f)
		{
			CParticle::Create(pos, m_move, CEffect::TYPE_BULLET);
			//m_fParTimer = 0.0f;
		}
	}

	if (m_pTarget == NULL)
	{// �z�[�~���O�����Ȃ��ꍇ
		pos += m_move * CManager::GetSlow()->Get();	// �ړ��ʉ��Z
	}
	else
	{// ����ꍇ
		CObject *pObj = m_pTarget->pObj;

		if (m_pTarget->pObj != NULL)
		{
			if (m_pTarget->pObj->GetDeath() == false && m_pTarget->pObj->GetType() == CObject::TYPE_ENEMY)
			{
				if (m_pTarget->pObj->GetMtx() != NULL)
				{
					m_move = D3DXVECTOR3(m_pTarget->pObj->GetMtx()->_41 - pos.x, m_pTarget->pObj->GetMtx()->_42 - pos.y, m_pTarget->pObj->GetMtx()->_43 - pos.z);
					D3DXVec3Normalize(&m_move, &m_move);
					float fRotDest = atan2f(  m_pTarget->pObj->GetMtx()->_41 - pos.x, m_pTarget->pObj->GetMtx()->_43 - pos.z);	//�ڕW�܂ł̊p�x
					float fRotDestXY = atan2f(m_pTarget->pObj->GetMtx()->_42 - pos.y, m_pTarget->pObj->GetMtx()->_41 - pos.x);
					float fRotDestZY = atan2f(m_pTarget->pObj->GetMtx()->_42 - pos.y, m_pTarget->pObj->GetMtx()->_43 - pos.z);
					if (m_nType == TYPE_NONE)
					{
						m_move.y *= m_pTarget->fSpeed;
					}

					m_move.x *= m_pTarget->fSpeed;
					m_move.z *= m_pTarget->fSpeed;
				}
			}
			else
			{
				pObj = NULL;
			}
		}
		pos += m_move * CManager::GetSlow()->Get();	// �ړ��ʉ��Z
	}

	pos += m_Inermove * CManager::GetSlow()->Get();

	m_Inermove.x += (0.0f - m_Inermove.x) * 0.1f * CManager::GetSlow()->Get();	//x���W
	m_Inermove.y += (0.0f - m_Inermove.y) * 0.1f * CManager::GetSlow()->Get();	//x���W
	m_Inermove.z += (0.0f - m_Inermove.z) * 0.1f * CManager::GetSlow()->Get();	//x���W

	if (m_pOrbit != NULL)
	{
		D3DXVECTOR3 nor = pos - GetPosition();

		D3DXVec3Normalize(&nor, &nor);	// �x�N�g���𐳋K������

		m_pOrbit->SetNor(nor);
	}

	if (m_pOrbit2 != NULL)
	{
		D3DXVECTOR3 nor = pos - GetPosition();

		D3DXVec3Normalize(&nor, &nor);	// �x�N�g���𐳋K������

		m_pOrbit2->SetNor(nor);
	}

	if (m_nType == TYPE_NONE)
	{
		if (m_fParTimer >= 1.0f)
		{
			//CEffect::Create(pos, CEffect::TYPE_BULLET);
			CParticle::Create(pos, m_move, CEffect::TYPE_BULLET);
			m_fParTimer = 0.0f;
		}
	}

	// ���_���ݒ�
	SetPosition(pos);

	if (pos.y < fHeight)
	{// �n�ʂɐG�ꂽ
		pos = GetPosition();
		pos.y = fHeight + 0.05f;
		CWet::Create(pos, 15.0f, 15.0f);
		Uninit();
	}
}

//===============================================
// �G�Ƃ̓����蔻��
//===============================================
bool CBullet::Collision(D3DXVECTOR3 pos, CObject::TYPE ObjType)
{
	CXFile *pFile = CManager::GetModelFile();

	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		CObject *pObj = CObject::GetTop(nCntPri);	// �擪���擾

		while (pObj != NULL)
		{// �g�p����Ă��Ȃ���Ԃ܂�

			CObject *pObjectNext = pObj->GetNext();	// ���̃I�u�W�F�N�g�ւ̃|�C���^���擾

			if (pObj->GetDeath() == false)
			{
				CObject::TYPE type;	// ���

				// �I�u�W�F�N�g�̎�ނ��擾
				type = pObj->GetType();

				if (type == ObjType)
				{// ��ނ��G�̏ꍇ

					D3DXVECTOR3 ObjPos;	// �I�u�W�F�N�g�̍��W
					float fObjWidth = 0.0f;
					float fObjHeight = 0.0f;

					// ���W�̎擾
					ObjPos = pObj->GetPosition();
					CEnemy *pObjX = (CEnemy*)pObj;

					if (pObjX == NULL)
					{// �g�p����Ă��Ȃ�
						pObj = pObjectNext;	// ���̃I�u�W�F�N�g�Ɉړ�
						continue;
					}

					if (pos.x + GetWidth() >= ObjPos.x + -50.0f && pos.x - GetWidth() <= ObjPos.x + 50.0f
						&& pos.z + GetWidth() >= ObjPos.z + -50.0f && pos.z - GetWidth() <= ObjPos.z + 50.0f
						&& pos.y + GetHeight() >= ObjPos.y + -50.0f && pos.y - GetHeight() <= ObjPos.y + 50.0f)
					{// �G�Əd�Ȃ����ꍇ

						// �I�u�W�F�N�g�̏I������
						if (pObjX->GetState() != CEnemy::STATE_COOL)
						{							
							if (m_nType == TYPE_NONE)
							{
								pObjX->Hit(800);
							}
							else
							{
								pObjX->Hit(60);
								//CGame::GetScore()->Add(5);
							}

							// �W�I�m�F
							Check(pObjX);

							// �������g�̏I������
							if (m_nType == TYPE_NONE)
							{
								Uninit();

								return TRUE;	// TRUE��Ԃ�(��������)
							}
						}
					}
				}
			}

			pObj = pObjectNext;	// ���̃I�u�W�F�N�g�Ɉړ�
		}
	}

	return FALSE;	// FALSE��Ԃ�(���ɂ��������Ă��Ȃ�)
}

//===============================================
// �G�Ƃ̓����蔻��
//===============================================
void CBullet::SetHom(CObject *pObj, float fSpeed)
{
	if (m_pTarget == NULL)
	{
		m_pTarget = new LockOn;
	}

	if (m_pTarget != NULL)
	{
		m_pTarget->pObj = pObj;
		m_pTarget->fSpeed = fSpeed;
	}
}

//===============================================
// �W�I�`�F�b�N
//===============================================
void CBullet::Check(CObject *pObject, CBullet *pBullet)
{
	CBullet *pBul = m_pTop;	// �擪���擾

	while (pBul != NULL)
	{// �g�p����Ă���ԌJ��Ԃ�
		CBullet *pBulNext = pBul->m_pNext;	// ����ێ�

		if (pBul->m_pTarget != NULL)
		{// ���b�N�I�����Ă���
			if (pBul->m_pTarget->pObj == pObject)
			{// �����W�I�̏ꍇ
				pBul->m_pTarget->pObj = NULL;
				delete pBul->m_pTarget;
				pBul->m_pTarget = NULL;
			}
		}

		pBul = pBulNext;	// ���Ɉړ�
	}
}

//===============================================
// ���S�m�F
//===============================================
void CBullet::DeathCheck(void)
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
// �����ړ��ʂ�ݒ�
//===============================================
void CBullet::SetInerMove(D3DXVECTOR3 move)
{
	m_Inermove = move;
}