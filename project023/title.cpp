//===============================================
//
// �^�C�g����ʂ̊Ǘ����� [title.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "title.h"
#include "object2D.h"
#include "texture.h"
#include "manager.h"
#include "main.h"
#include "input.h"
#include "fade.h"

//===============================================
// �ÓI�����o�ϐ�
//===============================================

//===============================================
// �R���X�g���N�^
//===============================================
CTitle::CTitle()
{

}

//===============================================
// �f�X�g���N�^
//===============================================
CTitle::~CTitle()
{

}

//===============================================
// ����������
//===============================================
HRESULT CTitle::Init(void)
{
	CObject2D *p = CObject2D::Create();
	p->BindTexture(CManager::GetTexture()->Regist("data\\TEXTURE\\title_logo.png"));
	p->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
	p->SetSize(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CTitle::Uninit(void)
{
	
}

//===============================================
// �X�V����
//===============================================
void CTitle::Update(void)
{
	CInputPad *pInputPad = CManager::GetInputPad();

	if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) || pInputPad->GetTrigger(CInputPad::BUTTON_A, 0))
	{
		CManager::GetFade()->Set(CScene::MODE_GAME);
	}
}

//===============================================
// �`�揈��
//===============================================
void CTitle::Draw(void)
{
	
}
