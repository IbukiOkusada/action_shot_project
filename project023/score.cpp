//===============================================
//
// �X�R�A�̏��� [score.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "score.h"
#include "manager.h"
#include "renderer.h"
#include "number.h"
#include "texture.h"
#include "object2D.h"

// �}�N����`
#define WIDTH	(30)	// ��
#define X_SPACE	(55)	// ���̈ړ���
#define HEIGHT	(50)	// ����

//===============================================
// �R���X�g���N�^
//===============================================
CScore::CScore()
{
	// �l���N���A
	for (int nCnt = 0; nCnt < NUM_SCORE; nCnt++)
	{
		m_apNumber[nCnt] = NULL;
	}

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nNum = 0;
	m_nIdxTexture = -1;
}

//===============================================
// �f�X�g���N�^
//===============================================
CScore::~CScore()
{

}

//===============================================
// ����������
//===============================================
HRESULT CScore::Init(void)
{
	CTexture *pTexture = CManager::GetTexture();

	// �e�N�X�`���̓ǂݍ���
	m_nIdxTexture = pTexture->Regist(CTexture::GetFileName(CTexture::TYPE_SCORE));

	for (int nCnt = 0; nCnt < NUM_SCORE; nCnt++)
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
void CScore::Uninit(void)
{
	for (int nCnt = 0; nCnt < NUM_SCORE; nCnt++)
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
void CScore::Update(void)
{
	
}

//===============================================
// ����
//===============================================
CScore *CScore::Create(D3DXVECTOR3 pos)
{
	CScore *pBg = NULL;

	// �I�u�W�F�N�g2D�̐���
	pBg = new CScore;

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
void CScore::Add(int nValue)
{
	// ���
	m_nNum += nValue;

	// ���l�ݒ�
	SetValue();
}

//===============================================
// �X�R�A�ݒ�
//===============================================
void CScore::Set(int nValue)
{
	// ���
	m_nNum = nValue;

	// ���l�ݒ�
	SetValue();
}

//===============================================
// �����Ƃ̒l�ݒ�
//===============================================
void CScore::SetValue(void)
{
	if (m_nNum < 0)
	{// 0�ȉ��̏ꍇ
		m_nNum = 0;
	}

	//�X�R�A���e�z��Ɋi�[
	for (int nCnt = 0; nCnt < NUM_SCORE; nCnt++)
	{
		// ���݂̌��̒l�����߂�
		int nNum = m_nNum % (int)pow(10, (NUM_SCORE - nCnt)) / (int)pow(10, (NUM_SCORE - nCnt) - 1);

		if (m_apNumber[nCnt] != NULL)
		{// �g�p����Ă���ꍇ
			// �l��ݒ�
			m_apNumber[nCnt]->SetIdx(nNum);
		}
	}
}

