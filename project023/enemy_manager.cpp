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
	// 出現

}

//==========================================================
// 出現処理
//==========================================================
void CEnemyManager::Spawn(void)
{
	//if (m_pTime == NULL)
	//{
	//	return;
	//}

	//if (m_pTime->GetAnim() == 0 && m_pTime->GetNum() % NEXTWAVECNT == 0 && m_pTime->GetNum() < START_TIME)
	//{// 次のウェーブ
	//	int NextNumEnemy = (int)(CObject::GetNumEnemAll() * 1.3f);

	//	// 敵の配置
	//	while (1)
	//	{
	//		if (CObject::GetNumEnemAll() < NextNumEnemy)
	//		{
	//			int nRand = rand() % 201 - 100;
	//			float fRot = D3DX_PI * ((float)nRand * 0.01f);

	//			CEnemy::Create(D3DXVECTOR3(0.0f + rand() % 300 - 150, 0.0f, 0.0f + rand() % 300 - 150), D3DXVECTOR3(0.0f, fRot, 0.0f),
	//				D3DXVECTOR3(-sinf(fRot) * 4.0f, 0.0f, -cosf(fRot) * 4.0f), "data\\TXT\\motion_murabito.txt");
	//		}
	//		else
	//		{
	//			break;
	//		}
	//	}
	//}
}