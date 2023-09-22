//==========================================================
//
// �Ԃ̏��� [car.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "car.h"
#include "Xfile.h"
#include "manager.h"
#include "debugproc.h"
#include "shadow.h"
#include "texture.h"
#include "slow.h"

//==========================================================
// �R���X�g���N�^
//==========================================================
CCar::CCar() : CObjectX(3)
{
	// �l�̃N���A
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pPrev = NULL;
	m_pNext = NULL;
	m_pShadow = NULL;
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CCar::~CCar()
{

}

//==========================================================
// ����������
//==========================================================
HRESULT CCar::Init(void)
{
	CObjectX::Init();
	m_pShadow = CShadow::Create(GetPosition(), 100.0f, 200.0f);
	m_pShadow->BindTexture(CManager::GetTexture()->Regist("data\\TEXTURE\\shadow001.jpg"));

	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CCar::Uninit(void)
{
	CObjectX::Uninit();

	if (m_pShadow != NULL)
	{
		m_pShadow->Uninit();
		m_pShadow = NULL;
	}
}

//==========================================================
// �X�V����
//==========================================================
void CCar::Update(void)
{
	m_posOld = GetPosition();
	D3DXVECTOR3 pos = GetPosition();
	pos += m_move * CManager::GetSlow()->Get();
	SetPosition(pos);

	if (m_pShadow != NULL)
	{
		m_pShadow->SetPosition(pos);
	}
}

//==========================================================
// �`�揈��
//==========================================================
void CCar::Draw(void)
{
	CObjectX::Draw();
}

//==========================================================
// ����
//==========================================================
CCar *CCar::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *pFileName, const int nPriority)
{
	CCar *pObjectX = NULL;
	CXFile *pModelFile = CManager::GetModelFile();

	// �I�u�W�F�N�gX�̐���
	pObjectX = new CCar;

	if (pObjectX != NULL)
	{// �����ł����ꍇ
	 // ����������
		pObjectX->Init();

		// ���W
		pObjectX->SetPosition(pos);
		pObjectX->SetOldPos(pos);

		// ����
		pObjectX->SetRotation(rot);

		// ��ސݒ�
		pObjectX->SetType(TYPE_CAR);

		// �ǂݍ��݊m�F
		pObjectX->BindFile(pModelFile->Regist(pFileName));
	}
	else
	{// �����Ɏ��s�����ꍇ
		return NULL;
	}

	return pObjectX;
}
