//===============================================
//
// ���x�\���̏��� [thermo.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "thermo.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

// �}�N����`
#define RATIO	(0.01f)

//===============================================
// �R���X�g���N�^
//===============================================
//CThermo::CThermo()
//{
//	// �l�̃N���A
//	m_Info.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//	m_Info.fLife = 0;
//	m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	m_Info.fRadius = 0.0f;
//	m_Info.Type = TYPE_NONE;
//}

//===============================================
// �R���X�g���N�^(�I�[�o�[���[�h)
//===============================================
CThermo::CThermo(int nPriority) : CObject3D(nPriority)
{
	// �l�̃N���A
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_colDiff = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_fRadius = 0.0f;
}

//===============================================
// �f�X�g���N�^
//===============================================
CThermo::~CThermo()
{

}

//===============================================
// ����������
//===============================================
HRESULT CThermo::Init(void)
{
	CObject3D::Init();

	SetType(TYPE_MAP);	// ��ސݒ�
	BindTexture(CManager::GetTexture()->Regist(CTexture::GetFileName(CTexture::TYPE_EFFECT)));

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CThermo::Uninit(void)
{
	CObject3D::Uninit();
}

//===============================================
// �X�V����
//===============================================
void CThermo::Update(void)
{
	CObject3D::Update();

	// ������␳����
	D3DXCOLOR col = m_colDiff - m_col;

	m_col += col * RATIO;

	SetCol(m_col);
}

//===============================================
// �`�揈��
//===============================================
void CThermo::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	//���C�e�B���O���I�t�ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�A���t�@�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CObject3D::Draw();

	//���C�e�B���O���I���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//�A���t�@�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 255);

	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//==========================================================
// ����
//==========================================================
CThermo *CThermo::Create(void)
{
	CThermo *pThermo = NULL;	// �e�̃|�C���^
	CTexture *pTexture = CManager::GetTexture();	// �e�N�X�`���̃|�C���^

	// �I�u�W�F�N�g2D�̐���
	pThermo = new CThermo;

	if (pThermo != NULL)
	{// �����ł����ꍇ

		// ����������
		pThermo->Init();
	}
	else
	{// �����Ɏ��s�����ꍇ
		return NULL;
	}

	return pThermo;
}

