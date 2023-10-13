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
#include "meshorbit.h"
#include "game.h"
#include "filter.h"
#include "object2D.h"
#include "meshballoon.h"
#include "meshwall.h"
#include "objectX.h"
#include "car_manager.h"
#include "car.h"
#include "sound.h"

//===============================================
// �}�N����`
//===============================================
#define MOVE	(2.2f)		// �ړ���
#define SHW_MOVE	(1.0f)	// �V�����[���ړ���
#define PLAYER_GRAVITY	(-0.15f)		//�v���C���[�d��
#define PLAYER_JUMP		(10.0f)		//�v���C���[�W�����v��
#define DEF_SLOWTIME	(60 * 5)	// �X���[�\����
#define SLOW_OK			(60 * 2)	// �X���[�\�ɂȂ鎞��
#define SHOT_LENGTH	(4000.0f)		// �˒��͈�
#define SHOT_RANGE	(D3DX_PI * 0.9f)	// �˒��p�x
#define SHOT_INTERVAL	(10)		// �U���C���^�[�o��
#define GUN_BULMOVE	(50.0f)
#define DEF_SLOWGAGELENGSH	(SCREEN_WIDTH * 0.4f)	// �X���[�Q�[�W�}�b�N�X�T�C�Y
#define SLOWGAGE_HEIGHT	(SCREEN_HEIGHT * 0.01f)
#define GAGE_TEXNAME	"data\\TEXTURE\\gage000.jpg"	// �Q�[�W�t�@�C����
#define MANUAL_TEXNAME	"data\\TEXTURE\\slow_button.png"
#define NOCHARGE_CNT	(20)		// �`���[�W�܂ł̃J�E���g��
#define BALLOON_MOVE	(25.0f)		// ���D�ړ���
#define BALLOON_WEIGHT	(150.0f)	// �ő�d��
#define WIDTH	(20.0f)		// ��
#define HEIGHT	(80.0f)		// ����

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
	21,
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
// ���D�����ݒ�
//===============================================
const CMeshBalloon::SET CPlayer::m_SetBalloon =
{
	D3DXVECTOR3(0.0f, 20.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f, 10.0f, 5, 10, 10,
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
	m_pSlowGage = NULL;
	m_pBalloon = NULL;
	m_pMapIcon = NULL;
	m_fMove = 0.0f;
}

//===============================================
// �R���X�g���N�^(�I�[�o�[���[�h)
//===============================================
CPlayer::CPlayer(int nPriOrity)
{
	// �l���N���A����
	m_bJump = false;
	m_bActiveSlow = false;
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
	m_pWeaponL = NULL;
	m_pWeaponR = NULL;
	m_pSlowGage = NULL;
	m_pBalloon = NULL;
	m_pMapIcon = NULL;
	m_bAttack = false;
	m_fAttackTimer = 0;
	m_nAttackHand = 0;
	m_fChargeCnt = 0;
	m_pCar = NULL;
	m_pSlowManual = NULL;
	m_fMove = 0.0f;

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
	m_fMove = 1.0f;

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
	m_nSlowTime = 0;

	CModel *pModel = m_pBody->GetParts(9);	// ����p�[�c���擾

	// ����̐ݒ�
	m_pWeaponL = CModel::Create(m_apFileName[WEAPON_GUNL]);
	m_pWeaponL->SetPosition(SetWepPos[WEAPON_GUNL]);
	m_pWeaponL->SetParent(pModel->GetMtxWorld());

	pModel = m_pBody->GetParts(5);	// �E��p�[�c���擾

	// ����̐ݒ�
	m_pWeaponR = CModel::Create(m_apFileName[WEAPON_GUNR]);
	m_pWeaponR->SetPosition(SetWepPos[WEAPON_GUNR]);
	m_pWeaponR->SetParent(pModel->GetMtxWorld());

	// �Q�[�W�̐ݒ�
	m_pSlowGage = CObject2D::Create(7);
	m_pSlowManual = CObject2D::Create(7);

	if (m_pSlowGage != NULL)
	{
		m_pSlowGage->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.95f, 0.0f));
		m_pSlowGage->SetSize(0, SLOWGAGE_HEIGHT);
		m_pSlowGage->BindTexture(CManager::GetTexture()->Regist(GAGE_TEXNAME));
	}

	if (m_pSlowManual != NULL)
	{
		m_pSlowManual->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.85f, 0.0f));
		m_pSlowManual->SetSize(SCREEN_WIDTH * 0.12f, SCREEN_HEIGHT * 0.09f);
		m_pSlowManual->BindTexture(CManager::GetTexture()->Regist(MANUAL_TEXNAME));
	}

	// ��ސݒ�
	m_WepType = ATK_GUN;
	m_WepTypeOld = m_WepType;

	// ����ԍ��擾
	for (int nCnt = 0; nCnt < WEAPON_MAX; nCnt++)
	{
		m_aWepNum[nCnt] = CManager::GetModelFile()->Regist(m_apFileName[nCnt]);
	}

	// ���b�N�I���̐���
	m_pLockon = CLockOn::Create(m_pBody->GetMtxWorld());
	m_pLockon->SetLock(true);

	// �O�Ղ̐���
	m_pOrbit = CMeshOrbit::Create(&m_Info.mtxWorld, D3DXVECTOR3(0.0f, 20.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// �}�b�v�A�C�R���̐���
	if (m_pMapIcon == NULL)
	{
		m_pMapIcon = CObject3D::Create(GetPosition(), GetRotation());
		m_pMapIcon->SetType(CObject::TYPE_MAP);
		m_pMapIcon->BindTexture(CManager::GetTexture()->Regist("data\\TEXTURE\\mapicon000.png"));
		m_pMapIcon->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

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

	if (m_pSlowGage != NULL)
	{
		m_pSlowGage = NULL;
	}

	// �p��
	Release();
}

//===============================================
// �X�V����
//===============================================
void CPlayer::Update(void)
{
	if (CManager::GetSlow()->Get() > 1.0f)
	{
		return;
	}

	// �O��̍��W���擾
	m_Info.posOld = GetPosition();
	int nSlowTimerOld = m_nSlowTime;	// �ύX�O�̃X���[�\����

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

	CManager::GetDebugProc()->Print("���� [%f, %f, %f]", GetRotation().x, GetRotation().y, GetRotation().z);

	// �p�[�e�B�N��
	Particle();

	if (m_bLock == false)
	{// ���b�N�I�����Ȃ�
		pCamera->SetRot(GetRotation());
	}

	if (m_pSlowGage == NULL || m_nSlowTime == nSlowTimerOld)
	{// �g�p���Ă��Ȃ��A�܂��̓X���[���ԂɕύX���Ȃ�
		return;
	}

	// �X���[�ő厞�Ԃ���̊��������߂�
	float fRate = (float)m_nSlowTime / (float)DEF_SLOWTIME;

	m_pSlowGage->SetSize(DEF_SLOWGAGELENGSH * fRate, SLOWGAGE_HEIGHT);
	m_pSlowGage->SetTex(-5.0f * fRate, 0.0f, 5.0f * fRate);
	SetGageColor(fRate);
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

		pPlayer->m_fRotDest = rot.y;

		// �ړ��ʐݒ�
		pPlayer->SetMove(move);

		// ��ނ̐ݒ�
		pPlayer->SetType(TYPE_PLAYER);

		// �e�̐ݒ�
		pPlayer->pShadow = CShadow::Create(pos, 30.0f, 30.0f);

		CManager::GetCamera()->Setting(pos, rot);
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
	CInputPad *pInputPad = CManager::GetInputPad();
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
	if ((pInputKey->GetTrigger(DIK_Q) == true || pInputPad->GetTrigger(CInputPad::BUTTON_Y, 0)) && CManager::GetSlow()->Get() == 1.0f)
	{// Q�L�[
		m_WepTypeOld = m_WepType;
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

		CLockOn::MultiDeath();

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

	//��O����
	if (pos.x > 3800.0f)
	{
		pos.x = 3800.0f;
		m_Info.move.x = 0.0f;
	}
	else if (pos.x < -4300.0f)
	{
		pos.x = -4300.0f;
		m_Info.move.x = 0.0f;
	}

	if (pos.z > 3800.0f)
	{
		pos.z = 3800.0f;
		m_Info.move.z = 0.0f;
	}
	else if (pos.z < -3800.0f)
	{
		pos.z = -3800.0f;
		m_Info.move.z = 0.0f;
	}

	// �Œ჉�C������
	bool m_bOld = m_bJump;
	m_bJump = true;
	bool bOldJump;

	// �I�u�W�F�N�g�Ƃ̓����蔻��
	D3DXVECTOR3 vtxMax = D3DXVECTOR3(WIDTH, HEIGHT, WIDTH);
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-WIDTH, 0.0f, -WIDTH);
	m_bJump = CObjectX::Collision(pos, m_Info.posOld, m_Info.move, vtxMin, vtxMax);
	bOldJump = m_bJump;

	// �ԂƂ̓����蔻��
	m_pCar = CManager::GetScene()->GetCarManager()->Collision(pos, m_Info.posOld, m_Info.move, vtxMin, vtxMax, &m_bJump);

	if (bOldJump == false && m_bJump == true)
	{
		m_bJump = bOldJump;
	}

	// �ǂƂ̓����蔻��
	CMeshWall::Collision(pos, m_Info.posOld);

	// �N���Ƃ̓����蔻��
	D3DXVECTOR3 nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float fHeight = CMeshField::GetHeight(pos);

	if (pos.y < -30.0f)
	{
		m_Info.move.y = 0.0f;
		pos.y = -30.0f;
		m_bJump = false;
	}

	if (fHeight > pos.y)
	{// 
		pos.y = fHeight;
		//m_Info.move.y = 0.0f;
		m_bJump = false;
	}

	if (m_bJump == true)
	{
		if (m_bAttack == false)
		{
			m_pBody->GetMotion()->BlendSet(BMOTION_JUMP);
		}
		m_pLeg->GetMotion()->BlendSet(LMOTION_JUMP);
	}


	if (m_bOld == true && m_bJump == false)
	{
		CManager::GetSound()->Play(CSound::LABEL_SE_LAND);
	}

	// �e�̍��W�X�V
	if (pShadow != NULL)
	{
		pShadow->SetPosition(D3DXVECTOR3(m_pBody->GetParts(0)->GetMtxWorld()->_41, fHeight + 0.01f, m_pBody->GetParts(0)->GetMtxWorld()->_43));
	}

	// ���_���ݒ�
	SetRotation(rot);
	SetPosition(pos);

	// �}�b�v�A�C�R���̈ړ�
	if (m_pMapIcon != NULL)
	{
		m_pMapIcon->SetPosition(GetPosition());
		m_pMapIcon->SetRotation(GetRotation());
	}

	pos = GetPosition();

	//�f�o�b�O�\��
	CManager::GetDebugProc()->Print("\n�ړ�[W,A,S,D] : �W�����v[SPACE] : ����[L, �}�E�X���N���b�N(��������)]\n"
		"�X���[[�Q�[�W�𒙂߂�ENTER, �}�E�X�E�N���b�N] : ����؂�ւ�[Q]\n");
	CManager::GetDebugProc()->Print("�v���C���[�̍��W[ %f, %f, %f ]\n", pos.x, pos.y, pos.z);
	CManager::GetDebugProc()->Print("�v���C���[�̌���[ %f, %f, %f ]\n", rot.x, rot.y, rot.z);
	CManager::GetDebugProc()->Print("�v���C���[�̈ړ���[ %f, %f, %f ]\n", m_Info.move.x, m_Info.move.y, m_Info.move.z);
	CManager::GetDebugProc()->Print("�X���[�\�^�C�}�[[ %d ]\n", m_nSlowTime);
}

//===============================================
// �ړ�
//===============================================
void CPlayer::Move(void)
{
	CCamera *pCamera = CManager::GetCamera();		// �J�����̃|�C���^
	D3DXVECTOR3 CamRot = pCamera->GetRotation();	// �J�����̊p�x
	CInputKeyboard *pInputKey = CManager::GetInputKeyboard();	// �L�[�{�[�h�̃|�C���^
	CInputPad *pInputPad = CManager::GetInputPad();
	float fSpeed = MOVE;	// �ړ���

	if (m_bAttack == true && m_WepType == ATK_SHOWER)
	{
		fSpeed = SHW_MOVE;
	}

	//�v���C���[�̍X�V
	if (pInputKey->GetPress(DIK_A) == true || pInputPad->GetStickPress(0, CInputPad::BUTTON_LEFT_X, 0.5f, CInputPad::STICK_MINUS) == true)
	{
		if (pInputKey->GetPress(DIK_W) == true || pInputPad->GetStickPress(0, CInputPad::BUTTON_LEFT_Y, 0.5f, CInputPad::STICK_PLUS))
		{
			m_Info.move.x += cosf(CamRot.y + (-D3DX_PI * 0.75f)) * fSpeed;
			m_Info.move.z += sinf(CamRot.y + (-D3DX_PI * 0.75f)) * fSpeed;
			m_fRotDest = (-CamRot.y + D3DX_PI * 0.25f);
		}
		else if (pInputKey->GetPress(DIK_S) == true || pInputPad->GetStickPress(0, CInputPad::BUTTON_LEFT_Y, 0.5f, CInputPad::STICK_MINUS))
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
	else if (pInputKey->GetPress(DIK_D) == true || pInputPad->GetStickPress(0, CInputPad::BUTTON_LEFT_X, 0.5f, CInputPad::STICK_PLUS) == true)
	{
		if (pInputKey->GetPress(DIK_W) == true || pInputPad->GetStickPress(0, CInputPad::BUTTON_LEFT_Y, 0.5f, CInputPad::STICK_PLUS))
		{
			m_Info.move.x += cosf(CamRot.y + (D3DX_PI * 0.75f)) * fSpeed;
			m_Info.move.z += sinf(CamRot.y + (D3DX_PI * 0.75f)) * fSpeed;

			m_fRotDest = (-CamRot.y + D3DX_PI * 0.75f);
		}
		else if (pInputKey->GetPress(DIK_S) == true || pInputPad->GetStickPress(0, CInputPad::BUTTON_LEFT_Y, 0.5f, CInputPad::STICK_MINUS))
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
	else if (pInputKey->GetPress(DIK_W) == true || pInputPad->GetStickPress(0, CInputPad::BUTTON_LEFT_Y, 0.5f, CInputPad::STICK_PLUS))
	{
		m_Info.move.x += -cosf(CamRot.y) * fSpeed;
		m_Info.move.z += -sinf(CamRot.y) * fSpeed;
		m_fRotDest = (-CamRot.y + D3DX_PI * 0.5f);

		// �ړ�������Ԃɂ���
		m_bMove = true;

	}
	else if (pInputKey->GetPress(DIK_S) == true || pInputPad->GetStickPress(0, CInputPad::BUTTON_LEFT_Y, 0.5f, CInputPad::STICK_MINUS))
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
	CInputPad *pInputPad = CManager::GetInputPad();

	// �X���[�^�C�}�[
	if (m_bActiveSlow == false && m_bJump == true && m_nSlowTime == DEF_SLOWTIME)
	{// ���͉\
		if (pInputKey->GetTrigger(DIK_RETURN) == true || pInputMouse->GetTrigger(CInputMouse::BUTTON_RBUTTON) == true || pInputPad->GetTrigger(CInputPad::BUTTON_LEFTBUTTON, 0))
		{// �X���[�Ή��{�^���g���K�[����
			m_bSlow = m_bSlow ? false : true;

			if (m_bSlow == true)
			{
				CManager::GetSound()->Play(CSound::LABEL_SE_ZONE);
				CManager::GetCamera()->SetOldRot(CManager::GetCamera()->GetRotation());
				m_bAttack = false;

				if (m_WepType == ATK_GUN)
				{
					CFilter::Create(CFilter::TYPE_SLOWGUN);
					CManager::GetCamera()->SetMode(CCamera::MODE_SLOWGUN);
				}
				else
				{
					CManager::GetCamera()->SetMode(CCamera::MODE_SLOWSHW);
				}
			}
			else
			{
				CManager::GetCamera()->SetMode(CCamera::MODE_NORMAL);
			}
		}
	}

	if (m_bSlow == true)
	{// ENTER�L�[�����͂��ꂽ�ꍇ
		if (m_nSlowTime > 0)
		{// �c���Ă���ꍇ
			m_nSlowTime--;
			CManager::GetSlow()->SetSlow(true);

			if (m_WepType == ATK_SHOWER)
			{
				SlowShw();
			}
			else if (m_WepType == ATK_GUN)
			{
				SlowGun();
			}
		}
		else
		{
			CManager::GetCamera()->SetMode(CCamera::MODE_NORMAL);
			m_bSlow = false;
			m_bActiveSlow = true;	// �X���[�ɂł��Ȃ���Ԃɂ���
			CManager::GetSlow()->SetSlow(false);
		}
	}
	else
	{
		if (m_pBalloon != NULL)
		{
			D3DXVECTOR3 pos = D3DXVECTOR3(m_pBalloon->GetMtx()->_41, m_pBalloon->GetMtx()->_42, m_pBalloon->GetMtx()->_43);
			m_pBalloon->SetPosition(pos);
			m_pBalloon->SetParent(NULL);
			m_pBalloon = NULL;
		}

		CManager::GetCamera()->SetMode(CCamera::MODE_NORMAL);

		// �\���ԉ�
		if (m_nSlowTime == DEF_SLOWTIME)
		{// ���^���܂ł��܂���
			CParticle::Create(D3DXVECTOR3(m_pBody->GetParts(0)->GetMtxWorld()->_41, m_pBody->GetParts(0)->GetMtxWorld()->_42, m_pBody->GetParts(0)->GetMtxWorld()->_43),
				CEffect::TYPE_SLOWOK);
			m_pSlowManual->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_pSlowManual->SetSize(m_pSlowManual->GetWidth() + m_fMove, m_pSlowManual->GetHeight() + m_fMove * 0.5f);

			if (m_pSlowManual->GetWidth() < SCREEN_WIDTH * 0.1f || m_pSlowManual->GetWidth() > SCREEN_WIDTH * 0.12f)
			{
				m_fMove *= -1.0f;
			}

			m_bActiveSlow = false;
		}
		else
		{
			m_pSlowManual->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		}

		CManager::GetSlow()->SetSlow(false);
	}
}

//===============================================
// ���̂̌����ύX
//===============================================
void CPlayer::SetBodyRot(void)
{
	CCamera *pCamera = CManager::GetCamera();		// �J�����̃|�C���^
	D3DXVECTOR3 CamRot = pCamera->GetRotation();	// �J�����̊p�x
	CInputPad *pInputPad = CManager::GetInputPad();
	CInputKeyboard *pInputKey = CManager::GetInputKeyboard();

	if (m_pBody == NULL || m_pLeg == NULL)
	{// ��i�K�̊K�w�\���ł͂Ȃ��ꍇ
		return;
	}

	D3DXVECTOR3 rot = m_pBody->GetRotation();	// ���̂̌������擾

	if (pInputPad->GetRightTriggerPress(0) >= 10 || pInputKey->GetPress(DIK_E))
	{// �g���K�[����
		m_bLock = false;
	}
	else
	{
		m_bLock = true;
	}

	if (m_bLock == true)
	{
		float fRotDiff = (-CamRot.y + D3DX_PI * 0.5f) - m_Info.rot.y;	// �J�����̌����Ă�������ɍ��킹��

		if (fRotDiff < -D3DX_PI)
		{// z���W�p�x���E
			fRotDiff += D3DX_PI * 2;
		}
		else if (fRotDiff > D3DX_PI)
		{// z���W�p�x���E
			fRotDiff += -D3DX_PI * 2;
		}

		fRotDiff *= 0.6f;

		float fRotDest = fRotDiff - rot.y;

		rot.y += fRotDest * 0.1f * CManager::GetSlow()->Get();
	}
	else
	{
		rot.y = 0.0f;
	}

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
	CInputPad *pInputPad = CManager::GetInputPad();

	CManager::GetDebugProc()->Print("�U���^�C�}�[[%f]\n", m_fAttackTimer);
	CManager::GetDebugProc()->Print("�L�[[%d / %d]\n", m_pBody->GetMotion()->GetNowKey(), m_pBody->GetMotion()->GetNowNumKey());

	if (CManager::GetSlow()->Get() != 1.0f)
	{
		return;
	}

	if (pInputKey->GetPress(DIK_L) == true || pInputMouse->GetPress(CInputMouse::BUTTON_LBUTTON) == true || pInputPad->GetPress(CInputPad::BUTTON_RIGHTBUTTON, 0))
	{//ENTER�L�[�������ꂽ�Ƃ�

		if (m_bAttack == false)
		{// �U�����Ă��Ȃ�
			switch (m_WepType)
			{
			case ATK_GUN:

				if (CManager::GetSlow()->Get() == 1.0f)
				{
					m_pBody->GetMotion()->Set(BMOTION_TWINATK);
				}

				break;

			case ATK_SHOWER:
				m_pBody->GetMotion()->Set(BMOTION_SHWATK);
				break;
			}
		}
		else
		{// �U�����Ă���
			if (m_WepTypeOld != m_WepType)
			{// �U�����ɕ���������ւ��Ă���
				m_fAttackTimer += CManager::GetSlow()->Get();	// �U���C���^�[�o��

				if (m_fAttackTimer < SHOT_INTERVAL)
				{// �C���^�[�o���K��l�ł͂Ȃ�
					return;
				}

				m_fAttackTimer = 0;
				m_nAttackHand = 0;
			}

			switch (m_WepType)
			{
			case ATK_GUN:

				if (CManager::GetSlow()->Get() == 1.0f)
				{
					m_pBody->GetMotion()->BlendSet(BMOTION_TWINATK);
				}

				break;

			case ATK_SHOWER:
				m_pBody->GetMotion()->BlendSet(BMOTION_SHWATK);
				break;
			}

			m_WepTypeOld = m_WepType;
		}

		if (m_pBody->GetMotion()->GetNowFrame() != 0)
		{// ���̃L�[�̊J�n�t���[���ȊO�̏ꍇ
			return;
		}

		if (m_pBody->GetMotion()->GetNowKey() % (int)(m_pBody->GetMotion()->GetNowNumKey() * 0.5f) != 0 && m_pBody->GetMotion()->GetNowMotion() != BMOTION_SLOWATK)
		{// �U���^�C�~���O�ł͂Ȃ�
			return;
		}
		else if (m_pBody->GetMotion()->GetNowKey() != 1 && m_pBody->GetMotion()->GetNowMotion() == BMOTION_SLOWATK)
		{
			m_bAttack = true;
			return;
		}

		D3DXMATRIX mtx;
		switch (m_WepType)
		{
		case ATK_GUN:

			//m_pBody->GetMotion()->Set(BMOTION_TWINATK);

			if (CManager::GetSlow()->Get() == 1.0f)
			{
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
					BulletMove = { -cosf(CamRot.y) * GUN_BULMOVE, 0.0f, -sinf(CamRot.y) * GUN_BULMOVE };
				}
				else
				{// ���b�N�I�����Ă���
					D3DXVECTOR3 vec;
					vec.x = m_pLockon->GetPosition().x - mtx._41;
					vec.y = m_pLockon->GetPosition().y - mtx._42;
					vec.z = m_pLockon->GetPosition().z - mtx._43;

					D3DXVec3Normalize(&vec, &vec);	// �x�N�g���𐳋K������

					BulletMove = vec * GUN_BULMOVE;
				}


				// �e�̔���
				pBullet = CBullet::Create(D3DXVECTOR3(mtx._41, mtx._42, mtx._43),
					D3DXVECTOR3(BulletMove.x, BulletMove.y, BulletMove.z), CBullet::TYPE_NONE);
				CManager::GetSound()->Play(CSound::LABEL_SE_WATERGUN);

				if (m_pLockon->GetLock() == true)
				{// ���b�N�I�����Ă���
					pBullet->SetHom(&*m_pLockon->GetTag(), GUN_BULMOVE);
				}
			}
			else
			{
				CLockOn *pLock = CLockOn::GetTop();

				while (pLock != NULL)
				{// �g�p����Ă���ԌJ��Ԃ�
					CLockOn *pBulNext = pLock->GetNext();	// ����ێ�

					if (pLock->GetDeath() == false && pLock->GetType() == CLockOn::TYPE_MULTI)
					{
						if (pLock->GetTag() != NULL)
						{// �����W�I�̏ꍇ

							if (m_nAttackHand == 0)
							{
								mtx = *m_pWeaponL->GetMtxWorld();
							}
							else
							{
								mtx = *m_pWeaponR->GetMtxWorld();
							}

							D3DXVECTOR3 vec;
							vec.x = pLock->GetPosition().x - mtx._41;
							vec.y = pLock->GetPosition().y - mtx._42;
							vec.z = pLock->GetPosition().z - mtx._43;


							D3DXVec3Normalize(&vec, &vec);	// �x�N�g���𐳋K������

							BulletMove = vec * 50.0f;

							// �e�̔���
							pBullet = CBullet::Create(D3DXVECTOR3(mtx._41, mtx._42, mtx._43),
								D3DXVECTOR3(BulletMove.x, BulletMove.y, BulletMove.z), CBullet::TYPE_NONE);

							pBullet->SetHom(&*pLock->GetTag(), 50.0f);
						}
					}

					m_nAttackHand ^= 1;

					pLock = pBulNext;	// ���Ɉړ�
				}
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

			D3DXVec3Normalize(&BulletMove, &BulletMove);

			if (pBullet != NULL)
			{
				pBullet->SetSize(80.0f, 30.0f);
				pBullet->SetLife(300.0f);
			}

			for (int nCnt = 0; nCnt < 10; nCnt++)
			{
				// ���W�̐ݒ�
				D3DXVECTOR3 pos = D3DXVECTOR3(mtx._41 + m_Info.move.x, mtx._42, mtx._43 + m_Info.move.z);
				D3DXVECTOR3 move;

				//�ړ��ʂ̐ݒ�
				move.x = -cosf(CamRot.y + -D3DX_PI * 0.09f + D3DX_PI * 0.18f * ((rand() % 10) * 0.1f)) * 5.0f;
				move.y = rand() % 30 * 0.1f;
				move.z = -sinf(CamRot.y + -D3DX_PI * 0.09f + D3DX_PI * 0.18f * ((rand() % 10) * 0.1f)) * 5.0f;

				pBullet = CBullet::Create(pos,
					move, CBullet::TYPE_SHOWER);
				pBullet->SetInerMove(D3DXVECTOR3(m_Info.move.x, 0.0f, m_Info.move.z));
				pBullet->SetLife(300.0f);
			}

			CParticle::Create(D3DXVECTOR3(mtx._41, mtx._42, mtx._43), CamRot, CEffect::TYPE_SHWBULLET);
			CManager::GetSound()->Play(CSound::LABEL_SE_SHW);

			break;
		}

		m_bAttack = true;
	}
	else
	{// ���͂��Ă��Ȃ�
		if (m_bAttack == true)
		{
			if (m_pBody->GetMotion()->GetNowFrame() != 0)
			{// ���̃L�[�̊J�n�t���[���ȊO�̏ꍇ
				return;
			}

			if (m_pBody->GetMotion()->GetNowKey() % (int)(m_pBody->GetMotion()->GetNowNumKey() * 0.5f) != 0)
			{// �U���^�C�~���O�ł͂Ȃ�
				return;
			}

			m_bAttack = false;
			m_nAttackHand = 0;
			m_fAttackTimer = 0;
		}
	}
}

//===============================================
// �W�����v
//===============================================
void CPlayer::Jump(void)
{
	CInputKeyboard *pInputKey = CManager::GetInputKeyboard();	// �L�[�{�[�h�̃|�C���^
	CInputPad *pInputPad = CManager::GetInputPad();

	// �W�����v
	if (pInputKey->GetPress(DIK_SPACE) == true || pInputPad->GetTrigger(CInputPad::BUTTON_A, 0))
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

			if (m_pCar != NULL)
			{
				m_Info.move.x += m_pCar->GetMove().x * CManager::GetSlow()->Get();	//x���W
				m_Info.move.z += m_pCar->GetMove().z * CManager::GetSlow()->Get();	//x���W
			}
		}
	}
}

//===============================================
// �X���[���V�����[����
//===============================================
void CPlayer::SlowShw(void)
{
	CCamera *pCamera = CManager::GetCamera();		// �J�����̃|�C���^
	D3DXVECTOR3 CamRot = pCamera->GetRotation();	// �J�����̊p�x

	CInputKeyboard *pInputKey = CManager::GetInputKeyboard();	// �L�[�{�[�h�̃|�C���^
	CInputMouse *pInputMouse = CManager::GetInputMouse();
	D3DXVECTOR3 BulletMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CInputPad *pInputPad = CManager::GetInputPad();
	CBullet *pBullet = NULL;

	if (pInputKey->GetPress(DIK_L) == true || pInputMouse->GetPress(CInputMouse::BUTTON_LBUTTON) == true || pInputPad->GetPress(CInputPad::BUTTON_RIGHTBUTTON, 0))
	{//ENTER�L�[�������ꂽ�Ƃ�

		m_pBody->GetMotion()->Set(BMOTION_SLOWSHW);
		m_bAttack = true;
		m_fChargeCnt += 1.0f;

		if (m_fChargeCnt > NOCHARGE_CNT)
		{// �`���[�W��
			if (m_pBalloon == NULL)
			{// �`���[�W�J�n���Ă��Ȃ��ꍇ
				m_pBalloon = CMeshBalloon::Create(m_SetBalloon.pos, m_SetBalloon.rot, m_SetBalloon.fLength, m_SetBalloon.fHeight,
				m_SetBalloon.nPriority, m_SetBalloon.nWidth, m_SetBalloon.nHeight);

				m_pBalloon->SetParent(m_pWeaponL->GetMtxWorld());

				// �e�N�X�`���̃����_���ύX
				int nRand = rand() % CMeshBalloon::TYPE_MAX;

				switch (nRand)
				{
				case CMeshBalloon::TYPE_PINK:

					m_pBalloon->BindTexture(CTexture::TYPE_BALLOONPINK);
					break;

				case CMeshBalloon::TYPE_BLUE:

					m_pBalloon->BindTexture(CTexture::TYPE_BALLOONBLUE);
					break;
				}
				
			}

			if (m_pBalloon != NULL)
			{
				D3DXVECTOR3 pos = m_pBalloon->GetPosition();
				m_pBalloon->AddLength(0.5f);
				pos.x += -0.5f;
				m_pBalloon->SetPosition(pos);
				CManager::GetSound()->Play(CSound::LABEL_SE_BALLOONUP);
			}
		}
	}
	else
	{// �U���{�^���������ĂȂ��A�܂��͗�����
		if (m_fChargeCnt > 0.0f && m_fChargeCnt <= NOCHARGE_CNT)
		{// �`���[�W�������ꍇ
			D3DXMATRIX mtx;
			mtx = *m_pWeaponL->GetMtxWorld();

			BulletMove = { -cosf(CamRot.y) * 2.0f, 1.0f, -sinf(CamRot.y) * 2.0f };

			// �e�̔���
			pBullet = CBullet::Create(D3DXVECTOR3(mtx._41, mtx._42, mtx._43),
				D3DXVECTOR3(BulletMove.x, BulletMove.y, BulletMove.z), CBullet::TYPE_GRAVITY);

			pBullet->SetSize(300.0f, 50.0f);
			pBullet->SetLife(300.0f);

			BulletMove = { -cosf(CamRot.y) * 4.0f, 1.0f, -sinf(CamRot.y) * 4.0f };

			// �e�̔���
			pBullet = CBullet::Create(D3DXVECTOR3(mtx._41, mtx._42, mtx._43),
				D3DXVECTOR3(BulletMove.x, BulletMove.y, BulletMove.z), CBullet::TYPE_GRAVITY);

			pBullet->SetSize(300.0f, 50.0f);
			pBullet->SetLife(300.0f);

			for (int nCnt = 0; nCnt < 10; nCnt++)
			{
				// ���W�̐ݒ�
				D3DXVECTOR3 pos = D3DXVECTOR3(mtx._41 + m_Info.move.x, mtx._42, mtx._43 + m_Info.move.z);
				D3DXVECTOR3 move;

				//�ړ��ʂ̐ݒ�
				move.x = -cosf(CamRot.y + -D3DX_PI * 0.18f + D3DX_PI * 0.36f * ((rand() % 10) * 0.1f)) * 7.0f;
				move.y = rand() % 30 * 0.1f;
				move.z = -sinf(CamRot.y + -D3DX_PI * 0.18f + D3DX_PI * 0.36f * ((rand() % 10) * 0.1f)) * 7.0f;

				pBullet = CBullet::Create(pos,
					move, CBullet::TYPE_SHOWER);
				//pBullet->SetInerMove(D3DXVECTOR3(m_Info.move.x, 0.0f, m_Info.move.z));
				pBullet->SetLife(300.0f);
			}

			CManager::GetSound()->Play(CSound::LABEL_SE_SHW);
		}
		else
		{
			// ���D����
			if (m_pBalloon != NULL)
			{
				ShotBalloon();
				CManager::GetSound()->Play(CSound::LABEL_SE_BALLOONSHOT);
			}
		}

		m_fChargeCnt = 0.0f;
		m_bAttack = false;
	}
}

//===============================================
// �X���[���񒚋���
//===============================================
void CPlayer::SlowGun(void)
{
	if (m_nSlowTime <= 30 * 1)
	{
		m_pBody->GetMotion()->Set(BMOTION_SLOWATK);

		m_bAttack = true;

		if (m_pBody->GetMotion()->GetNowFrame() != 0)
		{// ���̃L�[�̊J�n�t���[���ȊO�̏ꍇ
			return;
		}

		if (m_pBody->GetMotion()->GetNowKey() != 1 && (m_pBody->GetMotion()->GetNowMotion() == BMOTION_SLOWATK || m_pBody->GetMotion()->GetNowMotion() == BMOTION_SLOWSHW))
		{
			m_bAttack = true;
			return;
		}

		CLockOn *pLock = CLockOn::GetTop();

		while (pLock != NULL)
		{// �g�p����Ă���ԌJ��Ԃ�
			CLockOn *pBulNext = pLock->GetNext();	// ����ێ�
			D3DXVECTOR3 BulletMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			D3DXMATRIX mtx;
			CBullet *pBullet;

			if (pLock->GetDeath() == false && pLock->GetType() == CLockOn::TYPE_MULTI)
			{
				if (pLock->GetTag() != NULL)
				{// �����W�I�̏ꍇ

					if (m_WepType == ATK_GUN)
					{
						if (m_nAttackHand == 0)
						{
							mtx = *m_pWeaponL->GetMtxWorld();
						}
						else
						{
							mtx = *m_pWeaponR->GetMtxWorld();
						}

						D3DXVECTOR3 vec;
						vec.x = pLock->GetPosition().x - mtx._41;
						vec.y = pLock->GetPosition().y - mtx._42;
						vec.z = pLock->GetPosition().z - mtx._43;

						D3DXVec3Normalize(&vec, &vec);	// �x�N�g���𐳋K������

						BulletMove = vec * GUN_BULMOVE;

						// �e�̔���
						pBullet = CBullet::Create(D3DXVECTOR3(mtx._41, mtx._42, mtx._43),
							D3DXVECTOR3(BulletMove.x, BulletMove.y, BulletMove.z), CBullet::TYPE_NONE);

						pBullet->SetHom(&*pLock->GetTag(), GUN_BULMOVE);
					}
				}
			}
			m_nAttackHand ^= 1;

			pLock = pBulNext;	// ���Ɉړ�
		}

		CManager::GetSound()->Play(CSound::LABEL_SE_ZONEGUN);
		m_bSlow = false;
		m_nSlowTime = 0;
	}
}

//===============================================
// �X���[���ԑ���
//===============================================
void CPlayer::AddSlowTime(int nAddTime)
{
	int nSlowTimerOld = m_nSlowTime;	// �ύX�O�̃X���[�\����
	m_nSlowTime += nAddTime;

	if (m_nSlowTime > DEF_SLOWTIME)
	{// ���E�l�𒴂���
		m_nSlowTime = DEF_SLOWTIME;
	}

	if (m_pSlowGage == NULL || m_nSlowTime == nSlowTimerOld)
	{// �g�p���Ă��Ȃ��A�܂��̓X���[���ԂɕύX���Ȃ�
		return;
	}

	// �X���[�ő厞�Ԃ���̊��������߂�
	float fRate = (float)m_nSlowTime / (float)DEF_SLOWTIME;

	m_pSlowGage->SetSize(DEF_SLOWGAGELENGSH * fRate, SLOWGAGE_HEIGHT);
	m_pSlowGage->SetTex(-5.0f * fRate, 0.0f, 5.0f * fRate);
	SetGageColor(fRate);
}

//===============================================
// �Q�[�W�J���[�ύX
//===============================================
void CPlayer::SetGageColor(float fRate)
{
	if (m_pSlowGage == NULL)
	{
		return;
	}

	if (fRate >= 1.0f)
	{
		m_pSlowGage->SetCol(D3DXCOLOR(0.0f, 0.8f, 1.0f, 1.0f));
	}
	else if (fRate <= 0.1f)
	{
		m_pSlowGage->SetCol(D3DXCOLOR(0.1f, 1.0f, 0.1f, 1.0f));
		m_pSlowManual->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	}
	else
	{
		m_pSlowManual->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_pSlowGage->SetCol(D3DXCOLOR(1.0f * fRate, 1.0f, 1.0f * fRate, 1.0f));
	}
}

//===============================================
// �p�[�e�B�N��
//===============================================
void CPlayer::Particle(void)
{
	if (m_pLeg != NULL)
	{
		CMotion *pMotion = m_pLeg->GetMotion();

		if (pMotion->GetNowMotion() == BMOTION_WALK)
		{
			if (pMotion->GetNowFrame() == 0 && (pMotion->GetNowKey() == 0 || pMotion->GetNowKey() == 2))
			{// �n�ʂ��R����
				CParticle::Create(m_Info.pos, D3DXVECTOR3(m_Info.move.x, 0.0f, m_Info.move.z), CEffect::TYPE_DUST);
				CManager::GetSound()->Play(CSound::LABEL_SE_MOVE);
			}
		}
		else if (pMotion->GetNowMotion() == BMOTION_JUMP)
		{
			if (pMotion->GetNowFrame() == 0 && pMotion->GetOldMotion() != pMotion->GetNowMotion() && m_Info.move.y >= 0.0f)
			{// �n�ʂ��R����
				CParticle::Create(D3DXVECTOR3(m_Info.pos.x, m_Info.posOld.y, m_Info.pos.z), m_Info.move, CEffect::TYPE_DUST);
				CParticle::Create(m_Info.pos, m_Info.move, CEffect::TYPE_SWAP);
				CManager::GetSound()->Play(CSound::LABEL_SE_JUMP);
			}
		}
	}
}

//===============================================
// ���D���ˏ���
//===============================================
void CPlayer::ShotBalloon(void)
{
	CCamera *pCamera = CManager::GetCamera();		// �J�����̃|�C���^
	D3DXVECTOR3 CamRot = pCamera->GetRotation();	// �J�����̊p�x
	D3DXVECTOR3 Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float fMultiMove = 1.0f - (float)(m_pBalloon->GetLength() / BALLOON_WEIGHT);
	Move = { -cosf(CamRot.y) * BALLOON_MOVE * fMultiMove, 0.0f, -sinf(CamRot.y) * BALLOON_MOVE * fMultiMove };

	D3DXVECTOR3 pos = D3DXVECTOR3(m_pBalloon->GetMtx()->_41, m_pBalloon->GetMtx()->_42, m_pBalloon->GetMtx()->_43);
	m_pBalloon->SetPosition(pos);
	m_pBalloon->SetMove(Move);
	m_pBalloon->SetParent(NULL);
	m_pBalloon = NULL;

}