//==========================================================
//
// �t�B���^�[�̏��� [filter.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "filter.h"
#include "manager.h"
#include "game.h"
#include "texture.h"
#include "slow.h"

//===============================================
// �}�N����`
//===============================================
#define GUN_DEFHEIGHT	(700)				// �f�t�H���g����ǉ��ŉ�ʊO�ɐ������鍂��
#define GUN_DEFWIDTH	(GUN_DEFHEIGHT * 2)	// �f�t�H���g����ǉ��ŉ�ʊO�ɐ������镝
#define GUN_MULTIWIDTH	(2)					// �{��
#define GUN_MOVE		(-100.0f)
#define GUN_COLA		(0.1f)

//====================================================================================
// �I�u�W�F�N�g2D�N���X
//====================================================================================
//===============================================
// �R���X�g���N�^
//===============================================
//CFilter::CFilter()
//{
//	// �l���N���A����
//}

//===============================================
// �R���X�g���N�^(�I�[�o�[���[�h)
//===============================================
CFilter::CFilter(int nPriority) : CObject2D(nPriority)
{
	// �l���N���A����
	m_fCola = 0.0f;
	m_fSpeed = 0.0f;
}

//===============================================
// �f�X�g���N�^
//===============================================
CFilter::~CFilter()
{

}

//===============================================
// ����������
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
// �I������
//===============================================
void CFilter::Uninit(void)
{
	CObject2D::Uninit();
}

//===============================================
// �X�V����
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

		// �T�C�Y�ύX
		fWidth += m_fSpeed * GUN_MULTIWIDTH;
		fHeight += m_fSpeed;
		m_col.a += m_fCola;

		if (fWidth < SCREEN_WIDTH * 0.5f || fHeight <= SCREEN_HEIGHT * 0.5f || (CManager::GetSlow()->Get() == 1.0f && CManager::GetSlow()->GetOld() != 1.0f))
		{// �K��l�ɂ��ǂ蒅����
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

		// �T�C�Y�ύX
		fWidth += m_fSpeed * GUN_MULTIWIDTH;
		fHeight += m_fSpeed;
		m_col.a += m_fCola;
		SetSize(fWidth, fHeight);
		SetCol(m_col);

		if (fWidth > SCREEN_WIDTH * 0.5f + GUN_DEFWIDTH || fHeight > SCREEN_HEIGHT * 0.5f + GUN_DEFHEIGHT)
		{// �K��l�ɂ��ǂ蒅����
			Uninit();
		}

		break;
	}
}

//===============================================
// �`�揈��
//===============================================
void CFilter::Draw(void)
{
	CObject2D::Draw();
}

//===============================================
// ���_���ݒ�
//===============================================
CFilter *CFilter::Create(TYPE type)
{
	CFilter *pObject2D = NULL;

	// �I�u�W�F�N�g2D�̐���
	pObject2D = new CFilter(6);

	if (pObject2D != NULL)
	{// �����ł����ꍇ
	 // ����������
		pObject2D->Init();

		pObject2D->SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));

		pObject2D->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		pObject2D->SetSize(SCREEN_WIDTH * 0.5f + GUN_DEFWIDTH, SCREEN_HEIGHT * 0.5f + GUN_DEFHEIGHT);

		// ��ސݒ�
		pObject2D->SetType(TYPE_NONE);

		pObject2D->m_state = STATE_START;

		pObject2D->BindTexture(CManager::GetTexture()->Regist(CManager::GetTexture()->GetFileName(CTexture::TYPE_SLOWGUNFIL)));
	}
	else
	{// �����Ɏ��s�����ꍇ
		return NULL;
	}

	return pObject2D;
}
