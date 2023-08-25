//===============================================
//
// 敵の処理 [enemy.cpp]
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
#include "particle.h"
#include "score.h"
#include "lockon.h"
#include "game.h"
#include "player.h"
#include "meshcylinder.h"

//===============================================
// マクロ定義
//===============================================
#define MOVE			(2.0f)	// 移動量
#define STATE_CNT		(300)	// 状態管理カウント
#define DAMINTERVAL		(5)		// ダメージインターバル
#define MAX_LIFE		(600)	// 体力
#define HOTINTERVAL		(10)	// 熱中症状態インターバル
#define LEAVECNT		(120)	// 退場タイマー
#define LEAVEMOVE		(3.0f)	// 退場時の移動量
#define COOLDOWNCNT		(160)	// 退場前待機カウント

//===============================================
// 静的メンバ変数宣言
//===============================================
const int CEnemy::m_aParticleCounter[STATE_MAX] =
{
	30,
	20,
	20,
	10,
	10,
};

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
	m_pShadow = NULL;
	m_pBody = NULL;
	m_fStateCnt = 0;
	m_state = STATE_NORMAL;
	m_fLife = 0.0f;
	m_Interval.fHot = 0;
	m_Interval.fDamage = 0;
	m_pLockOn = NULL;
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

	m_fMoveCnt = (float)(rand() % 1000);
	m_fLife = 200.0f;

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
	if (m_pShadow != NULL)
	{
		m_pShadow->Uninit();
		m_pShadow = NULL;
	}

	// ロックオンの終了
	if (m_pLockOn != NULL)
	{
		m_pLockOn->Uninit();
		m_pLockOn = NULL;
	}

	// ロックオン確認
	CBullet::Check(this);
	CLockOn::Check(this);

	// 廃棄
	Release();
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

	if (m_pShadow != NULL)
	{
		m_pShadow->SetPosition(D3DXVECTOR3(m_pBody->GetParts(0)->GetMtxWorld()->_41, m_Info.pos.y, m_pBody->GetParts(0)->GetMtxWorld()->_43));
	}

	// 状態ごとに更新
	switch (m_state)
	{
	case STATE_NORMAL:

		UpdateNormal();
		break;

	case STATE_HOT:

		UpdateNormal();
		break;

	case STATE_DOWN:

		UpdateNormal();
		break;

	case STATE_DEFCOOL:

		UpdateCool();
		break;

	case STATE_COOL:

		UpdateCool();
		break;

	case STATE_COOLDOWN:

		UpdateCoolDown();
		break;
	}
}


//===============================================
// 描画処理
//===============================================
void CEnemy::Draw(void)
{
	SetCol();

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
		pEnemy->m_pShadow = CShadow::Create(pos, 30.0f, 30.0f);

		// ビルボードの設定
		//pEnemy->m_pBillState = CObjectBillboard::Create();
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
	float fHeight = CGame::GetMeshField()->GetHeight(m_Info.pos, nor);
	m_Info.pos.y = fHeight;


	SetCol();
}

//===============================================
// ヒット処理
//===============================================
void CEnemy::Hit(float fDamage)
{
	if (m_Interval.fDamage <= 0)
	{
		float fLifeOld = m_fLife;
		m_fLife -= fDamage;

		if (m_fLife < 0)
		{
			m_fLife = 0;
		}

		CGame::GetScore()->Add((int)(fLifeOld - m_fLife));

		if (m_state != STATE_DEFCOOL)
		{// 受けない状態以外
			// 状態設定
			SetState();

			m_Interval.fDamage = DAMINTERVAL;
		}
	}
}

//===============================================
// 状態設定
//===============================================
void CEnemy::SetState(void)
{
	// 残り体力によって状態を設定
	if (m_fLife <= 0)
	{// 0以下
		m_state = STATE_COOLDOWN;
		m_fStateCnt = COOLDOWNCNT;
		m_fMoveCnt = 0.0f;

		CParticle::Create(D3DXVECTOR3(GetMtx()->_41,
			GetMtx()->_42,
			GetMtx()->_43), CEffect::TYPE_EXPLOSION);

		CMeshSmake *pMesh;

		pMesh = CMeshSmake::Create(GetPosition(), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 37.0f, 2.0f, 3, 10, 10);

		pMesh->BindTexture(CManager::GetTexture()->Regist("data\\TEXTURE\\smake001.jpg"));

		pMesh = CMeshSmake::Create(GetPosition(), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 35.0f, 3.0f, 3, 10, 10);

		pMesh->BindTexture(CManager::GetTexture()->Regist("data\\TEXTURE\\smake000.jpg"));
	}
	else if (m_fLife < 200 * STATE_HOT)
	{//あともう少し
		m_state = STATE_NORMAL;
	}
	else if (m_fLife >= 200 * STATE_HOT && m_fLife < 200 * STATE_DOWN)
	{// まだ残っている
		m_state = STATE_HOT;
	}
	else if (m_fLife >= 200 * STATE_DOWN)
	{// ほとんど残っている
		m_state = STATE_DOWN;
		if (m_fLife == 200 * STATE_DOWN)
		{
			CGame::GetScore()->Add(-50);
		}
	}
}

//===============================================
// 状態ごとのパーティクル設定
//===============================================
void CEnemy::SetParticle(void)
{
	D3DXMATRIX mtxProjection;
	D3DXMATRIX mtxView;
	D3DXMATRIX mtxWorld;
	D3DXVECTOR3 ScreenPos;
	D3DVIEWPORT9 Viewport;

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	pDevice->GetTransform(D3DTS_PROJECTION, &mtxProjection);
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);
	pDevice->GetViewport(&Viewport);
	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);
	D3DXVec3Project(&ScreenPos, &GetPosition(), &Viewport, &mtxProjection, &mtxView, &mtxWorld);

	if (ScreenPos.x < 0.0f || ScreenPos.x > SCREEN_WIDTH || 
		ScreenPos.y < 0.0f || ScreenPos.y > SCREEN_HEIGHT || ScreenPos.z >= 1.0f)
	{// 画面に描画されていない
		return;
	}

	switch (m_state)
	{
	case STATE_NORMAL:
		CParticle::Create(D3DXVECTOR3(m_pBody->GetParts(3)->GetMtxWorld()->_41,
			m_pBody->GetParts(3)->GetMtxWorld()->_42,
			m_pBody->GetParts(3)->GetMtxWorld()->_43),
			CEffect::TYPE_SWEAT);
		break;

	case STATE_HOT:
		CParticle::Create(D3DXVECTOR3(m_pBody->GetParts(3)->GetMtxWorld()->_41,
			m_pBody->GetParts(3)->GetMtxWorld()->_42,
			m_pBody->GetParts(3)->GetMtxWorld()->_43),
			CEffect::TYPE_SWEAT);
		break;

	case STATE_DOWN:
		CParticle::Create(D3DXVECTOR3(m_pBody->GetParts(3)->GetMtxWorld()->_41,
			m_pBody->GetParts(3)->GetMtxWorld()->_42 + 12.0f,
			m_pBody->GetParts(3)->GetMtxWorld()->_43),
			CEffect::TYPE_HEAT);

		/*CParticle::Create(D3DXVECTOR3(m_pBody->GetParts(3)->GetMtxWorld()->_41,
			m_pBody->GetParts(3)->GetMtxWorld()->_42,
			m_pBody->GetParts(3)->GetMtxWorld()->_43),
			CEffect::TYPE_SWEAT);*/
		break;
	}
}

//===============================================
// 色設定
//===============================================
void CEnemy::SetCol(void)
{
	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	col.g = 1.0f - (float)(m_fLife / MAX_LIFE);
	col.b = 1.0f - (float)(m_fLife / MAX_LIFE);

	for (int nCnt = 0; nCnt < m_pBody->GetNumParts(); nCnt++)
	{
		if (m_pBody->GetParts(nCnt) != NULL)
		{
			if (m_fLife >= 200)
			{
				m_pBody->GetParts(nCnt)->SetChangeCol(true, col);
			}
			else
			{
				if (m_state == STATE_COOL)
				{// 退場中
					// 透明度を変更
					col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					col.a = (float)(m_fStateCnt / LEAVECNT);
					
					m_pBody->GetParts(nCnt)->SetChangeCol(true, col);
					m_pShadow->SetCol(col);
				}
				else
				{
					m_pBody->GetParts(nCnt)->SetChangeCol(false);
				}
			}
		}
	}
}

//===============================================
// 通常時の更新処理
//===============================================
void CEnemy::UpdateNormal(void)
{
	if (m_fStateCnt < STATE_CNT)
	{
		m_fStateCnt += CManager::GetSlow()->Get();

		if (GetPosition().x > 2900.0f || GetPosition().x < -2900.0f ||
			GetPosition().z > 2900.0f || GetPosition().z < -2900.0f)
		{
			m_fStateCnt = 0;
		}
	}

	// ダメージインターバル
	if (m_Interval.fDamage > 0)
	{
		m_Interval.fDamage -= CManager::GetSlow()->Get();
	}

	if (m_state != STATE_DEFCOOL)
	{
		// 体温上昇インターバル
		m_Interval.fHot += CManager::GetSlow()->Get();

		if (m_Interval.fHot >= HOTINTERVAL)
		{
			m_Interval.fHot = 0;
			m_fLife++;

			if (m_fLife > MAX_LIFE)
			{
				m_fLife = MAX_LIFE;
			}
		}

		// 状態更新
		SetState();
	}

	// パーティクルインターバル
	m_Interval.fParticle += CManager::GetSlow()->Get();

	if (m_Interval.fParticle >= m_aParticleCounter[m_state])
	{
		SetParticle();
		m_Interval.fParticle = 0.0f;
	}
}

//===============================================
// 涼しいときの更新処理
//===============================================
void CEnemy::UpdateCool(void)
{
	m_fStateCnt -= CManager::GetSlow()->Get();

	if (GetPosition().x > 2900.0f || GetPosition().x < -2900.0f ||
		GetPosition().z > 2900.0f || GetPosition().z < -2900.0f)
	{
		m_fStateCnt = 0;
	}

	if (m_fStateCnt <= 0.0f)
	{// 遷移タイマー規定値
		Uninit();
	}
}

//===============================================
// 涼しくなった直後の更新処理
//===============================================
void CEnemy::UpdateCoolDown(void)
{
	m_fStateCnt -= CManager::GetSlow()->Get();

	Controller();

	if (m_fStateCnt <= 0.0f)
	{
		m_state = STATE_COOL;
		m_fStateCnt = LEAVECNT;
		m_fMoveCnt = LEAVECNT;

		if (CGame::GetPlayer() != NULL)
		{
			CGame::GetPlayer()->AddSlowTime();

			// 向きを変更する
			D3DXVECTOR3 rot = GetRotation();
			rot.y = (float)(rand() % 628 - 314) * 0.01f;

			// 向きに合わせた移動量に変更
			m_Info.move.x = -sinf(rot.y) * LEAVEMOVE;
			m_Info.move.z = -cosf(rot.y) * LEAVEMOVE;

			SetRotation(rot);
		}
	}
}