//===============================================
//
// �v���C���[�̏��� [player.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "enemy.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "debugproc.h"
#include "shadow.h"
#include "character.h"
#include "motion.h"
#include "slow.h"
#include "model.h"
#include "billboard.h"
#include "meshfield.h"
#include "texture.h"
#include "slow.h"
#include "bullet.h"

//===============================================
// �}�N����`
//===============================================
#define MOVE		(2.0f)		// �ړ���
#define PLAYER_GRAVITY	(-0.7f)	// �v���C���[�d��
#define PLAYER_JUMP	(15.0f)		// �v���C���[�W�����v��
#define STATE_CNT	(300)		// ��ԊǗ��J�E���g

//===============================================
// �R���X�g���N�^(�I�[�o�[���[�h)
//===============================================
CEnemy::CEnemy(int nPriOrity)
{
	// �l���N���A����
	m_Info.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fRotMove = 0.0f;
	m_fRotDiff = 0.0f;
	m_fRotDest = 0.0f;
	pShadow = NULL;
	m_pBody = NULL;
	m_pBillState = NULL;
	m_fStateCnt = 0;
}

//===============================================
// �f�X�g���N�^
//===============================================
CEnemy::~CEnemy()
{

}

//===============================================
// ����������
//===============================================
HRESULT CEnemy::Init(void)
{
	
	return S_OK;
}

//===============================================
// ����������(�I�[�o�[���[�h)
//===============================================
HRESULT CEnemy::Init(const char *pName)
{
	CTexture *pTexture = CManager::GetTexture();

	// ���̂̐ݒ�
	if (pName != NULL)
	{// �t�@�C���������݂��Ă���
		m_pBody = CCharacter::Create(pName);
		m_pBody->SetParent(&m_Info.mtxWorld);

		if (m_pBody->GetMotion() != NULL)
		{
			// �������[�V�����̐ݒ�
			m_pBody->GetMotion()->InitSet(1);
		}
	}

	m_fMoveCnt = rand() % 1000;

	m_pBillState = CObjectBillboard::Create(m_pBody->GetParts(2)->GetPosition());
	m_pBillState->BindTexture(CTexture::TYPE_ENEMYSTATE);
	m_pBillState->SetSize(10.0f, 10.0f);

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CEnemy::Uninit(void)
{
	// ���̂̏I������
	if (m_pBody != NULL)
	{
		m_pBody->Uninit();
		delete m_pBody;
		m_pBody = NULL;
	}

	// �e�̏I��
	if (pShadow != NULL)
	{
		pShadow->Uninit();
		pShadow = NULL;
	}

	// �r���{�[�h�̏I��
	if (m_pBillState != NULL)
	{
		m_pBillState->Uninit();
		m_pBillState = NULL;
	}

	// �p��
	Release();

	CBullet::Check(this);
}

//===============================================
// �X�V����
//===============================================
void CEnemy::Update(void)
{
	// �O��̍��W���擾
	m_Info.posOld = GetPosition();

	// ���̍X�V
	if (m_pBody != NULL)
	{// �g�p����Ă���ꍇ
		m_pBody->Update();
	}

	// �v���C���[����
	Controller();

	if (pShadow != NULL)
	{
		pShadow->SetPosition(D3DXVECTOR3(m_pBody->GetParts(0)->GetMtxWorld()->_41, m_Info.pos.y, m_pBody->GetParts(0)->GetMtxWorld()->_43));
	}

	// �r���{�[�h�̍��W����
	if (m_pBillState != NULL)
	{
		m_pBillState->SetPosition(D3DXVECTOR3(m_pBody->GetParts(3)->GetMtxWorld()->_41, 
			m_pBody->GetParts(3)->GetMtxWorld()->_42 + 20.0f, m_pBody->GetParts(3)->GetMtxWorld()->_43));
	}

	if (m_fStateCnt < STATE_CNT)
	{
		m_fStateCnt += CManager::GetSlow()->Get();

		if (m_fStateCnt >= STATE_CNT)
		{
			m_pBillState->BindTexture(CTexture::TYPE_ENEMYSTATEADD);
		}

		if (GetPosition().x > 2900.0f || GetPosition().x < -2900.0f ||
			GetPosition().z > 2900.0f || GetPosition().z < -2900.0f)
		{
			m_fStateCnt = 0;
			m_pBillState->BindTexture(CTexture::TYPE_ENEMYSTATEADD);
		}
	}
}


//===============================================
// �`�揈��
//===============================================
void CEnemy::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	//�f�o�C�X�ւ̃|�C���^���擾
	CTexture *pTexture = CManager::GetTexture();	// �e�N�X�`���ւ̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_Info.mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Info.rot.y, m_Info.rot.x, m_Info.rot.z);
	D3DXMatrixMultiply(&m_Info.mtxWorld, &m_Info.mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_Info.pos.x, m_Info.pos.y, m_Info.pos.z);
	D3DXMatrixMultiply(&m_Info.mtxWorld, &m_Info.mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_Info.mtxWorld);

	// ���̂̕`��
	if (m_pBody != NULL)
	{
		m_pBody->Draw();
	}
}

//===============================================
// ����
//===============================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, const char *pBodyName, const int nPriority)
{
	CEnemy *pEnemy = NULL;
	CXFile *pModelFile = CManager::GetModelFile();

	// �I�u�W�F�N�g2D�̐���
	pEnemy = new CEnemy(nPriority);

	if (pEnemy != NULL)
	{// �����ł����ꍇ

		// ����������
		pEnemy->Init(pBodyName);

		// ���W�ݒ�
		pEnemy->SetPosition(pos);

		// �����ݒ�
		pEnemy->SetRotation(rot);

		// �ړ��ʐݒ�
		pEnemy->SetMove(move);

		// ��ނ̐ݒ�
		pEnemy->SetType(TYPE_ENEMY);

		// �e�̐ݒ�
		pEnemy->pShadow = CShadow::Create(pos, 30.0f, 30.0f);

		pEnemy->m_pBillState->SetPosition(pEnemy->GetPosition());

		// �r���{�[�h�̐ݒ�
		//pEnemy->m_pBillState = CObjectBillboard::Create()
	}
	else
	{// �����Ɏ��s�����ꍇ
		return NULL;
	}

	return pEnemy;
}

//===============================================
// ���쏈��
//===============================================
void CEnemy::Controller(void)
{
	// �ݒ肳�ꂽ�ړ��ʂ����Z����
	if (m_fMoveCnt > 0.0f)
	{
		m_fMoveCnt -= CManager::GetSlow()->Get();

		m_Info.pos += m_Info.move * CManager::GetSlow()->Get();

		m_pBody->GetMotion()->BlendSet(1);
	}
	else
	{
		m_pBody->GetMotion()->BlendSet(0);
	}

	D3DXVECTOR3 nor;
	float fHeight = CManager::GetMeshField()->GetHeight(m_Info.pos, nor);
	m_Info.pos.y = fHeight;
}

//===============================================
// �q�b�g����
//===============================================
void CEnemy::Hit(float fDamage)
{

}