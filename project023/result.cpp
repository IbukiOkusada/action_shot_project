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
	CObject2D *p = CObject2D::Create();
	p->BindTexture(CManager::GetTexture()->Regist("data\\TEXTURE\\result_logo.png"));
	p->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
	p->SetSize(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);
	m_pScore = CScore::Create(D3DXVECTOR3(500.0f, 500.0f, 0.0f));
	m_pScore->Set(m_nScore);

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

	CScene::Update();
}

//===============================================
// �`�揈��
//===============================================
void CResult::Draw(void)
{
	CScene::Draw();
}
