//===============================================
//
// タイトル画面の管理処理 [title.cpp]
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
// 静的メンバ変数
//===============================================

//===============================================
// コンストラクタ
//===============================================
CTitle::CTitle()
{

}

//===============================================
// デストラクタ
//===============================================
CTitle::~CTitle()
{

}

//===============================================
// 初期化処理
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
// 終了処理
//===============================================
void CTitle::Uninit(void)
{
	
}

//===============================================
// 更新処理
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
// 描画処理
//===============================================
void CTitle::Draw(void)
{
	
}
