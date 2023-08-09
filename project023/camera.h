//==========================================================
//
// カメラの処理全般 [camera.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _CAMERA_H_		 // このマクロが定義されていない場合
#define _CAMERA_H_		 // 二重インクルード防止用マクロを定義

#include "main.h"		//main.hで定義しているものが必要なためinclude

// マクロ定義
#define MAX_CAMERA_ROTZ (D3DX_PI * 0.9f)	// カメラ最大角度
#define MIN_CAMERA_ROTZ (D3DX_PI * 0.22f)	// カメラ最大角度

//**********************************************************
// カメラクラスの定義
//**********************************************************
class CCamera
{
public:	// 誰でもアクセス可能な定義

	enum MODE
	{
		MODE_NORMAL = 0,	// 通常
		MODE_SLOWGUN,		// スロー角度強制状態
		MODE_SLOWSHW,		// シャワー
		MODE_MAX
	};

public:	// 誰でもアクセス可能
	CCamera();	// コンストラクタ
	~CCamera();	// デストラクタ

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);
	void Pursue(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);
	void Setting(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);
	void SetRot(const D3DXVECTOR3 rot);
	void SerMode(MODE mode) { m_mode = mode; }
	void SetOldRot(D3DXVECTOR3 rot) { m_SlowOldRot = rot; }
	void MoveV(void);
	void MouseCamera(void);
	void MoveVR(void);

	// メンバ関数
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	D3DXVECTOR3 GetPositionV(void) { return m_posV; }
	D3DXVECTOR3 GetPositionR(void) { return m_posR; }

private:	// 自分だけがアクセス可能

	// メンバ関数
	void MoveR(void);
	void SetV(void);
	void SetR(void);
	void Edit(void);
	void Slow(void);
	void SlowShw(void);

	// メンバ変数
	D3DXMATRIX m_mtxView;		// ビューマトリックス
	D3DXMATRIX m_mtxProjection;	// プロジェクションマトリックス
	D3DXVECTOR3 m_posV;			// 視点
	D3DXVECTOR3 m_posR;			// 注視点
	D3DXVECTOR3 m_vecU;			// 上方向ベクトル
	D3DXVECTOR3 m_rot;			// 向き
	D3DXVECTOR3 m_SlowOldRot;	// スロー前の向き
	MODE m_mode;				// モード
	float m_fMulScore;			// スコア倍率
	float m_fLength;			// 視点と注視点の距離
};

#endif