//==========================================================
//
// ロックオンの処理 [lockon.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "lockon.h"
#include "manager.h"
#include "texture.h"
#include "debugproc.h"
#include "renderer.h"
#include "objectX.h"
#include "model.h"
#include "camera.h"

//==========================================================
// コンストラクタ
//==========================================================
CLockOn::CLockOn(int nPriOrity) : CObjectBillboard(nPriOrity)
{
	// 値のクリア
	m_bLock = false;
	m_DisL.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_DisL.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_DisR.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_DisR.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fLength = 0.0f;
	m_fAngle = 0.0f;
	m_pMtx = NULL;
}

//==========================================================
// デストラクタ
//==========================================================
CLockOn::~CLockOn()
{

}

//==========================================================
// 初期化処理
//==========================================================
HRESULT CLockOn::Init(void)
{
	// ビルボードの初期化
	CObjectBillboard::Init();

	// 色を変更
	SetVtx(D3DXCOLOR(1.0f, 1.0f, 0.5f, 1.0f));

	return S_OK;
}

//==========================================================
// 終了処理
//==========================================================
void CLockOn::Uninit(void)
{
	// 終了
	CObjectBillboard::Uninit();
}

//==========================================================
// 更新処理
//==========================================================
void CLockOn::Update(void)
{
	if (m_bUse == false)
	{
		return;
	}

	CCamera *pCamera = CManager::GetCamera();		// カメラのポインタ
	D3DXVECTOR3 CamRot = pCamera->GetRotation();	// カメラの角度

	// ロックオン処理
	LockOn();

	if (m_pMtx != NULL)
	{
		m_DisL.pos.x = m_pMtx->_41 + cosf(m_DisL.rot.z + CamRot.y + (-m_fAngle)) * m_fLength;
		m_DisL.pos.y = m_pMtx->_42 + 0.0f;
		m_DisL.pos.z = m_pMtx->_43 + sinf(m_DisL.rot.z + CamRot.y + (-m_fAngle)) * m_fLength;

		m_DisR.pos.x = m_pMtx->_41 + cosf(m_DisR.rot.z + CamRot.y + (m_fAngle)) * m_fLength;
		m_DisR.pos.y = m_pMtx->_42 + 0.0f;
		m_DisR.pos.z = m_pMtx->_43 + sinf(m_DisR.rot.z + CamRot.y + (m_fAngle)) * m_fLength;
	}

	// マトリックス更新
	SetDisMtx(&m_DisL);
	SetDisMtx(&m_DisR);
}

//==========================================================
// 描画処理
//==========================================================
void CLockOn::Draw(void)
{
	if (m_bUse == false || m_bLock == false)
	{
		return;
	}

	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();

	//ライティングをオフにする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//Zテストを無効化する
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	CObjectBillboard::Draw();

	//ライティングをオフにする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//Zテストを有効にする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

//==========================================================
// 範囲設定
//==========================================================
void CLockOn::SetDistance(float fLength, float fAngle)
{
	m_fAngle = fAngle;
	m_fLength = fLength;

	m_DisL.pos.x = sinf(m_DisL.rot.z + D3DX_PI * 0.25f + (-fAngle)) * fLength;
	m_DisL.pos.y = 0.0f;
	m_DisL.pos.z = cosf(m_DisL.rot.z + D3DX_PI * 0.25f + (-fAngle)) * fLength;

	m_DisR.pos.x = sinf(m_DisR.rot.z + D3DX_PI * 0.25f + (fAngle)) * fLength;
	m_DisR.pos.y = 0.0f;
	m_DisR.pos.z = cosf(m_DisR.rot.z + D3DX_PI * 0.25f + (fAngle)) * fLength;
}

//==========================================================
// 生成
//==========================================================
CLockOn *CLockOn::Create(D3DXMATRIX *pMtx)
{
	CLockOn *pLock = NULL;

	// 生成
	pLock = new CLockOn();

	if (pLock == NULL)
	{// 確保できなかった場合
		return NULL;
	}

	// 初期化処理
	pLock->Init();

	// 親のマトリックス設定
	pLock->SetParent(pMtx);

	// テクスチャ指定
	pLock->BindTexture(CTexture::TYPE_LOCKON);

	return pLock;
}

//==========================================================
// ロックオンターゲット設定
//==========================================================
void CLockOn::LockOn(void)
{
	CObject *pOldObj = NULL;
	int nCnt = 0;
	int nCntObj = 0;

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

			if (pObj->GetDeath() == false)
			{
				D3DXVECTOR3 ObjPos = pObj->GetPosition();

				D3DXVECTOR3 vec1, vec2;	//判定用変数
				D3DXVECTOR3 vecToPos;	//判定用変数
				float fMaxField;		//判定用
				float fField, fField2;
				float fRate, fRate2;	//判定用変数

				// プレイヤーから判定距離へのベクトルを求める
				vec1 = D3DXVECTOR3(m_DisL.mtxWorld._41 - m_pMtx->_41, m_DisL.mtxWorld._42 - m_pMtx->_42, m_DisL.mtxWorld._43 - m_pMtx->_43);
				vec2 = D3DXVECTOR3(m_DisR.mtxWorld._41 - m_pMtx->_41, m_DisR.mtxWorld._42 - m_pMtx->_42, m_DisR.mtxWorld._43 - m_pMtx->_43);

				// 現在の座標のベクトルを求める
				vecToPos = D3DXVECTOR3(ObjPos.x - m_pMtx->_41,
					ObjPos.y - m_pMtx->_42,
					ObjPos.z - m_pMtx->_43);

				// 面積を求める
				fMaxField = (vec1.x * vec2.z) - (vec1.z * vec2.x);

				// 現在の位置との面積を求める
				fField = (vecToPos.x * vec2.z) - (vecToPos.z * vec2.x);
				fField2 = (vecToPos.z * vec1.x) - (vecToPos.x * vec1.z);

				// 交点の割合を求める
				fRate = fField / fMaxField;
				fRate2 = fField2 / fMaxField;

				if (fRate >= 0.0f && fRate <= 1.0f && fRate2 >= 0.0f && fRate2 <= 1.0f && (fRate + fRate2) <= 1.0f)
				{// 三角ポリゴンの中にいる
					if (pOldObj != NULL)
					{// 一番近いオブジェクトがある場合

						D3DXVECTOR3 OldPos = pOldObj->GetPosition();

						// 一番近いモデルとプレイヤーの距離を求める
						float fOldObjLength =
							sqrtf((OldPos.x - m_pMtx->_41) * (OldPos.x - m_pMtx->_41)
								+ (OldPos.y - m_pMtx->_42) * (OldPos.y - m_pMtx->_42)
								+ (OldPos.z - m_pMtx->_43) * (OldPos.z - m_pMtx->_43));

						// 今回のモデルとプレイヤーの距離を求める
						float fObjLength =
							sqrtf((ObjPos.x - m_pMtx->_41) * (ObjPos.x - m_pMtx->_41)
								+ (ObjPos.y - m_pMtx->_42) * (ObjPos.y - m_pMtx->_42)
								+ (ObjPos.z - m_pMtx->_43) * (ObjPos.z - m_pMtx->_43));

						if (fObjLength < fOldObjLength)
						{// 今回のモデルの方が近い場合
							pOldObj = pObj;	// 一番近いモデルを変更
						}
					}
					else
					{// 前回モデルを覚えていない場合
						pOldObj = pObj;
					}
				}
			}

			pObj = pObjectNext;	// 次のオブジェクトに移動
		}
	}

	if (pOldObj != NULL)
	{// 使用されている場合
		SetPosition(D3DXVECTOR3(pOldObj->GetPosition().x, pOldObj->GetPosition().y + 30.0f, pOldObj->GetPosition().z));
		SetSize(20.0f, 20.0f);
		m_bLock = true;
		m_pObj = pOldObj;
	}
	else
	{
		m_bLock = false;
		SetSize(0.0f, 0.0f);
		m_pObj = NULL;
	}
}

//==========================================================
// 範囲マトリックス変更
//==========================================================
void CLockOn::SetDisMtx(DISTANCE *pDis)
{
	D3DXMATRIX mtxRot, mtxTrans, mtxParent;	//計算用マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&pDis->mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, pDis->rot.y, pDis->rot.x, pDis->rot.z);
	D3DXMatrixMultiply(&pDis->mtxWorld, &pDis->mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, pDis->pos.x, pDis->pos.y, pDis->pos.z);
	D3DXMatrixMultiply(&pDis->mtxWorld, &pDis->mtxWorld, &mtxTrans);
}

//==========================================================
// 使用する親マトリックスを設定
//==========================================================
void CLockOn::SetParent(D3DXMATRIX *pMtx)
{
	// 親のマトリックスを指定
	m_pMtx = pMtx;
}

//==========================================================
// 使用する親マトリックスを設定
//==========================================================
CObject *CLockOn::GetTag(void)
{
	if (m_pObj != NULL)
	{
		if (m_pObj->GetDeath() == false)
		{
			CObject *pObj = m_pObj;
			return pObj;
		}
	}

	return NULL;
}