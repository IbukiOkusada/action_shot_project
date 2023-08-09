//==========================================================
//
// フィルターの処理 [filter.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "filter.h"
#include "manager.h"
#include "game.h"
#include "texture.h"
#include "slow.h"

//===============================================
// マクロ定義
//===============================================
#define GUN_DEFHEIGHT	(700)				// デフォルトから追加で画面外に生成する高さ
#define GUN_DEFWIDTH	(GUN_DEFHEIGHT * 2)	// デフォルトから追加で画面外に生成する幅
#define GUN_MULTIWIDTH	(2)					// 倍率
#define GUN_MOVE		(-100.0f)
#define GUN_COLA		(0.1f)

//====================================================================================
// オブジェクト2Dクラス
//====================================================================================
//===============================================
// コンストラクタ
//===============================================
//CFilter::CFilter()
//{
//	// 値をクリアする
//}

//===============================================
// コンストラクタ(オーバーロード)
//===============================================
CFilter::CFilter(int nPriority) : CObject2D(nPriority)
{
	// 値をクリアする
	m_fCola = 0.0f;
	m_fSpeed = 0.0f;
}

//===============================================
// デストラクタ
//===============================================
CFilter::~CFilter()
{

}

//===============================================
// 初期化処理
//===============================================
HRESULT CFilter::Init(void)
{
	CObject2D::Init();

	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	m_fSpeed = GUN_MOVE;
	m_fCola = GUN_COLA;
	m_state = STATE_START;

	return S_OK;
}

//===============================================
// 終了処理
//===============================================
void CFilter::Uninit(void)
{
	CObject2D::Uninit();
}

//===============================================
// 更新処理
//===============================================
void CFilter::Update(void)
{
	float fWidth = GetWidth();
	float fHeight = GetHeight();

	switch (m_state)
	{
	case STATE_NONE:
		break;

	case STATE_NORMAL:

		if (CManager::GetSlow()->Get() > CManager::GetSlow()->GetOld())
		{
			m_state = STATE_END;
		}

		break;

	case STATE_START:

		// サイズ変更
		fWidth += m_fSpeed * GUN_MULTIWIDTH;
		fHeight += m_fSpeed;
		m_col.a += m_fCola;

		if (fWidth < SCREEN_WIDTH * 0.5f || fHeight <= SCREEN_HEIGHT * 0.5f || (CManager::GetSlow()->Get() == 1.0f && CManager::GetSlow()->GetOld() != 1.0f))
		{// 規定値にたどり着いた
			fWidth = SCREEN_WIDTH * 0.5f;
			fHeight = SCREEN_HEIGHT * 0.5f;
			m_state = STATE_NORMAL;
			m_fSpeed *= -1.0f;
			m_fCola *= -1.0f;
			m_col.a = 1.0f;
		}

		SetSize(fWidth, fHeight);
		SetCol(m_col);

		break;

	case STATE_END:

		// サイズ変更
		fWidth += m_fSpeed * GUN_MULTIWIDTH;
		fHeight += m_fSpeed;
		m_col.a += m_fCola;
		SetSize(fWidth, fHeight);
		SetCol(m_col);

		if (fWidth > SCREEN_WIDTH * 0.5f + GUN_DEFWIDTH || fHeight > SCREEN_HEIGHT * 0.5f + GUN_DEFHEIGHT)
		{// 規定値にたどり着いた
			Uninit();
		}

		break;
	}
}

//===============================================
// 描画処理
//===============================================
void CFilter::Draw(void)
{
	CObject2D::Draw();
}

//===============================================
// 頂点情報設定
//===============================================
CFilter *CFilter::Create(TYPE type)
{
	CFilter *pObject2D = NULL;

	// オブジェクト2Dの生成
	pObject2D = new CFilter(6);

	if (pObject2D != NULL)
	{// 生成できた場合
	 // 初期化処理
		pObject2D->Init();

		pObject2D->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));

		pObject2D->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		pObject2D->SetSize(SCREEN_WIDTH * 0.5f + GUN_DEFWIDTH, SCREEN_HEIGHT * 0.5f + GUN_DEFHEIGHT);

		// 種類設定
		pObject2D->SetType(TYPE_NONE);

		pObject2D->m_state = STATE_START;

		pObject2D->BindTexture(CManager::GetTexture()->Regist(CManager::GetTexture()->GetFileName(CTexture::TYPE_SLOWGUNFIL)));
	}
	else
	{// 生成に失敗した場合
		return NULL;
	}

	return pObject2D;
}
