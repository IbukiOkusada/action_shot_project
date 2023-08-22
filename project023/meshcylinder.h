//==========================================================
//
// メッシュシリンダーの処理 [meshcylinder.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _MESHCYLINDER_H_	// このマクロが定義されていない場合
#define _MESHCYLINDER_H_	// 二重インクルード防止用マクロを定義

#include "main.h"
#include "mesh.h"

//**********************************************************
// メッシュシリンダークラスの定義(派生クラス)
//**********************************************************
class CMeshCylinder : public CObjectMesh
{
public:		// 誰でもアクセス可能

	CMeshCylinder();	// コンストラクタ
	~CMeshCylinder();	// デストラクタ

	// メンバ関数
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	void SetVtxInfo(void);
	static CMeshCylinder *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, float fLength,
		float fHeight, const int nPriority = 3, const int nWidth = 1, const int nHeight = 1);

private:	// 自分だけがアクセス可能

	// メンバ関数
	void SetSize(float fLength, float fHeight);

	// メンバ関数
	float m_fHeight;	// 高さ
	float m_fLength;	//距離
	float m_fRot;		//一頂点の角度

};

//**********************************************************
// メッシュ煙クラスの定義(派生クラス)
//**********************************************************
class CMeshSmake : public CMeshCylinder
{
public:		// 誰でもアクセス可能

	CMeshSmake();	// コンストラクタ
	~CMeshSmake();	// デストラクタ

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CMeshSmake *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, float fLength,
		float fHeight, const int nPriority = 3, const int nWidth = 1, const int nHeight = 1);

private:	// 自分だけがアクセス可能

	// メンバ関数
	void SetSize(float fLength, float fHeight);
	void SetCol(D3DXCOLOR col);
	void SetHeight(float fHeight);

	// メンバ関数
	float m_fHeight;	// 高さ
	float m_fLength;	// 距離
	float m_fRot;		//一頂点の角度
	D3DXCOLOR m_col;	// 色
	D3DXVECTOR2 m_tex;	// テクスチャ座標

};

#endif
