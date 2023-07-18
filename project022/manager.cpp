//===============================================
//
// �}�l�[�W���[�̏��� [manager.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "manager.h"
#include "renderer.h"
#include "object.h"
#include "object2D.h"
#include "player.h"
#include "multibg.h"
#include "input.h"
#include "debugproc.h"
#include "bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "effect.h"
#include "sound.h"
#include "score.h"
#include "time.h"
#include "block.h"
#include "item.h"
#include "camera.h"
#include "light.h"
#include "object3D.h"
#include "billboard.h"
#include "objectX.h"
#include "Xfile.h"
#include "character.h"
#include "texture.h"
#include "meshfield.h"
#include "meshwall.h"
#include "meshcylinder.h"
#include "meshdome.h"
#include "fileload.h"
#include "slow.h"
#include "editor.h"

//===============================================
// �ÓI�����o�ϐ�
//===============================================
CRenderer *CManager::m_pRenderer = NULL;		// �����_���[�̃|�C���^
CInputKeyboard *CManager::m_pInputKeyboard = NULL;	// ���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^
CInputMouse *CManager::m_pInputMouse = NULL;	// ���̓f�o�C�X(�}�E�X)�̃|�C���^
CDebugProc *CManager::m_pDebugProc = NULL;		// �f�o�b�O�\���̃|�C���^
CMultiBg *CManager::m_pBg = NULL;		// ���d�w�i�̃|�C���^
CSound *CManager::m_pSound = NULL;		// �T�E���h�̃|�C���^
CScore *CManager::m_pScore = NULL;		// �X�R�A�̃|�C���^
CTime *CManager::m_pTime = NULL;		// �^�C���̃|�C���^
CPlayer *CManager::m_pPlayer = NULL;	// �v���C���[�̃|�C���^
CCamera *CManager::m_pCamera = NULL;	// �J�����̃|�C���^
CLight *CManager::m_pLight = NULL;		// ���C�g�̃|�C���^
CTexture *CManager::m_pTexture = NULL;	// �e�N�X�`���̃|�C���^
CXFile *CManager::m_pModelFile = NULL;	// X�t�@�C�����̃|�C���^
CFileLoad *CManager::m_pFileLoad = NULL;	// �t�@�C���ǂݍ��݂̃|�C���^
CEditor *CManager::m_pEditor = NULL;
CSlow *CManager::m_pSlow = NULL;		// �X���[��Ԃւ̃|�C���^
CObject3D *CManager::m_pObject3D = NULL;
CMeshField *CManager::m_pMeshField = NULL;

//===================================================
// �R���X�g���N�^
//===================================================
CManager::CManager()
{
	
}

//===================================================
// �f�X�g���N�^
//===================================================
CManager::~CManager()
{

}

//===================================================
// ����������
//===================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// �����_���[�̐���
	if (m_pRenderer == NULL)
	{// �g�p���Ă��Ȃ��ꍇ
		m_pRenderer = new CRenderer;
	}

	//����������
	if (m_pRenderer != NULL)
	{// �g�p���Ă���ꍇ
		if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
		{//�����������s�����ꍇ
			return E_FAIL;
		}
	}

	// ���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (m_pInputKeyboard == NULL)
	{// �g�p���Ă��Ȃ��ꍇ
		m_pInputKeyboard = new CInputKeyboard;

		//����������
		if (m_pInputKeyboard != NULL)
		{// �g�p���Ă���ꍇ
			if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
			{//�����������s�����ꍇ
				return E_FAIL;
			}
		}
	}

	// ���̓f�o�C�X(�}�E�X)�̐���
	if (m_pInputMouse == NULL)
	{// �g�p���Ă��Ȃ��ꍇ
		m_pInputMouse = new CInputMouse;

		//����������
		if (m_pInputMouse != NULL)
		{// �g�p���Ă���ꍇ
			if (FAILED(m_pInputMouse->Init(hInstance, hWnd)))
			{//�����������s�����ꍇ
				return E_FAIL;
			}
		}
	}

	// �f�o�b�O�\���̐���
	if (m_pDebugProc == NULL)
	{// �g�p���Ă��Ȃ��ꍇ
		m_pDebugProc = new CDebugProc;
	}

	//����������
	if (m_pDebugProc != NULL)
	{// �g�p���Ă���ꍇ
		m_pDebugProc->Init();
	}

	// �T�E���h�̐���
	if (m_pSound == NULL)
	{// �g�p���Ă��Ȃ��ꍇ
		m_pSound = new CSound;

		// ������
		if (m_pSound != NULL)
		{
			m_pSound->Init(hWnd);
		}
	}

	// �J�����̐���
	if (m_pCamera == NULL)
	{// �g�p���Ă��Ȃ��ꍇ
		m_pCamera = new CCamera;

		// ������
		if (m_pCamera != NULL)
		{
			m_pCamera->Init();
		}
	}

	// ���C�g�̐���
	if (m_pLight == NULL)
	{// �g�p���Ă��Ȃ��ꍇ
		m_pLight = new CLight;

		// ������
		if (m_pLight != NULL)
		{
			m_pLight->Init();
		}
	}

	//�e�N�X�`���̐���
	if (m_pTexture == NULL)
	{// �g�p���Ă��Ȃ��ꍇ
		m_pTexture = new CTexture;

		// �����ǂݍ���
		if (m_pTexture != NULL)
		{
			m_pTexture->Load();
		}
	}

	// X�t�@�C�����̐���
	if (m_pModelFile == NULL)
	{// �g�p���Ă��Ȃ��ꍇ
		m_pModelFile = new CXFile;
	}

	// �X���[���̐���
	if (m_pSlow == NULL)
	{
		m_pSlow = new CSlow;
		m_pSlow->Init();
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

	m_pSound->Play(CSound::LABEL_BGM000);

	// �I�u�W�F�N�g����
	CMeshDome::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20000.0f, 10.0f, 3, 10, 10);
	CMeshCylinder::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 17000.0f, 100.0f, 3, 10, 10);
	CEnemy::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 
		D3DXVECTOR3(0.0f, D3DX_PI * 0.25f, 0.0f), D3DXVECTOR3(-sinf(D3DX_PI * 0.25f) * 1.0f, 0.0f, -cosf(D3DX_PI * 0.25f) * 1.0f), "data\\TXT\\motion_murabito.txt");
	CObjectX *p = CObjectX::Create(D3DXVECTOR3(2500.0f, 0.0f, 2500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data/MODEL/container000.x");

	p->SetType(CObject::TYPE_ENEMYSPAWN);

	//m_pObject3D = CObject3D::Create(D3DXVECTOR3(1000.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//m_pObject3D->BindTexture(-1);
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 
		"data\\TXT\\motion_body.txt", "data\\TXT\\motion_leg.txt", 1);

	// �A�C�e���z�u
	//ItemReset();

	// �X�R�A�̐���
	m_pScore = CScore::Create(D3DXVECTOR3(800.0f, 50.0f, 0.0f));

	// �^�C���̐���
	m_pTime = CTime::Create(D3DXVECTOR3(500.0f, 50.0f, 0.0f));

	return S_OK;
}

//===================================================
// �I������
//===================================================
void CManager::Uninit(void)
{
	// �T�E���h�̒�~
	m_pSound->Stop();

	if (m_pInputKeyboard != NULL)
	{// �g�p���Ă���ꍇ
		// �I������
		m_pInputKeyboard->Uninit();

		delete m_pInputKeyboard;	// �������̊J��

		m_pInputKeyboard = NULL;	// �g�p���Ă��Ȃ���Ԃɂ���
	}

	if (m_pDebugProc != NULL)
	{// �g�p���Ă���ꍇ
		// �I������
		m_pDebugProc->Uninit();

		delete m_pDebugProc;	// �������̊J��

		m_pDebugProc = NULL;	// �g�p���Ă��Ȃ���Ԃɂ���
	}

	if (m_pRenderer != NULL)
	{// �g�p���Ă���ꍇ
		// �I������
		m_pRenderer->Uninit();

		delete m_pRenderer;	// �������̊J��

		m_pRenderer = NULL;	// �g�p���Ă��Ȃ���Ԃɂ���
	}

	if (m_pSound != NULL)
	{// �g�p���Ă���ꍇ
		// �I������
		m_pSound->Uninit();

		delete m_pSound;	// �������̊J��

		m_pSound = NULL;	// �g�p���Ă��Ȃ���Ԃɂ���
	}

	if (m_pScore != NULL)
	{// �g�p���Ă���ꍇ
		// �I������
		m_pScore->Uninit();

		delete m_pScore;	// �������̊J��

		m_pScore = NULL;	// �g�p���Ă��Ȃ���Ԃɂ���
	}

	if (m_pTime != NULL)
	{// �g�p���Ă���ꍇ
		// �I������
		m_pTime->Uninit();

		delete m_pTime;	// �������̊J��

		m_pTime = NULL;	// �g�p���Ă��Ȃ���Ԃɂ���
	}

	// �e�N�X�`���̔p��
	if (m_pTexture != NULL)
	{// �g�p���Ă���ꍇ
		// �I������
		m_pTexture->Unload();

		delete m_pTexture;	// �������̊J��

		m_pTexture = NULL;	// �g�p���Ă��Ȃ���Ԃɂ���
	}

	// X�t�@�C�����̔p��
	if (m_pModelFile != NULL)
	{// �g�p���Ă���ꍇ
		// �I������
		m_pModelFile->Unload();

		delete m_pModelFile;	// �������̊J��

		m_pModelFile = NULL;	// �g�p���Ă��Ȃ���Ԃɂ���
	}

	if (m_pFileLoad != NULL)
	{
		m_pFileLoad->Uninit();

		delete m_pFileLoad;		// �������̊J��
		m_pFileLoad = NULL;
	}

	// �G�f�B�^�[���̔p��
	if (m_pEditor != NULL)
	{// �g�p���Ă���ꍇ
		// �I������
		m_pEditor->Uninit();

		delete m_pEditor;	// �������̊J��

		m_pEditor = NULL;	// �g�p���Ă��Ȃ���Ԃɂ���
	}
}

//===================================================
// �X�V����
//===================================================
void CManager::Update(void)
{
	// �f�o�b�O�\���̍X�V����
	if (m_pDebugProc != NULL)
	{// �g�p���Ă���ꍇ
		m_pDebugProc->Update();
	}

	// �L�[�{�[�h�̍X�V����
	if (m_pInputKeyboard != NULL)
	{// �g�p���Ă���ꍇ
		m_pInputKeyboard->Update();
	}

	// �}�E�X�̍X�V����
	if (m_pInputMouse != NULL)
	{// �g�p���Ă���ꍇ
		m_pInputMouse->Update();
	}


	// �J�����̍X�V����
	if (m_pCamera != NULL)
	{
		m_pCamera->Update();
	}

	// �X���[�̍X�V����
	if (m_pSlow != NULL)
	{
		m_pSlow->Update();
	}

	// �����_���[�̍X�V����
	if (m_pRenderer != NULL)
	{// �g�p���Ă���ꍇ
		CEditor *pEditor = GetEditor();

		if (pEditor == NULL)
		{
			m_pRenderer->Update();
		}
		else if (pEditor != NULL && pEditor->GetUse() == false)
		{
			m_pRenderer->Update();
		}
	}

	// �^�C���̍X�V����
	if (m_pTime != NULL)
	{
		// �^�C���̍X�V
		m_pTime->Update();
	}

	if (m_pInputKeyboard != NULL)
	{// �g�p���Ă���ꍇ
		if (CObject::GetItemNumAll() <= 0)
		{// ����z�u����Ă��Ȃ��ꍇ
			m_pDebugProc->Print("�G�Ĕz�u[F3]\n");
			if (m_pInputKeyboard->GetTrigger(DIK_F3) == true)
			{
				ItemReset();
			}
		}
	}

#ifdef _DEBUG

	// �G�f�B�^�[�̍X�V����
	if (m_pEditor != NULL)
	{
		m_pEditor->Update();
	}

#endif
}

//===================================================
// �`�揈��
//===================================================
void CManager::Draw(void)
{
	// �`�揈��
	if (m_pRenderer != NULL)
	{// �g�p���Ă���ꍇ
		m_pRenderer->Draw();
	}
}

//===================================================
// �����_���[�̎擾
//===================================================
CRenderer *CManager::GetRenderer(void)
{
	return m_pRenderer;
}

//===================================================
// ���̓f�o�C�X�̎擾(�L�[�{�[�h)
//===================================================
CInputKeyboard *CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}

//===================================================
// ���̓f�o�C�X�̎擾(�}�E�X)
//===================================================
CInputMouse *CManager::GetInputMouse(void)
{
	return m_pInputMouse;
}

//===================================================
// �f�o�b�O�\���̎擾
//===================================================
CDebugProc *CManager::GetDebugProc(void)
{
	return m_pDebugProc;
}

//===================================================
// �T�E���h�̎擾
//===================================================
CSound *CManager::GetSound(void)
{
	return m_pSound;
}

//===================================================
// �X�R�A�̎擾
//===================================================
CScore *CManager::GetScore(void)
{
	return m_pScore;
}

//===================================================
// �X�R�A�̎擾
//===================================================
CTime *CManager::GetTime(void)
{
	return m_pTime;
}

//===================================================
// ���d�X�N���[���w�i�̎擾
//===================================================
CMultiBg *CManager::GetMultiBg(void)
{
	return m_pBg;
}

//===================================================
// �v���C���[�̎擾
//===================================================
CPlayer *CManager::GetPlayer(void)
{
	return m_pPlayer;
}

//===================================================
// �A�C�e���̍Ĕz�u
//===================================================
void CManager::ItemReset(void)
{
	CObjectX::Create(D3DXVECTOR3(800.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_pFileLoad->GetModelFileName(0));
	CObjectX::Create(D3DXVECTOR3(800.0f, 0.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_pFileLoad->GetModelFileName(1));
	CObjectX::Create(D3DXVECTOR3(800.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_pFileLoad->GetModelFileName(2));
}

//===================================================
// �J�����̎擾
//===================================================
CCamera *CManager::GetCamera(void)
{
	return m_pCamera;
}

//===================================================
// ���C�g�̎擾
//===================================================
CLight *CManager::GetLight(void)
{
	return m_pLight;
}

//===================================================
// �e�N�X�`���̎擾
//===================================================
CTexture *CManager::GetTexture(void)
{
	return m_pTexture;
}

//===================================================
// X�t�@�C�����̎擾
//===================================================
CXFile *CManager::GetModelFile(void)
{
	return m_pModelFile;
}

//===================================================
// �t�@�C���ǂݍ��݂̎擾
//===================================================
CFileLoad *CManager::GetFileLoad(void)
{
	return m_pFileLoad;
}

//===================================================
// �G�f�B�^�[���̎擾
//===================================================
CEditor *CManager::GetEditor(void)
{
	return m_pEditor;
}

//===================================================
// �X���[���̎擾
//===================================================
CSlow *CManager::GetSlow(void)
{
	return m_pSlow;
}

//===================================================
// 3D�I�u�W�F�N�g�̎擾
//===================================================
CObject3D *CManager::GetObject3D(void)
{
	return m_pObject3D;
}

//===================================================
// ���b�V���t�B�[���h�̎擾
//===================================================
CMeshField *CManager::GetMeshField(void)
{
	return m_pMeshField;
}