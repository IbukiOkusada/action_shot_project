//===============================================
//
// ゲーム画面の管理処理 [game.cpp]
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

//===============================================
// 静的メンバ変数
//===============================================
CScore *CGame::m_pScore = NULL;		// スコアのポインタ
CTime *CGame::m_pTime = NULL;		// タイムのポインタ
CPlayer *CGame::m_pPlayer = NULL;	// プレイヤーのポインタ
CSlow *CGame::m_pSlow = NULL;		// スロー状態へのポインタ
CMeshField *CGame::m_pMeshField = NULL;
CFileLoad *CGame::m_pFileLoad = NULL;

//===============================================
// コンストラクタ
//===============================================
CGame::CGame()
{

}

//===============================================
// デストラクタ
//===============================================
CGame::~CGame()
{

}

//===============================================
// 初期化処理
//===============================================
HRESULT CGame::Init(void)
{
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

	// オブジェクト生成
	CMeshDome::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20000.0f, 10.0f, 3, 10, 10);
	CMeshCylinder::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 17000.0f, 100.0f, 3, 10, 10);
	CEnemy::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, D3DX_PI * 0.25f, 0.0f), D3DXVECTOR3(-sinf(D3DX_PI * 0.25f) * 1.0f, 0.0f, -cosf(D3DX_PI * 0.25f) * 1.0f), "data\\TXT\\motion_murabito.txt");
	CObjectX *p = CObjectX::Create(D3DXVECTOR3(2500.0f, 0.0f, 2500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data/MODEL/container000.x");
	p->SetType(CObject::TYPE_ENEMYSPAWN);
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 3500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		"data\\TXT\\motion_body.txt", "data\\TXT\\motion_leg.txt", 1);

	// スコアの生成
	m_pScore = CScore::Create(D3DXVECTOR3(800.0f, 50.0f, 0.0f));

	// タイムの生成
	m_pTime = CTime::Create(D3DXVECTOR3(500.0f, 50.0f, 0.0f));
	m_pTime->Set(120);

	return S_OK;
}

//===============================================
// 終了処理
//===============================================
void CGame::Uninit(void)
{
	if (m_pFileLoad != NULL)
	{
		m_pFileLoad->Uninit();

		delete m_pFileLoad;		// メモリの開放
		m_pFileLoad = NULL;
	}

	// スコア
	if (m_pScore != NULL)
	{
		m_pScore->Uninit();
		delete m_pScore;	// メモリの開放
		m_pScore = NULL;	// 使用していない状態にする
	}

	// タイム
	if (m_pTime != NULL)
	{
		m_pTime->Uninit();
		delete m_pTime;	// メモリの開放
		m_pTime = NULL;	// 使用していない状態にする
	}

	// スロー
	if (m_pSlow != NULL)
	{
		m_pSlow->Uninit();
		delete m_pSlow;	// メモリの開放
		m_pSlow = NULL;	// 使用していない状態にする
	}

	m_pScore = NULL;		// スコアのポインタ
	m_pTime = NULL;		// タイムのポインタ
	m_pPlayer = NULL;	// プレイヤーのポインタ
	m_pSlow = NULL;		// スロー状態へのポインタ
	m_pMeshField = NULL;
	m_pFileLoad = NULL;
}

//===============================================
// 更新処理
//===============================================
void CGame::Update(void)
{
	// スロー
	if (m_pSlow != NULL)
	{
		m_pSlow->Update();
	}

	// タイム
	if (m_pTime != NULL)
	{
		m_pTime->Update();
		if (m_pTime->GetNum() <= 0)
		{// 時間切れ
			CManager::GetFade()->Set(CScene::MODE_RESULT);
		}
	}

	/*if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN))
	{
		CManager::GetFade()->Set(CScene::MODE_RESULT);
	}*/
}

//===============================================
// 描画処理
//===============================================
void CGame::Draw(void)
{
	
}

//===================================================
// スコアの取得
//===================================================
CScore *CGame::GetScore(void)
{
	return m_pScore;
}

//===================================================
// スコアの取得
//===================================================
CTime *CGame::GetTime(void)
{
	return m_pTime;
}

//===================================================
// プレイヤーの取得
//===================================================
CPlayer *CGame::GetPlayer(void)
{
	return m_pPlayer;
}

//===================================================
// スロー情報の取得
//===================================================
CSlow *CGame::GetSlow(void)
{
	return m_pSlow;
}

//===================================================
// メッシュフィールドの取得
//===================================================
CMeshField *CGame::GetMeshField(void)
{
	return m_pMeshField;
}

//===================================================
// ファイル読み込みの取得
//===================================================
CFileLoad *CGame::GetFileLoad(void)
{
	return m_pFileLoad;
}

//===================================================
// 読み込みデータリセット
//===================================================
void CGame::DataReset(void)
{
	// 終了
	if (m_pFileLoad != NULL)
	{
		m_pFileLoad->Uninit();

		delete m_pFileLoad;		// メモリの開放
		m_pFileLoad = NULL;
	}

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
}