//===============================================
//
// ゲーム画面の管理処理 [game.h]
// Author : Ibuki Okusada
//
//===============================================
#ifndef _GAME_H_		// このマクロが定義されていない場合
#define _GAME_H_		// 二重インクルード防止用マクロを定義

#include "manager.h"

// 前方宣言
class CScore;
class CTime;
class CPlayer;
class CMapCamera;
class CLight;
class CFileLoad;
class CEditor;
class CSlow;
class CObject3D;
class CMeshField;
class CPause;
class CThermo;

//===============================================
// ゲームクラスの定義(派生クラス)
//===============================================
class CGame : public CScene
{
public:

	// メンバ関数
	CGame();	// コンストラクタ
	~CGame();	// デストラクタ

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// メンバ関数(ポインタ)
	static CScore *GetScore(void);
	static CTime *GetTime(void);
	static CPlayer *GetPlayer(void);
	static CSlow *GetSlow(void);
	static CMeshField *GetMeshField(void);
	static void SetMesh(CMeshField *pMesh) { m_pMeshField = pMesh; }
	static CFileLoad *GetFileLoad(void);
	static CPause *GetPause(void);
	static CEditor *GetEditor(void);
	CMapCamera *GetMapCamera(void) { return m_pMapCamera; }
	void DataReset(void);
	void EnemySet(void);

private:

	static CFileLoad *m_pFileLoad;		// ファイル読み込みのポインタ
	static CScore *m_pScore;			// スコアのポインタ
	static CTime *m_pTime;				// タイムのポインタ
	static CPlayer *m_pPlayer;			// プレイヤーのポインタ
	static CSlow *m_pSlow;				// スローのポインタ
	static CMeshField *m_pMeshField;	// メッシュフィールドのポインタ
	static CPause *m_pPause;			// ポーズのポインタ
	static CEditor *m_pEditor;			// エディターのポインタ
	CMapCamera *m_pMapCamera;			// ミニマップ用カメラ
	CThermo *m_pMapThermo;				// マップ全体の温度表示
	int m_nMaxEnemy;					// 現在のエネミー最大数
};

#endif