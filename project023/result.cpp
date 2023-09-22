//===============================================
//
// リザルト画面の管理処理 [result.cpp]
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
// 静的メンバ変数
//===============================================
CScore *CResult::m_pScore = NULL;
int CResult::m_nScore = 0;

//===============================================
// コンストラクタ
//===============================================
CResult::CResult()
{
	m_pMeshSky = NULL;
}

//===============================================
// デストラクタ
//===============================================
CResult::~CResult()
{

}

//===============================================
// 初期化処理
//===============================================
HRESULT CResult::Init(void)
{
	CObject2D *p = CObject2D::Create(7);
	p->BindTexture(CManager::GetTexture()->Regist("data\\TEXTURE\\result_logo.png"));
	p->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.25f, 0.0f));
	p->SetSize(SCREEN_WIDTH * 0.2f, SCREEN_HEIGHT * 0.1f);
	m_pScore = CScore::Create(D3DXVECTOR3(500.0f, 500.0f, 0.0f));
	m_pScore->Set(m_nScore);

	// オブジェクト生成
	m_pMeshSky = CMeshDome::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20000.0f, 10.0f, 3, 10, 10);
	CMeshCylinder::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 17000.0f, 100.0f, 3, 10, 10);

	// 外部ファイル読み込みの生成
	if (m_pFileLoad == NULL)
	{// 使用していない場合
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
// 終了処理
//===============================================
void CResult::Uninit(void)
{
	m_nScore = 0;

	// スコア
	if (m_pScore != NULL)
	{
		CRanking::SetScore(m_pScore->GetNum());
		m_pScore->Uninit();
		delete m_pScore;	// メモリの開放
		m_pScore = NULL;	// 使用していない状態にする
	}

	if (m_pFileLoad != NULL)
	{
		m_pFileLoad->Uninit();

		delete m_pFileLoad;		// メモリの開放
		m_pFileLoad = NULL;
	}

	m_pMeshSky = NULL;
}

//===============================================
// 更新処理
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
// 描画処理
//===============================================
void CResult::Draw(void)
{
	CScene::Draw();
}
