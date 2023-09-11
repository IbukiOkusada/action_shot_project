//==========================================================
//
// ���b�V���t�B�[���h�̏��� [meshfield.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "meshwall.h"
#include "texture.h"
#include "manager.h"

// �}�N����`
#define TEXTUREFILE_DATA	"data\\TEXTURE\\welltile.png"		//�e�N�X�`���f�[�^

//==========================================================
// �R���X�g���N�^
//==========================================================
CMeshWall::CMeshWall()
{

}

//==========================================================
// �f�X�g���N�^
//==========================================================
CMeshWall::~CMeshWall()
{

}

//==========================================================
// ����������
//==========================================================
HRESULT CMeshWall::Init(void)
{
	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CMeshWall::Uninit(void)
{
	//���_�o�b�t�@�̔p��
	CObjectMesh::Uninit();
}

//==========================================================
// �X�V����
//==========================================================
void CMeshWall::Update(void)
{

}

//==========================================================
// �`�揈��
//==========================================================
void CMeshWall::Draw(void)
{
	// �`��
	CObjectMesh::Draw();
}

//==========================================================
// ���_���ݒ�
//==========================================================
void CMeshWall::SetVtxInfo(void)
{
	int nVertex = GetVertex();			// ���_�����擾
	int nNumWidth = GetNumWidth();		// ���������擾
	int nNumHeight = GetNumHeight();	// �����������擾

	//���_���W�̐ݒ�(��������E��O�Ɍ������Ē��_����ݒ肷��
	for (int nCntpVtx = 0; nCntpVtx < nVertex; nCntpVtx++)
	{
		//���_���W
		m_pVtx[nCntpVtx].pos.x = -(m_fWidth * nNumWidth) + (nCntpVtx % (nNumWidth + 1) * (m_fWidth * 2));
		m_pVtx[nCntpVtx].pos.y = ((m_fHeight * 2) * nNumHeight) + ((nCntpVtx / (nNumWidth + 1) * (-m_fHeight * 2)));
		m_pVtx[nCntpVtx].pos.z = 0.0f;

		//�@��
		m_pVtx[nCntpVtx].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//�F
		m_pVtx[nCntpVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		m_pVtx[nCntpVtx].tex = D3DXVECTOR2(1.0f * (nCntpVtx % (nNumWidth + 1)), 1.0f * (nCntpVtx / (nNumWidth + 1)));
	}

	// ���_�ݒ�
	SetVtx();
}

//==========================================================
// ����
//==========================================================
CMeshWall *CMeshWall::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, float fWidth, float fHeight,
	const char *pFileName, const int nWidth, const int nHeight, const int nPriority )
{
	CMeshWall *pMeshWall = NULL;	// ���b�V���t�B�[���h�̃|�C���^
	CTexture *pTexture = CManager::GetTexture();	// �e�N�X�`���ւ̃|�C���^

	// �������̊m��
	pMeshWall = new CMeshWall;

	if (pMeshWall != NULL)
	{// �m�ۂł����ꍇ

		// ������
		pMeshWall->Init();

		// ���W�ݒ�
		pMeshWall->SetPosition(pos);

		// �����ݒ�
		pMeshWall->SetRotation(rot);

		// ���_����
		pMeshWall->CObjectMesh::Create(nWidth, nHeight);

		// �T�C�Y�ݒ�
		pMeshWall->SetSize(fWidth, fHeight);

		// �e�N�X�`���ݒ�
		pMeshWall->BindTexture(pTexture->Regist(pFileName));
	}

	return pMeshWall;
}


//==========================================================
// ���ݒ�
//==========================================================
void CMeshWall::SetSize(float fWidth, float fHeight)
{
	// �T�C�Y�ݒ�
	m_fWidth = fWidth;
	m_fHeight = fHeight;

	// ���_���ݒ�
	SetVtxInfo();
}
