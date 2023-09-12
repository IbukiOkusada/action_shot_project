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
#include "pause.h"
#include "result.h"
#include "lockon.h"
#include "meshballoon.h"
#include "editor.h"
#include "thermo.h"
#include "enemy_manager.h"

//===============================================
// マクロ定義
//===============================================
#define START_TIME	(120)	// 制限時間
#define START_SCORE	(0)		// 開始スコア
#define MAP_SIZE	(100.0f)	// マップサイズ
#define STARTSET_NUMENEMY	(30)	// 開始時に配置する敵の数

//===============================================
// 静的メンバ変数
//===============================================
CScore *CGame::m_pScore = NULL;		// スコアのポインタ
CSlow *CGame::m_pSlow = NULL;		// スロー状態へのポインタ
CMeshField *CGame::m_pMeshField = NULL;	// メッシュフィールドのポインタ
CPause *CGame::m_pPause = NULL;		// ポーズのポインタ

//===============================================
// コンストラクタ
//===============================================
CGame::CGame()
{
	m_pMapCamera = NULL;
	m_pMapThermo = NULL;
	m_nMaxEnemy = 0;
	m_pTime = NULL;
	m_pEnemyManager = NULL;
	m_pPlayer = NULL;
	m_pFileLoad = NULL;
	m_pEditor = NULL;
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

	// エディットの生成
	if (m_pEditor == NULL)
	{// 使用していない場合
		m_pEditor = new CEditor;

		// 初期化
		if (m_pEditor != NULL)
		{
			m_pEditor->Init();
		}
	}

	// オブジェクト生成
	CMeshDome::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20000.0f, 10.0f, 3, 10, 10);
	CMeshCylinder::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 17000.0f, 100.0f, 3, 10, 10);
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 3500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		"data\\TXT\\motion_body.txt", "data\\TXT\\motion_leg.txt", 1);

	// スコアの生成
	m_pScore = CScore::Create(D3DXVECTOR3(400.0f, 50.0f, 0.0f));
	m_pScore->Set(START_SCORE);

	// タイムの生成
	m_pTime = CTime::Create(D3DXVECTOR3(800.0f, 50.0f, 0.0f));
	m_pTime->Set(START_TIME);

	CObject2D *pUi = CObject2D::Create(7);
	pUi->SetPosition(D3DXVECTOR3(560.0f, 65.0f, 0.0f));
	pUi->SetSize(25, 30);
	pUi->BindTexture(CManager::GetTexture()->Regist("data\\TEXTURE\\target000.png"));

	pUi = CObject2D::Create(7);
	pUi->SetPosition(D3DXVECTOR3(MAP_SIZE, MAP_SIZE, 0.0f));
	pUi->SetSize(MAP_SIZE, MAP_SIZE);
	pUi->BindTexture(CManager::GetTexture()->Regist("data\\TEXTURE\\map000.png"));

	// マップの生成
	if (m_pMapThermo == NULL)
	{
		m_pMapThermo = CThermo::Create();
		m_pMapThermo->BindTexture(CManager::GetTexture()->Regist("data\\TEXTURE\\thermo000.jpg"));
		m_pMapThermo->SetColor(D3DXCOLOR(0.7f, 0.05f, 0.05f, 0.0f));
		m_pMapThermo->SetpVtx(8000.0f, 8000.0f);
	}

	// ポーズの生成
	if (m_pPause == NULL)
	{
		m_pPause = CPause::Create();
	}

	CManager::GetCamera()->SetMode(CCamera::MODE_NORMAL);

	m_nMaxEnemy = CObject::GetNumEnemAll();

	// ミニマップ用カメラを生成
	if (m_pMapCamera == NULL)
	{// 使用していない場合
		m_pMapCamera = new CMapCamera;

		// 初期化
		if (m_pMapCamera != NULL)
		{
			D3DVIEWPORT9 viewport;
			//プレイヤー追従カメラの画面位置設定
			viewport.X = 0;
			viewport.Y = 0;
			viewport.Width = 200;
			viewport.Height = 200;
			viewport.MinZ = 0.0f;
			viewport.MaxZ = 0.1f;
			m_pMapCamera->Init();
			m_pMapCamera->SetLength(10000.0f);
			m_pMapCamera->SetRotation(D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.00001f));
			m_pMapCamera->SetViewPort(viewport);
		}
	}

	// エネミーマネージャーを生成
	if (m_pEnemyManager == NULL)
	{
		m_pEnemyManager = new CEnemyManager;
		m_pEnemyManager->Init();
		m_pEnemyManager->Spawn(STARTSET_NUMENEMY);
	}

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

	// エネミーマネージャー
	if (m_pEnemyManager == NULL)
	{
		m_pEnemyManager->Uninit();
		delete m_pEnemyManager;
		m_pEnemyManager = NULL;
	}

	// スコア
	if (m_pScore != NULL)
	{
		CResult::SetScore(m_pScore->GetNum());
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
	if (m_pPause != NULL)
	{
		m_pPause->Uninit();
		delete m_pPause;	// メモリの開放
		m_pPause = NULL;	// 使用していない状態にする
	}

	// エディター情報の廃棄
	if (m_pEditor != NULL)
	{// 使用している場合
		
		m_pEditor->Uninit();
		delete m_pEditor;	// メモリの開放
		m_pEditor = NULL;	// 使用していない状態にする
	}

	// ミニマップカメラ
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

	m_pScore = NULL;		// スコアのポインタ
	m_pTime = NULL;		// タイムのポインタ
	m_pPlayer = NULL;	// プレイヤーのポインタ
	m_pMeshField = NULL;
	m_pFileLoad = NULL;
}

//===============================================
// 更新処理
//===============================================
void CGame::Update(void)
{
	// ポーズ
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

#if _DEBUG

	// エディターの更新処理
	if (m_pEditor != NULL)
	{
		m_pEditor->Update();
	}

	if (m_pEditor->GetActive() == true || m_pEditor->GetMeshActive() == true)
	{
		// 更新処理
		CScene::Update();
		return;
	}

#endif

	// タイム
	if (m_pTime != NULL)
	{
		m_pTime->Update();
		if (m_pTime->GetNum() <= 0)
		{// 時間切れ
			CManager::GetFade()->Set(CScene::MODE_RESULT);
		}
	}

	// 残り人数
	if (m_pScore != NULL)
	{
		m_pScore->Update();
	}

	if (m_pMapThermo != NULL)
	{
		D3DXCOLOR col = m_pMapThermo->GetCol();
		if (m_nMaxEnemy > 0)
		{// 一体でも存在している
			col.a = 1.0f - (float)(CObject::GetNumEnemAll() / m_nMaxEnemy);
		}
		else
		{
			col.a = 1.0f;
		}
		m_pMapThermo->SetColor(col);
	}

	if (CManager::GetSlow()->Get() == 1.0f && CManager::GetSlow()->GetOld() != 1.0f)
	{
		CLockOn::MultiDeath();
	}

	// 更新処理
	CScene::Update();

	// 敵の配置管理
	EnemySet();
}

//===============================================
// 描画処理
//===============================================
void CGame::Draw(void)
{
	CScene::Draw();

	// ポーズ
	if (m_pPause != NULL)
	{
		m_pPause->Draw();
	}
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
// ポーズの取得
//===================================================
CPause *CGame::GetPause(void)
{
	return m_pPause;
}

//===================================================
// エディター情報の取得
//===================================================
CEditor *CGame::GetEditor(void)
{
	return m_pEditor;
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

//===================================================
// 敵の配置
//===================================================
void CGame::EnemySet(void)
{
	if (m_pEnemyManager != NULL)
	{
		m_pEnemyManager->Update();
	}
}