//===============================================
//
// 弾の処理 [particle.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "particle.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "debugproc.h"
#include "explosion.h"
#include "enemy.h"

//===============================================
// マクロ定義
//===============================================
#define LIFE	(30)		// 寿命

//===============================================
// コンストラクタ
//===============================================
CParticle::CParticle()
{

}

//===============================================
// デストラクタ
//===============================================
CParticle::~CParticle()
{

}

//===============================================
// 生成
//===============================================
void CParticle::Create(D3DXVECTOR3 pos, CEffect::TYPE type)
{
	// オブジェクトの種類の設定
	Set(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), type);
}

//===============================================
// 頂点情報設定
//===============================================
void CParticle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, CEffect::TYPE type)
{
	// オブジェクトの種類の設定
	Set(pos, move, type);
}

//===============================================
// 設定
//===============================================
void CParticle::Set(D3DXVECTOR3 Defpos, D3DXVECTOR3 Defmove, CEffect::TYPE type)
{
	D3DXVECTOR3 pos = {};
	D3DXVECTOR3 move = {};	// 移動量
	D3DXCOLOR col = {};	// 色
	float fRadius = 0.0f;
	float fLife = 0;
	D3DXVECTOR3 nor;

	// 移動ベクトルを求める
	D3DXVec3Normalize(&nor, &Defmove);	// ベクトルを正規化する

	int nMoveX = (int)(D3DX_PI * nor.x) * 100;
	int nMoveY = (int)(D3DX_PI * nor.y) * 100;
	int nMoveZ = (int)(D3DX_PI * nor.z) * 100;

	switch (type)
	{
	case CEffect::TYPE_NONE:	// 何もない
		
	break;

	case CEffect::TYPE_BULLET:	// 弾

		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			// 座標の設定
			pos = Defpos;

			float fCol = (float)(rand() % 3) / 10.0f + 0.3f;

			//移動量の設定
			move.x = sinf((float)(rand() % (nMoveX + 1) - (nMoveX / 2)) / 100.0f) * ((float)(rand() % 51 - 25)) * 0.1f;
			move.y = cosf((float)(rand() % (nMoveY + 1) - (nMoveY / 2)) / 100.0f) * ((float)(rand() % 51 - 25)) * 0.1f;
			move.z = sinf((float)(rand() % (nMoveZ + 1) - (nMoveZ / 2)) / 100.0f) * ((float)(rand() % 51 - 25)) * 0.1f;

			//色の設定
			col = D3DXCOLOR(fCol, fCol + 0.1f, 1.0f, 1.0f);

			//半径の設定
			fRadius = 5.0f;

			//寿命の設定
			fLife = 10.0f;

			CEffect::Create(Defpos, move, col, fRadius, fLife, type);
		}

		break;

	case CEffect::TYPE_EXPLOSION:	// 爆発

		for (int nCnt = 0; nCnt < 8; nCnt++)
		{
			// 座標の設定
			pos = Defpos;

			//移動量の設定
			move.x = sinf((float)(rand() % 629 - 314) / 100.0f) * ((float)(rand() % 100)) / 50.0f;
			move.y = ((float)(rand() % 100)) / 10.0f + 3.0f;
			move.z = cosf((float)(rand() % 629 - 314) / 100.0f) * ((float)(rand() % 100)) / 50.0f;

			//色の設定
			col = D3DXCOLOR(0.4f, (float)(rand() % 6) / 10.0f + 0.4f, 1.0f, 1.0f);

			//半径の設定
			fRadius = 10.0f;

			//寿命の設定
			fLife = 75.0f;

			CEffect::Create(Defpos, move, col, fRadius, fLife, type);
		}

		break;

	case CEffect::TYPE_DUST:	// 爆発

		for (int nCnt = 0; nCnt < 1; nCnt++)
		{
			// 座標の設定
			pos = Defpos;

			//移動量の設定
			move.x = sinf((float)(rand() % 629 - 314) / 100.0f) * ((float)(rand() % 10 - 1)) / 10.0f;
			move.y = cosf((float)(rand() % 629 - 314) / 100.0f) * ((float)(rand() % 10 - 1)) / 10.0f;

			//色の設定
			col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

			//半径の設定
			fRadius = (float)(rand() % 20);

			//寿命の設定
			fLife = 20.0f;

			CEffect::Create(Defpos, move, col, fRadius, fLife, type);
		}

		break;

	case CEffect::TYPE_SHWBULLET:	// 弾

		for (int nCnt = 0; nCnt < 15; nCnt++)
		{
			// 座標の設定
			pos = Defpos;

			float fCol = (float)(rand() % 5) / 10.0f + 0.1f;

			//移動量の設定
			move.x = -cosf(Defmove.y + -D3DX_PI * 0.15f + D3DX_PI * 0.3f * ((rand() % 10) * 0.1f)) * 5.0f;
			move.y = rand() % 300 * 0.01f;
			move.z = -sinf(Defmove.y + -D3DX_PI * 0.15f + D3DX_PI * 0.3f * ((rand() % 10) * 0.1f)) * 5.0f;

			//色の設定
			col = D3DXCOLOR(fCol, fCol + 0.1f, 1.0f, 1.0f);

			//半径の設定
			fRadius = 15.0f;

			//寿命の設定
			fLife = 100.0f;

			CEffect::Create(Defpos, move, col, fRadius, fLife, type);
		}

		break;
	}
}