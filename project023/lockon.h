//==========================================================
//
// ロックオンの処理 [lockon.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _LOCKON_H_
#define _LOCKON_H_

#include "billboard.h"

// 前方宣言
class CModel;
class CObject;

//**********************************************************
// ロックオンクラスの定義
//**********************************************************
class CLockOn : public CObjectBillboard
{
private:	// 自分だけがアクセス可能

	// 射程構造体
	typedef struct
	{
		D3DXVECTOR3 pos;		// 位置
		D3DXVECTOR3 rot;		// 向き
		D3DXMATRIX mtxWorld;	// ワールドマトリックス
	}DISTANCE;

public:	// 誰でもアクセス可能

	CLockOn(int nPriOrity = 5);	// コンストラクタ
	~CLockOn();	// デストラクタ

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetParent(D3DXMATRIX *pMtx);
	void SetDistance(float fLength, float fAngle);
	bool GetLock(void) { return m_bLock; }
	void SetLock(bool bLock) { m_bUse = bLock; }
	static CLockOn *Create(D3DXMATRIX *pMtx);
	CObject *GetTag(void);

private:	// 自分だけがアクセス可能

	// メンバ関数
	void LockOn(void);
	void SetDisMtx(DISTANCE *pDis);

	CObject *m_pObj;		// ロックオンするモデル
	D3DXMATRIX *m_pMtx;		// 親のマトリックス
	DISTANCE m_DisL;		// 左側距離
	DISTANCE m_DisR;		// 右側距離
	float m_fLength;		// 長さ
	float m_fAngle;			// 角度
	bool m_bLock;			// ロックオンしているかどうか
	bool m_bUse;			// 使用するかどうか
};

#endif

