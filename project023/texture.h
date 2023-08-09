//===============================================
//
// テクスチャの管理全般 [texture.h]
// Author : Ibuki Okusada
//
//===============================================
#ifndef _TEXTURE_H_		// このマクロが定義されていない場合
#define _TEXTURE_H_		// 二重インクルード防止用マクロを定義

#include "main.h"

// マクロ定義
#define MAX_TEXTURE		(256)	// テクスチャの最大数
#define MAX_FILENAME	(256)	// ファイル名最大文字数

//**********************************************************
// テクスチャクラスの定義
//**********************************************************
class CTexture
{
public:	// 誰でもアクセス可能な定義
	
	// 初期読み込み種類
	typedef enum
	{
		TYPE_EXPLOSION = 0,	// 爆発
		TYPE_EFFECT,		// エフェクト
		TYPE_SHADOW,		// 影
		TYPE_SCORE,			// スコア
		TYPE_TIMER,			// タイマー
		TYPE_LOCKON,		// ロックオン
		TYPE_BULLET,		// 弾
		TYPE_ENEMYSTATE,	// 敵の状態
		TYPE_ENEMYSTATEADD,	// 敵の状態悪
		TYPE_SLOWLOCK,		// スロー中ロックオン
		TYPE_PERFECT,
		TYPE_GOOD,
		TYPE_SLOWGUNFIL,
		TYPE_MAX
	}TYPE;

private:	// 自分だけがアクセス可能な定義
	
	// ファイル情報
	typedef struct
	{
		LPDIRECT3DTEXTURE9 pTexture;	// テクスチャのポインタ
		char aName[MAX_FILENAME];		// ファイル名
	}File;

public:	// 誰でもアクセス可能

	CTexture();		// コンストラクタ
	~CTexture();	// デストラクタ

	// メンバ関数
	HRESULT Load(void);
	void Unload(void);
	int Regist(const char* pFileName);
	LPDIRECT3DTEXTURE9 SetAddress(int nIdx);

	// メンバ関数(取得)
	int GetNumAll(void) { return m_nNumAll; }
	const static char *GetFileName(int nIdx);

private:	// 自分だけがアクセス可能

	// メンバ関数
	File m_aFile[MAX_TEXTURE];	// テクスチャへのポインタ
	static int m_nNumAll;		// 読み込み総数
	const static char *m_apDefFileName[TYPE_MAX];	// 初期読み込みファイル名
};

#endif
