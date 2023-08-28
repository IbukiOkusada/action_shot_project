//===============================================
//
// ランキング画面の管理処理 [ranking.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "ranking.h"
#include "object2D.h"
#include "texture.h"
#include "manager.h"
#include "main.h"
#include "input.h"
#include "fade.h"
#include "score.h"

//===============================================
// マクロ定義
//===============================================
#define RANKING_FILE	"data\\FILE\\ranking.bin"	// ランキングファイル
#define AUTOMOVE_TITLE	(600)						// タイトル自動遷移タイマー

//===============================================
// 静的メンバ変数
//===============================================
CScore *CRanking::m_apScore[NUM_RANK] = {};	// ランキングのポインタ
int CRanking::m_nScore = 0;					// スコア

//===============================================
// コンストラクタ
//===============================================
CRanking::CRanking()
{
	// 値をクリアする
	m_nTimer = 0;
	m_nRank = 0;
}

//===============================================
// デストラクタ
//===============================================
CRanking::~CRanking()
{

}

//===============================================
// 初期化処理
//===============================================
HRESULT CRanking::Init(void)
{
	int aScore[NUM_RANK] = {};	// スコア格納用
	m_nRank = -1;	//ランクインしてない状態

	// データの読み込み
	Load(&aScore[0]);

	// データのソート
	Sort(&aScore[0]);

	// ランクイン確認
	RankIn(&aScore[0], m_nScore);

	// ロゴの生成
	CObject2D *p = CObject2D::Create();
	p->BindTexture(CManager::GetTexture()->Regist("data\\TEXTURE\\ranking_logo.png"));
	p->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.15f, 0.0f));
	p->SetSize(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);

	// 順位分スコアの生成
	for (int nCntRank = 0; nCntRank < NUM_RANK; nCntRank++)
	{
		if (m_apScore[nCntRank] == NULL)
		{
			p = CObject2D::Create();
			p->BindTexture(CManager::GetTexture()->Regist("data\\TEXTURE\\ranking001.png"));
			p->SetPosition(D3DXVECTOR3(350.0f, 250.0f + nCntRank * 100.0f, 0.0f));
			p->SetSize(30, 50);
			p->SetVtx(nCntRank + 1, 10, 1);

			m_apScore[nCntRank] = CScore::Create(D3DXVECTOR3(450.0f, 250.0f + nCntRank * 100.0f, 0.0f));
			m_apScore[nCntRank]->Set(aScore[nCntRank]);

			if (m_nRank == nCntRank)
			{
				m_apScore[nCntRank]->SetColor(D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f));
			}
		}
	}

	return S_OK;
}

//===============================================
// 終了処理
//===============================================
void CRanking::Uninit(void)
{
	for (int nCntRank = 0; nCntRank < NUM_RANK; nCntRank++)
	{
		if (m_apScore[nCntRank] != NULL)
		{
			m_apScore[nCntRank]->Uninit();
			delete m_apScore[nCntRank];	// メモリの開放
			m_apScore[nCntRank] = NULL;	// 使用していない状態にする
		}
	}

	m_nScore = 0;
}

//===============================================
// 更新処理
//===============================================
void CRanking::Update(void)
{
	CInputPad *pInputPad = CManager::GetInputPad();

	if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) || pInputPad->GetTrigger(CInputPad::BUTTON_A, 0))
	{
		CManager::GetFade()->Set(CScene::MODE_TITLE);
	}

	CScene::Update();

	if (CManager::GetFade()->GetState() == CFade::STATE_NONE)
	{
		m_nTimer++;

		if (m_nTimer >= AUTOMOVE_TITLE)
		{// タイトル自動遷移規定値
			CManager::GetFade()->Set(CScene::MODE_TITLE);
		}
	}
}

//===============================================
// 描画処理
//===============================================
void CRanking::Draw(void)
{
	CScene::Draw();
}

//===============================================
// ランキングデータ保存
//===============================================
void CRanking::Save(int *pScore)
{
	FILE *pFile;

	pFile = fopen(RANKING_FILE, "wb");

	if (pFile != NULL)
	{//ファイルが開けた場合

		//データを読み込む
		fwrite(pScore, sizeof(int), NUM_RANK, pFile);

		//ファイルを閉じる
		fclose(pFile);
	}
}

//===============================================
// ランキングデータ読み込み
//===============================================
void CRanking::Load(int *pScore)
{
	FILE *pFile;

	pFile = fopen(RANKING_FILE, "rb");

	if (pFile != NULL)
	{//ファイルが開けた場合

		//データを読み込む
		fread(pScore, sizeof(int), NUM_RANK, pFile);

		//ファイルを閉じる
		fclose(pFile);
	}
	else
	{//ファイルが開けなかった場合
		//要素を入れておく
		for (int nCntRanking = 0; nCntRanking < NUM_RANK; nCntRanking++)
		{
			pScore[nCntRanking] = 5 * (nCntRanking + 1);
		}
	}
}

//===============================================
// ランキングデータソート
//===============================================
void CRanking::Sort(int *pScore)
{
	// 降順ソート
	for (int nCntFst = 0; nCntFst < NUM_RANK - 1; nCntFst++)
	{
		int nTempNum = nCntFst;	// 仮の一番大きい番号

		for (int nCntSec = nCntFst + 1; nCntSec < NUM_RANK; nCntSec++)
		{
			if (pScore[nCntSec] > pScore[nTempNum])
			{// 値が大きい場合
				nTempNum = nCntSec;	// 大きい番号を変更
			}
		}

		if (nTempNum != nCntFst)
		{// 変更する場合
			int nTemp = pScore[nCntFst];
			pScore[nCntFst] = pScore[nTempNum];
			pScore[nTempNum] = nTemp;
		}
	}
}

//===============================================
// ランキングイン確認
//===============================================
void CRanking::RankIn(int *pScore, int nResult)
{
	if (nResult > pScore[NUM_RANK - 1])
	{
		pScore[NUM_RANK - 1] = nResult;

		// ソート処理
		Sort(pScore);

		// 保存処理
		Save(pScore);

		//ランクインした順位を確認する
		for (int nCntRank = 0; nCntRank < NUM_RANK; nCntRank++)
		{
			if (pScore[nCntRank] == nResult)
			{
				m_nRank = nCntRank;	// ランクインした順位を保存
				
				break;
			}
		}
	}
}