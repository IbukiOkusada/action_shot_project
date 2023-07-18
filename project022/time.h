//==========================================================
//
// タイムの処理 [time.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _TIME_H_	// このマクロが定義されていない場合
#define _TIME_H_	// 二重インクルード防止用マクロを定義

#include "main.h"

// 前方宣言
class CNumber;

//==========================================================
// テクスチャスライドオブジェクト(2D)のクラス定義(派生クラス)
//==========================================================
class CTime
{
public:	// ここから関数(誰でもアクセス可能)

	CTime();	// コンストラクタ
	~CTime();	// デストラクタ

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CTime *Create(D3DXVECTOR3 pos);

	// メンバ関数
	void Add(int nValue);
	void Set(int nValue);

	// メンバ関数(取得)
	int GetNum(void) { return m_nNum; }

private:	// 自分だけがアクセス可能

	// マクロ定義
	#define NUM_PLACE	(4)	// スコアの桁数

	// メンバ関数
	void SetValue(void);

	// メンバ変数
	CNumber *m_apNumber[NUM_PLACE];			// 数字のポインタ
	D3DXVECTOR3 m_pos;	// 座標
	int m_nNum;	// 現在の値
	int m_nAnimTimer;	// 1秒カウント
	int m_nIdxTexture;	// テクスチャ番号
	
};

#endif
