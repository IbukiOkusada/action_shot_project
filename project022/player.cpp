//===============================================
//
// �v���C���[�̏��� [player.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "player.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "debugproc.h"
#include "bullet.h"
#include "explosion.h"
#include "multibg.h"
#include "particle.h"
#include "camera.h"
#include "Xfile.h"
#include "shadow.h"
#include "waist.h"
#include "character.h"
#include "motion.h"
#include "model.h"
#include "slow.h"
#include "texture.h"
#include "meshfield.h"
#include "Xfile.h"
#include "lockon.h"

//===============================================
// �}�N����`
//===============================================
#define MOVE	(3.0f)		// �ړ���
#define PLAYER_GRAVITY	(-0.2f)	//�v���C���[�d��
#define PLAYER_JUMP		(11.0f)	//�v���C���[�W�����v��
#define DEF_SLOWTIME	(60 * 5)	// �X���[�\����
#define SLOW_OK			(60 * 2)	// �X���[�\�ɂȂ鎞��
#define SHOT_LENGTH	(4000.0f)		// �˒��͈�
#define SHOT_RANGE	(D3DX_PI * 0.9f)	// �˒��p�x

//===============================================
// ���킲�Ƃ̐ݒ�
//===============================================
const D3DXVECTOR3 CPlayer::SetWepPos[WEAPON_MAX] =	// ����ݒ�ʒu
{
	{ -13.0f, 4.5f, 0.0f },
	{ 13.0f, 4.5f, 0.0f },
	{ -7.0f, 13.0f, 0.0f },
};

//===============================================
// ���킲�Ƃ̍U���^�C�}�[
//===============================================
const int CPlayer::m_aWepTimer[ATK_MAX] =		// �U���^�C�}�[
{
	19,
	5,
};

//===============================================
// ����t�@�C����
//===============================================
const char *CPlayer::m_apFileName[WEAPON_MAX] = 
{
	"data\\MODEL\\sample\\watergunL.x",
	"data\\MODEL\\sample\\watergunR.x",
	"data\\MODEL\\sample\\watershower.x",
};

//===============================================
// �R���X�g���N�^
//===============================================
//CPlayer::CPlayer()
//{
//	// �l���N���A����
//	m_nCounterAnim = 0;
//	m_nPatternAnim = 0;
//}

//===============================================
// �R���X�g���N�^(�I�[�o�[���[�h)
//===============================================
CPlayer::CPlayer(const D3DXVECTOR3 pos)
{
	// �l���N���A����
	m_bJump = false;
	m_Info.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fRotMove = 0.0f;
	m_fRotDiff = 0.0f;
	m_fRotDest = 0.0f;
	m_nSlowTime = 0;
	pShadow = NULL;
	m_pBody = NULL;
	m_pLeg = NULL;
	m_pWaist = NULL;
	m_pWeaponL = NULL;
	m_pWeaponR = NULL;
}

//===============================================
// �R���X�g���N�^(�I�[�o�[���[�h)
//===============================================
CPlayer::CPlayer(int nPriOrity)
{
	// �l���N���A����
	m_bJump = false;
	m_bSlow = false;
	m_Info.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fRotMove = 0.0f;
	m_fRotDiff = 0.0f;
	m_fRotDest = 0.0f;
	m_nSlowTime = 0;
	pShadow = NULL;
	m_pBody = NULL;
	m_pLeg = NULL;
	m_pWaist = NULL;
	m_bAttack = false;
	m_nAttackTimer = 0;
	m_nAttackHand = 0;

	for (int nCnt = 0; nCnt < WEAPON_MAX; nCnt++)
	{
		m_aWepNum[nCnt] = -1;
	}
}

//===============================================
// �f�X�g���N�^
//===============================================
CPlayer::~CPlayer()
{

}

//===============================================
// ����������
//===============================================
HRESULT CPlayer::Init(void)
{
	// ���̐���
	if (m_pWaist == NULL)
	{
		m_pWaist = new CWaist;
		m_pWaist->SetParent(&m_Info.mtxWorld);
	}

	return S_OK;
}

//===============================================
// ����������(�I�[�o�[���[�h)
//===============================================
HRESULT CPlayer::Init(const char *pBodyName, const char *pLegName)
{
	CTexture *pTexture = CManager::GetTexture();

	// ���̐���
	if (m_pWaist == NULL)
	{
		m_pWaist = new CWaist;
		m_pWaist->SetParent(&m_Info.mtxWorld);
	}

	// ���̂̐ݒ�
	if (pBodyName != NULL)
	{// �t�@�C���������݂��Ă���
		m_pBody = CCharacter::Create(pBodyName);
		m_pBody->SetParent(m_pWaist->GetMtxWorld());

		if (m_pBody->GetMotion() != NULL)
		{
			// �������[�V�����̐ݒ�
			m_pBody->GetMotion()->InitSet(BMOTION_NEUTRAL);
		}
	}

	// �����g�̐ݒ�
	if (pLegName != NULL)
	{// �t�@�C���������݂��Ă���
		m_pLeg = CCharacter::Create(pLegName);
		m_pLeg->SetParent(m_pWaist->GetMtxWorld());

		if (m_pLeg->GetMotion() != NULL)
		{
			// �������[�V�����̐ݒ�
			m_pLeg->GetMotion()->InitSet(LMOTION_NEUTRAL);
		}
	}

	// ���̍��������킹��
	if (m_pLeg != NULL)
	{// �r���g�p����Ă���ꍇ
		CModel *pModel = m_pLeg->GetParts(0);	// ���p�[�c���擾

		if (pModel != NULL)
		{// �p�[�c�����݂���ꍇ
			D3DXVECTOR3 pos = pModel->GetPosition();	// ���f���̑��Έʒu���擾

			// ������ݒ�
			m_pWaist->SetHeight(pos);

			// ���̃��f���̈ʒu��ύX
			pModel->SetPosition(pos);
		}
	}

	// �X���[�\���Ԃ������ݒ�
	m_nSlowTime = DEF_SLOWTIME;

	CModel *pModel = m_pBody->GetParts(9);	// ���p�[�c���擾

	// ����̐ݒ�
	m_pWeaponL = CModel::Create(m_apFileName[WEAPON_GUNL]);
	m_pWeaponL->SetPosition(SetWepPos[WEAPON_GUNL]);
	m_pWeaponL->SetParent(pModel->GetMtxWorld());

	pModel = m_pBody->GetParts(5);	// ���p�[�c���擾

	// ����̐ݒ�
	m_pWeaponR = CModel::Create(m_apFileName[WEAPON_GUNR]);
	m_pWeaponR->SetPosition(SetWepPos[WEAPON_GUNR]);
	m_pWeaponR->SetParent(pModel->GetMtxWorld());

	// ��ސݒ�
	m_WepType = ATK_GUN;

	// ����ԍ��擾
	for (int nCnt = 0; nCnt < WEAPON_MAX; nCnt++)
	{
		m_aWepNum[nCnt] = CManager::GetModelFile()->Regist(m_apFileName[nCnt]);
	}

	// ���b�N�I���̐���
	m_pLockon = CLockOn::Create(m_pBody->GetMtxWorld());
	m_pLockon->SetDistance(SHOT_LENGTH, SHOT_RANGE);
	m_pLockon->SetLock(true);

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CPlayer::Uninit(void)
{
	// ���̂̏I������
	if (m_pBody != NULL)
	{
		m_pBody->Uninit();
		delete m_pBody;
		m_pBody = NULL;
	}

	// �����g�̏I������
	if (m_pLeg != NULL)
	{
		m_pLeg->Uninit();
		delete m_pLeg;
		m_pLeg = NULL;
	}

	// ���̏I������
	if (m_pWaist != NULL)
	{
		delete m_pWaist;
		m_pWaist = NULL;
	}

	// ����̏I��
	if (m_pWeaponL != NULL)
	{
		m_pWeaponL->Uninit();
		delete m_pWeaponL;
		m_pWeaponL = NULL;
	}
	if (m_pWeaponR != NULL)
	{
		m_pWeaponR->Uninit();
		delete m_pWeaponR;
		m_pWeaponR = NULL;
	}

	// �p��
	Release();
}

//===============================================
// �X�V����
//===============================================
void CPlayer::Update(void)
{
	// �O��̍��W���擾
	m_Info.posOld = GetPosition();

	// ���̍X�V
	if (m_pBody != NULL)
	{// �g�p����Ă���ꍇ
		m_pBody->Update();
	}
	
	// �����g�X�V
	if (m_pLeg != NULL)
	{// �g�p����Ă���ꍇ
		m_pLeg->Update();

		CModel *pModel = m_pLeg->GetParts(0);

		// ���̍������U
		if (pModel != NULL)
		{
			m_pWaist->SetPosition(m_pWaist->GetSetPosition() + pModel->GetCurrentPosition());
		}
	}

	// �v���C���[����
	Controller();

	// �����ݒ�
	SetBodyRot();

	// �J�����Ǐ]
	CCamera *pCamera = CManager::GetCamera();

	// �Ǐ]����
	pCamera->Pursue(GetPosition(), GetRotation());
}

//===============================================
// �`�揈��
//===============================================
void CPlayer::Draw(void)
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

	// ���̐ݒ�
	if (m_pWaist != NULL)
	{
		m_pWaist->SetMatrix();
	}

	// �����g�̕`��
	if (m_pLeg != NULL)
	{
		CModel *pModel = m_pLeg->GetParts(0);

		D3DXVECTOR3 pos = pModel->GetCurrentPosition();

		pModel->SetCurrentPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		m_pLeg->Draw();

		pModel->SetCurrentPosition(pos);
	}

	// ���̂̕`��
	if (m_pBody != NULL)
	{
		m_pBody->Draw();
	}
	
	// ����̕`��
	if (m_pWeaponL != NULL)
	{
		m_pWeaponL->Draw();
	}

	// ����̕`��
	if (m_pWeaponR != NULL && m_WepType == ATK_GUN)
	{// �g�p���Ă��邩�񒚎���
		m_pWeaponR->Draw();
	}
}

//===============================================
// ����
//===============================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, const char *pBodyName, const char *pLegName, const int nPriority)
{
	CPlayer *pPlayer = NULL;
	CXFile *pModelFile = CManager::GetModelFile();

	// �I�u�W�F�N�g2D�̐���
	pPlayer = new CPlayer(nPriority);

	if (pPlayer != NULL)
	{// �����ł����ꍇ
		// ����������
		pPlayer->Init(pBodyName, pLegName);

		// ���W�ݒ�
		pPlayer->SetPosition(pos);

		// �����ݒ�
		pPlayer->SetRotation(rot);

		// �ړ��ʐݒ�
		pPlayer->SetMove(move);

		// ��ނ̐ݒ�
		pPlayer->SetType(TYPE_PLAYER);

		// �e�̐ݒ�
		pPlayer->pShadow = CShadow::Create(pos, 30.0f, 30.0f);
	}
	else
	{// �����Ɏ��s�����ꍇ
		return NULL;
	}

	return pPlayer;
}

//===============================================
// ���쏈��
//===============================================
void CPlayer::Controller(void)
{
	D3DXVECTOR3 pos = GetPosition();	// ���W���擾
	D3DXVECTOR3 rot = GetRotation();	// �������擾
	CInputKeyboard *pInputKey = CManager::GetInputKeyboard();	// �L�[�{�[�h�̃|�C���^
	CInputMouse *pInputMouse = CManager::GetInputMouse();
	CCamera *pCamera = CManager::GetCamera();		// �J�����̃|�C���^
	D3DXVECTOR3 CamRot = pCamera->GetRotation();	// �J�����̊p�x
	m_fRotMove = rot.y;	//���݂̌������擾
	m_bMove = false;	// �ړ���ԃ��Z�b�g

	// �ړ�
	if (m_bJump == false)
	{// �W�����v���Ă��Ȃ��ꍇ
		Move();
	}

	if (m_bJump == false && m_bMove == true)
	{// �W�����v���Ă��Ȃ���Ԃňړ�
		if (m_bAttack == false)
		{
			m_pBody->GetMotion()->BlendSet(BMOTION_WALK);
		}
		m_pLeg->GetMotion()->BlendSet(LMOTION_WALK);
	}
	else if (m_bJump == false && m_bMove == false)
	{
		if (m_bAttack == false)
		{
			m_pBody->GetMotion()->BlendSet(BMOTION_NEUTRAL);
		}
		m_pLeg->GetMotion()->BlendSet(LMOTION_NEUTRAL);
	}
	else if (m_bJump == true && m_bAttack == false)
	{
		m_pBody->GetMotion()->BlendSet(BMOTION_JUMP);
	}

	// ����؂�ւ�
	if (pInputKey->GetTrigger(DIK_Q) == true)
	{// Q�L�[
		m_WepType = (ATK)((m_WepType + 1) % ATK_MAX);

		switch (m_WepType)
		{
		case ATK_GUN:
			m_pWeaponL->BindModelFile(m_aWepNum[WEAPON_GUNL]);
			m_pWeaponL->SetPosition(SetWepPos[WEAPON_GUNL]);
			break;

		case ATK_SHOWER:
			m_pWeaponL->BindModelFile(m_aWepNum[WEAPON_SHOWER]);
			m_pWeaponL->SetPosition(SetWepPos[WEAPON_SHOWER]);
			break;
		}

		if (m_WepType == ATK_GUN)
		{
			m_pLockon->SetLock(true);
		}
		else
		{
			m_pLockon->SetLock(false);
		}
	}
	else if (pInputKey->GetTrigger(DIK_E) == true)
	{// E�L�[
		m_WepType = (ATK)((m_WepType + ATK_MAX - 1) % ATK_MAX);

		switch (m_WepType)
		{
		case ATK_GUN:
			m_pWeaponL->BindModelFile(m_aWepNum[WEAPON_GUNL]);
			m_pWeaponL->SetPosition(SetWepPos[WEAPON_GUNL]);
			break;

		case ATK_SHOWER:
			m_pWeaponL->BindModelFile(m_aWepNum[WEAPON_SHOWER]);
			m_pWeaponL->SetPosition(SetWepPos[WEAPON_SHOWER]);
			break;
		}

		if (m_WepType == ATK_GUN)
		{
			m_pLockon->SetLock(true);
		}
		else
		{
			m_pLockon->SetLock(false);
		}
	}

	// �W�����v
	Jump();

	//�U��
	Attack();

	// �X���[����
	Slow();

	float fGravity = PLAYER_GRAVITY * CManager::GetSlow()->Get();
	m_Info.move.y += fGravity;
	pos.y += m_Info.move.y * CManager::GetSlow()->Get();

	if (m_bJump == false)
	{
		m_Info.move.x += (0.0f - m_Info.move.x) * 0.12f;	//x���W
		m_Info.move.z += (0.0f - m_Info.move.z) * 0.12f;	//x���W
	}

	pos.x += m_Info.move.x * CManager::GetSlow()->Get();
	pos.z += m_Info.move.z * CManager::GetSlow()->Get();

	if (m_fRotDest > D3DX_PI || m_fRotDest < -D3DX_PI)
	{//-3.14�`3.14�͈̔͊O�̏ꍇ
		if (m_fRotDest > D3DX_PI)
		{
			m_fRotDest += (-D3DX_PI * 2);
		}
		else if (m_fRotDest < -D3DX_PI)
		{
			m_fRotDest += (D3DX_PI * 2);
		}
	}

	m_fRotDiff = m_fRotDest - m_fRotMove;	//�ڕW�܂ł̈ړ������̍���

	if (m_fRotDiff > D3DX_PI || m_fRotDiff < -D3DX_PI)
	{//-3.14�`3.14�͈̔͊O�̏ꍇ
		if (m_fRotDiff > D3DX_PI)
		{
			m_fRotDiff += (-D3DX_PI * 2);
		}
		else if (m_fRotDiff < -D3DX_PI)
		{
			m_fRotDiff += (D3DX_PI * 2);
		}
	}

	rot.y += m_fRotDiff * 0.08f;

	if (rot.y > D3DX_PI || rot.y < -D3DX_PI)
	{//-3.14�`3.14�͈̔͊O�̏ꍇ
		if (rot.y > D3DX_PI)
		{
			rot.y += (-D3DX_PI * 2);
		}
		else if (rot.y < -D3DX_PI)
		{
			rot.y += (D3DX_PI * 2);
		}
	}

	if (pos.y < 0.0f)
	{
		m_Info.move.y = 0.0f;
		pos.y = 0.0f;
		m_bJump = false;
	}

	D3DXVECTOR3 nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float fHeight = CManager::GetMeshField()->GetHeight(pos, nor);

	if (fHeight > pos.y)
	{// 
		pos.y = fHeight;
		m_bJump = false;
	}

	// �e�̍��W�X�V
	if (pShadow != NULL)
	{
		pShadow->SetPosition(D3DXVECTOR3(m_pBody->GetParts(0)->GetMtxWorld()->_41, 0.0f, m_pBody->GetParts(0)->GetMtxWorld()->_43));
	}


	// ���_���ݒ�
	SetRotation(rot);
	SetPosition(pos);

	pos = GetPosition();

	// �f�o�b�O�\��
	CManager::GetDebugProc()->Print("\n�ړ�[W,A,S,D] : �W�����v[SPACE] : ����[L, �}�E�X���N���b�N]\n : �X���[[ENTER������, �}�E�X�E�N���b�N������]\n");
	CManager::GetDebugProc()->Print("�v���C���[�̍��W[ %f, %f, %f ]\n", pos.x, pos.y, pos.z);
	CManager::GetDebugProc()->Print("�v���C���[�̌���[ %f, %f, %f ]\n", rot.x, rot.y, rot.z);
	CManager::GetDebugProc()->Print("�v���C���[�̈ړ���[ %f, %f, %f ]\n", m_Info.move.x, m_Info.move.y, m_Info.move.z);
	CManager::GetDebugProc()->Print("�X���[�\�^�C�}�[[ %d ]\n", m_nSlowTime);
	CManager::GetDebugProc()->Print("�d��[ %f ]\n", fGravity);
}

//===============================================
// �ړ�
//===============================================
void CPlayer::Move(void)
{
	CCamera *pCamera = CManager::GetCamera();		// �J�����̃|�C���^
	D3DXVECTOR3 CamRot = pCamera->GetRotation();	// �J�����̊p�x
	CInputKeyboard *pInputKey = CManager::GetInputKeyboard();	// �L�[�{�[�h�̃|�C���^
	float fSpeed = MOVE;	// �ړ���

	//�v���C���[�̍X�V
	if (pInputKey->GetPress(DIK_A) == true)
	{
		if (pInputKey->GetPress(DIK_W) == true)
		{
			m_Info.move.x += cosf(CamRot.y + (-D3DX_PI * 0.75f)) * fSpeed;
			m_Info.move.z += sinf(CamRot.y + (-D3DX_PI * 0.75f)) * fSpeed;
			m_fRotDest = (-CamRot.y + D3DX_PI * 0.25f);
		}
		else if (pInputKey->GetPress(DIK_S) == true)
		{
			m_Info.move.x += cosf(CamRot.y + (-D3DX_PI * 0.25f)) * fSpeed;
			m_Info.move.z += sinf(CamRot.y + (-D3DX_PI * 0.25f)) * fSpeed;
			m_fRotDest = (-CamRot.y + -D3DX_PI * 0.25f);
		}
		else
		{
			m_Info.move.x += cosf(CamRot.y + (-D3DX_PI * 0.5f)) * fSpeed;
			m_Info.move.z += sinf(CamRot.y + (-D3DX_PI * 0.5f)) * fSpeed;
			m_fRotDest = -CamRot.y;
		}

		// �ړ�������Ԃɂ���
		m_bMove = true;
	}
	else if (pInputKey->GetPress(DIK_D) == true)
	{
		if (pInputKey->GetPress(DIK_W) == true)
		{
			m_Info.move.x += cosf(CamRot.y + (D3DX_PI * 0.75f)) * fSpeed;
			m_Info.move.z += sinf(CamRot.y + (D3DX_PI * 0.75f)) * fSpeed;

			m_fRotDest = (-CamRot.y + D3DX_PI * 0.75f);
		}
		else if (pInputKey->GetPress(DIK_S) == true)
		{
			m_Info.move.x += cosf(CamRot.y + (D3DX_PI * 0.25f)) * fSpeed;
			m_Info.move.z += sinf(CamRot.y + (D3DX_PI * 0.25f)) * fSpeed;

			m_fRotDest = (-CamRot.y + -D3DX_PI * 0.75f);
		}
		else
		{
			m_Info.move.x += cosf(CamRot.y + (D3DX_PI * 0.5f)) * fSpeed;
			m_Info.move.z += sinf(CamRot.y + (D3DX_PI * 0.5f)) * fSpeed;
			m_fRotDest = (-CamRot.y + D3DX_PI * 1.0f);
		}

		// �ړ�������Ԃɂ���
		m_bMove = true;
	}
	else if (pInputKey->GetPress(DIK_W) == true)
	{
		m_Info.move.x += -cosf(CamRot.y) * fSpeed;
		m_Info.move.z += -sinf(CamRot.y) * fSpeed;
		m_fRotDest = (-CamRot.y + D3DX_PI * 0.5f);

		// �ړ�������Ԃɂ���
		m_bMove = true;

	}
	else if (pInputKey->GetPress(DIK_S) == true)
	{
		m_Info.move.x += cosf(CamRot.y) * fSpeed;
		m_Info.move.z += sinf(CamRot.y) * fSpeed;
		m_fRotDest = (-CamRot.y + -D3DX_PI * 0.5f);

		// �ړ�������Ԃɂ���
		m_bMove = true;
	}
}

//===============================================
// �X���[�֘A
//===============================================
void CPlayer::Slow(void)
{
	CInputKeyboard *pInputKey = CManager::GetInputKeyboard();	// �L�[�{�[�h�̃|�C���^
	CInputMouse *pInputMouse = CManager::GetInputMouse();

	// �X���[�^�C�}�[
	if (m_bSlow == false)
	{// ���͉\
		if (pInputKey->GetPress(DIK_RETURN) == true || pInputMouse->GetPress(CInputMouse::BUTTON_RBUTTON) == true)
		{// ENTER�L�[�����͂��ꂽ�ꍇ
			if (m_nSlowTime > 0)
			{// �c���Ă���ꍇ
				m_nSlowTime--;
				CManager::GetSlow()->SetSlow(true);
			}
			else
			{
				m_bSlow = true;	// �X���[�ɂł��Ȃ���Ԃɂ���
				CManager::GetSlow()->SetSlow(false);
			}
		}
		else
		{
			// �\���ԉ�
			if (m_nSlowTime < SLOW_OK)
			{// �X���[�\�̎��Ԃ��Z��
				m_bSlow = true;
			}
			else if (m_nSlowTime < DEF_SLOWTIME)
			{// ����܂�
				m_nSlowTime++;
			}

			CManager::GetSlow()->SetSlow(false);
		}
	}
	else
	{// �ł��Ȃ�
		if (m_nSlowTime < SLOW_OK)
		{
			m_nSlowTime++;
		}
		else
		{
			m_bSlow = false;	// �X���[�\��Ԃɂ���
		}
	}
}

//===============================================
// ���̂̌����ύX
//===============================================
void CPlayer::SetBodyRot(void)
{
	CCamera *pCamera = CManager::GetCamera();		// �J�����̃|�C���^
	D3DXVECTOR3 CamRot = pCamera->GetRotation();	// �J�����̊p�x

	if (m_pBody == NULL || m_pLeg == NULL)
	{// ��i�K�̊K�w�\���ł͂Ȃ��ꍇ
		return;
	}

	D3DXVECTOR3 rot = m_pBody->GetRotation();	// ���̂̌������擾

	rot.y = (-CamRot.y + D3DX_PI * 0.5f) - m_Info.rot.y;	// �J�����̌����Ă�������ɍ��킹��

	if (rot.z < -D3DX_PI)
	{// z���W�p�x���E
		rot.z += D3DX_PI * 2;
	}
	else if (rot.z > D3DX_PI)
	{// z���W�p�x���E
		rot.z += -D3DX_PI * 2;
	}

	if (rot.x < -D3DX_PI)
	{// x���W�p�x���E
		rot.x += D3DX_PI * 2;
	}
	else if (rot.x > D3DX_PI)
	{// x���W�p�x���E
		rot.x += -D3DX_PI * 2;
	}

	if (rot.y < -D3DX_PI)
	{// x���W�p�x���E
		rot.y += D3DX_PI * 2;
	}
	else if (rot.y > D3DX_PI)
	{// x���W�p�x���E
		rot.y += -D3DX_PI * 2;
	}

	rot.y *= 0.6f;

	// ���̂̌�����ݒ�
	m_pBody->SetRotation(rot);
}

//===============================================
// �U��
//===============================================
void CPlayer::Attack(void)
{
	CInputKeyboard *pInputKey = CManager::GetInputKeyboard();	// �L�[�{�[�h�̃|�C���^
	CInputMouse *pInputMouse = CManager::GetInputMouse();
	CCamera *pCamera = CManager::GetCamera();		// �J�����̃|�C���^
	D3DXVECTOR3 CamRot = pCamera->GetRotation();	// �J�����̊p�x
	D3DXVECTOR3 BulletMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CBullet *pBullet = NULL;

	if (pInputKey->GetPress(DIK_L) == true || pInputMouse->GetPress(CInputMouse::BUTTON_LBUTTON) == true)
	{//ENTER�L�[�������ꂽ�Ƃ�
		if (m_nAttackTimer == 0)
		{
			D3DXMATRIX mtx;
			switch (m_WepType)
			{
			case ATK_GUN:

				m_pBody->GetMotion()->Set(BMOTION_TWINATK);

				if (m_nAttackHand == 0)
				{
					mtx = *m_pWeaponL->GetMtxWorld();
				}
				else
				{
					mtx = *m_pWeaponR->GetMtxWorld();
				}

				if (m_pLockon->GetLock() == false)
				{// ���b�N�I�����Ă��Ȃ�
					BulletMove = { -cosf(CamRot.y) * 50.0f, 0.0f, -sinf(CamRot.y) * 50.0f };
				}
				else
				{// ���b�N�I�����Ă���
					D3DXVECTOR3 vec;
					vec.x = m_pLockon->GetPosition().x - mtx._41;
					vec.y = m_pLockon->GetPosition().y - mtx._42;
					vec.z = m_pLockon->GetPosition().z - mtx._43;

					D3DXVec3Normalize(&vec, &vec);	// �x�N�g���𐳋K������

					BulletMove = vec * 20.0f;
				}


				// �e�̔���
				pBullet = CBullet::Create(D3DXVECTOR3(mtx._41, mtx._42, mtx._43),
					D3DXVECTOR3(BulletMove.x, BulletMove.y, BulletMove.z), CBullet::TYPE_NONE);

				if (m_pLockon->GetLock() == true)
				{// ���b�N�I�����Ă���
					//pBullet->SetHom(&*m_pLockon->GetTag(), 50.0f);
				}

				m_nAttackHand ^= 1;
				break;
			case ATK_SHOWER:
				m_pBody->GetMotion()->Set(BMOTION_SHWATK);
				mtx = *m_pWeaponL->GetMtxWorld();

				BulletMove = { -cosf(CamRot.y) * 2.0f, 1.0f, -sinf(CamRot.y) * 2.0f };

				// �e�̔���
				pBullet = CBullet::Create(D3DXVECTOR3(mtx._41, mtx._42, mtx._43),
					D3DXVECTOR3(BulletMove.x, BulletMove.y, BulletMove.z), CBullet::TYPE_GRAVITY);

				if (pBullet != NULL)
				{
					pBullet->SetSize(80.0f, 30.0f);
					pBullet->SetLife(300.0f);
				}

				CParticle::Create(D3DXVECTOR3(mtx._41, mtx._42, mtx._43), CamRot, CEffect::TYPE_SHWBULLET);

				break;
			}

			m_bAttack = true;
			m_nAttackTimer++;
		}
		else
		{
			m_nAttackTimer++;
			if (m_nAttackTimer > m_aWepTimer[m_WepType] * (1.0f + (1.0f - CManager::GetSlow()->Get())))
			{
				m_nAttackTimer = 0;
			}
		}
	}
	else
	{
		if (m_bAttack == true)
		{
			m_nAttackTimer++;
			if (m_nAttackTimer > m_aWepTimer[m_WepType] * (1.0f + (1.0f - CManager::GetSlow()->Get())))
			{
				m_nAttackTimer = 0;
				m_bAttack = false;
				m_nAttackHand = 0;
			}
		}
	}
}

//===============================================
// �W�����v
//===============================================
void CPlayer::Jump(void)
{
	CInputKeyboard *pInputKey = CManager::GetInputKeyboard();	// �L�[�{�[�h�̃|�C���^

	// �W�����v
	if (pInputKey->GetPress(DIK_SPACE) == true)
	{// SPACE�L�[
		if (m_bJump == false)
		{// �W�����v���Ă��Ȃ��ꍇ
			m_bJump = true;
			m_Info.move.y = PLAYER_JUMP;
			if (m_bAttack == false)
			{
				m_pBody->GetMotion()->BlendSet(BMOTION_JUMP);
			}
			m_pLeg->GetMotion()->BlendSet(LMOTION_JUMP);
			m_Info.move.x += (0.0f - m_Info.move.x) * 0.25f;	//x���W
			m_Info.move.z += (0.0f - m_Info.move.z) * 0.25f;	//x���W
		}
	}
}
