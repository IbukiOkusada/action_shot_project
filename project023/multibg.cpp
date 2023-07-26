//===============================================
//
// ���d�X�N���[���̔w�i�̏��� [bg.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "multibg.h"
#include "object2D.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "texture.h"

//===============================================
// �}�N����`
//===============================================
#define VTX	(4)	// ���_��
#define WIDTH	(100.0f)	// ��
#define HEIGHT	(100.0f)	// ����
#define POS_X	(300.0f)	// X���W
#define POS_Y	(300.0f)	// Y���W
#define TEXMOVE_U	(0.000005f)		// �v���C���[�ړ��{��U���W
#define TEXMOVE_V	(0.0000008f)	// �v���C���[�ړ��{��V���W
#define TEXCNTMOVE	(0.00005f)	// �J�E���g���w�i�ړ��{��

//===============================================
// �ÓI�����o�ϐ��錾(�t�@�C����)
//===============================================
const char *CMultiBg::m_apTextureFileName[] =
{
	"data\\TEXTURE\\bg002.png",
	"data\\TEXTURE\\bg002.png",
	"data\\TEXTURE\\bg002.png",
};

// �e�N�X�`���ړ���
const CMultiBg::STex CMultiBg::apMoveTex[TYPE_MAX] =
{
	{ 0.1f, 0.0f, 0.0f, -0.00025f },
	{ 0.2f, 0.0f, 0.0f, -0.0005f },
	{ 0.3f, 0.0f, 0.0f, -0.001f },
};

//===============================================
// �R���X�g���N�^
//===============================================
CMultiBg::CMultiBg() :CObject(0)
{
	// �l���N���A
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		m_aBg[nCnt].pObject2D = NULL;
		m_aBg[nCnt].sTex.fMoveU = 0.0f;
		m_aBg[nCnt].sTex.fMoveV = 0.0f;
		m_aBg[nCnt].sTex.fTexU = 0.0f;
		m_aBg[nCnt].sTex.fTexV = 0.0f;
		m_aIdxTexture[nCnt] = -1;
	}
}

//===============================================
// �f�X�g���N�^
//===============================================
CMultiBg::~CMultiBg()
{

}

//===============================================
// ����������
//===============================================
HRESULT CMultiBg::Init(void)
{
	CTexture *pTexture = CManager::GetTexture();

	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		// �e�N�X�`���̓ǂݍ���
		m_aIdxTexture[nCnt] = pTexture->Regist(m_apTextureFileName[nCnt]);
		SBg *pBg = &m_aBg[nCnt];	// �w�i���̃|�C���^

		if (pBg->pObject2D == NULL)
		{// �g�p���Ă��Ȃ��ꍇ
			pBg->pObject2D = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);

			CObject2D *pObjBg = pBg->pObject2D;	// �ړ�
			STex *pTex = &pBg->sTex;

			if (pObjBg != NULL)
			{// �g�p���Ă���ꍇ
				pObjBg->Init();

				// ��ނ̐ݒ�
				pObjBg->SetType(TYPE_BG);

				// �e�N�X�`�����蓖��
				pObjBg->BindTexture(m_aIdxTexture[nCnt]);

				m_aBg[nCnt].sTex = apMoveTex[nCnt];

				// �I�u�W�F�N�g�̍X�V����
				pObjBg->SetVtx(pTex->fTexU, pTex->fTexV, (float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f);
			}
		}
	}

	/*m_aBg[0].fMoveU = 0.001f;
	m_aBg[1].fMoveU = 0.003f;
	m_aBg[2].fMoveU = 0.005f;*/
	// �I�u�W�F�N�g�̏���������
	//CObject2D::Init();

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CMultiBg::Uninit(void)
{
	// �I�u�W�F�N�g�̏I������
	CObject::Release();
}

//===============================================
// �X�V����
//===============================================
void CMultiBg::Update(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		SBg *pBg = &m_aBg[nCnt];

		if (pBg != NULL)
		{// �g�p����Ă���ꍇ

			STex *pTex = &m_aBg[nCnt].sTex;	// �e�N�X�`�����̃|�C���^

			// �e�N�X�`�����W�̍X�V����
			pTex->fTexU += pTex->fMoveU;
			pTex->fTexV += pTex->fMoveV;

			if (pTex->fTexU < 0.0f)
			{
				pTex->fTexU = 1.0f;
			}
			else if (pTex->fTexU > 1.0f)
			{
				pTex->fTexU = 0.0f;
			}

			if (pTex->fTexV < 0.0f)
			{
				pTex->fTexV = 1.0f;
			}
			else if (pTex->fTexV > 1.0f)
			{
				pTex->fTexV = 0.0f;
			}

			// �I�u�W�F�N�g�̍X�V����
			pBg->pObject2D->SetVtx(pTex->fTexU, pTex->fTexV, (float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f);
		}
	}
}

//===============================================
// �`�揈��
//===============================================
void CMultiBg::Draw(void)
{
	// �{�͕̂`�斳��
}

//===============================================
// ����
//===============================================
CMultiBg *CMultiBg::Create()
{
	CMultiBg *pBg = NULL;

	// �I�u�W�F�N�g2D�̐���
	pBg = new CMultiBg;

	if (pBg != NULL)
	{// �����ł����ꍇ
		// ����������
		pBg->Init();

		// ��ނ̐ݒ�
		pBg->SetType(CObject::TYPE_NONE);
	}
	else
	{// �����Ɏ��s�����ꍇ
		return NULL;
	}

	return pBg;
}

//===============================================
// �w�i�̊����ړ�
//===============================================
void CMultiBg::SetPlayerMove(const D3DXVECTOR3 move)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		SBg *pBg = &m_aBg[nCnt];

		if (pBg != NULL)
		{// �g�p����Ă���ꍇ
			pBg->sTex.fTexU += move.x * (TEXMOVE_U + nCnt * TEXCNTMOVE);
			pBg->sTex.fTexV += move.y * (TEXMOVE_V + nCnt * TEXCNTMOVE);
		}
	}
}