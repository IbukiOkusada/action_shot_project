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

//===============================================
// �}�N����`
//===============================================
#define START_TIME	(120)	// ��������
#define START_SCORE	(0)		// �J�n�X�R�A

//===============================================
// �ÓI�����o�ϐ�
//===============================================
CScore *CGame::m_pScore = NULL;		// �X�R�A�̃|�C���^
CTime *CGame::m_pTime = NULL;		// �^�C���̃|�C���^
CPlayer *CGame::m_pPlayer = NULL;	// �v���C���[�̃|�C���^
CSlow *CGame::m_pSlow = NULL;		// �X���[��Ԃւ̃|�C���^
CMeshField *CGame::m_pMeshField = NULL;	// ���b�V���t�B�[���h�̃|�C���^
CFileLoad *CGame::m_pFileLoad = NULL;	// �t�@�C���ǂݍ��݂̃|�C���^
CPause *CGame::m_pPause = NULL;		// �|�[�Y�̃|�C���^
CMultiCamera *CGame::m_pMapCamera = NULL;	// �}�b�v�J�����̃|�C���^
CEditor *CGame::m_pEditor = NULL;	// �G�f�B�^�[�ւ̃|�C���^

//===============================================
// �R���X�g���N�^
//===============================================
CGame::CGame()
{

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

	//// �G�f�B�b�g�̐���
	//if (m_pEditor == NULL)
	//{// �g�p���Ă��Ȃ��ꍇ
	//	m_pEditor = new CEditor;

	//	// ������
	//	if (m_pEditor != NULL)
	//	{
	//		m_pEditor->Init();
	//	}
	//}

	// �I�u�W�F�N�g����
	CMeshDome::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20000.0f, 10.0f, 3, 10, 10);
	CMeshCylinder::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 17000.0f, 100.0f, 3, 10, 10);
	CEnemy::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, D3DX_PI * 0.25f, 0.0f), D3DXVECTOR3(-sinf(D3DX_PI * 0.25f) * 1.0f, 0.0f, -cosf(D3DX_PI * 0.25f) * 1.0f), "data\\TXT\\motion_murabito.txt");
	CObjectX *p = CObjectX::Create(D3DXVECTOR3(2500.0f, 0.0f, 2500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data/MODEL/container000.x");
	p->SetType(CObject::TYPE_ENEMYSPAWN);
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 3500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		"data\\TXT\\motion_body.txt", "data\\TXT\\motion_leg.txt", 1);

	//CMeshBalloon::Create(D3DXVECTOR3(1000.0f, 100.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10.0f, 10.0f, 3, 20, 20);

	// �X�R�A�̐���
	m_pScore = CScore::Create(D3DXVECTOR3(400.0f, 50.0f, 0.0f));
	m_pScore->Set(START_SCORE);

	// �^�C���̐���
	m_pTime = CTime::Create(D3DXVECTOR3(800.0f, 50.0f, 0.0f));
	m_pTime->Set(START_TIME);

	CObject2D *pUi = CObject2D::Create(7);
	pUi->SetPosition(D3DXVECTOR3(560.0f, 65.0f, 0.0f));
	pUi->SetSize(25, 30);
	pUi->BindTexture(CManager::GetTexture()->Regist("data\\TEXTURE\\target000.png"));

	pUi = CObject2D::Create(7);
	pUi->SetPosition(D3DXVECTOR3(80.0f, 80.0f, 0.0f));
	pUi->SetSize(80, 80);
	pUi->BindTexture(CManager::GetTexture()->Regist("data\\TEXTURE\\map000.png"));

	// �|�[�Y�̐���
	if (m_pPause == NULL)
	{
		m_pPause = CPause::Create();
	}

	CManager::GetCamera()->SetMode(CCamera::MODE_NORMAL);

	while (1)
	{
		if (CObject::GetNumEnemAll() < 50)
		{
			int nRand = rand() % 201 - 100;
			float fRot = D3DX_PI * ((float)nRand * 0.01f);

			CEnemy::Create(D3DXVECTOR3(0.0f + rand() % 300 - 150, 0.0f, 0.0f + rand() % 300 - 150), D3DXVECTOR3(0.0f, fRot, 0.0f),
				D3DXVECTOR3(-sinf(fRot) * 4.0f, 0.0f, -cosf(fRot) * 4.0f), "data\\TXT\\motion_murabito.txt");
		}
		else
		{
			break;
		}
	}

	// �~�j�}�b�v�p�J�����𐶐�
	if (m_pMapCamera == NULL)
	{// �g�p���Ă��Ȃ��ꍇ
		m_pMapCamera = new CMultiCamera;

		// ������
		if (m_pMapCamera != NULL)
		{
			D3DVIEWPORT9 viewport;
			//�v���C���[�Ǐ]�J�����̉�ʈʒu�ݒ�
			viewport.X = 0;
			viewport.Y = 0;
			viewport.Width = SCREEN_WIDTH * 0.125f;
			viewport.Height = SCREEN_HEIGHT * 0.22f;
			viewport.MinZ = 0.1f;
			viewport.MaxZ = 0.2f;
			m_pMapCamera->Init();
			m_pMapCamera->SetLength(10000.0f);
			m_pMapCamera->SetRotation(D3DXVECTOR3(0.0f, 0.0001f, 0.00001f));
			m_pMapCamera->SetViewPort(viewport);
		}
	}

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

	m_pScore = NULL;		// �X�R�A�̃|�C���^
	m_pTime = NULL;		// �^�C���̃|�C���^
	m_pPlayer = NULL;	// �v���C���[�̃|�C���^
	m_pMeshField = NULL;
	m_pFileLoad = NULL;
}

//===============================================
// �X�V����
//===============================================
void CGame::Update(void)
{
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

	// �X�V����
	CScene::Update();

	// �^�C��
	if (m_pTime != NULL)
	{
		m_pTime->Update();
		if (m_pTime->GetNum() <= 0)
		{// ���Ԑ؂�
			CManager::GetFade()->Set(CScene::MODE_RESULT);
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

#ifdef _DEBUG

	// �G�f�B�^�[�̍X�V����
	if (m_pEditor != NULL)
	{
		m_pEditor->Update();
	}

#endif
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