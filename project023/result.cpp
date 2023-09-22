//===============================================
//
// ���U���g��ʂ̊Ǘ����� [result.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "result.h"
#include "object2D.h"
#include "texture.h"
#include "manager.h"
#include "main.h"
#include "input.h"
#include "objectX.h"
#include "fade.h"
#include "score.h"
#include "ranking.h"
#include "fileload.h"
#include "meshdome.h"
#include "meshcylinder.h"
#include "sound.h"

//===============================================
// �ÓI�����o�ϐ�
//===============================================
CScore *CResult::m_pScore = NULL;
int CResult::m_nScore = 0;

//===============================================
// �R���X�g���N�^
//===============================================
CResult::CResult()
{
	m_pMeshSky = NULL;
}

//===============================================
// �f�X�g���N�^
//===============================================
CResult::~CResult()
{

}

//===============================================
// ����������
//===============================================
HRESULT CResult::Init(void)
{
	CObject2D *p = CObject2D::Create(7);
	p->BindTexture(CManager::GetTexture()->Regist("data\\TEXTURE\\result_logo.png"));
	p->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.25f, 0.0f));
	p->SetSize(SCREEN_WIDTH * 0.2f, SCREEN_HEIGHT * 0.1f);
	m_pScore = CScore::Create(D3DXVECTOR3(500.0f, 500.0f, 0.0f));
	m_pScore->Set(m_nScore);

	// �I�u�W�F�N�g����
	m_pMeshSky = CMeshDome::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20000.0f, 10.0f, 3, 10, 10);
	CMeshCylinder::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 17000.0f, 100.0f, 3, 10, 10);

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

	CManager::GetSound()->Play(CSound::LABEL_BGM_RESULT);

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CResult::Uninit(void)
{
	m_nScore = 0;

	// �X�R�A
	if (m_pScore != NULL)
	{
		CRanking::SetScore(m_pScore->GetNum());
		m_pScore->Uninit();
		delete m_pScore;	// �������̊J��
		m_pScore = NULL;	// �g�p���Ă��Ȃ���Ԃɂ���
	}

	if (m_pFileLoad != NULL)
	{
		m_pFileLoad->Uninit();

		delete m_pFileLoad;		// �������̊J��
		m_pFileLoad = NULL;
	}

	m_pMeshSky = NULL;
}

//===============================================
// �X�V����
//===============================================
void CResult::Update(void)
{
	CInputPad *pInputPad = CManager::GetInputPad();

	if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) || pInputPad->GetTrigger(CInputPad::BUTTON_A, 0))
	{
		CManager::GetFade()->Set(CScene::MODE_RANKING);
	}

	m_pMeshSky->SetColor(0.9f);

	CScene::Update();
}

//===============================================
// �`�揈��
//===============================================
void CResult::Draw(void)
{
	CScene::Draw();
}
