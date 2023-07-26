//===============================================
//
// �G��Ղ̏��� [wet.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "wet.h"
#include "object3D.h"
#include "manager.h"
#include "slow.h"
#include "texture.h"

//===============================================
// �}�N����`
//===============================================
#define LIFE	(250)	// �̗�

//===============================================
// �R���X�g���N�^
//===============================================
CWet::CWet()
{
	// �l�̃N���A
	m_fLife = 0.0f;
	m_fDefWidth = 0.0f;
	m_fDefHeight = 0.0f;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

//===============================================
// �f�X�g���N�^
//===============================================
CWet::~CWet()
{

}

//===============================================
// ����������
//===============================================
HRESULT CWet::Init(void)
{
	// ������
	CShadow::Init();

	// �l������������
	m_fLife = LIFE;

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CWet::Uninit(void)
{
	CShadow::Uninit();
}

//===============================================
// �X�V����
//===============================================
void CWet::Update(void)
{
	m_fLife -= CManager::GetSlow()->Get();	// �̗͂̌��� 

	float fRate = (float)(m_fLife / LIFE);	// ���݂̍ő�̗͂̊���

	// �T�C�Y�̒���
	float fWidth = m_fDefWidth * fRate;
	float fHeight = m_fDefHeight * fRate;
	m_col.a = 1.0f * (fRate - 0.5f);

	// �T�C�Y�ݒ�
	SetpVtx(fWidth, fHeight);
	SetCol(m_col);

	if (m_fLife <= 0.0f || m_col.a <= 0.0f)
	{// ����������
		Uninit();
	}
}

//===============================================
// �`�揈��
//===============================================
void CWet::Draw(void)
{
	CShadow::Draw();
}

//===============================================
// ����
//===============================================
CWet *CWet::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CWet *pWet = NULL;
	CTexture *pTexture = CManager::GetTexture();	// �e�N�X�`���̃|�C���^

	pWet = new CWet;

	if (pWet == NULL)
	{
		return NULL;
	}

	// ������
	pWet->Init();

	// ���W�ݒ�
	pWet->SetPosition(pos);

	// �T�C�Y�ݒ�
	pWet->SetSize(fWidth, fHeight);

	// ��ސݒ�
	pWet->SetType(TYPE_NONE);

	// �e�N�X�`���ݒ�
	pWet->BindTexture(pTexture->Regist(CTexture::GetFileName(CTexture::TYPE_SHADOW)));

	return pWet;
}

//===============================================
// �f�t�H���g�T�C�Y�ݒ�
//===============================================
void CWet::SetSize(float fWidth, float fHeight)
{
	m_fDefWidth = fWidth;
	m_fDefHeight = fHeight;

	// �T�C�Y�ݒ�
	SetpVtx(m_fDefWidth, m_fDefHeight);
}