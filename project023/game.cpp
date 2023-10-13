//===============================================
//
// �Q�[����ʂ̊Ǘ����� [game.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "game.h"
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
#include "filter.h"

//===============================================
// �}�N����`
//===============================================
#define START_TIME	(60 * 4)	// ��������
#define START_SCORE	(0)		// �J�n�X�R�A
#define MAP_SIZE	(100.0f)	// �}�b�v�T�C�Y
#define STARTSET_NUMENEMY	(3)	// �J�n���ɔz�u����G�̐�
#define MORNING_TIME	(60 * 6)	// �����I������
#define AM_COMRUSH	(60 * 9)	// �ʋ΃��b�V��
#define RELAX_TIME	(60 * 11)	// �����b�N�X�^�C��
#define NOON_TIME	(60 * 12.5)	// ���x��
#define EVENT_RUSH	(60 * 15.5)	// �C�x���g
#define PM_RELAX_TIME	(60 * 16)	// �A��J�n����
#define PM_GOHOME_RUSH	(60 * 19)	// �A��b�V��
#define MAX_TIME	(60 * 20 + 10)	// �ő厞��
#define SPEED_UP	(30.0f)

//===============================================
// �ÓI�����o�ϐ�
//===============================================
CScore *CGame::m_pScore = NULL;		// �X�R�A�̃|�C���^
CSlow *CGame::m_pSlow = NULL;		// �X���[��Ԃւ̃|�C���^
CMeshField *CGame::m_pMeshField = NULL;	// ���b�V���t�B�[���h�̃|�C���^
CPause *CGame::m_pPause = NULL;		// �|�[�Y�̃|�C���^

//===============================================
// �R���X�g���N�^
//===============================================
CGame::CGame()
{
	// �l�̃N���A
	m_pMapCamera = NULL;
	m_pMapThermo = NULL;
	m_nMaxEnemy = 0;
	m_pTime = NULL;
	m_pEnemyManager = NULL;
	m_pPlayer = NULL;
	m_pFileLoad = NULL;
	m_pEditor = NULL;
	m_pCarManager = NULL;
	m_pMeshDome = NULL;
	m_pStart = NULL;

	for (int nCnt = 0; nCnt < NUM_FILTER; nCnt++)
	{
		m_apFilter[nCnt] = NULL;
	}
}

//===============================================
// �f�X�g���N�^
//===============================================
CGame::~CGame()
{

}

//===============================================
// ����������
//===============================================
HRESULT CGame::Init(void)
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

	// �G�f�B�b�g�̐���
	if (m_pEditor == NULL)
	{// �g�p���Ă��Ȃ��ꍇ
		m_pEditor = new CEditor;

		// ������
		if (m_pEditor != NULL)
		{
			m_pEditor->Init();
		}
	}

	// �I�u�W�F�N�g����
	m_pMeshDome = CMeshDome::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20000.0f, 10.0f, 3, 10, 10);
	CMeshCylinder::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 17000.0f, 100.0f, 3, 10, 10);
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(-3900.0f, 0.0f, 3700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		"data\\TXT\\motion_body.txt", "data\\TXT\\motion_leg.txt", 1);

	// �X�R�A�̐���
	m_pScore = CScore::Create(D3DXVECTOR3(250.0f, 50.0f, 0.0f), 3);
	m_pScore->Set(START_SCORE);

	// �^�C���̐���
	m_pTime = CTime::Create(D3DXVECTOR3(550.0f, 100.0f, 0.0f));
	m_pTime->Set(START_TIME);
	m_pTime->SetMax(MAX_TIME);

	CObject2D *pUi = CObject2D::Create(7);
	pUi->SetPosition(D3DXVECTOR3(410.0f, 65.0f, 0.0f));
	pUi->SetSize(25, 30);
	pUi->BindTexture(CManager::GetTexture()->Regist("data\\TEXTURE\\target000.png"));

	pUi = CObject2D::Create(7);
	pUi->SetPosition(D3DXVECTOR3(MAP_SIZE, MAP_SIZE, 0.0f));
	pUi->SetSize(MAP_SIZE, MAP_SIZE);
	pUi->BindTexture(CManager::GetTexture()->Regist("data\\TEXTURE\\map000.png"));

	if (m_pStart == NULL)
	{
		m_pStart = CObject2D::Create(7);
		m_pStart->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 1.5f, SCREEN_HEIGHT * 0.4f, 0.0f));
		m_pStart->SetRotation(D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI * 0.05f));
		m_pStart->SetLength(SCREEN_WIDTH * 0.75f, SCREEN_HEIGHT * 0.25f);
		m_pStart->BindTexture(CManager::GetTexture()->Regist("data\\TEXTURE\\start.png"));
	}

	// �}�b�v�̐���
	if (m_pMapThermo == NULL)
	{
		m_pMapThermo = CThermo::Create();
		m_pMapThermo->BindTexture(CManager::GetTexture()->Regist("data\\TEXTURE\\thermo000.jpg"));
		m_pMapThermo->SetColor(D3DXCOLOR(0.7f, 0.05f, 0.05f, 0.0f));
		m_pMapThermo->SetpVtx(8000.0f, 8000.0f);
	}

	// �|�[�Y�̐���
	if (m_pPause == NULL)
	{
		m_pPause = CPause::Create();
	}

	CManager::GetCamera()->SetMode(CCamera::MODE_NORMAL);

	m_nMaxEnemy = CObject::GetNumEnemAll();

	// �~�j�}�b�v�p�J�����𐶐�
	if (m_pMapCamera == NULL)
	{// �g�p���Ă��Ȃ��ꍇ
		m_pMapCamera = new CMapCamera;

		// ������
		if (m_pMapCamera != NULL)
		{
			D3DVIEWPORT9 viewport;
			//�v���C���[�Ǐ]�J�����̉�ʈʒu�ݒ�
			viewport.X = 0;
			viewport.Y = 0;
			viewport.Width = 200;
			viewport.Height = 200;
			viewport.MinZ = 0.0f;
			viewport.MaxZ = 0.1f;
			m_pMapCamera->Init();
			m_pMapCamera->SetLength(11500.0f);
			m_pMapCamera->SetRotation(D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.00001f));
			m_pMapCamera->SetViewPort(viewport);
		}
	}

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
		m_pEnemyManager->Spawn(STARTSET_NUMENEMY);
	}

	// �J�[�}�l�[�W���[�𐶐�
	if (m_pCarManager == NULL)
	{
		m_pCarManager = new CCarManager;
		m_pCarManager->Init();
	}

	// �G�̔z�u�Ǘ�
	EnemySet();

	// �Ԃ̔z�u�Ǘ�
	CarSet();

	// ��̐F�ύX
	SkySet();

	// �X�|�b�g���C�g���I��
	CManager::GetLight()->EnablePointLight(true);

	CManager::GetSound()->Play(CSound::LABEL_BGM_GAME);

	m_apFilter[0] = CHeatFilter::Create();
	m_apFilter[1] = CHeatFilter::Create();
	m_apFilter[1]->BindTexture(CManager::GetTexture()->Regist("data\\TEXTURE\\smake000.jpg"));

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CGame::Uninit(void)
{
	if (m_pFileLoad != NULL)
	{
		m_pFileLoad->Uninit();

		delete m_pFileLoad;		// �������̊J��
		m_pFileLoad = NULL;
	}

	// �G�l�~�[�}�l�[�W���[
	if (m_pEnemyManager != NULL)
	{
		CResult::SetSuv(m_pEnemyManager->GetSuv());
		CResult::SetDead(m_pEnemyManager->GetDead());
		m_pEnemyManager->Uninit();
		delete m_pEnemyManager;
		m_pEnemyManager = NULL;
	}

	// �J�[�}�l�[�W���[
	if (m_pCarManager != NULL)
	{
		m_pCarManager->Uninit();
		delete m_pCarManager;
		m_pCarManager = NULL;
	}

	// �G���H�Ǘ�
	if (m_pEnemyRoute != NULL)
	{
		m_pEnemyRoute->Uninit();
		delete m_pEnemyRoute;
		m_pEnemyRoute = NULL;
	}


	// �X�R�A
	if (m_pScore != NULL)
	{
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

	// �X���[
	if (m_pPause != NULL)
	{
		m_pPause->Uninit();
		delete m_pPause;	// �������̊J��
		m_pPause = NULL;	// �g�p���Ă��Ȃ���Ԃɂ���
	}

	// �G�f�B�^�[���̔p��
	if (m_pEditor != NULL)
	{// �g�p���Ă���ꍇ
		
		m_pEditor->Uninit();
		delete m_pEditor;	// �������̊J��
		m_pEditor = NULL;	// �g�p���Ă��Ȃ���Ԃɂ���
	}

	// �~�j�}�b�v�J����
	if (m_pMapCamera != NULL)
	{
		m_pMapCamera->Uninit();
		delete m_pMapCamera;
		m_pMapCamera = NULL;
	}

	if (m_pMapThermo != NULL)
	{
		m_pMapThermo = NULL;
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
void CGame::Update(void)
{
	if (m_pStart != NULL)
	{
		D3DXVECTOR3 pos = m_pStart->GetPosition();

		// �ړ�
		if (pos.x > SCREEN_WIDTH * 0.75f)
		{
			pos.x -= 30.0f;
		}
		else if (pos.x < SCREEN_WIDTH * 0.35f)
		{
			pos.x -= 40.0f;
		}
		else
		{
			pos.x -= 2.5f;
		}

		m_pStart->SetPosition(pos);
		m_pStart->SetVtx();
		
		if (pos.x < -SCREEN_WIDTH * 0.5f)
		{
			m_pStart->Uninit();
			m_pStart = NULL;
			CManager::GetSlow()->SetSlow(1.0f);
		}

		if (m_pScore != NULL)
		{
			m_pScore->Update();
		}

		if (m_pTime->GetNum() != m_pTime->GetStartNum())
		{
			CarSet();
		}

		CScene::Update();

		return;
	}

	// �|�[�Y
	if (m_pPause != NULL)
	{
		m_pPause->Update();

		if (m_pPause->GetEnable() == true)
		{
			if (m_pPause->GetSelect() == true)
			{
				CManager::GetFade()->Update();
			}
			return;
		}
	}

	// �z���t�B���^�[�̐F��ύX
	if (m_pEnemyManager->GetDead() > 0)
	{
		int nDead = m_pEnemyManager->GetDead();
		int nSuv = m_pEnemyManager->GetSuv();

		for (int nCnt = 0; nCnt < NUM_FILTER; nCnt++)
		{
			if (m_apFilter[nCnt] != NULL)
			{
				m_apFilter[nCnt]->SetFil((float)((float)nDead / (float)(nSuv + 20)));
			}
		}
	}

#if _DEBUG

	// �G�f�B�^�[�̍X�V����
	if (m_pEditor != NULL)
	{
		m_pEditor->Update();
	}

	if (m_pEditor->GetActive() == true || m_pEditor->GetMeshActive() == true)
	{
		// �X�V����
		CScene::Update();
		return;
	}

#endif

	// �^�C��
	if (m_pTime != NULL)
	{
		m_pTime->Update();
		if (m_pTime->GetNum() >= MAX_TIME)
		{// ���Ԑ؂�
			//m_pTime->Set(START_TIME);

			CManager::GetFade()->Set(CScene::MODE_RESULT);
		}
		else
		{
			// �G�̔z�u�Ǘ�
			EnemySet();

			// �Ԃ̔z�u�Ǘ�
			CarSet();

			// ��̐F�ύX
			SkySet();
		}
	}

	// �c��l��
	if (m_pScore != NULL)
	{
		m_pScore->Update();
	}

	if (m_pMapThermo != NULL)
	{
		int nDead = m_pEnemyManager->GetDead();
		D3DXCOLOR col = m_pMapThermo->GetCol();
		if (nDead > 0)
		{// ��̂ł����݂��Ă���
			col.a = (float)(nDead / 100);
		}
		else
		{
			col.a = 0.0f;
		}
		m_pMapThermo->SetColor(col);
	}

	if (CManager::GetSlow()->Get() == 1.0f && CManager::GetSlow()->GetOld() != 1.0f)
	{
		CLockOn::MultiDeath();
	}

	if (m_pPlayer != NULL)
	{
		if (m_pTime->GetDiff() <= 0.25f || m_pTime->GetDiff() >= 0.8f)
		{

			CManager::GetLight()->SetPositonPointLight(m_pPlayer->GetPosition());
		}
		else if(m_pTime->GetDiff() == 0.25f)
		{
			CManager::GetLight()->EnablePointLight(false);
		}
		else if (m_pTime->GetDiff() == 0.8f)
		{
			CManager::GetLight()->EnablePointLight(true);
		}
	}

	// �X�V����
	CScene::Update();
}

//===============================================
// �`�揈��
//===============================================
void CGame::Draw(void)
{
	CScene::Draw();

	// �|�[�Y
	if (m_pPause != NULL)
	{
		m_pPause->Draw();
	}
}

//===================================================
// �X�R�A�̎擾
//===================================================
CScore *CGame::GetScore(void)
{
	return m_pScore;
}

//===================================================
// �X�R�A�̎擾
//===================================================
CTime *CGame::GetTime(void)
{
	return m_pTime;
}

//===================================================
// �v���C���[�̎擾
//===================================================
CPlayer *CGame::GetPlayer(void)
{
	return m_pPlayer;
}

//===================================================
// �X���[���̎擾
//===================================================
CSlow *CGame::GetSlow(void)
{
	return m_pSlow;
}

//===================================================
// ���b�V���t�B�[���h�̎擾
//===================================================
CMeshField *CGame::GetMeshField(void)
{
	return m_pMeshField;
}

//===================================================
// �t�@�C���ǂݍ��݂̎擾
//===================================================
CFileLoad *CGame::GetFileLoad(void)
{
	return m_pFileLoad;
}

//===================================================
// �|�[�Y�̎擾
//===================================================
CPause *CGame::GetPause(void)
{
	return m_pPause;
}

//===================================================
// �G�f�B�^�[���̎擾
//===================================================
CEditor *CGame::GetEditor(void)
{
	return m_pEditor;
}

//===================================================
// �ǂݍ��݃f�[�^���Z�b�g
//===================================================
void CGame::DataReset(void)
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
void CGame::EnemySet(void)
{
	if (m_pEnemyManager == NULL)
	{
		return;
	}

	// �z�u�͈́A��ށA����ݒ�
	if(m_pTime->GetNum() < MORNING_TIME)
	{// ����
		m_pEnemyManager->SetRouteRange(PARK_ROUTE, SHOP_ROUTE);
		m_pEnemyManager->SetTypeRange(CEnemyManager::ENEMY_MAX, 0);
		m_pEnemyManager->SetNum(1);
		m_pEnemyManager->SetTimer(15);
	}
	else if (m_pTime->GetNum() >= MORNING_TIME && m_pTime->GetNum() < AM_COMRUSH)
	{// �o�΃��b�V��
		m_pEnemyManager->SetRouteRange(SHOP_ROUTE, 0);
		m_pEnemyManager->SetTypeRange(CEnemyManager::ENEMY_KIDSBOY, 0);
		m_pEnemyManager->SetNum(3);
		m_pEnemyManager->SetTimer(8);

		if (m_pTime->GetNum() == MORNING_TIME && m_pTime->GetAnim() == 0.0f)
		{
			if (m_pStart == NULL)
			{
				m_pEnemyManager->Spawn(CObject::GetNumEnemAll() + 30);
				m_pStart = CObject2D::Create(7);
				m_pStart->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 1.5f, SCREEN_HEIGHT * 0.4f, 0.0f));
				m_pStart->SetRotation(D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI * 0.05f));
				m_pStart->SetLength(SCREEN_WIDTH * 0.75f, SCREEN_HEIGHT * 0.25f);
				m_pStart->BindTexture(CManager::GetTexture()->Regist("data\\TEXTURE\\rush000.png"));
				m_pStart->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f));
				CManager::GetSlow()->SetSlow(SPEED_UP);
				CManager::GetSound()->Play(CSound::LABEL_SE_CLOCK);
			}
		}
	}
	else if (m_pTime->GetNum() >= RELAX_TIME && m_pTime->GetNum() < NOON_TIME)
	{// ���x��
		m_pEnemyManager->SetRouteRange(PARK_ROUTE, SHOP_ROUTE);
		m_pEnemyManager->SetTypeRange(CEnemyManager::ENEMY_KIDSBOY, CEnemyManager::ENEMY_KIDSBOY);
		m_pEnemyManager->SetTimer(20);
		m_pEnemyManager->SetNum(2);
	}
	else if (m_pTime->GetNum() >= NOON_TIME && m_pTime->GetNum() < EVENT_RUSH)
	{// �C�x���g���b�V��
		m_pEnemyManager->SetRouteRange(PARK_ROUTE, SHOP_ROUTE);
		m_pEnemyManager->SetTypeRange(CEnemyManager::ENEMY_KIDSBOY, CEnemyManager::ENEMY_KIDSBOY);
		m_pEnemyManager->SetTimer(5);
		m_pEnemyManager->SetNum(3);

		if (m_pTime->GetNum() == NOON_TIME && m_pTime->GetAnim() == 0.0f)
		{
			if (m_pStart == NULL)
			{
				m_pEnemyManager->Spawn(CObject::GetNumEnemAll() + 30);
				m_pStart = CObject2D::Create(7);
				m_pStart->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 1.5f, SCREEN_HEIGHT * 0.4f, 0.0f));
				m_pStart->SetRotation(D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI * 0.05f));
				m_pStart->SetLength(SCREEN_WIDTH * 0.75f, SCREEN_HEIGHT * 0.25f);
				m_pStart->BindTexture(CManager::GetTexture()->Regist("data\\TEXTURE\\rush002.png"));
				CManager::GetSlow()->SetSlow(SPEED_UP);
				CManager::GetSound()->Play(CSound::LABEL_SE_CLOCK);
			}
		}
	}
	else if (m_pTime->GetNum() >= PM_RELAX_TIME && m_pTime->GetNum() < PM_GOHOME_RUSH)
	{// �A��b�V��
		m_pEnemyManager->SetRouteRange(NUM_ROUTE, 0);
		m_pEnemyManager->SetTypeRange(CEnemyManager::ENEMY_MAX, 0);
		m_pEnemyManager->SetNum(2);
		m_pEnemyManager->SetTimer(3);

		if (m_pTime->GetNum() == PM_RELAX_TIME && m_pTime->GetAnim() == 0.0f)
		{
			if (m_pStart == NULL)
			{
				m_pEnemyManager->Spawn(CObject::GetNumEnemAll() + 30);
				m_pStart = CObject2D::Create(7);
				m_pStart->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 1.5f, SCREEN_HEIGHT * 0.4f, 0.0f));
				m_pStart->SetRotation(D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI * 0.05f));
				m_pStart->SetLength(SCREEN_WIDTH * 0.75f, SCREEN_HEIGHT * 0.25f);
				m_pStart->BindTexture(CManager::GetTexture()->Regist("data\\TEXTURE\\rush001.png"));
				CManager::GetSlow()->SetSlow(SPEED_UP);
				CManager::GetSound()->Play(CSound::LABEL_SE_CLOCK);
			}
		}
	}
	else if (m_pTime->GetNum() >= PM_GOHOME_RUSH)
	{// �A��b�V���I��肩��Q�[���I���܂�
		m_pEnemyManager->SetRouteRange(SHOP_ROUTE + 5, 0);
		m_pEnemyManager->SetTypeRange(CEnemyManager::ENEMY_MAX, 0);
		m_pEnemyManager->SetNum(1);
		m_pEnemyManager->SetTimer(20);

		if (m_pTime->GetNum() == MAX_TIME - 10 && m_pTime->GetAnim() == 0.0f)
		{
			if (m_pStart == NULL)
			{
				m_pEnemyManager->Spawn(CObject::GetNumEnemAll() + 30);
				m_pStart = CObject2D::Create(7);
				m_pStart->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 1.5f, SCREEN_HEIGHT * 0.4f, 0.0f));
				m_pStart->SetRotation(D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI * 0.05f));
				m_pStart->SetLength(SCREEN_WIDTH * 0.75f, SCREEN_HEIGHT * 0.25f);
				m_pStart->BindTexture(CManager::GetTexture()->Regist("data\\TEXTURE\\rush003.png"));
				CManager::GetSlow()->SetSlow(SPEED_UP);
				CManager::GetSound()->Play(CSound::LABEL_SE_CLOCK);
			}
		}
	}
	else
	{// ����ȊO
		m_pEnemyManager->SetRouteRange(NUM_ROUTE, 0);
		m_pEnemyManager->SetTypeRange( CEnemyManager::ENEMY_MAX, 0);
		m_pEnemyManager->SetNum(1);
		m_pEnemyManager->SetTimer(40);
	}

	// �X�V
	m_pEnemyManager->Update();
}

//===================================================
// �Ԃ̔z�u
//===================================================
void CGame::CarSet(void)
{
	if (m_pCarManager != NULL)
	{
		m_pCarManager->Update();
	}
}

//===================================================
// ��̐F�ݒ�
//===================================================
void CGame::SkySet(void)
{
	if (m_pMeshDome != NULL)
	{
		if (CManager::GetSlow()->Get() >= 1.0f)
		{
			m_pMeshDome->SetColor(m_pTime->GetDiff());
			CManager::GetLight()->SetLight(m_pTime->GetDiff());
		}
	}
}