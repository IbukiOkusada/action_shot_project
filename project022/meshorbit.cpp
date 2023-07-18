//==========================================================
//
//メッシュ構造の軌跡処理 [meshorbit.cpp]
//Author Ibuki Okusada
//
//==========================================================
#include "meshorbit.h"
#include "parts.h"

//==========================================================
//グローバル変数
//==========================================================
MeshOrbit g_MeshOrbit;	//軌跡の情報

//==========================================================
//軌跡の初期化処理
//==========================================================
void InitMeshOrbit(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		//デバイスへのポインタ

	//各種変数の初期化
	g_MeshOrbit.pMtxParent = &GetBody()->mtxWorld;
	g_MeshOrbit.aOffSet[0] = D3DXVECTOR3(0.0f, 100.0f, 0.0f);
	g_MeshOrbit.aOffSet[1] = D3DXVECTOR3(0.0f, 30.0f, 0.0f);
	g_MeshOrbit.aCol[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_MeshOrbit.aCol[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * MAX_MESH,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_MeshOrbit.pVtxBuff,
		NULL);

	VERTEX_3D *pVtx;

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_MeshOrbit.pVtxBuff->Lock(
		0,
		0,
		(void**)&pVtx,
		0);

	//頂点座標の設定(左奥から右手前に向かって頂点情報を設定する
	for (int nCntpVtx = 0; nCntpVtx < MAX_MESH; nCntpVtx++)
	{
		//頂点座標
		pVtx[nCntpVtx].pos = g_MeshOrbit.aPosPoint[nCntpVtx];

		//法線
		pVtx[nCntpVtx].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//色
		pVtx[nCntpVtx].col = g_MeshOrbit.aColPoint[nCntpVtx];

		//テクスチャ
		pVtx[nCntpVtx].tex = D3DXVECTOR2(0.0f, 0.0f);
	}

	//頂点バッファをアンロックする
	g_MeshOrbit.pVtxBuff->Unlock();
}

//==========================================================
//軌跡の終了処理
//==========================================================
void UninitMeshOrbit(void)
{
	//頂点バッファの廃棄
	if (g_MeshOrbit.pMtxParent != NULL)
	{
		g_MeshOrbit.pMtxParent = NULL;
	}

	//頂点バッファの廃棄
	if (g_MeshOrbit.pVtxBuff != NULL)
	{
		g_MeshOrbit.pVtxBuff->Release();
		g_MeshOrbit.pVtxBuff = NULL;
	}
}

//==========================================================
//軌跡の更新処理
//==========================================================
void UpdateMeshOrbit(void)
{

}

//==========================================================
//軌跡の描画処理
//==========================================================
void DrawMeshOrbit(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		//デバイスへのポインタ
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DXMATRIX mtxWorld;	//ワールドマトリックス

	//ライティングをオフにする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//カリングオンにする

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_MeshOrbit.aMtxWorldPoint[0]);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_MeshOrbit.aOffSet[0].x, g_MeshOrbit.aOffSet[0].y, g_MeshOrbit.aOffSet[0].z);
	D3DXMatrixMultiply(&g_MeshOrbit.aMtxWorldPoint[0], &g_MeshOrbit.aMtxWorldPoint[0], &mtxTrans);

	//パーツのワールドマトリックスと親のマトリックスをかけ合わせる
	D3DXMatrixMultiply(&g_MeshOrbit.aMtxWorldPoint[0],
		&g_MeshOrbit.aMtxWorldPoint[0], g_MeshOrbit.pMtxParent);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_MeshOrbit.aMtxWorldPoint[0]);

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_MeshOrbit.aMtxWorldPoint[1]);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_MeshOrbit.aOffSet[1].x, g_MeshOrbit.aOffSet[1].y, g_MeshOrbit.aOffSet[1].z);
	D3DXMatrixMultiply(&g_MeshOrbit.aMtxWorldPoint[1], &g_MeshOrbit.aMtxWorldPoint[1], &mtxTrans);

	//パーツのワールドマトリックスと親のマトリックスをかけ合わせる
	D3DXMatrixMultiply(&g_MeshOrbit.aMtxWorldPoint[1],
		&g_MeshOrbit.aMtxWorldPoint[1], g_MeshOrbit.pMtxParent);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_MeshOrbit.aMtxWorldPoint[1]);

	//保存してある情報をずらす
	for (int nCntMesh = 2; nCntMesh < MAX_MESH; nCntMesh++)
	{
		g_MeshOrbit.aPosPoint[nCntMesh] = g_MeshOrbit.aPosPoint[nCntMesh - 2];
		g_MeshOrbit.aCol[nCntMesh] = g_MeshOrbit.aCol[nCntMesh - 2];
	}

	//最新の情報を代入
	g_MeshOrbit.aPosPoint[0].x = g_MeshOrbit.aMtxWorldPoint[0]._41;
	g_MeshOrbit.aPosPoint[0].y = g_MeshOrbit.aMtxWorldPoint[0]._42;
	g_MeshOrbit.aPosPoint[0].z = g_MeshOrbit.aMtxWorldPoint[0]._43;
	g_MeshOrbit.aColPoint[0] = g_MeshOrbit.aCol[0];

	g_MeshOrbit.aPosPoint[1].x = g_MeshOrbit.aMtxWorldPoint[1]._41;
	g_MeshOrbit.aPosPoint[1].y = g_MeshOrbit.aMtxWorldPoint[1]._42;
	g_MeshOrbit.aPosPoint[1].z = g_MeshOrbit.aMtxWorldPoint[1]._43;
	g_MeshOrbit.aColPoint[1] = g_MeshOrbit.aCol[1];

	//メッシュ構造の軌跡を描画

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(
		0,
		g_MeshOrbit.pVtxBuff,
		0,
		sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, NULL);

	for (int nCntParts = 0; nCntParts < MAX_MESH; nCntParts++)
	{
		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_MeshOrbit.aMtxWorldPoint[nCntParts % 2]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,	//プリミティブの種類
			0,
			nCntParts //頂点情報構造体のサイズ
			);
	}

	//カリングオフにする

	//ライティングをオンにする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}