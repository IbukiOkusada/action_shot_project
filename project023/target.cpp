//===============================================
//
// �X�R�A�̏��� [target.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "target.h"
#include "manager.h"
#include "renderer.h"
#include "number.h"
#include "texture.h"
#include "object2D.h"
#include "enemy.h"
#include "fade.h"

// �}�N����`
#define WIDTH	(30)	// ��
#define X_SPACE	(55)	// ���̈ړ���
#define HEIGHT	(50)	// ����

//===============================================
// �R���X�g���N�^
//===============================================
CTarget::CTarget()
{
	// �l���N���A
	for (int nCnt = 0; nCnt < NUM_TARGET; nCnt++)
	{
		m_apNumber[nCnt] = NULL;
	}

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nNum = 0;
	m_nIdxTexture = -1;

	while (1)
	{
		if (CObject::GetNumEnemAll() < 50)
		{
			int nRand = rand() % 201 - 100;
			float fRot = D3DX_PI * ((float)nRand * 0.01f);

			CEnemy::Create(D3DXVECTOR3(0.0f + rand() % 300 - 150, 0.0f, 0.0f + rand() % 300 - 150), D3DXVECTOR3(0.0f, fRot, 0.0f),
				D3DXVECTOR3(-sinf(fRot) * 4.0f, 0.0f, -cosf(fRot) * 4.0f), "data\\TXT\\motion_murabito.txt");
		}
		else
		{
			break;
		}
	}
}

//===============================================
// �f�X�g���N�^
//===============================================
CTarget::~CTarget()
{

}

//===============================================
// ����������
//===============================================
HRESULT CTarget::Init(void)
{
	CTexture *pTexture = CManager::GetTexture();

	// �e�N�X�`���̓ǂݍ���
	m_nIdxTexture = pTexture->Regist(CTexture::GetFileName(CTexture::TYPE_SCORE));

	for (int nCnt = 0; nCnt < NUM_TARGET; nCnt++)
	{
		CNumber *pNum = m_apNumber[nCnt];	// �����̃|�C���^

		if (m_apNumber[nCnt] == NULL)
		{// �g�p���Ă��Ȃ��ꍇ
			D3DXVECTOR3 pos = m_pos;	// �ݒ���W
			pos.x += nCnt * X_SPACE;	// ���ړ�
			m_apNumber[nCnt] = CNumber::Create(pos, WIDTH, HEIGHT);

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
void CTarget::Uninit(void)
{
	for (int nCnt = 0; nCnt < NUM_TARGET; nCnt++)
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
void CTarget::Update(void)
{
	int nNum = CObject::GetNumEnemAll();

	if (nNum <= 0)
	{
		CManager::GetFade()->Set(CScene::MODE_RESULT);
	}
	else
	{
		Set(nNum);
	}
}

//===============================================
// ����
//===============================================
CTarget *CTarget::Create(D3DXVECTOR3 pos)
{
	CTarget *pBg = NULL;

	// �I�u�W�F�N�g2D�̐���
	pBg = new CTarget;

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
// �X�R�A���Z
//===============================================
void CTarget::Add(int nValue)
{
	// ���
	m_nNum += nValue;

	// ���l�ݒ�
	SetValue();
}

//===============================================
// �X�R�A�ݒ�
//===============================================
void CTarget::Set(int nValue)
{
	// ���
	m_nNum = nValue;

	// ���l�ݒ�
	SetValue();
}

//===============================================
// �����Ƃ̒l�ݒ�
//===============================================
void CTarget::SetValue(void)
{
	if (m_nNum < 0)
	{// 0�ȉ��̏ꍇ
		m_nNum = 0;
	}

	//�X�R�A���e�z��Ɋi�[
	for (int nCnt = 0; nCnt < NUM_TARGET; nCnt++)
	{
		// ���݂̌��̒l�����߂�
		int nNum = m_nNum % (int)pow(10, (NUM_TARGET - nCnt)) / (int)pow(10, (NUM_TARGET - nCnt) - 1);

		if (m_apNumber[nCnt] != NULL)
		{// �g�p����Ă���ꍇ
			// �l��ݒ�
			m_apNumber[nCnt]->SetIdx(nNum);
		}
	}
}

//===============================================
// �F�ݒ�
//===============================================
void CTarget::SetColor(D3DXCOLOR col)
{
	for (int nCnt = 0; nCnt < NUM_TARGET; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{// �g�p���Ă��Ȃ��ꍇ
			m_apNumber[nCnt]->GetObject2D()->SetCol(col);
		}
	}
}
