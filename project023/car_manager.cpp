//===============================================
//
// 車全般の管理処理(car_manager.cpp)
// Author : Ibuki Okusada
//
//===============================================
#include "car_manager.h"
#include "car.h"
#include "manager.h"
#include "slow.h"
#include "shadow.h"

// マクロ定義
#define LOAD_POSX	(-200.0f)	// 生成X座標
#define LOAD_POSY	(-30.0f)	// 生成Y座標
#define LOAD_POSZ	(-4200.0f)	// 生成Z座標
#define MOVE_Z		(11.0f)		// Z移動量
#define SPAWN_DEF	(160)		// 基本生成カウント
#define SPAWN_RAND	(180)		// ランダム分生成カウント

// 静的メンバ変数
const char *CCarManager::m_apFileName[MAX_CAR] = 
{
	"data\\MODEL\\car000.x",
	"data\\MODEL\\car001.x",
	"data\\MODEL\\car002.x",
	"data\\MODEL\\car003.x",
	"data\\MODEL\\car004.x",
	"data\\MODEL\\car005.x",
};

// 静的メンバ変数
const D3DXVECTOR2 CCarManager::m_aShadowSize[MAX_CAR] =
{
	{ 100.0f, 200.0f },
	{ 100.0f, 200.0f },
	{ 100.0f, 200.0f },
	{ 100.0f, 200.0f },
	{ 180.0f, 720.0f },
	{ 180.0f, 720.0f },
};

//===============================================
// コンストラクタ
//===============================================
CCarManager::CCarManager()
{
	// 値のクリア
	for (int nCnt = 0; nCnt < LOAD_MAX; nCnt++)
	{
		m_aSpawn[nCnt].fCount = 0.0f;
		m_aSpawn[nCnt].fDef = 0.0f;
		m_aSpawn[nCnt].nNum = 0;
		m_apTop[nCnt] = NULL;
		m_apCur[nCnt] = NULL;
	}
}

//===============================================
// デストラクタ
//===============================================
CCarManager::~CCarManager()
{

}

//===============================================
// 初期化処理
//===============================================
HRESULT CCarManager::Init(void)
{
	for (int nCnt = 0; nCnt < LOAD_MAX; nCnt++)
	{
		m_aSpawn[nCnt].fDef = SPAWN_DEF;
	}

	return S_OK;
}

//===============================================
// 終了処理
//===============================================
void CCarManager::Uninit(void)
{

}

//===============================================
// 更新処理
//===============================================
void CCarManager::Update(void)
{
	// 生成管理
	Spawn();

	// 廃棄
	Delete();
}

//===============================================
// リストにセット
//===============================================
bool CCarManager::BindList(CCar *pCar, LOAD load)
{
	if (load >= LOAD_RIGHT && load < LOAD_MAX)
	{// 範囲内
		// 自分自身をリストに追加
		if (m_apTop[load] != NULL)
		{// 先頭が存在している場合
			m_apCur[load]->SetNext(pCar);	// 現在最後尾のオブジェクトのポインタにつなげる
			pCar->SetPrev(m_apCur[load]);
			m_apCur[load] = pCar;	// 自分自身が最後尾になる
		}
		else
		{// 存在しない場合
			m_apTop[load] = pCar;	// 自分自身が先頭になる
			m_apCur[load] = pCar;	// 自分自身が最後尾になる
		}
	}
	else
	{// リスト追加失敗
		return false;
	}

	// 総数増加
	m_aSpawn[load].nNum++;

	return true;
}

//===============================================
// リストから外す
//===============================================
void CCarManager::DetachList(CCar *pCar, LOAD load)
{
	// リストから自分自身を削除する
	if (m_apTop[load] == pCar)
	{// 自身が先頭
		if (m_apTop[load]->GetNext() != NULL)
		{// 次が存在している
			m_apTop[load] = m_apTop[load]->GetNext();	// 次を先頭にする
			m_apTop[load]->SetPrev(NULL);	// 次の前のポインタを覚えていないようにする
		}
		else
		{// 存在していない
			m_apTop[load] = NULL;	// 先頭がない状態にする
			m_apCur[load] = NULL;	// 最後尾がない状態にする
		}
	}
	else if (m_apCur[load] == pCar)
	{// 自身が最後尾
		if (m_apCur[load]->GetPrev() != NULL)
		{// 手前が存在している
			m_apCur[load] = pCar->GetPrev();	// 前を最後尾にする
			m_apCur[load]->SetNext(NULL);		// 前の次のポインタを覚えていないようにする
		}
		else
		{// 存在していない
			m_apTop[load] = NULL;	// 先頭がない状態にする
			m_apCur[load] = NULL;	// 最後尾がない状態にする
		}
	}
	else
	{// 間
		if (pCar->GetNext() != NULL)
		{// 次が存在している
			pCar->GetNext()->SetPrev(pCar->GetPrev());	// 自身の次に前のポインタを覚えさせる
		}
		if (pCar->GetPrev() != NULL)
		{// 手前が存在している
			pCar->GetPrev()->SetNext(pCar->GetNext());	// 自身の前に次のポインタを覚えさせる
		}
	}

	// 総数減少
	m_aSpawn[load].nNum--;
}

//===============================================
// 生成処理
//===============================================
void CCarManager::Spawn(void)
{
	D3DXVECTOR3 pos = D3DXVECTOR3(LOAD_POSX, LOAD_POSY, LOAD_POSZ);
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, MOVE_Z);

	// 車線分繰り返し
	for (int nCnt = 0; nCnt < LOAD_MAX; nCnt++)
	{
		m_aSpawn[nCnt].fCount += CManager::GetSlow()->Get();

		if (m_aSpawn[nCnt].fCount < m_aSpawn[nCnt].fDef)
		{// 規定値に達していない
			pos.x *= -1.0f;
			pos.z *= -1.0f;
			move.z *= -1.0f;
			continue;
		}

		int nRand = rand() % MAX_CAR;

		rot.y = D3DX_PI * nCnt;
		CCar *pCar = CCar::Create(pos, rot, m_apFileName[nRand]);
		pCar->SetMove(move);
		pCar->GetShadow()->SetpVtx(m_aShadowSize[nRand].x, m_aShadowSize[nRand].y);

		// リストに設定
		BindList(pCar, (LOAD)nCnt);
		m_aSpawn[nCnt].fCount = 0.0f;
		m_aSpawn[nCnt].fDef = SPAWN_DEF + (float)(rand() % SPAWN_RAND);
		pos.x *= -1.0f;
		pos.z *= -1.0f;
		move.z *= -1.0f;
	}
}

//===============================================
// 生成
//===============================================
void CCarManager::Delete(void)
{
	// 左車線
	{
		CCar *pCar = m_apTop[LOAD_LEFT];

		while (pCar != NULL)
		{
			CCar *pCarNext = pCar->GetNext();
			float fMoveZ = pCar->GetMove().z;
			float fPosZ = pCar->GetPosition().z;

			if (fPosZ < LOAD_POSZ)
			{// 端まで行った
				// 終了
				DetachList(pCar, LOAD_LEFT);
				pCar->Uninit();
			}

			pCar = pCarNext;
		}
	}

	// 右車線
	{
		CCar *pCar = m_apTop[LOAD_RIGHT];

		while (pCar != NULL)
		{
			CCar *pCarNext = pCar->GetNext();
			float fMoveZ = pCar->GetMove().z;
			float fPosZ = pCar->GetPosition().z;

			if (fPosZ > -LOAD_POSZ)
			{// 端まで行った
				// 終了
				DetachList(pCar, LOAD_RIGHT);
				pCar->Uninit();
			}

			pCar = pCarNext;
		}
	}
}