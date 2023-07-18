//===============================================
//
// プレイヤーの処理 [player.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "player.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "debugproc.h"
#include "bullet.h"
#include "explosion.h"
#include "multibg.h"
#include "particle.h"
#include "camera.h"
#include "Xfile.h"
#include "shadow.h"
#include "waist.h"
#include "character.h"
#include "motion.h"
#include "model.h"
#include "slow.h"
#include "texture.h"
#include "meshfield.h"
#include "Xfile.h"
#include "lockon.h"

//===============================================
// マクロ定義
//===============================================
#define MOVE	(3.0f)		// 移動量
#define PLAYER_GRAVITY	(-0.2f)	//プレイヤー重力
#define PLAYER_JUMP		(11.0f)	//プレイヤージャンプ力
#define DEF_SLOWTIME	(60 * 5)	// スロー可能時間
#define SLOW_OK			(60 * 2)	// スロー可能になる時間
#define SHOT_LENGTH	(4000.0f)		// 射程範囲
#define SHOT_RANGE	(D3DX_PI * 0.9f)	// 射程角度

//===============================================
// 武器ごとの設定
//===============================================
const D3DXVECTOR3 CPlayer::SetWepPos[WEAPON_MAX] =	// 武器設定位置
{
	{ -13.0f, 4.5f, 0.0f },
	{ 13.0f, 4.5f, 0.0f },
	{ -7.0f, 13.0f, 0.0f },
};

//===============================================
// 武器ごとの攻撃タイマー
//===============================================
const int CPlayer::m_aWepTimer[ATK_MAX] =		// 攻撃タイマー
{
	19,
	5,
};

//===============================================
// 武器ファイル名
//===============================================
const char *CPlayer::m_apFileName[WEAPON_MAX] = 
{
	"data\\MODEL\\sample\\watergunL.x",
	"data\\MODEL\\sample\\watergunR.x",
	"data\\MODEL\\sample\\watershower.x",
};

//===============================================
// コンストラクタ
//===============================================
//CPlayer::CPlayer()
//{
//	// 値をクリアする
//	m_nCounterAnim = 0;
//	m_nPatternAnim = 0;
//}

//===============================================
// コンストラクタ(オーバーロード)
//===============================================
CPlayer::CPlayer(const D3DXVECTOR3 pos)
{
	// 値をクリアする
	m_bJump = false;
	m_Info.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fRotMove = 0.0f;
	m_fRotDiff = 0.0f;
	m_fRotDest = 0.0f;
	m_nSlowTime = 0;
	pShadow = NULL;
	m_pBody = NULL;
	m_pLeg = NULL;
	m_pWaist = NULL;
	m_pWeaponL = NULL;
	m_pWeaponR = NULL;
}

//===============================================
// コンストラクタ(オーバーロード)
//===============================================
CPlayer::CPlayer(int nPriOrity)
{
	// 値をクリアする
	m_bJump = false;
	m_bSlow = false;
	m_Info.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fRotMove = 0.0f;
	m_fRotDiff = 0.0f;
	m_fRotDest = 0.0f;
	m_nSlowTime = 0;
	pShadow = NULL;
	m_pBody = NULL;
	m_pLeg = NULL;
	m_pWaist = NULL;
	m_bAttack = false;
	m_nAttackTimer = 0;
	m_nAttackHand = 0;

	for (int nCnt = 0; nCnt < WEAPON_MAX; nCnt++)
	{
		m_aWepNum[nCnt] = -1;
	}
}

//===============================================
// デストラクタ
//===============================================
CPlayer::~CPlayer()
{

}

//===============================================
// 初期化処理
//===============================================
HRESULT CPlayer::Init(void)
{
	// 腰の生成
	if (m_pWaist == NULL)
	{
		m_pWaist = new CWaist;
		m_pWaist->SetParent(&m_Info.mtxWorld);
	}

	return S_OK;
}

//===============================================
// 初期化処理(オーバーロード)
//===============================================
HRESULT CPlayer::Init(const char *pBodyName, const char *pLegName)
{
	CTexture *pTexture = CManager::GetTexture();

	// 腰の生成
	if (m_pWaist == NULL)
	{
		m_pWaist = new CWaist;
		m_pWaist->SetParent(&m_Info.mtxWorld);
	}

	// 胴体の設定
	if (pBodyName != NULL)
	{// ファイル名が存在している
		m_pBody = CCharacter::Create(pBodyName);
		m_pBody->SetParent(m_pWaist->GetMtxWorld());

		if (m_pBody->GetMotion() != NULL)
		{
			// 初期モーションの設定
			m_pBody->GetMotion()->InitSet(BMOTION_NEUTRAL);
		}
	}

	// 下半身の設定
	if (pLegName != NULL)
	{// ファイル名が存在している
		m_pLeg = CCharacter::Create(pLegName);
		m_pLeg->SetParent(m_pWaist->GetMtxWorld());

		if (m_pLeg->GetMotion() != NULL)
		{
			// 初期モーションの設定
			m_pLeg->GetMotion()->InitSet(LMOTION_NEUTRAL);
		}
	}

	// 腰の高さを合わせる
	if (m_pLeg != NULL)
	{// 脚が使用されている場合
		CModel *pModel = m_pLeg->GetParts(0);	// 腰パーツを取得

		if (pModel != NULL)
		{// パーツが存在する場合
			D3DXVECTOR3 pos = pModel->GetPosition();	// モデルの相対位置を取得

			// 高さを設定
			m_pWaist->SetHeight(pos);

			// 腰のモデルの位置を変更
			pModel->SetPosition(pos);
		}
	}

	// スロー可能時間を初期設定
	m_nSlowTime = DEF_SLOWTIME;

	CModel *pModel = m_pBody->GetParts(9);	// 腰パーツを取得

	// 武器の設定
	m_pWeaponL = CModel::Create(m_apFileName[WEAPON_GUNL]);
	m_pWeaponL->SetPosition(SetWepPos[WEAPON_GUNL]);
	m_pWeaponL->SetParent(pModel->GetMtxWorld());

	pModel = m_pBody->GetParts(5);	// 腰パーツを取得

	// 武器の設定
	m_pWeaponR = CModel::Create(m_apFileName[WEAPON_GUNR]);
	m_pWeaponR->SetPosition(SetWepPos[WEAPON_GUNR]);
	m_pWeaponR->SetParent(pModel->GetMtxWorld());

	// 種類設定
	m_WepType = ATK_GUN;

	// 武器番号取得
	for (int nCnt = 0; nCnt < WEAPON_MAX; nCnt++)
	{
		m_aWepNum[nCnt] = CManager::GetModelFile()->Regist(m_apFileName[nCnt]);
	}

	// ロックオンの生成
	m_pLockon = CLockOn::Create(m_pBody->GetMtxWorld());
	m_pLockon->SetDistance(SHOT_LENGTH, SHOT_RANGE);
	m_pLockon->SetLock(true);

	return S_OK;
}

//===============================================
// 終了処理
//===============================================
void CPlayer::Uninit(void)
{
	// 胴体の終了処理
	if (m_pBody != NULL)
	{
		m_pBody->Uninit();
		delete m_pBody;
		m_pBody = NULL;
	}

	// 下半身の終了処理
	if (m_pLeg != NULL)
	{
		m_pLeg->Uninit();
		delete m_pLeg;
		m_pLeg = NULL;
	}

	// 腰の終了処理
	if (m_pWaist != NULL)
	{
		delete m_pWaist;
		m_pWaist = NULL;
	}

	// 武器の終了
	if (m_pWeaponL != NULL)
	{
		m_pWeaponL->Uninit();
		delete m_pWeaponL;
		m_pWeaponL = NULL;
	}
	if (m_pWeaponR != NULL)
	{
		m_pWeaponR->Uninit();
		delete m_pWeaponR;
		m_pWeaponR = NULL;
	}

	// 廃棄
	Release();
}

//===============================================
// 更新処理
//===============================================
void CPlayer::Update(void)
{
	// 前回の座標を取得
	m_Info.posOld = GetPosition();

	// 胴体更新
	if (m_pBody != NULL)
	{// 使用されている場合
		m_pBody->Update();
	}
	
	// 下半身更新
	if (m_pLeg != NULL)
	{// 使用されている場合
		m_pLeg->Update();

		CModel *pModel = m_pLeg->GetParts(0);

		// 腰の高さを補填
		if (pModel != NULL)
		{
			m_pWaist->SetPosition(m_pWaist->GetSetPosition() + pModel->GetCurrentPosition());
		}
	}

	// プレイヤー操作
	Controller();

	// 向き設定
	SetBodyRot();

	// カメラ追従
	CCamera *pCamera = CManager::GetCamera();

	// 追従処理
	pCamera->Pursue(GetPosition(), GetRotation());
}

//===============================================
// 描画処理
//===============================================
void CPlayer::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	//デバイスへのポインタを取得
	CTexture *pTexture = CManager::GetTexture();	// テクスチャへのポインタ
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_Info.mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Info.rot.y, m_Info.rot.x, m_Info.rot.z);
	D3DXMatrixMultiply(&m_Info.mtxWorld, &m_Info.mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_Info.pos.x, m_Info.pos.y, m_Info.pos.z);
	D3DXMatrixMultiply(&m_Info.mtxWorld, &m_Info.mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_Info.mtxWorld);

	// 腰の設定
	if (m_pWaist != NULL)
	{
		m_pWaist->SetMatrix();
	}

	// 下半身の描画
	if (m_pLeg != NULL)
	{
		CModel *pModel = m_pLeg->GetParts(0);

		D3DXVECTOR3 pos = pModel->GetCurrentPosition();

		pModel->SetCurrentPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		m_pLeg->Draw();

		pModel->SetCurrentPosition(pos);
	}

	// 胴体の描画
	if (m_pBody != NULL)
	{
		m_pBody->Draw();
	}
	
	// 武器の描画
	if (m_pWeaponL != NULL)
	{
		m_pWeaponL->Draw();
	}

	// 武器の描画
	if (m_pWeaponR != NULL && m_WepType == ATK_GUN)
	{// 使用しているかつ二丁持ち
		m_pWeaponR->Draw();
	}
}

//===============================================
// 生成
//===============================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, const char *pBodyName, const char *pLegName, const int nPriority)
{
	CPlayer *pPlayer = NULL;
	CXFile *pModelFile = CManager::GetModelFile();

	// オブジェクト2Dの生成
	pPlayer = new CPlayer(nPriority);

	if (pPlayer != NULL)
	{// 生成できた場合
		// 初期化処理
		pPlayer->Init(pBodyName, pLegName);

		// 座標設定
		pPlayer->SetPosition(pos);

		// 向き設定
		pPlayer->SetRotation(rot);

		// 移動量設定
		pPlayer->SetMove(move);

		// 種類の設定
		pPlayer->SetType(TYPE_PLAYER);

		// 影の設定
		pPlayer->pShadow = CShadow::Create(pos, 30.0f, 30.0f);
	}
	else
	{// 生成に失敗した場合
		return NULL;
	}

	return pPlayer;
}

//===============================================
// 操作処理
//===============================================
void CPlayer::Controller(void)
{
	D3DXVECTOR3 pos = GetPosition();	// 座標を取得
	D3DXVECTOR3 rot = GetRotation();	// 向きを取得
	CInputKeyboard *pInputKey = CManager::GetInputKeyboard();	// キーボードのポインタ
	CInputMouse *pInputMouse = CManager::GetInputMouse();
	CCamera *pCamera = CManager::GetCamera();		// カメラのポインタ
	D3DXVECTOR3 CamRot = pCamera->GetRotation();	// カメラの角度
	m_fRotMove = rot.y;	//現在の向きを取得
	m_bMove = false;	// 移動状態リセット

	// 移動
	if (m_bJump == false)
	{// ジャンプしていない場合
		Move();
	}

	if (m_bJump == false && m_bMove == true)
	{// ジャンプしていない状態で移動
		if (m_bAttack == false)
		{
			m_pBody->GetMotion()->BlendSet(BMOTION_WALK);
		}
		m_pLeg->GetMotion()->BlendSet(LMOTION_WALK);
	}
	else if (m_bJump == false && m_bMove == false)
	{
		if (m_bAttack == false)
		{
			m_pBody->GetMotion()->BlendSet(BMOTION_NEUTRAL);
		}
		m_pLeg->GetMotion()->BlendSet(LMOTION_NEUTRAL);
	}
	else if (m_bJump == true && m_bAttack == false)
	{
		m_pBody->GetMotion()->BlendSet(BMOTION_JUMP);
	}

	// 武器切り替え
	if (pInputKey->GetTrigger(DIK_Q) == true)
	{// Qキー
		m_WepType = (ATK)((m_WepType + 1) % ATK_MAX);

		switch (m_WepType)
		{
		case ATK_GUN:
			m_pWeaponL->BindModelFile(m_aWepNum[WEAPON_GUNL]);
			m_pWeaponL->SetPosition(SetWepPos[WEAPON_GUNL]);
			break;

		case ATK_SHOWER:
			m_pWeaponL->BindModelFile(m_aWepNum[WEAPON_SHOWER]);
			m_pWeaponL->SetPosition(SetWepPos[WEAPON_SHOWER]);
			break;
		}

		if (m_WepType == ATK_GUN)
		{
			m_pLockon->SetLock(true);
		}
		else
		{
			m_pLockon->SetLock(false);
		}
	}
	else if (pInputKey->GetTrigger(DIK_E) == true)
	{// Eキー
		m_WepType = (ATK)((m_WepType + ATK_MAX - 1) % ATK_MAX);

		switch (m_WepType)
		{
		case ATK_GUN:
			m_pWeaponL->BindModelFile(m_aWepNum[WEAPON_GUNL]);
			m_pWeaponL->SetPosition(SetWepPos[WEAPON_GUNL]);
			break;

		case ATK_SHOWER:
			m_pWeaponL->BindModelFile(m_aWepNum[WEAPON_SHOWER]);
			m_pWeaponL->SetPosition(SetWepPos[WEAPON_SHOWER]);
			break;
		}

		if (m_WepType == ATK_GUN)
		{
			m_pLockon->SetLock(true);
		}
		else
		{
			m_pLockon->SetLock(false);
		}
	}

	// ジャンプ
	Jump();

	//攻撃
	Attack();

	// スロー操作
	Slow();

	float fGravity = PLAYER_GRAVITY * CManager::GetSlow()->Get();
	m_Info.move.y += fGravity;
	pos.y += m_Info.move.y * CManager::GetSlow()->Get();

	if (m_bJump == false)
	{
		m_Info.move.x += (0.0f - m_Info.move.x) * 0.12f;	//x座標
		m_Info.move.z += (0.0f - m_Info.move.z) * 0.12f;	//x座標
	}

	pos.x += m_Info.move.x * CManager::GetSlow()->Get();
	pos.z += m_Info.move.z * CManager::GetSlow()->Get();

	if (m_fRotDest > D3DX_PI || m_fRotDest < -D3DX_PI)
	{//-3.14～3.14の範囲外の場合
		if (m_fRotDest > D3DX_PI)
		{
			m_fRotDest += (-D3DX_PI * 2);
		}
		else if (m_fRotDest < -D3DX_PI)
		{
			m_fRotDest += (D3DX_PI * 2);
		}
	}

	m_fRotDiff = m_fRotDest - m_fRotMove;	//目標までの移動方向の差分

	if (m_fRotDiff > D3DX_PI || m_fRotDiff < -D3DX_PI)
	{//-3.14～3.14の範囲外の場合
		if (m_fRotDiff > D3DX_PI)
		{
			m_fRotDiff += (-D3DX_PI * 2);
		}
		else if (m_fRotDiff < -D3DX_PI)
		{
			m_fRotDiff += (D3DX_PI * 2);
		}
	}

	rot.y += m_fRotDiff * 0.08f;

	if (rot.y > D3DX_PI || rot.y < -D3DX_PI)
	{//-3.14～3.14の範囲外の場合
		if (rot.y > D3DX_PI)
		{
			rot.y += (-D3DX_PI * 2);
		}
		else if (rot.y < -D3DX_PI)
		{
			rot.y += (D3DX_PI * 2);
		}
	}

	if (pos.y < 0.0f)
	{
		m_Info.move.y = 0.0f;
		pos.y = 0.0f;
		m_bJump = false;
	}

	D3DXVECTOR3 nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float fHeight = CManager::GetMeshField()->GetHeight(pos, nor);

	if (fHeight > pos.y)
	{// 
		pos.y = fHeight;
		m_bJump = false;
	}

	// 影の座標更新
	if (pShadow != NULL)
	{
		pShadow->SetPosition(D3DXVECTOR3(m_pBody->GetParts(0)->GetMtxWorld()->_41, 0.0f, m_pBody->GetParts(0)->GetMtxWorld()->_43));
	}


	// 頂点情報設定
	SetRotation(rot);
	SetPosition(pos);

	pos = GetPosition();

	// デバッグ表示
	CManager::GetDebugProc()->Print("\n移動[W,A,S,D] : ジャンプ[SPACE] : 発射[L, マウス左クリック]\n : スロー[ENTER長押し, マウス右クリック長押し]\n");
	CManager::GetDebugProc()->Print("プレイヤーの座標[ %f, %f, %f ]\n", pos.x, pos.y, pos.z);
	CManager::GetDebugProc()->Print("プレイヤーの向き[ %f, %f, %f ]\n", rot.x, rot.y, rot.z);
	CManager::GetDebugProc()->Print("プレイヤーの移動量[ %f, %f, %f ]\n", m_Info.move.x, m_Info.move.y, m_Info.move.z);
	CManager::GetDebugProc()->Print("スロー可能タイマー[ %d ]\n", m_nSlowTime);
	CManager::GetDebugProc()->Print("重力[ %f ]\n", fGravity);
}

//===============================================
// 移動
//===============================================
void CPlayer::Move(void)
{
	CCamera *pCamera = CManager::GetCamera();		// カメラのポインタ
	D3DXVECTOR3 CamRot = pCamera->GetRotation();	// カメラの角度
	CInputKeyboard *pInputKey = CManager::GetInputKeyboard();	// キーボードのポインタ
	float fSpeed = MOVE;	// 移動量

	//プレイヤーの更新
	if (pInputKey->GetPress(DIK_A) == true)
	{
		if (pInputKey->GetPress(DIK_W) == true)
		{
			m_Info.move.x += cosf(CamRot.y + (-D3DX_PI * 0.75f)) * fSpeed;
			m_Info.move.z += sinf(CamRot.y + (-D3DX_PI * 0.75f)) * fSpeed;
			m_fRotDest = (-CamRot.y + D3DX_PI * 0.25f);
		}
		else if (pInputKey->GetPress(DIK_S) == true)
		{
			m_Info.move.x += cosf(CamRot.y + (-D3DX_PI * 0.25f)) * fSpeed;
			m_Info.move.z += sinf(CamRot.y + (-D3DX_PI * 0.25f)) * fSpeed;
			m_fRotDest = (-CamRot.y + -D3DX_PI * 0.25f);
		}
		else
		{
			m_Info.move.x += cosf(CamRot.y + (-D3DX_PI * 0.5f)) * fSpeed;
			m_Info.move.z += sinf(CamRot.y + (-D3DX_PI * 0.5f)) * fSpeed;
			m_fRotDest = -CamRot.y;
		}

		// 移動した状態にする
		m_bMove = true;
	}
	else if (pInputKey->GetPress(DIK_D) == true)
	{
		if (pInputKey->GetPress(DIK_W) == true)
		{
			m_Info.move.x += cosf(CamRot.y + (D3DX_PI * 0.75f)) * fSpeed;
			m_Info.move.z += sinf(CamRot.y + (D3DX_PI * 0.75f)) * fSpeed;

			m_fRotDest = (-CamRot.y + D3DX_PI * 0.75f);
		}
		else if (pInputKey->GetPress(DIK_S) == true)
		{
			m_Info.move.x += cosf(CamRot.y + (D3DX_PI * 0.25f)) * fSpeed;
			m_Info.move.z += sinf(CamRot.y + (D3DX_PI * 0.25f)) * fSpeed;

			m_fRotDest = (-CamRot.y + -D3DX_PI * 0.75f);
		}
		else
		{
			m_Info.move.x += cosf(CamRot.y + (D3DX_PI * 0.5f)) * fSpeed;
			m_Info.move.z += sinf(CamRot.y + (D3DX_PI * 0.5f)) * fSpeed;
			m_fRotDest = (-CamRot.y + D3DX_PI * 1.0f);
		}

		// 移動した状態にする
		m_bMove = true;
	}
	else if (pInputKey->GetPress(DIK_W) == true)
	{
		m_Info.move.x += -cosf(CamRot.y) * fSpeed;
		m_Info.move.z += -sinf(CamRot.y) * fSpeed;
		m_fRotDest = (-CamRot.y + D3DX_PI * 0.5f);

		// 移動した状態にする
		m_bMove = true;

	}
	else if (pInputKey->GetPress(DIK_S) == true)
	{
		m_Info.move.x += cosf(CamRot.y) * fSpeed;
		m_Info.move.z += sinf(CamRot.y) * fSpeed;
		m_fRotDest = (-CamRot.y + -D3DX_PI * 0.5f);

		// 移動した状態にする
		m_bMove = true;
	}
}

//===============================================
// スロー関連
//===============================================
void CPlayer::Slow(void)
{
	CInputKeyboard *pInputKey = CManager::GetInputKeyboard();	// キーボードのポインタ
	CInputMouse *pInputMouse = CManager::GetInputMouse();

	// スロータイマー
	if (m_bSlow == false)
	{// 入力可能
		if (pInputKey->GetPress(DIK_RETURN) == true || pInputMouse->GetPress(CInputMouse::BUTTON_RBUTTON) == true)
		{// ENTERキーが入力された場合
			if (m_nSlowTime > 0)
			{// 残っている場合
				m_nSlowTime--;
				CManager::GetSlow()->SetSlow(true);
			}
			else
			{
				m_bSlow = true;	// スローにできない状態にする
				CManager::GetSlow()->SetSlow(false);
			}
		}
		else
		{
			// 可能時間回復
			if (m_nSlowTime < SLOW_OK)
			{// スロー可能の時間より短い
				m_bSlow = true;
			}
			else if (m_nSlowTime < DEF_SLOWTIME)
			{// 上限まで
				m_nSlowTime++;
			}

			CManager::GetSlow()->SetSlow(false);
		}
	}
	else
	{// できない
		if (m_nSlowTime < SLOW_OK)
		{
			m_nSlowTime++;
		}
		else
		{
			m_bSlow = false;	// スロー可能状態にする
		}
	}
}

//===============================================
// 胴体の向き変更
//===============================================
void CPlayer::SetBodyRot(void)
{
	CCamera *pCamera = CManager::GetCamera();		// カメラのポインタ
	D3DXVECTOR3 CamRot = pCamera->GetRotation();	// カメラの角度

	if (m_pBody == NULL || m_pLeg == NULL)
	{// 二段階の階層構造ではない場合
		return;
	}

	D3DXVECTOR3 rot = m_pBody->GetRotation();	// 胴体の向きを取得

	rot.y = (-CamRot.y + D3DX_PI * 0.5f) - m_Info.rot.y;	// カメラの向いている方向に合わせる

	if (rot.z < -D3DX_PI)
	{// z座標角度限界
		rot.z += D3DX_PI * 2;
	}
	else if (rot.z > D3DX_PI)
	{// z座標角度限界
		rot.z += -D3DX_PI * 2;
	}

	if (rot.x < -D3DX_PI)
	{// x座標角度限界
		rot.x += D3DX_PI * 2;
	}
	else if (rot.x > D3DX_PI)
	{// x座標角度限界
		rot.x += -D3DX_PI * 2;
	}

	if (rot.y < -D3DX_PI)
	{// x座標角度限界
		rot.y += D3DX_PI * 2;
	}
	else if (rot.y > D3DX_PI)
	{// x座標角度限界
		rot.y += -D3DX_PI * 2;
	}

	rot.y *= 0.6f;

	// 胴体の向きを設定
	m_pBody->SetRotation(rot);
}

//===============================================
// 攻撃
//===============================================
void CPlayer::Attack(void)
{
	CInputKeyboard *pInputKey = CManager::GetInputKeyboard();	// キーボードのポインタ
	CInputMouse *pInputMouse = CManager::GetInputMouse();
	CCamera *pCamera = CManager::GetCamera();		// カメラのポインタ
	D3DXVECTOR3 CamRot = pCamera->GetRotation();	// カメラの角度
	D3DXVECTOR3 BulletMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CBullet *pBullet = NULL;

	if (pInputKey->GetPress(DIK_L) == true || pInputMouse->GetPress(CInputMouse::BUTTON_LBUTTON) == true)
	{//ENTERキーが押されたとき
		if (m_nAttackTimer == 0)
		{
			D3DXMATRIX mtx;
			switch (m_WepType)
			{
			case ATK_GUN:

				m_pBody->GetMotion()->Set(BMOTION_TWINATK);

				if (m_nAttackHand == 0)
				{
					mtx = *m_pWeaponL->GetMtxWorld();
				}
				else
				{
					mtx = *m_pWeaponR->GetMtxWorld();
				}

				if (m_pLockon->GetLock() == false)
				{// ロックオンしていない
					BulletMove = { -cosf(CamRot.y) * 50.0f, 0.0f, -sinf(CamRot.y) * 50.0f };
				}
				else
				{// ロックオンしている
					D3DXVECTOR3 vec;
					vec.x = m_pLockon->GetPosition().x - mtx._41;
					vec.y = m_pLockon->GetPosition().y - mtx._42;
					vec.z = m_pLockon->GetPosition().z - mtx._43;

					D3DXVec3Normalize(&vec, &vec);	// ベクトルを正規化する

					BulletMove = vec * 20.0f;
				}


				// 弾の発射
				pBullet = CBullet::Create(D3DXVECTOR3(mtx._41, mtx._42, mtx._43),
					D3DXVECTOR3(BulletMove.x, BulletMove.y, BulletMove.z), CBullet::TYPE_NONE);

				if (m_pLockon->GetLock() == true)
				{// ロックオンしている
					//pBullet->SetHom(&*m_pLockon->GetTag(), 50.0f);
				}

				m_nAttackHand ^= 1;
				break;
			case ATK_SHOWER:
				m_pBody->GetMotion()->Set(BMOTION_SHWATK);
				mtx = *m_pWeaponL->GetMtxWorld();

				BulletMove = { -cosf(CamRot.y) * 2.0f, 1.0f, -sinf(CamRot.y) * 2.0f };

				// 弾の発射
				pBullet = CBullet::Create(D3DXVECTOR3(mtx._41, mtx._42, mtx._43),
					D3DXVECTOR3(BulletMove.x, BulletMove.y, BulletMove.z), CBullet::TYPE_GRAVITY);

				if (pBullet != NULL)
				{
					pBullet->SetSize(80.0f, 30.0f);
					pBullet->SetLife(300.0f);
				}

				CParticle::Create(D3DXVECTOR3(mtx._41, mtx._42, mtx._43), CamRot, CEffect::TYPE_SHWBULLET);

				break;
			}

			m_bAttack = true;
			m_nAttackTimer++;
		}
		else
		{
			m_nAttackTimer++;
			if (m_nAttackTimer > m_aWepTimer[m_WepType] * (1.0f + (1.0f - CManager::GetSlow()->Get())))
			{
				m_nAttackTimer = 0;
			}
		}
	}
	else
	{
		if (m_bAttack == true)
		{
			m_nAttackTimer++;
			if (m_nAttackTimer > m_aWepTimer[m_WepType] * (1.0f + (1.0f - CManager::GetSlow()->Get())))
			{
				m_nAttackTimer = 0;
				m_bAttack = false;
				m_nAttackHand = 0;
			}
		}
	}
}

//===============================================
// ジャンプ
//===============================================
void CPlayer::Jump(void)
{
	CInputKeyboard *pInputKey = CManager::GetInputKeyboard();	// キーボードのポインタ

	// ジャンプ
	if (pInputKey->GetPress(DIK_SPACE) == true)
	{// SPACEキー
		if (m_bJump == false)
		{// ジャンプしていない場合
			m_bJump = true;
			m_Info.move.y = PLAYER_JUMP;
			if (m_bAttack == false)
			{
				m_pBody->GetMotion()->BlendSet(BMOTION_JUMP);
			}
			m_pLeg->GetMotion()->BlendSet(LMOTION_JUMP);
			m_Info.move.x += (0.0f - m_Info.move.x) * 0.25f;	//x座標
			m_Info.move.z += (0.0f - m_Info.move.z) * 0.25f;	//x座標
		}
	}
}
