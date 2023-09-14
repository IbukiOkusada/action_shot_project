//==========================================================
//
// 敵の出現管理処理 [enemy_manager.h]
// Author : Ibuki Okusada
//
//==========================================================
#include "enemy_manager.h"
#include "manager.h"
#include "object.h"
#include "time.h"
#include "enemy.h"
#include "meshfield.h"

// マクロ定義
#define NEXTWAVECNT	(2)	// 各wave開始カウント

//==========================================================
// コンストラクタ
//==========================================================
CEnemyManager::CEnemyManager()
{
	// 値のクリア
	m_nMaxEnemy = 0;
}

//==========================================================
// デストラクタ
//==========================================================
CEnemyManager::~CEnemyManager()
{

}

//==========================================================
// 初期化処理
//==========================================================
HRESULT CEnemyManager::Init(void)
{
	CEnemy::Create("data\\TXT\\motion_murabito.txt");

	// 現在の最大人数を覚える
	m_nMaxEnemy = CObject::GetNumEnemAll();

	return true;
}

//==========================================================
// 終了処理
//==========================================================
void CEnemyManager::Uninit(void)
{

}

//==========================================================
// 更新処理
//==========================================================
void CEnemyManager::Update(void)
{
	CTime *pTime = CManager::GetScene()->GetTime();

	if (pTime == NULL)
	{
		return;
	}

	if (pTime->GetAnim() == 0 && pTime->GetNum() % NEXTWAVECNT == 0 && pTime->GetNum() < pTime->GetStartNum() && pTime->GetNum() > 0)
	{// 次のウェーブ
		// 出現
		int NextNumEnemy = CObject::GetNumEnemAll() + 6;
		Spawn(NextNumEnemy);
	}
}

//==========================================================
// 出現処理
//==========================================================
void CEnemyManager::Spawn(int nSetNum)
{
	// 敵の配置
	while (1)
	{
		if (CObject::GetNumEnemAll() < nSetNum)
		{
			CEnemy::Create("data\\TXT\\motion_murabito.txt");
		}
		else
		{
			break;
		}
	}
}