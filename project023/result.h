//===============================================
//
// リザルト画面の管理処理 [result.h]
// Author : Ibuki Okusada
//
//===============================================
#ifndef _RESULT_H_		// このマクロが定義されていない場合
#define _RESULT_H_		// 二重インクルード防止用マクロを定義

#include "manager.h"

class CScore;

//===============================================
// タイトルクラスの定義(派生クラス)
//===============================================
class CResult : public CScene
{
public:

	// メンバ関数
	CResult();	// コンストラクタ
	~CResult();	// デストラクタ

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// メンバ関数(取得)
	static CScore *GetScore() { return m_pScore; }
	static void SetScore(int nValue) { m_nScore = nValue; }

private:

	static CScore *m_pScore;
	static int m_nScore;
};

#endif