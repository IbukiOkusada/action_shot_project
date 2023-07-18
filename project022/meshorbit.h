//==========================================================
//
//メッシュ構造の軌跡処理 [meshorbit.h]
//Author Ibuki Okusada
//
//==========================================================
#ifndef _MESHORBIT_H_
#define _MESHORBIT_H_

#include "main.h"	//main.hで定義しているものが必要なためinclude

//==========================================================
//マクロ定義
//==========================================================
#define MAX_MESH	(2 * 10 + 2)	//軌跡の頂点数

//==========================================================
//構造体の定義
//==========================================================
//軌跡
typedef struct
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;	//頂点バッファのポインタ
	D3DXMATRIX *pMtxParent;				//親のマトリックスのポインタ
	D3DXVECTOR3 aOffSet[2];				//両端のオフセット
	D3DXCOLOR aCol[2];					//両端の基準色
	D3DXMATRIX aMtxWorldPoint[2];		//両端のワールドマトリックス
	D3DXVECTOR3 aPosPoint[MAX_MESH];	//計算後の各頂点情報
	D3DXCOLOR aColPoint[MAX_MESH];		//各頂点カラー
}MeshOrbit;

//==========================================================
//プロトタイプ宣言
//==========================================================
void InitMeshOrbit(void);
void UninitMeshOrbit(void);
void UpdateMeshOrbit(void);
void DrawMeshOrbit(void);

#endif
