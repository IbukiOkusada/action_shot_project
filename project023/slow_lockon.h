//==========================================================
//
// スロー中のロックオン処理 [slow_lockon.h]
// Author : Ibuki Okusada
//
//==========================================================

#include "object3D.h"

// 前方宣言
class CModel;
class CEnemy;
class CObject;

//**********************************************************
// ロックオンクラスの定義
//**********************************************************
class CSlowLock : public CObject3D
{
public:	// 誰でもアクセス可能

	CSlowLock(int nPriOrity = 5);	// コンストラクタ
	~CSlowLock();	// デストラクタ

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CSlowLock *Create(void);
	TYPE GetType(void) { return m_type; }

private:	// 自分だけがアクセス可能

	// メンバ関数
	void LockOn(void);
	void Controller(void);

	float m_fLength;		// 長さ
	TYPE m_type;			// ロックオン種類
};
