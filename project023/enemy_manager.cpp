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
#define NEXTWAVECNT	(20)	// 各wave開始カウント

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
	CTime *pTime = CManager::GetScene()->GetTime();

	if (pTime == NULL)
	{
		return;
	}

	if (pTime->GetAnim() == 0 && pTime->GetNum() % NEXTWAVECNT == 0 && pTime->GetNum() < pTime->GetStartNum() && pTime->GetNum() > 0)
	{// 次のウェーブ
		// 出現
		int NextNumEnemy = (int)(CObject::GetNumEnemAll() * 1.3f);
		Spawn(NextNumEnemy);
	}
}

//==========================================================
// 出現処理
//==========================================================
void CEnemyManager::Spawn(int nSetNum)
{
	int nSetArea = rand() % NUM_AREA;	// 配置場所をランダムで指定
	D3DXVECTOR3 SetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 配置場所を指定されたエリアに設定
	{
		int nCnt = 0;

		// 床の描画
		CMeshField *pMesh = CMeshField::GetTop();	// 先頭を取得
		CMeshField *pArea = NULL;;

		while (pMesh != NULL)
		{// 使用されている間繰り返し
			CMeshField *pMeshNext = pMesh->GetNext();	// 次を保持

			if (nCnt == nSetArea)
			{// 設置エリア
				pArea = pMesh;
			}

			pMesh->SetHot(false);
			pMesh = pMeshNext;	// 次に移動
			nCnt++;

			if (nCnt >= NUM_AREA)
			{
				break;
			}
		}

		SetPos = pArea->GetPosition();
		pArea->SetHot(true);
	}

	// 敵の配置
	while (1)
	{
		if (CObject::GetNumEnemAll() < nSetNum)
		{
			int nRand = rand() % 201 - 100;
			float fRot = D3DX_PI * ((float)nRand * 0.01f);

			CEnemy::Create(D3DXVECTOR3(SetPos.x + rand() % 300 - 150, 0.0f, SetPos.z + rand() % 300 - 150), D3DXVECTOR3(0.0f, fRot, 0.0f),
				D3DXVECTOR3(-sinf(fRot) * 4.0f, 0.0f, -cosf(fRot) * 4.0f), "data\\TXT\\motion_murabito.txt");
		}
		else
		{
			break;
		}
	}
}