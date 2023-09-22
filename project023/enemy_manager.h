//==========================================================
//
// 敵の出現管理処理 [enemy_manager.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _ENEMY_MANAGER_H_
#define _ENEMY_MANAGER_H_

#define NUM_AREA	(4)		// 敵の生成場所数

//==========================================================
// 敵の出現管理クラスの定義(基底クラス)
//==========================================================
class CEnemyManager
{
private:

	enum ENEMY
	{
		ENEMY_SOCIETY = 0,
		ENEMY_SOCIETYYW,
		ENEMY_KIDSBOY,
		ENEMY_KIDSGIRL,
		ENEMY_MAX
	};
public:		// 誰でもアクセス可能

	CEnemyManager();	// コンストラクタ
	~CEnemyManager();	// デストラクタ

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void UpdateTutorial(void);
	void Spawn(int nSetNum);
	void AddDead(void) { m_nDeadCounter++; }
	void AddSuv(void) { m_nSuvCounter++; }
	int GetSuv(void) { return m_nSuvCounter; }
	int GetDead(void) { return m_nDeadCounter; }

private:	// 自分だけがアクセス可能

	int m_nMaxEnemy;	// 現在のエネミー最大数
	int m_nTimer;		// 生成
	int m_nFrameTimer;	// タイマーフレーム
	int m_nDeadCounter;	// 死亡人数
	int m_nSuvCounter;	// 生存人数
	static const char *m_apEnemyFileName[ENEMY_MAX];
};

#endif
