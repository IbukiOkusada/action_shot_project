//===============================================
//
// マネージャーの処理 [manager.cpp]
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
// 静的メンバ変数
//===============================================
CRenderer *CManager::m_pRenderer = NULL;		// レンダラーのポインタ
CInputKeyboard *CManager::m_pInputKeyboard = NULL;	// 入力デバイス(キーボード)へのポインタ
CInputMouse *CManager::m_pInputMouse = NULL;	// 入力デバイス(マウス)のポインタ
CDebugProc *CManager::m_pDebugProc = NULL;		// デバッグ表示のポインタ
CMultiBg *CManager::m_pBg = NULL;		// 多重背景のポインタ
CSound *CManager::m_pSound = NULL;		// サウンドのポインタ
CScore *CManager::m_pScore = NULL;		// スコアのポインタ
CTime *CManager::m_pTime = NULL;		// タイムのポインタ
CPlayer *CManager::m_pPlayer = NULL;	// プレイヤーのポインタ
CCamera *CManager::m_pCamera = NULL;	// カメラのポインタ
CLight *CManager::m_pLight = NULL;		// ライトのポインタ
CTexture *CManager::m_pTexture = NULL;	// テクスチャのポインタ
CXFile *CManager::m_pModelFile = NULL;	// Xファイル情報のポインタ
CFileLoad *CManager::m_pFileLoad = NULL;	// ファイル読み込みのポインタ
CEditor *CManager::m_pEditor = NULL;
CSlow *CManager::m_pSlow = NULL;		// スロー状態へのポインタ
CObject3D *CManager::m_pObject3D = NULL;
CMeshField *CManager::m_pMeshField = NULL;

//===================================================
// コンストラクタ
//===================================================
CManager::CManager()
{
	
}

//===================================================
// デストラクタ
//===================================================
CManager::~CManager()
{

}

//===================================================
// 初期化処理
//===================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// レンダラーの生成
	if (m_pRenderer == NULL)
	{// 使用していない場合
		m_pRenderer = new CRenderer;
	}

	//初期化処理
	if (m_pRenderer != NULL)
	{// 使用している場合
		if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
		{//初期化が失敗した場合
			return E_FAIL;
		}
	}

	// 入力デバイス(キーボード)の生成
	if (m_pInputKeyboard == NULL)
	{// 使用していない場合
		m_pInputKeyboard = new CInputKeyboard;

		//初期化処理
		if (m_pInputKeyboard != NULL)
		{// 使用している場合
			if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
			{//初期化が失敗した場合
				return E_FAIL;
			}
		}
	}

	// 入力デバイス(マウス)の生成
	if (m_pInputMouse == NULL)
	{// 使用していない場合
		m_pInputMouse = new CInputMouse;

		//初期化処理
		if (m_pInputMouse != NULL)
		{// 使用している場合
			if (FAILED(m_pInputMouse->Init(hInstance, hWnd)))
			{//初期化が失敗した場合
				return E_FAIL;
			}
		}
	}

	// デバッグ表示の生成
	if (m_pDebugProc == NULL)
	{// 使用していない場合
		m_pDebugProc = new CDebugProc;
	}

	//初期化処理
	if (m_pDebugProc != NULL)
	{// 使用している場合
		m_pDebugProc->Init();
	}

	// サウンドの生成
	if (m_pSound == NULL)
	{// 使用していない場合
		m_pSound = new CSound;

		// 初期化
		if (m_pSound != NULL)
		{
			m_pSound->Init(hWnd);
		}
	}

	// カメラの生成
	if (m_pCamera == NULL)
	{// 使用していない場合
		m_pCamera = new CCamera;

		// 初期化
		if (m_pCamera != NULL)
		{
			m_pCamera->Init();
		}
	}

	// ライトの生成
	if (m_pLight == NULL)
	{// 使用していない場合
		m_pLight = new CLight;

		// 初期化
		if (m_pLight != NULL)
		{
			m_pLight->Init();
		}
	}

	//テクスチャの生成
	if (m_pTexture == NULL)
	{// 使用していない場合
		m_pTexture = new CTexture;

		// 初期読み込み
		if (m_pTexture != NULL)
		{
			m_pTexture->Load();
		}
	}

	// Xファイル情報の生成
	if (m_pModelFile == NULL)
	{// 使用していない場合
		m_pModelFile = new CXFile;
	}

	// スロー情報の生成
	if (m_pSlow == NULL)
	{
		m_pSlow = new CSlow;
		m_pSlow->Init();
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

	m_pSound->Play(CSound::LABEL_BGM000);

	// オブジェクト生成
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

	// アイテム配置
	//ItemReset();

	// スコアの生成
	m_pScore = CScore::Create(D3DXVECTOR3(800.0f, 50.0f, 0.0f));

	// タイムの生成
	m_pTime = CTime::Create(D3DXVECTOR3(500.0f, 50.0f, 0.0f));

	return S_OK;
}

//===================================================
// 終了処理
//===================================================
void CManager::Uninit(void)
{
	// サウンドの停止
	m_pSound->Stop();

	if (m_pInputKeyboard != NULL)
	{// 使用している場合
		// 終了処理
		m_pInputKeyboard->Uninit();

		delete m_pInputKeyboard;	// メモリの開放

		m_pInputKeyboard = NULL;	// 使用していない状態にする
	}

	if (m_pDebugProc != NULL)
	{// 使用している場合
		// 終了処理
		m_pDebugProc->Uninit();

		delete m_pDebugProc;	// メモリの開放

		m_pDebugProc = NULL;	// 使用していない状態にする
	}

	if (m_pRenderer != NULL)
	{// 使用している場合
		// 終了処理
		m_pRenderer->Uninit();

		delete m_pRenderer;	// メモリの開放

		m_pRenderer = NULL;	// 使用していない状態にする
	}

	if (m_pSound != NULL)
	{// 使用している場合
		// 終了処理
		m_pSound->Uninit();

		delete m_pSound;	// メモリの開放

		m_pSound = NULL;	// 使用していない状態にする
	}

	if (m_pScore != NULL)
	{// 使用している場合
		// 終了処理
		m_pScore->Uninit();

		delete m_pScore;	// メモリの開放

		m_pScore = NULL;	// 使用していない状態にする
	}

	if (m_pTime != NULL)
	{// 使用している場合
		// 終了処理
		m_pTime->Uninit();

		delete m_pTime;	// メモリの開放

		m_pTime = NULL;	// 使用していない状態にする
	}

	// テクスチャの廃棄
	if (m_pTexture != NULL)
	{// 使用している場合
		// 終了処理
		m_pTexture->Unload();

		delete m_pTexture;	// メモリの開放

		m_pTexture = NULL;	// 使用していない状態にする
	}

	// Xファイル情報の廃棄
	if (m_pModelFile != NULL)
	{// 使用している場合
		// 終了処理
		m_pModelFile->Unload();

		delete m_pModelFile;	// メモリの開放

		m_pModelFile = NULL;	// 使用していない状態にする
	}

	if (m_pFileLoad != NULL)
	{
		m_pFileLoad->Uninit();

		delete m_pFileLoad;		// メモリの開放
		m_pFileLoad = NULL;
	}

	// エディター情報の廃棄
	if (m_pEditor != NULL)
	{// 使用している場合
		// 終了処理
		m_pEditor->Uninit();

		delete m_pEditor;	// メモリの開放

		m_pEditor = NULL;	// 使用していない状態にする
	}
}

//===================================================
// 更新処理
//===================================================
void CManager::Update(void)
{
	// デバッグ表示の更新処理
	if (m_pDebugProc != NULL)
	{// 使用している場合
		m_pDebugProc->Update();
	}

	// キーボードの更新処理
	if (m_pInputKeyboard != NULL)
	{// 使用している場合
		m_pInputKeyboard->Update();
	}

	// マウスの更新処理
	if (m_pInputMouse != NULL)
	{// 使用している場合
		m_pInputMouse->Update();
	}


	// カメラの更新処理
	if (m_pCamera != NULL)
	{
		m_pCamera->Update();
	}

	// スローの更新処理
	if (m_pSlow != NULL)
	{
		m_pSlow->Update();
	}

	// レンダラーの更新処理
	if (m_pRenderer != NULL)
	{// 使用している場合
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

	// タイムの更新処理
	if (m_pTime != NULL)
	{
		// タイムの更新
		m_pTime->Update();
	}

	if (m_pInputKeyboard != NULL)
	{// 使用している場合
		if (CObject::GetItemNumAll() <= 0)
		{// 一つも配置されていない場合
			m_pDebugProc->Print("敵再配置[F3]\n");
			if (m_pInputKeyboard->GetTrigger(DIK_F3) == true)
			{
				ItemReset();
			}
		}
	}

#ifdef _DEBUG

	// エディターの更新処理
	if (m_pEditor != NULL)
	{
		m_pEditor->Update();
	}

#endif
}

//===================================================
// 描画処理
//===================================================
void CManager::Draw(void)
{
	// 描画処理
	if (m_pRenderer != NULL)
	{// 使用している場合
		m_pRenderer->Draw();
	}
}

//===================================================
// レンダラーの取得
//===================================================
CRenderer *CManager::GetRenderer(void)
{
	return m_pRenderer;
}

//===================================================
// 入力デバイスの取得(キーボード)
//===================================================
CInputKeyboard *CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}

//===================================================
// 入力デバイスの取得(マウス)
//===================================================
CInputMouse *CManager::GetInputMouse(void)
{
	return m_pInputMouse;
}

//===================================================
// デバッグ表示の取得
//===================================================
CDebugProc *CManager::GetDebugProc(void)
{
	return m_pDebugProc;
}

//===================================================
// サウンドの取得
//===================================================
CSound *CManager::GetSound(void)
{
	return m_pSound;
}

//===================================================
// スコアの取得
//===================================================
CScore *CManager::GetScore(void)
{
	return m_pScore;
}

//===================================================
// スコアの取得
//===================================================
CTime *CManager::GetTime(void)
{
	return m_pTime;
}

//===================================================
// 多重スクロール背景の取得
//===================================================
CMultiBg *CManager::GetMultiBg(void)
{
	return m_pBg;
}

//===================================================
// プレイヤーの取得
//===================================================
CPlayer *CManager::GetPlayer(void)
{
	return m_pPlayer;
}

//===================================================
// アイテムの再配置
//===================================================
void CManager::ItemReset(void)
{
	CObjectX::Create(D3DXVECTOR3(800.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_pFileLoad->GetModelFileName(0));
	CObjectX::Create(D3DXVECTOR3(800.0f, 0.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_pFileLoad->GetModelFileName(1));
	CObjectX::Create(D3DXVECTOR3(800.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_pFileLoad->GetModelFileName(2));
}

//===================================================
// カメラの取得
//===================================================
CCamera *CManager::GetCamera(void)
{
	return m_pCamera;
}

//===================================================
// ライトの取得
//===================================================
CLight *CManager::GetLight(void)
{
	return m_pLight;
}

//===================================================
// テクスチャの取得
//===================================================
CTexture *CManager::GetTexture(void)
{
	return m_pTexture;
}

//===================================================
// Xファイル情報の取得
//===================================================
CXFile *CManager::GetModelFile(void)
{
	return m_pModelFile;
}

//===================================================
// ファイル読み込みの取得
//===================================================
CFileLoad *CManager::GetFileLoad(void)
{
	return m_pFileLoad;
}

//===================================================
// エディター情報の取得
//===================================================
CEditor *CManager::GetEditor(void)
{
	return m_pEditor;
}

//===================================================
// スロー情報の取得
//===================================================
CSlow *CManager::GetSlow(void)
{
	return m_pSlow;
}

//===================================================
// 3Dオブジェクトの取得
//===================================================
CObject3D *CManager::GetObject3D(void)
{
	return m_pObject3D;
}

//===================================================
// メッシュフィールドの取得
//===================================================
CMeshField *CManager::GetMeshField(void)
{
	return m_pMeshField;
}