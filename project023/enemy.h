//==========================================================
//
// 敵の処理 [enemy.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _ENEMY_H_		// このマクロが定義されていない場合
#define _ENEMY_H_		// 二重インクルード防止用マクロを定義

#include "main.h"
#include "object.h"

// 前方宣言
class CCharacter;
class CShadow;
class CObjectBillboard;

//==========================================================
// プレイヤーのクラス定義(派生クラス)
//==========================================================
class CEnemy : public CObject
{
public:	// 誰でもアクセス可能な定義

	// 状態列挙型
	enum STATE
	{
		STATE_NORMAL = 0,	// 通常
		STATE_HOT,			// 暑い
		STATE_DOWN,			// 熱中症
		STATE_COOL,			// 涼しい
		STATE_DEFCOOL,		// 最初から涼しい
		STATE_MAX
	};

private:	// 自分だけがアクセス可能な定義

	// 情報構造体
	typedef struct
	{
		D3DXVECTOR3 pos;		// 位置
		D3DXVECTOR3 rot;		// 向き
		D3DXVECTOR3 move;		// 移動量
		D3DXVECTOR3 posOld;		// 設定位置
		D3DXMATRIX mtxWorld;	// ワールドマトリックス
	}INFO;

	// インターバル
	struct Interval
	{
		float fDamage;	// ダメージ
		float fParticle;// パーティクル
		float fHot;		// 体温上昇
	};

public:	// 誰でもアクセス可能

	CEnemy(int nPriOrity = 1);
	~CEnemy();	// デストラクタ

	// メンバ関数
	HRESULT Init(void);
	HRESULT Init(const char *pName);	// オーバーロード
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEnemy *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 move,
		const char *pBodyName, const int nPriority = 4);
	void Hit(float fDamage);
	void SetState(void);
	STATE GetState(void) { return m_state; }

	// メンバ関数(設定)
	void SetMove(const D3DXVECTOR3 move) { m_Info.move = move; }
	void SetPosition(const D3DXVECTOR3 pos) { m_Info.pos = pos; }
	void SetRotation(const D3DXVECTOR3 rot) { m_Info.rot = rot; }

	// メンバ関数(取得)
	D3DXVECTOR3 GetMove(void) { return m_Info.move; }
	D3DXVECTOR3 GetPosition(void) { return m_Info.pos; }
	D3DXVECTOR3 GetRotation(void) { return m_Info.rot; }
	D3DXMATRIX *GetMtx(void) { return &m_Info.mtxWorld; }

private:	// 自分だけがアクセス可能

	// メンバ関数
	void Controller(void);
	void SetParticle(void);
	void SetCol(void);

	// メンバ変数
	static const int m_aParticleCounter[STATE_MAX];
	CCharacter *m_pBody;	// 上半身
	float m_fMoveCnt;		// 移動カウント
	float m_fStateCnt;		// 状態管理カウント
	INFO m_Info;			// 自分自身の情報
	bool m_bMove;			// 移動したかどうか
	float m_fRotMove;		// 現在の角度
	float m_fRotDiff;		// 目的の角度
	float m_fRotDest;		// 角度計算
	CShadow *pShadow;		// 影
	float m_fLife;			// 体力
	Interval m_Interval;	// インターバル
	STATE m_state;			// 状態管理
	CObjectBillboard *m_pBillState;	// 状態表示用ビルボード
};

#endif