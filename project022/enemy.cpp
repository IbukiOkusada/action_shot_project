//===============================================
//
// プレイヤーの処理 [player.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "enemy.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "debugproc.h"
#include "shadow.h"
#include "character.h"
#include "motion.h"
#include "slow.h"
#include "model.h"
#include "billboard.h"
#include "meshfield.h"
#include "texture.h"
#include "slow.h"
#include "bullet.h"

//===============================================
// マクロ定義
//===============================================
#define MOVE		(2.0f)		// 移動量
#define PLAYER_GRAVITY	(-0.7f)	// プレイヤー重力
#define PLAYER_JUMP	(15.0f)		// プレイヤージャンプ力
#define STATE_CNT	(300)		// 状態管理カウント

//===============================================
// コンストラクタ(オーバーロード)
//===============================================
CEnemy::CEnemy(int nPriOrity)
{
	// 値をクリアする
	m_Info.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fRotMove = 0.0f;
	m_fRotDiff = 0.0f;
	m_fRotDest = 0.0f;
	pShadow = NULL;
	m_pBody = NULL;
	m_pBillState = NULL;
	m_fStateCnt = 0;
}

//===============================================
// デストラクタ
//===============================================
CEnemy::~CEnemy()
{

}

//===============================================
// 初期化処理
//===============================================
HRESULT CEnemy::Init(void)
{
	
	return S_OK;
}

//===============================================
// 初期化処理(オーバーロード)
//===============================================
HRESULT CEnemy::Init(const char *pName)
{
	CTexture *pTexture = CManager::GetTexture();

	// 胴体の設定
	if (pName != NULL)
	{// ファイル名が存在している
		m_pBody = CCharacter::Create(pName);
		m_pBody->SetParent(&m_Info.mtxWorld);

		if (m_pBody->GetMotion() != NULL)
		{
			// 初期モーションの設定
			m_pBody->GetMotion()->InitSet(1);
		}
	}

	m_fMoveCnt = rand() % 1000;

	m_pBillState = CObjectBillboard::Create(m_pBody->GetParts(2)->GetPosition());
	m_pBillState->BindTexture(CTexture::TYPE_ENEMYSTATE);
	m_pBillState->SetSize(10.0f, 10.0f);

	return S_OK;
}

//===============================================
// 終了処理
//===============================================
void CEnemy::Uninit(void)
{
	// 胴体の終了処理
	if (m_pBody != NULL)
	{
		m_pBody->Uninit();
		delete m_pBody;
		m_pBody = NULL;
	}

	// 影の終了
	if (pShadow != NULL)
	{
		pShadow->Uninit();
		pShadow = NULL;
	}

	// ビルボードの終了
	if (m_pBillState != NULL)
	{
		m_pBillState->Uninit();
		m_pBillState = NULL;
	}

	// 廃棄
	Release();

	CBullet::Check(this);
}

//===============================================
// 更新処理
//===============================================
void CEnemy::Update(void)
{
	// 前回の座標を取得
	m_Info.posOld = GetPosition();

	// 胴体更新
	if (m_pBody != NULL)
	{// 使用されている場合
		m_pBody->Update();
	}

	// プレイヤー操作
	Controller();

	if (pShadow != NULL)
	{
		pShadow->SetPosition(D3DXVECTOR3(m_pBody->GetParts(0)->GetMtxWorld()->_41, m_Info.pos.y, m_pBody->GetParts(0)->GetMtxWorld()->_43));
	}

	// ビルボードの座標操作
	if (m_pBillState != NULL)
	{
		m_pBillState->SetPosition(D3DXVECTOR3(m_pBody->GetParts(3)->GetMtxWorld()->_41, 
			m_pBody->GetParts(3)->GetMtxWorld()->_42 + 20.0f, m_pBody->GetParts(3)->GetMtxWorld()->_43));
	}

	if (m_fStateCnt < STATE_CNT)
	{
		m_fStateCnt += CManager::GetSlow()->Get();

		if (m_fStateCnt >= STATE_CNT)
		{
			m_pBillState->BindTexture(CTexture::TYPE_ENEMYSTATEADD);
		}

		if (GetPosition().x > 2900.0f || GetPosition().x < -2900.0f ||
			GetPosition().z > 2900.0f || GetPosition().z < -2900.0f)
		{
			m_fStateCnt = 0;
			m_pBillState->BindTexture(CTexture::TYPE_ENEMYSTATEADD);
		}
	}
}


//===============================================
// 描画処理
//===============================================
void CEnemy::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	//デバイスへのポインタを取得
	CTexture *pTexture = CManager::GetTexture();	// テクスチャへのポインタ
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_Info.mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Info.rot.y, m_Info.rot.x, m_Info.rot.z);
	D3DXMatrixMultiply(&m_Info.mtxWorld, &m_Info.mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_Info.pos.x, m_Info.pos.y, m_Info.pos.z);
	D3DXMatrixMultiply(&m_Info.mtxWorld, &m_Info.mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_Info.mtxWorld);

	// 胴体の描画
	if (m_pBody != NULL)
	{
		m_pBody->Draw();
	}
}

//===============================================
// 生成
//===============================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, const char *pBodyName, const int nPriority)
{
	CEnemy *pEnemy = NULL;
	CXFile *pModelFile = CManager::GetModelFile();

	// オブジェクト2Dの生成
	pEnemy = new CEnemy(nPriority);

	if (pEnemy != NULL)
	{// 生成できた場合

		// 初期化処理
		pEnemy->Init(pBodyName);

		// 座標設定
		pEnemy->SetPosition(pos);

		// 向き設定
		pEnemy->SetRotation(rot);

		// 移動量設定
		pEnemy->SetMove(move);

		// 種類の設定
		pEnemy->SetType(TYPE_ENEMY);

		// 影の設定
		pEnemy->pShadow = CShadow::Create(pos, 30.0f, 30.0f);

		pEnemy->m_pBillState->SetPosition(pEnemy->GetPosition());

		// ビルボードの設定
		//pEnemy->m_pBillState = CObjectBillboard::Create()
	}
	else
	{// 生成に失敗した場合
		return NULL;
	}

	return pEnemy;
}

//===============================================
// 操作処理
//===============================================
void CEnemy::Controller(void)
{
	// 設定された移動量を加算する
	if (m_fMoveCnt > 0.0f)
	{
		m_fMoveCnt -= CManager::GetSlow()->Get();

		m_Info.pos += m_Info.move * CManager::GetSlow()->Get();

		m_pBody->GetMotion()->BlendSet(1);
	}
	else
	{
		m_pBody->GetMotion()->BlendSet(0);
	}

	D3DXVECTOR3 nor;
	float fHeight = CManager::GetMeshField()->GetHeight(m_Info.pos, nor);
	m_Info.pos.y = fHeight;
}

//===============================================
// ヒット処理
//===============================================
void CEnemy::Hit(float fDamage)
{

}