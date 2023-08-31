//==========================================================
//
// 敵の出現管理処理 [enemy_manager.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _ENEMY_MANAGER_H_
#define _ENEMY_MANAGER_H_

//==========================================================
// 敵の出現管理クラスの定義(基底クラス)
//==========================================================
class CEnemyManager
{
public:		// 誰でもアクセス可能

	CEnemyManager();	// コンストラクタ
	~CEnemyManager();	// デストラクタ

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

private:	// 自分だけがアクセス可能

	void Spawn(void);
	int m_nMaxEnemy;	// 現在のエネミー最大数
};

#endif
