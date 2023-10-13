//===============================================
//
// �^�C���̏��� [time.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "time.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "number.h"
#include "object2D.h"
#include "slow.h"
#include "debugproc.h"

// �}�N����`
#define WIDTH	(60)	// ��
#define X_SPACE	(50)	// ���̈ړ���
#define HEIGHT	(80)	// ����
#define NUM_WIDTH	(20)
#define NUM_HEIGHT	(40)

//===============================================
// �R���X�g���N�^
//===============================================
CTime::CTime()
{
	// �l���N���A
	for (int nCnt = 0; nCnt < NUM_PLACE; nCnt++)
	{
		m_apNumber[nCnt] = NULL;
	}

	m_pSun = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nNum = 0;
	m_fAnimTimer = 0.0f;
	m_nIdxTexture = -1;
	m_nMaxNum = 0;
	m_fDiff = 0.0f;
}

//===============================================
// �f�X�g���N�^
//===============================================
CTime::~CTime()
{

}

//===============================================
// ����������
//===============================================
HRESULT CTime::Init(void)
{
	CTexture *pTexture = CManager::GetTexture();

	m_pSun = CObject2D::Create(7);
	m_pSun->BindTexture(pTexture->Regist("data\\TEXTURE\\timer000.png"));
	m_pSun->SetLength((HEIGHT + WIDTH) * 2, (HEIGHT + WIDTH) * 2);
	m_pSun->SetPosition(D3DXVECTOR3(m_pos.x + X_SPACE * 1.05f + NUM_WIDTH, m_pos.y - HEIGHT * 1.25f, 0.0f));
	m_pSun->SetVtx();

	// �e�N�X�`���̓ǂݍ���
	m_nIdxTexture = pTexture->Regist(CTexture::GetFileName(CTexture::TYPE_TIMER));
	CObject2D *pObj = CObject2D::Create(7);
	pObj->SetPosition(D3DXVECTOR3(m_pos.x + X_SPACE * 1.0f + NUM_WIDTH * 1.4f, m_pos.y, 0.0f));
	pObj->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f));
	pObj->SetSize(NUM_WIDTH * 2 + X_SPACE * 1.5f, NUM_HEIGHT);
	pObj->BindTexture(pTexture->Regist("data\\TEXTURE\\map001.png"));

	pObj = CObject2D::Create(7);
	pObj->SetPosition(D3DXVECTOR3(m_pos.x + X_SPACE * 1.0f + NUM_WIDTH * 1.4f, m_pos.y, 0.0f));
	pObj->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	pObj->SetSize(NUM_WIDTH * 0.4f, NUM_HEIGHT * 0.5f);
	pObj->BindTexture(pTexture->Regist("data\\TEXTURE\\number002.png"));

	for (int nCnt = 0; nCnt < NUM_PLACE; nCnt++)
	{
		CNumber *pNum = m_apNumber[nCnt];	// �����̃|�C���^

		if (m_apNumber[nCnt] == NULL)
		{// �g�p���Ă��Ȃ��ꍇ
			D3DXVECTOR3 pos = m_pos;	// �ݒ���W
			pos.x += nCnt * X_SPACE + 1.0f;	// ���ړ�
			m_apNumber[nCnt] = CNumber::Create(pos, NUM_WIDTH, NUM_HEIGHT);


			if (m_apNumber[nCnt] != NULL)
			{// �g�p���Ă���ꍇ
				m_apNumber[nCnt]->GetObject2D()->BindTexture(m_nIdxTexture);
				
			}
		}
	}

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CTime::Uninit(void)
{
	for (int nCnt = 0; nCnt < NUM_PLACE; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{// �g�p���Ă��Ȃ��ꍇ
			m_apNumber[nCnt]->Uninit();

			delete m_apNumber[nCnt];

			m_apNumber[nCnt] = NULL;
		}
	}
}

//===============================================
// �X�V����
//===============================================
void CTime::Update(void)
{
	m_fAnimTimer += CManager::GetSlow()->Get();

	if (m_nNum >= 60 * 14 && m_nNum <= 60 * 16)
	{
		if (m_fAnimTimer >= 25)
		{// 12�t���[��������
			m_fAnimTimer = 0;	// �J�E���^�[���Z�b�g
			Add(1);
		}
	}
	else if (m_nNum >= 60 * 16 && m_nNum <= 60 * 20)
	{
		if (m_fAnimTimer >= 20)
		{// 12�t���[��������
			m_fAnimTimer = 0;	// �J�E���^�[���Z�b�g
			Add(1);
		}
	}
	else
	{
		if (m_fAnimTimer >= 12)
		{// 12�t���[��������
			m_fAnimTimer = 0;	// �J�E���^�[���Z�b�g
			Add(1);
		}
	}
}

//===============================================
// ����
//===============================================
CTime *CTime::Create(D3DXVECTOR3 pos)
{
	CTime *pBg = NULL;

	// �I�u�W�F�N�g2D�̐���
	pBg = new CTime;

	if (pBg != NULL)
	{// �����ł����ꍇ

		pBg->m_pos = pos;

		// ����������
		pBg->Init();
	}
	else
	{// �����Ɏ��s�����ꍇ
		return NULL;
	}

	return pBg;
}

//===============================================
// ���Z
//===============================================
void CTime::Add(int nValue)
{
	// ���
	m_nNum += nValue;

	if (m_nNum % 10 == 0)
	{
		// ���l�ݒ�
		SetValue();
	}

	// �p�x�ύX
	float fRot = m_pSun->GetRotation().y;
	m_fDiff = (float)(m_nNum - m_nSetNum) / (float)(m_nMaxNum - m_nSetNum);

	fRot = m_fDiff * (-D3DX_PI * 2);

	if (fRot < -D3DX_PI)
	{
		fRot += D3DX_PI * 2;
	}
	m_pSun->SetRotation(D3DXVECTOR3(0.0f, 0.0f, fRot));
	m_pSun->SetVtx();
}

//===============================================
// �ݒ�
//===============================================
void CTime::Set(int nValue)
{
	// ���
	m_nNum = nValue;
	m_nSetNum = nValue;

	// ���l�ݒ�
	SetValue();
}

//===============================================
// �����Ƃ̒l�ݒ�
//===============================================
void CTime::SetValue(void)
{
	int aTexU[NUM_PLACE] = {};	// �v�Z�i�[�p

	if (m_nNum < 0)
	{// 0�ȉ��̏ꍇ
		m_nNum = 0;
	}
	else if (m_nNum >= 60 * 100)
	{
		m_nNum = 60 * 100 - 1;
	}

	//�^�C�����e�z��Ɋi�[
	aTexU[0] = m_nNum / 60 / 10;
	aTexU[1] = m_nNum / 60 - aTexU[0] * 10;
	aTexU[2] = m_nNum % 60 / 10;
	aTexU[3] = m_nNum % 60 - aTexU[2] * 10;

	//�X�R�A���e�z��Ɋi�[
	for (int nCnt = 0; nCnt < NUM_PLACE; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{// �g�p����Ă���ꍇ
			// �l��ݒ�
			m_apNumber[nCnt]->SetIdx(aTexU[nCnt]);
		}
	}
}
