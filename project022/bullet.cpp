//===============================================
//
// 弾の処理 [bullet.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "bullet.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "debugproc.h"
#include "explosion.h"
#include "enemy.h"
#include "effect.h"
#include "particle.h"
#include "sound.h"
#include "score.h"
#include "texture.h"
#include "objectX.h"
#include "Xfile.h"
#include "slow.h"

//===============================================
// マクロ定義
//===============================================
#define LIFE	(120.0f)		// 寿命

// 静的メンバ変数
CBullet *CBullet::m_pTop = NULL;	// 先頭のオブジェクトへのポインタ
CBullet *CBullet::m_pCur = NULL;	// 最後尾のオブジェクトへのポインタ
int CBullet::m_nNumAll = 0;

//===============================================
// コンストラクタ
//===============================================
CBullet::CBullet()
{
	// 値のクリア
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fLife = 0.0f;
}

//===============================================
// コンストラクタ(オーバーロード)
//===============================================
CBullet::CBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	// 値のクリア
	SetPosition(pos);
	m_fLife = 0.0f;
	m_move = move;
	m_pTarget = NULL;
	m_pNext = NULL;
	m_pPrev = NULL;

	// 自分自身をリストに追加
	if (m_pTop != NULL)
	{// 先頭が存在している場合
		m_pCur->m_pNext = this;	// 現在最後尾のオブジェクトのポインタにつなげる
		m_pPrev = m_pCur;
		m_pCur = this;	// 自分自身が最後尾になる
	}
	else
	{// 存在しない場合
		m_pTop = this;	// 自分自身が先頭になる
		m_pCur = this;	// 自分自身が最後尾になる
	}
}

//===============================================
// デストラクタ
//===============================================
CBullet::~CBullet()
{

}

//===============================================
// 初期化処理
//===============================================
HRESULT CBullet::Init(void)
{
	// オブジェクトの初期化処理
	CObjectBillboard::Init();

	m_fLife = LIFE;
	m_nChangeTimer = 20;
	m_nType = 0;
	m_bDeath = false;

	return S_OK;
}

//===============================================
// 終了処理
//===============================================
void CBullet::Uninit(void)
{
	// オブジェクトの終了処理
	CObjectBillboard::Uninit();

	if (m_pTarget != NULL)
	{
		delete m_pTarget;
		m_pTarget = NULL;
	}

	m_bDeath = true;
}

//===============================================
// 更新処理
//===============================================
void CBullet::Update(void)
{
	D3DXVECTOR3 pos = GetPosition();

	// 座標更新
	Controller();

	// 頂点情報更新
	//SetVtx();

	m_fLife -= CManager::GetSlow()->Get();

	if (m_fLife > 0.0f)
	{//  寿命がある場合
		m_nChangeTimer--;

		//弾との当たり判定
		if (Collision(pos, CObject::TYPE_ENEMY) == true)
		{// 当たった場合
			//スコアの加算
			CManager::GetSound()->Play(CSound::LABEL_SE_BREAK);

			// 死亡確認
			DeathCheck();
			return;	// 終了しているため返す
		}
	}
	else
	{// 寿命切れ

		// 爆発の生成
		//CExplos ion::Create(GetPosition());

		// 終了処理
		Uninit();

		// 死亡確認
		DeathCheck();
		return;
	}
}

//===============================================
// 描画処理
//===============================================
void CBullet::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ

	//デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();

	//ライティングをオフにする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	
	//CObjectBillboard::Draw();

	//ライティングをオンにする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//===============================================
// 頂点情報設定
//===============================================
CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, TYPE type)
{
	CBullet *pBullet = NULL;
	CTexture *pTexture = CManager::GetTexture();	// テクスチャへのポインタ

	// オブジェクト2Dの生成
	pBullet = new CBullet(pos, move);

	if (pBullet != NULL)
	{// 生成できた場合

		// 初期化処理
		pBullet->Init();

		// 弾の種類設定
		pBullet->m_nType = type;

		// オブジェクトタイプの設定
		pBullet->SetType(CObject::TYPE_BULLET);

		pBullet->BindTexture(-1);

		pBullet->SetSize(10.0f, 10.0f);
	}
	else
	{// 生成に失敗した場合
		return NULL;
	}

	return pBullet;
}

//===============================================
// 操作処理
//===============================================
void CBullet::Controller(void)
{
	D3DXVECTOR3 pos = GetPosition();	// 座標を取得

	if (m_nType == TYPE_GRAVITY)
	{
		m_move.y += -0.07f * CManager::GetSlow()->Get();
	}
	else
	{
		m_fParTimer += CManager::GetSlow()->Get();

		if (m_fParTimer >= 1.0f)
		{
			//CEffect::Create(pos, CEffect::TYPE_BULLET);
			CParticle::Create(pos, m_move, CEffect::TYPE_BULLET);
			m_fParTimer = 0.0f;
		}
	}

	if (m_pTarget == NULL)
	{// ホーミングをしない場合
		pos += m_move * CManager::GetSlow()->Get();	// 移動量加算
	}
	else
	{// する場合
		CObject *pObj = m_pTarget->pObj;

		if (m_pTarget->pObj != NULL)
		{
			if (m_pTarget->pObj->GetDeath() == false)
			{
				if (m_pTarget->pObj->GetMtx() != NULL)
				{
					m_move = D3DXVECTOR3(m_pTarget->pObj->GetMtx()->_41 - pos.x, m_pTarget->pObj->GetMtx()->_42 - pos.y, m_pTarget->pObj->GetMtx()->_43 - pos.z);
					D3DXVec3Normalize(&m_move, &m_move);
					float fRotDest = atan2f(  m_pTarget->pObj->GetMtx()->_41 - pos.x, m_pTarget->pObj->GetMtx()->_43 - pos.z);	//目標までの角度
					float fRotDestXY = atan2f(m_pTarget->pObj->GetMtx()->_42 - pos.y, m_pTarget->pObj->GetMtx()->_41 - pos.x);
					float fRotDestZY = atan2f(m_pTarget->pObj->GetMtx()->_42 - pos.y, m_pTarget->pObj->GetMtx()->_43 - pos.z);
					m_move.y *= m_pTarget->fSpeed;
					m_move.x *= m_pTarget->fSpeed;
					m_move.z *= m_pTarget->fSpeed;
				}
			}
			else
			{
				pObj = NULL;
			}
		}
		pos += m_move * CManager::GetSlow()->Get();	// 移動量加算

	}

	// 頂点情報設定
	SetPosition(pos);
}

//===============================================
// 敵との当たり判定
//===============================================
bool CBullet::Collision(D3DXVECTOR3 pos, CObject::TYPE ObjType)
{
	CXFile *pFile = CManager::GetModelFile();

	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		CObject *pObj = CObject::GetTop(nCntPri);	// 先頭を取得

		while (pObj != NULL)
		{// 使用されていない状態まで

			CObject *pObjectNext = pObj->GetNext();	// 次のオブジェクトへのポインタを取得


			if (pObj->GetDeath() == false)
			{
				CObject::TYPE type;	// 種類

				// オブジェクトの種類を取得
				type = pObj->GetType();

				if (type == ObjType)
				{// 種類が敵の場合

					D3DXVECTOR3 ObjPos;	// オブジェクトの座標
					float fObjWidth = 0.0f;
					float fObjHeight = 0.0f;

					// 座標の取得
					ObjPos = pObj->GetPosition();
					CEnemy *pObjX = (CEnemy*)pObj;

					if (pObjX == NULL)
					{// 使用されていない
						pObj = pObjectNext;	// 次のオブジェクトに移動
						continue;
					}

					if (pos.x + GetWidth() >= ObjPos.x + -50.0f && pos.x - GetWidth() <= ObjPos.x + 50.0f
						&& pos.z + GetWidth() >= ObjPos.z + -50.0f && pos.z - GetWidth() <= ObjPos.z + 50.0f
						&& pos.y + GetHeight() >= ObjPos.y + -50.0f && pos.y - GetHeight() <= ObjPos.y + 50.0f)
					{// 敵と重なった場合

						// オブジェクトの終了処理
						if (pObj->GetType() == CObject::TYPE_ENEMY)
						{
							CManager::GetScore()->Add(100);
							CParticle::Create(pObj->GetPosition(), CEffect::TYPE_EXPLOSION);
							pObj->Uninit();
						}

						// 標的確認
						Check(pObj);

						// 自分自身の終了処理
						if (m_nType == TYPE_NONE)
						{
							Uninit();

							return TRUE;	// TRUEを返す(当たった)
						}
					}
				}
			}

			pObj = pObjectNext;	// 次のオブジェクトに移動
		}
	}

	return FALSE;	// FALSEを返す(何にも当たっていない)
}

//===============================================
// 敵との当たり判定
//===============================================
void CBullet::SetHom(CObject *pObj, float fSpeed)
{
	if (m_pTarget == NULL)
	{
		m_pTarget = new LockOn;
	}

	if (m_pTarget != NULL)
	{
		m_pTarget->pObj = pObj;
		m_pTarget->fSpeed = fSpeed;
	}
}

//===============================================
// 標的チェック
//===============================================
void CBullet::Check(CObject *pObject, CBullet *pBullet)
{
	CBullet *pBul = m_pTop;	// 先頭を取得

	while (pBul != NULL)
	{// 使用されている間繰り返し
		CBullet *pBulNext = pBul->m_pNext;	// 次を保持

		if (pBul != pBullet)
		{
			if (pBul->m_pTarget != NULL)
			{// ロックオンしている
				if (pBul->m_pTarget->pObj == pObject)
				{// 同じ標的の場合
					pBul->m_pTarget->pObj = NULL;
					delete pBul->m_pTarget;
					pBul->m_pTarget = NULL;
				}
			}
		}

		pBul = pBulNext;	// 次に移動
	}
}

//===============================================
// 死亡確認
//===============================================
void CBullet::DeathCheck(void)
{
	if (m_bDeath == true)
	{
		// リストから自分自身を削除する
		if (m_pTop == this)
		{// 自身が先頭
			if (m_pNext != NULL)
			{// 次が存在している
				m_pTop = m_pNext;	// 次を先頭にする
				m_pNext->m_pPrev = NULL;	// 次の前のポインタを覚えていないようにする
			}
			else
			{// 存在していない
				m_pTop = NULL;	// 先頭がない状態にする
				m_pCur = NULL;	// 最後尾がない状態にする
			}
		}
		else if (m_pCur == this)
		{// 自身が最後尾
			if (m_pPrev != NULL)
			{// 次が存在している
				m_pCur = m_pPrev;	// 前を最後尾にする
				m_pPrev->m_pNext = NULL;	// 前の次のポインタを覚えていないようにする
			}
			else
			{// 存在していない
				m_pTop = NULL;	// 先頭がない状態にする
				m_pCur = NULL;	// 最後尾がない状態にする
			}
		}
		else
		{
			m_pPrev->m_pNext = m_pNext;	// 自身の前に次のポインタを覚えさせる
			m_pNext->m_pPrev = m_pPrev;	// 自身の次に前のポインタを覚えさせる
		}
	}
}