//==========================================================
//
// ���b�V���V�����_�[�̏��� [meshcylinder.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "meshcylinder.h"
#include "texture.h"
#include "manager.h"
#include "renderer.h"

// �}�N����`
#define TEXTUREFILE_DATA	"data\\TEXTURE\\city000.png"		//�e�N�X�`���f�[�^

//==========================================================
// �R���X�g���N�^
//==========================================================
CMeshCylinder::CMeshCylinder()
{

}

//==========================================================
// �f�X�g���N�^
//==========================================================
CMeshCylinder::~CMeshCylinder()
{

}

//==========================================================
// ����������
//==========================================================
HRESULT CMeshCylinder::Init(void)
{
	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CMeshCylinder::Uninit(void)
{
	// ���_�o�b�t�@�̔p��
	CObjectMesh::Uninit();
}

//==========================================================
// �X�V����
//==========================================================
void CMeshCylinder::Update(void)
{

}

//==========================================================
// �`�揈��
//==========================================================
void CMeshCylinder::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	//���C�e�B���O���I�t�ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// �`��
	CObjectMesh::Draw();

	//���C�e�B���O���I���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//==========================================================
// ���_���ݒ�
//==========================================================
void CMeshCylinder::SetVtxInfo(void)
{
	int nVertex = GetVertex();			// ���_�����擾
	int nNumWidth = GetNumWidth();		// ���������擾
	int nNumHeight = GetNumHeight();	// �����������擾
	D3DXVECTOR3 pos = GetPosition();	// ���W
	D3DXVECTOR3 vecDir;	//�ݒ�ύX�p�x�N�g��

	//���_���W�̐ݒ�(��������E��O�Ɍ������Ē��_����ݒ肷��
	for (int nCntVtx = 0; nCntVtx < nVertex; nCntVtx++)
	{
		float fRot = m_fRot * (nCntVtx % (nNumWidth + 1));

		if (fRot > D3DX_PI || fRot < -D3DX_PI)
		{//-3.14�`3.14�͈̔͊O�̏ꍇ
			if (fRot > D3DX_PI)
			{
				fRot += (-D3DX_PI * 2);
			}
			else if (fRot < -D3DX_PI)
			{
				fRot += (D3DX_PI * 2);
			}
		}

		//���_���W
		m_pVtx[nCntVtx].pos.x = sinf(fRot) * m_fLength;
		m_pVtx[nCntVtx].pos.y = ((m_fHeight * 2) * nNumHeight) + ((nCntVtx / (nNumWidth + 1) * (-m_fHeight * 2)));
		m_pVtx[nCntVtx].pos.z = cosf(fRot) * m_fLength;

		vecDir = (m_pVtx[nCntVtx].pos - pos);

		//�x�N�g���𐳋K������
		D3DXVec3Normalize(&vecDir, &vecDir);

		//�@��
		m_pVtx[nCntVtx].nor = vecDir;

		//�F
		m_pVtx[nCntVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		m_pVtx[nCntVtx].tex = D3DXVECTOR2((5.0f / nNumWidth) * (nCntVtx % (nNumWidth + 1)), (1.0f / nNumHeight) * (nCntVtx / (nNumWidth + 1)));
	}

	// ���_�ݒ�
	SetVtx();
}

//==========================================================
// ����
//==========================================================
CMeshCylinder *CMeshCylinder::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot,
	float fLength, float fHeight, const int nPriority, const int nWidth, const int nHeight)
{
	CMeshCylinder *pMeshWall = NULL;	// ���b�V���t�B�[���h�̃|�C���^
	CTexture *pTexture = CManager::GetTexture();	// �e�N�X�`���ւ̃|�C���^

													// �������̊m��
	pMeshWall = new CMeshCylinder;

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

		// �꒸�_�ӂ�̊p�x�����߂�
		pMeshWall->m_fRot = (D3DX_PI * 2) / nWidth;

		// �T�C�Y�ݒ�
		pMeshWall->SetSize(fLength, fHeight);

		// �e�N�X�`���ݒ�
		pMeshWall->BindTexture(pTexture->Regist(TEXTUREFILE_DATA));
	}

	return pMeshWall;
}

//==========================================================
// ���ݒ�
//==========================================================
void CMeshCylinder::SetSize(float fLength, float fHeight)
{
	// �T�C�Y�ݒ�
	m_fLength = fLength;
	m_fHeight = fHeight;

	// ���_���ݒ�
	SetVtxInfo();
}

