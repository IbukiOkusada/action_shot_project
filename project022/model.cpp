//==========================================================
//
// �K�w�\���̃��f������ [model.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "model.h"
#include "Xfile.h"
#include "manager.h"
#include "texture.h"
#include "renderer.h"

//==========================================================
// �R���X�g���N�^
//==========================================================
CModel::CModel()
{
	// �l�̃N���A
	m_nIdxModel = -1;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//m_pParent = NULL;
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CModel::~CModel()
{

}

//==========================================================
// ����������
//==========================================================
HRESULT CModel::Init(const char *pFileName)
{
	CXFile *pModelFile = CManager::GetModelFile();	// ���f���t�@�C�����̃|�C���^

	//X�t�@�C������ǂݍ���
	m_nIdxModel = pModelFile->Regist(pFileName);

	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CModel::Uninit(void)
{
	// �|�C���^���g�p���Ă��Ȃ���Ԃɂ���
	m_pParentMtx = NULL;
}

//==========================================================
// �X�V����
//==========================================================
void CModel::Update(void)
{

}

//==========================================================
// �`�揈��
//==========================================================
void CModel::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	//�f�o�C�X�ւ̃|�C���^���擾
	CTexture *pTexture = CManager::GetTexture();	// �e�N�X�`���ւ̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	CXFile *pModelFile = CManager::GetModelFile();	// X�t�@�C�����̃|�C���^
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;				//�}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATRIX mtxParent;			// �e�̃}�g���b�N�X���

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_CurRot.y, m_CurRot.x, m_CurRot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_CurPos.x, m_CurPos.y, m_CurPos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	if(m_pParentMtx != NULL)
	{// �o���Ă���ꍇ
		mtxParent = *m_pParentMtx;

		//�p�[�c�̃}�g���b�N�X�Ɛe�̃}�g���b�N�X���������킹��
		D3DXMatrixMultiply(&m_mtxWorld,
			&m_mtxWorld, &mtxParent);
	}

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// ���f�������擾
	CXFile::FileData *pFileData = pModelFile->SetAddress(m_nIdxModel);

	if (pFileData != NULL)
	{// �g�p����Ă���ꍇ
	 //�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)pFileData->pBuffMat->GetBufferPointer();
		for (int nCntMat = 0; nCntMat < (int)pFileData->dwNumMat; nCntMat++)
		{
			int nIdxTex = pFileData->pIdexTexture[nCntMat];	// �e�N�X�`���ԍ�

			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, pTexture->SetAddress(nIdxTex));

			//���f��(�p�[�c)�̕`��
			pFileData->pMesh->DrawSubset(nCntMat);
		}
	}

	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//==========================================================
// ����
//==========================================================
CModel *CModel::Create(const char *pFileName)
{
	CModel *pModel = NULL;
	CXFile *pModelFile = CManager::GetModelFile();

	// �I�u�W�F�N�gX�̐���
	pModel = new CModel;

	if (pModel != NULL)
	{// �����ł����ꍇ

		// ����������
		pModel->Init(pFileName);

	}
	else
	{// �����Ɏ��s�����ꍇ
		return NULL;
	}

	return pModel;
}

//==========================================================
// �e���f����ݒ�
//==========================================================
void CModel::SetParent(D3DXMATRIX *pMtx)
{
	m_pParentMtx = pMtx;
}

//==========================================================
// �����ʒu��ݒ�
//==========================================================
void CModel::SetPosition(const D3DXVECTOR3 pos)
{
	m_pos = pos;

	SetCurrentPosition(m_pos);
}

//==========================================================
// ����������ݒ�
//==========================================================
void CModel::SetRotation(const D3DXVECTOR3 rot)
{
	m_rot = rot;

	SetCurrentRotation(m_rot);
}

//==========================================================
// ���݂̈ʒu��ݒ�
//==========================================================
void CModel::SetCurrentPosition(const D3DXVECTOR3 pos)
{
	m_CurPos = pos;
}

//==========================================================
// ���݂̌�����ݒ�
//==========================================================
void CModel::SetCurrentRotation(const D3DXVECTOR3 rot)
{
	m_CurRot = rot;
}

//==========================================================
// ���f���ԍ��̐ݒ�
//==========================================================
void CModel::BindModelFile(int nIdx)
{
	m_nIdxModel = nIdx;
}