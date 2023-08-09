//==========================================================
//
// X�t�@�C�����f���̏����S�� [objectX.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "main.h"
#include "objectX.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "Xfile.h"
#include "enemy.h"
#include "slow.h"

//==========================================================
// �R���X�g���N�^
//==========================================================
CObjectX::CObjectX(int nPriority) : CObject(nPriority)
{
	m_nIdxModel = -1;
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CObjectX::~CObjectX()
{

}

//==========================================================
//���f���̏���������
//==========================================================
HRESULT CObjectX::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();		//�f�o�C�X�ւ̃|�C���^���擾

	//�e��ϐ��̏�����
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	return S_OK;
}

//==========================================================
//���f���̏I������
//==========================================================
void CObjectX::Uninit(void)
{
	// �p��
	Release();
}

//==========================================================
//���f���̍X�V����
//==========================================================
void CObjectX::Update(void)
{
	if (GetType() == CObject::TYPE_ENEMYSPAWN)
	{
		if (GetNumEnemAll() < 50)
		{
			int nRand = rand() % 201 - 100;
			float fRot = D3DX_PI * ((float)nRand * 0.01f);

			CEnemy::Create(D3DXVECTOR3(0.0f + rand() % 300 - 150, 0.0f, 0.0f + rand() % 300 - 150), D3DXVECTOR3(0.0f, fRot, 0.0f),
				D3DXVECTOR3(-sinf(fRot) * 4.0f, 0.0f, -cosf(fRot) * 4.0f), "data\\TXT\\motion_murabito.txt");
		}
	}
}

//==========================================================
//���f���̕`�揈��
//==========================================================
void CObjectX::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();		//�f�o�C�X�ւ̃|�C���^���擾
	CTexture *pTexture = CManager::GetTexture();	// �e�N�X�`���ւ̃|�C���^
	CXFile *pModelFile = CManager::GetModelFile();	// X�t�@�C�����̃|�C���^
	CXFile::FileData *pFileData = pModelFile->SetAddress(m_nIdxModel);
	D3DXMATRIX mtxRot, mtxTrans;			//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;					//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;						//�}�e���A���f�[�^�ւ̃|�C���^

	if (pFileData != NULL)
	{// ���f�����g�p����Ă���ꍇ
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_mtxWorld);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		//���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)pFileData->pBuffMat->GetBufferPointer();
		for (int nCntMat = 0; nCntMat < (int)pFileData->dwNumMat; nCntMat++)
		{
			D3DMATERIAL9 mat = SetSlowCol(&pMat[nCntMat].MatD3D);

			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&mat);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, pTexture->SetAddress(pFileData->pIdexTexture[nCntMat]));

			//���f��(�p�[�c)�̕`��
			pFileData->pMesh->DrawSubset(nCntMat);
		}

		//�ۑ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
}

//==========================================================
// ����
//==========================================================
CObjectX *CObjectX::Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot, const char *pFileName, const int nPriority)
{
	CObjectX *pObjectX = NULL;
	CXFile *pModelFile = CManager::GetModelFile();

	// �I�u�W�F�N�gX�̐���
	pObjectX = new CObjectX(nPriority);

	if (pObjectX != NULL)
	{// �����ł����ꍇ
		// ����������
		pObjectX->Init();

		// ���W
		pObjectX->SetPosition(pos);

		// ����
		pObjectX->SetRotation(rot);

		// ��ސݒ�
		pObjectX->SetType(TYPE_MODEL);

		// �ǂݍ��݊m�F
		pObjectX->BindFile(pModelFile->Regist(pFileName));
	}
	else
	{// �����Ɏ��s�����ꍇ
		return NULL;
	}

	return pObjectX;
}

//==========================================================
// ���f���̃t�@�C���ݒ�
//==========================================================
void CObjectX::BindFile(int nIdx)
{
	m_nIdxModel = nIdx;	//�g�p���郂�f���̐ݒ�
}

//==========================================================
// ���W�̐ݒ�
//==========================================================
void CObjectX::SetPosition(const D3DXVECTOR3 pos)
{
	m_pos = pos; 
}

//==========================================================
// �����̐ݒ�
//==========================================================
void CObjectX::SetRotation(const D3DXVECTOR3 rot)
{ 
	m_rot = rot;

	if (m_rot.z < -D3DX_PI)
	{// z���W�p�x���E
		m_rot.z += D3DX_PI * 2;
	}
	else if (m_rot.z > D3DX_PI)
	{// z���W�p�x���E
		m_rot.z += -D3DX_PI * 2;
	}

	if (m_rot.x < -D3DX_PI)
	{// x���W�p�x���E
		m_rot.x += D3DX_PI * 2;
	}
	else if (m_rot.x > D3DX_PI)
	{// x���W�p�x���E
		m_rot.x += -D3DX_PI * 2;
	}

	if (m_rot.y < -D3DX_PI)
	{// x���W�p�x���E
		m_rot.y += D3DX_PI * 2;
	}
	else if (m_rot.y > D3DX_PI)
	{// x���W�p�x���E
		m_rot.y += -D3DX_PI * 2;
	}
}

//==========================================================
// �X���[��Ԃ̐F�ݒ�
//==========================================================
D3DMATERIAL9 CObjectX::SetSlowCol(D3DMATERIAL9 *pMat)
{
	CSlow *pSlow = CManager::GetSlow();
	D3DMATERIAL9 mat = *pMat;

	if (pSlow == NULL)
	{
		return mat;
	}

	if (pSlow->Get() == 1.0f)
	{
		return mat;
	}

	float GetSlowMul = pSlow->Get();

	mat.Ambient = D3DXCOLOR(mat.Ambient.r * GetSlowMul, mat.Ambient.g * GetSlowMul, mat.Ambient.b, mat.Ambient.a);
	mat.Diffuse = D3DXCOLOR(mat.Diffuse.r * GetSlowMul, mat.Diffuse.r * GetSlowMul, mat.Diffuse.b, mat.Diffuse.a);
	mat.Emissive = D3DXCOLOR(mat.Emissive.r * GetSlowMul, mat.Emissive.r * GetSlowMul, mat.Emissive.b, mat.Emissive.a);

	return mat;
}