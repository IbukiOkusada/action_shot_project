//==========================================================
//
// スロー中のロックオン処理 [slow_lockon.h]
// Author : Ibuki Okusada
//
//==========================================================
#include "slow_lockon.h"
#include "lockon.h"
#include "manager.h"
#include "texture.h"
#include "debugproc.h"
#include "renderer.h"
#include "objectX.h"
#include "model.h"
#include "camera.h"
#include "slow.h"
#include "enemy.h"
#include "game.h"
#include "meshfield.h"
#include "object2D.h"
#include "character.h"

#define DEF_LENGTH	(5000)	// デフォルト距離
#define DEF_SIZE	(70)

//==========================================================
// コンストラクタ
//==========================================================
CSlowLock::CSlowLock(int nPriOrity) : CObject3D(nPriOrity)
{
	// 値のクリア
	m_fLength = 0.0f;
}

//==========================================================
// デストラクタ
//==========================================================
CSlowLock::~CSlowLock()
{

}

//==========================================================
// 初期化処理
//==========================================================
HRESULT CSlowLock::Init(void)
{
	// ビルボードの初期化
	CObject3D::Init();
	
	SetpVtx(DEF_SIZE, DEF_SIZE);
	m_fLength = DEF_SIZE;

	CObject2D *p = CObject2D::Create(7);

	p->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
	p->SetSize(SCREEN_WIDTH * 0.1f, SCREEN_HEIGHT * 0.1f);
	p->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f));

	return S_OK;
}

//==========================================================
// 終了処理
//==========================================================
void CSlowLock::Uninit(void)
{
	// 終了
	CObject3D::Uninit();
}

//==========================================================
// 更新処理
//==========================================================
void CSlowLock::Update(void)
{
	CCamera *pCamera = CManager::GetCamera();		// カメラのポインタ
	D3DXVECTOR3 CamRot = pCamera->GetRotation();	// カメラの角度

	if (CManager::GetSlow()->Get() != 1.0f)
	{
		// 角度調整
		Controller();

		// ロックオン処理
		LockOn();
	}
}

//==========================================================
// 描画処理
//==========================================================
void CSlowLock::Draw(void)
{
	if (CManager::GetSlow()->Get() == 1.0f)
	{
		return;
	}

	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();

	//CObject3D::Draw();
}

//==========================================================
// 生成
//==========================================================
CSlowLock *CSlowLock::Create(void)
{
	CSlowLock *pLock = NULL;

	// 生成
	pLock = new CSlowLock();

	if (pLock == NULL)
	{// 確保できなかった場合
		return NULL;
	}

	// 初期化処理
	pLock->Init();

	// テクスチャ指定
	pLock->BindTexture(CTexture::TYPE_SLOWLOCK);

	return pLock;
}

//==========================================================
// ロックオンターゲット設定
//==========================================================
void CSlowLock::LockOn(void)
{
	CEnemy *pEnemy = NULL;
	int nCnt = 0;
	int nCntObj = 0;
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ
	D3DXMATRIX mtxProjection;
	D3DXMATRIX mtxView;
	D3DXMATRIX mtxWorld;
	D3DXVECTOR3 EnemyPos;
	D3DXVECTOR3 ScreenPos;
	D3DVIEWPORT9 Viewport;

	//デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();

	pDevice->GetTransform(D3DTS_PROJECTION, &mtxProjection);
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);
	pDevice->GetViewport(&Viewport);

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		CObject *pObj = CObject::GetTop(nCntPri);	// 先頭を取得

		while (pObj != NULL)
		{// 使用されていない状態まで

			CObject *pObjectNext = pObj->GetNext();	// 次のオブジェクトへのポインタを取得

			if (pObj == NULL)
			{// 使用されていない場合
				pObj = pObjectNext;	// 次のオブジェクトに移動
				continue;
			}

			if (pObj->GetType() != CObject::TYPE_ENEMY)
			{// 種類がモデルではない場合
				pObj = pObjectNext;	// 次のオブジェクトに移動
				continue;
			}

			if (pObj->GetDeath() == true)
			{
				pObj = pObjectNext;	// 次のオブジェクトに移動
				continue;
			}

			pEnemy = pObj->GetEnemy();

			if (pEnemy == NULL)
			{
				pObj = pObjectNext;	// 次のオブジェクトに移動
				continue;
			}

			EnemyPos.x = pEnemy->GetBody()->GetParts(0)->GetMtxWorld()->_41;
			EnemyPos.y = pEnemy->GetBody()->GetParts(0)->GetMtxWorld()->_42;
			EnemyPos.z = pEnemy->GetBody()->GetParts(0)->GetMtxWorld()->_43;

			D3DXVec3Project(&ScreenPos, &EnemyPos, &Viewport, &mtxProjection, &mtxView, &mtxWorld);

			//CManager::GetDebugProc()->Print("エネミーのスクリーン座標[%f, %f, %f]\n", ScreenPos.x, ScreenPos.y, ScreenPos.z);
			//CManager::GetDebugProc()->Print("判定範囲[MIN %f, %f, MAX %f, %f]\n", SCREEN_WIDTH * 0.45f, SCREEN_HEIGHT * 0.45f, SCREEN_WIDTH * 0.55f, SCREEN_HEIGHT * 0.55f);
			if (ScreenPos.x < SCREEN_WIDTH * 0.4f || ScreenPos.x > SCREEN_WIDTH * 0.6f ||
				ScreenPos.y < SCREEN_HEIGHT * 0.4f || ScreenPos.y > SCREEN_HEIGHT * 0.6f || ScreenPos.z >= 1.0f)
			{// 画面に描画されていない
				pObj = pObjectNext;	// 次のオブジェクトに移動
				pEnemy = NULL;
				continue;
			}

			CLockOn *pLock = CLockOn::GetTop();	// 先頭を取得

			while (pLock != NULL)
			{// 使用されている間繰り返し
				CLockOn *pLockNext = pLock->GetNext();	// 次を保持

				if (pLock->GetDeath() == false && pLock->GetType() == CLockOn::TYPE_MULTI)
				{
					CEnemy *pLockEnemy = pLock->GetEnemy();
					if (pLockEnemy == pEnemy)
					{// 同じ標的の場合
						pEnemy = NULL;
						break;
					}
				}

				pLock = pLockNext;	// 次に移動
			}

			if (pEnemy != NULL)
			{
				break;
			}

			pObj = pObjectNext;	// 次のオブジェクトに移動
		}
	}

	if (pEnemy != NULL)
	{// 使用されている場合

		CLockOn *pLock = CLockOn::Create(pEnemy->GetMtx(), CLockOn::TYPE_MULTI);
		pLock->SetTag(pEnemy);
		pLock->SetCol(D3DXCOLOR(0.0f, 1.0f, 0.5f, 0.3f));
	}
}

//==========================================================
// 操作関連
//==========================================================
void CSlowLock::Controller(void)
{
	CCamera *pCamera = CManager::GetCamera();

	D3DXVECTOR3 CamRot = pCamera->GetRotation();
	D3DXVECTOR3 CamPosV = pCamera->GetPositionV();
	D3DXVECTOR3 CamPosR = pCamera->GetPositionR();
	D3DXVECTOR3 nor = (CamPosR - CamPosV);
	D3DXVECTOR3 vec;
	D3DXVec3Normalize(&vec, &nor);	// ベクトルを保存

	float fRotDiff = (float)((CamRot.z - MIN_CAMERA_ROTZ) / (MAX_CAMERA_ROTZ - MIN_CAMERA_ROTZ));

	float fPosYDiff = CamPosR.y * 0.1f;

	SetPosition(D3DXVECTOR3(CamPosR.x + (vec.x * (DEF_LENGTH + CamPosR.y * 0.5f)) * fRotDiff, 0.0f, CamPosR.z + (vec.z * (DEF_LENGTH + CamPosR.y * 0.5f)) * fRotDiff));

	D3DXVECTOR3 pos = GetPosition();

	if (pos.z + m_fLength >= 3600.0f)
	{
		pos.z = 3600.0f - m_fLength;
	}
	else if (pos.z - m_fLength <= -3600.0f)
	{
		pos.z = -3600.0f + m_fLength;
	}

	if (pos.x + m_fLength >= 3900.0f)
	{
		pos.x = 3900.0f - m_fLength;
	}
	else if (pos.x - m_fLength <= -3450.0f)
	{
		pos.x = -3450.0f + m_fLength;
	}


	if (CGame::GetMeshField() != NULL)
	{
		float fHeight = CGame::GetMeshField()->GetHeight(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		pos.y = fHeight;
	}

	SetPosition(pos);

	m_fLength = DEF_SIZE + fPosYDiff;

	SetpVtx(m_fLength, m_fLength);

	//CManager::GetDebugProc()->Print("スローロックオンベクトル[%f, %f, %f]\n", nor.x, nor.y, nor.z);
	//CManager::GetDebugProc()->Print("スローロックオン座標[%f, %f, %f]\n", GetPosition().x, GetPosition().y, GetPosition().z);
}