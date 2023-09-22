//===============================================
//
// �`���[�g���A����ʂ̊Ǘ����� [tutorial.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "tutorial.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "score.h"
#include "time.h"
#include "camera.h"
#include "light.h"
#include "texture.h"
#include "meshcylinder.h"
#include "meshdome.h"
#include "fileload.h"
#include "slow.h"
#include "enemy.h"
#include "player.h"
#include "objectX.h"
#include "Xfile.h"
#include "input.h"
#include "fade.h"
#include "pause.h"
#include "result.h"
#include "lockon.h"
#include "meshballoon.h"
#include "editor.h"
#include "thermo.h"
#include "enemy_manager.h"
#include "car_manager.h"
#include "enemy_route.h"
#include "sound.h"

//===============================================
// �}�N����`
//===============================================
#define START_TIME	(60 * 3)	// ��������
#define START_SCORE	(0)		// �J�n�X�R�A
#define MAP_SIZE	(100.0f)	// �}�b�v�T�C�Y
#define STARTSET_NUMENEMY	(30)	// �J�n���ɔz�u����G�̐�
#define MAX_TIME	(60 * 20)	// �ő厞��

//===============================================
// �ÓI�����o�ϐ�
//===============================================
CScore *CTutorial::m_pScore = NULL;		// �X�R�A�̃|�C���^
CSlow *CTutorial::m_pSlow = NULL;		// �X���[��Ԃւ̃|�C���^
CMeshField *CTutorial::m_pMeshField = NULL;	// ���b�V���t�B�[���h�̃|�C���^

//===============================================
// �R���X�g���N�^
//===============================================
CTutorial::CTutorial()
{
	// �l�̃N���A
	m_pTime = NULL;
	m_pEnemyManager = NULL;
	m_pPlayer = NULL;
	m_pFileLoad = NULL;
	m_pCarManager = NULL;
	m_pMeshDome = NULL;
}

//===============================================
// �f�X�g���N�^
//===============================================
CTutorial::~CTutorial()
{

}

//===============================================
// ����������
//===============================================
HRESULT CTutorial::Init(void)
{
	// �O���t�@�C���ǂݍ��݂̐���
	if (m_pFileLoad == NULL)
	{// �g�p���Ă��Ȃ��ꍇ
		m_pFileLoad = new CFileLoad;

		if (m_pFileLoad != NULL)
		{
			m_pFileLoad->Init();
			m_pFileLoad->OpenFile("data\\TXT\\model.txt");
		}
	}
	CManager::GetCamera()->SetRot(D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, CManager::GetCamera()->GetRotation().z));

	// �I�u�W�F�N�g����
	m_pMeshDome = CMeshDome::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20000.0f, 10.0f, 3, 10, 10);
	CMeshCylinder::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 17000.0f, 100.0f, 3, 10, 10);
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(2800.0f, 0.0f, -3800.0f), D3DXVECTOR3(0.0f, D3DX_PI - 0.01f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		"data\\TXT\\motion_body.txt", "data\\TXT\\motion_leg.txt", 1);
	m_pPlayer->SetRotation(D3DXVECTOR3(0.0f, D3DX_PI - 0.01f, 0.0f));

	// �^�C���̐���
	m_pTime = CTime::Create(D3DXVECTOR3(600.0f, 100.0f, 0.0f));
	m_pTime->Set(START_TIME);
	m_pTime->SetMax(MAX_TIME);

	CManager::GetCamera()->SetMode(CCamera::MODE_NORMAL);

	// �G���H�Ǘ��𐶐�
	if (m_pEnemyRoute == NULL)
	{
		m_pEnemyRoute = new CEnemyRoute;
		m_pEnemyRoute->Init();
	}

	// �G�l�~�[�}�l�[�W���[�𐶐�
	if (m_pEnemyManager == NULL)
	{
		m_pEnemyManager = new CEnemyManager;
		m_pEnemyManager->Init();
		//m_pEnemyManager->Spawn(STARTSET_NUMENEMY);
	}

	// �J�[�}�l�[�W���[�𐶐�
	if (m_pCarManager == NULL)
	{
		m_pCarManager = new CCarManager;
		m_pCarManager->Init();
	}

	CObjectX::Create(D3DXVECTOR3(3000.0f, 0.0f, -3400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\board000.x");

	CObjectX::Create(D3DXVECTOR3(2800.0f, 0.0f, -2000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\board001.x");

	CObjectX::Create(D3DXVECTOR3(3100.0f, 0.0f, 50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\board002.x");

	CObjectX::Create(D3DXVECTOR3(2300.0f, 0.0f, 50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\board003.x");

	CObjectX::Create(D3DXVECTOR3(1400.0f, 0.0f, 570.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\board004.x");

	CObjectX::Create(D3DXVECTOR3(650.0f, 0.0f, 70.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), "data\\MODEL\\board005.x");

	CObjectX::Create(D3DXVECTOR3(-1250.0f, 0.0f, -1350.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), "data\\MODEL\\board006.x");

	CObjectX::Create(D3DXVECTOR3(-3500.0f, 0.0f, -1350.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), "data\\MODEL\\board007.x");

	CObjectX::Create(D3DXVECTOR3(-3500.0f, 0.0f, -650.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.0f, 0.0f), "data\\MODEL\\board008.x");

	CObjectX::Create(D3DXVECTOR3(-3500.0f, 0.0f, -650.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.0f, 0.0f), "data\\MODEL\\board008.x");

	CObjectX::Create(D3DXVECTOR3(-3650.0f, 0.0f, 900.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.0f, 0.0f), "data\\MODEL\\board009.x");

	CObjectX::Create(D3DXVECTOR3(1950.0f, 0.0f, -450.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.0f, 0.0f), "data\\MODEL\\board010.x");

	CObjectX::Create(D3DXVECTOR3(1200.0f, 0.0f, -450.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.0f, 0.0f), "data\\MODEL\\board010.x");

	CObjectX::Create(D3DXVECTOR3(850.0f, 0.0f, 300.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.0f, 0.0f), "data\\MODEL\\board010.x");

	CObjectX::Create(D3DXVECTOR3(-1000.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f), "data\\MODEL\\board010.x");

	CObjectX::Create(D3DXVECTOR3(-1000.0f, 0.0f, -600.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f), "data\\MODEL\\board010.x");

	CObjectX::Create(D3DXVECTOR3(-600.0f, 0.0f, -1300.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.0f, 0.0f), "data\\MODEL\\board010.x");

	CObjectX::Create(D3DXVECTOR3(-1400.0f, 0.0f, -1300.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.0f, 0.0f), "data\\MODEL\\board010.x");

	CObjectX::Create(D3DXVECTOR3(-1700.0f, 0.0f, -1300.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.0f, 0.0f), "data\\MODEL\\board010.x");

	CObjectX::Create(D3DXVECTOR3(-2000.0f, 0.0f, -1300.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.0f, 0.0f), "data\\MODEL\\board010.x");

	CObjectX::Create(D3DXVECTOR3(-3850.0f, 0.0f, -900.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.75f, 0.0f), "data\\MODEL\\board010.x");

	CObjectX::Create(D3DXVECTOR3(-3150.0f, 0.0f, 890.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.0f, 0.0f), "data\\MODEL\\board010.x");

	CObjectX::Create(D3DXVECTOR3(-4000.0f, 0.0f, 600.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), "data\\MODEL\\board010.x");

	CObjectX::Create(D3DXVECTOR3(-4000.0f, 0.0f, 2400.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), "data\\MODEL\\board010.x");

	CObjectX::Create(D3DXVECTOR3(-4000.0f, 0.0f, 3400.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), "data\\MODEL\\board010.x");

	// ��̐F�ύX
	SkySet();

	StartEnemy();

	// �|�C���g���C�g��L���ɂ���
	CManager::GetLight()->EnablePointLight(true);

	CManager::GetSound()->Play(CSound::LABEL_BGM_TUTORIAL);

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CTutorial::Uninit(void)
{
	if (m_pFileLoad != NULL)
	{
		m_pFileLoad->Uninit();

		delete m_pFileLoad;		// �������̊J��
		m_pFileLoad = NULL;
	}

	// �G�l�~�[�}�l�[�W���[
	if (m_pEnemyManager == NULL)
	{
		m_pEnemyManager->Uninit();
		delete m_pEnemyManager;
		m_pEnemyManager = NULL;
	}

	// �J�[�}�l�[�W���[
	if (m_pCarManager == NULL)
	{
		m_pCarManager->Uninit();
		delete m_pCarManager;
		m_pCarManager = NULL;
	}

	// �G���H�Ǘ�
	if (m_pEnemyRoute == NULL)
	{
		m_pEnemyRoute->Uninit();
		delete m_pEnemyRoute;
		m_pEnemyRoute = NULL;
	}


	// �X�R�A
	if (m_pScore != NULL)
	{
		CResult::SetScore(m_pScore->GetNum());
		m_pScore->Uninit();
		delete m_pScore;	// �������̊J��
		m_pScore = NULL;	// �g�p���Ă��Ȃ���Ԃɂ���
	}

	// �^�C��
	if (m_pTime != NULL)
	{
		m_pTime->Uninit();
		delete m_pTime;	// �������̊J��
		m_pTime = NULL;	// �g�p���Ă��Ȃ���Ԃɂ���
	}

	m_pScore = NULL;		// �X�R�A�̃|�C���^
	m_pTime = NULL;		// �^�C���̃|�C���^
	m_pPlayer = NULL;	// �v���C���[�̃|�C���^
	m_pMeshField = NULL;
	m_pFileLoad = NULL;
	m_pMeshDome = NULL;
}

//===============================================
// �X�V����
//===============================================
void CTutorial::Update(void)
{
	// �^�C��
	if (m_pTime != NULL)
	{
		if (m_pTime->GetNum() >= MAX_TIME)
		{// ���Ԑ؂�
			//m_pTime->Set(START_TIME);
		}
		else
		{
			if (m_pPlayer->GetPosition().x <= -3700.0f && m_pPlayer->GetPosition().x >= -4100.0f && m_pPlayer->GetPosition().z >= 3700.0f)
			{
				CManager::GetFade()->Set(CScene::MODE_GAME);
			}

			// �G�̔z�u�Ǘ�
			EnemySet();

			// �Ԃ̔z�u�Ǘ�
			CarSet();

			SkySet();
		}
	}

	// �c��l��
	if (m_pScore != NULL)
	{
		m_pScore->Update();
	}

	if (CManager::GetSlow()->Get() == 1.0f && CManager::GetSlow()->GetOld() != 1.0f)
	{
		CLockOn::MultiDeath();
	}

	if (m_pPlayer != NULL)
	{
		CManager::GetLight()->SetPositonPointLight(m_pPlayer->GetPosition());
	}

	// �X�V����
	CScene::Update();
}

//===============================================
// �`�揈��
//===============================================
void CTutorial::Draw(void)
{
	CScene::Draw();
}

//===================================================
// �X�R�A�̎擾
//===================================================
CScore *CTutorial::GetScore(void)
{
	return m_pScore;
}

//===================================================
// �X�R�A�̎擾
//===================================================
CTime *CTutorial::GetTime(void)
{
	return m_pTime;
}

//===================================================
// �v���C���[�̎擾
//===================================================
CPlayer *CTutorial::GetPlayer(void)
{
	return m_pPlayer;
}

//===================================================
// �X���[���̎擾
//===================================================
CSlow *CTutorial::GetSlow(void)
{
	return m_pSlow;
}

//===================================================
// ���b�V���t�B�[���h�̎擾
//===================================================
CMeshField *CTutorial::GetMeshField(void)
{
	return m_pMeshField;
}

//===================================================
// �t�@�C���ǂݍ��݂̎擾
//===================================================
CFileLoad *CTutorial::GetFileLoad(void)
{
	return m_pFileLoad;
}

//===================================================
// �ǂݍ��݃f�[�^���Z�b�g
//===================================================
void CTutorial::DataReset(void)
{
	// �I��
	if (m_pFileLoad != NULL)
	{
		m_pFileLoad->Uninit();

		delete m_pFileLoad;		// �������̊J��
		m_pFileLoad = NULL;
	}

	// �O���t�@�C���ǂݍ��݂̐���
	if (m_pFileLoad == NULL)
	{// �g�p���Ă��Ȃ��ꍇ
		m_pFileLoad = new CFileLoad;

		if (m_pFileLoad != NULL)
		{
			m_pFileLoad->Init();
			m_pFileLoad->OpenFile("data\\TXT\\model.txt");
		}
	}
}

//===================================================
// �G�̔z�u
//===================================================
void CTutorial::EnemySet(void)
{
	if (m_pEnemyManager != NULL)
	{
		m_pEnemyManager->UpdateTutorial();
	}
}

//===================================================
// �Ԃ̔z�u
//===================================================
void CTutorial::CarSet(void)
{
	if (m_pCarManager != NULL)
	{
		m_pCarManager->Update();
	}
}

//===================================================
// ��̐F�ݒ�
//===================================================
void CTutorial::SkySet(void)
{
	if (m_pMeshDome != NULL)
	{
		m_pMeshDome->SetColor(0.1f);
		CManager::GetLight()->SetLight(0.05f);
	}
}

void CTutorial::StartEnemy(void)
{
	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		CEnemy::Create(D3DXVECTOR3(2650.0f + nCnt * 100.0f, 0.0f, 600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\TXT\\motion_murabito.txt");
	}

	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		CEnemy::Create(D3DXVECTOR3(1650.0f + nCnt * 100.0f, 0.0f, 600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\TXT\\motion_murabito.txt");
	}

	CEnemy::Create(D3DXVECTOR3(1750.0f, 0.0f, 500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\TXT\\motion_murabito.txt");
	CEnemy::Create(D3DXVECTOR3(1750.0f, 0.0f, 700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\TXT\\motion_murabito.txt");

	for (int nCnt = 0; nCnt < 8; nCnt++)
	{
		for (int nCnt2 = 0; nCnt2 < 5; nCnt2++)
		{
			CEnemy::Create(D3DXVECTOR3(-2300.0f + nCnt * -150.0f, 0.0f, -2750.0f + nCnt2 * 150.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\TXT\\motion_murabito.txt");
		}
	}
}