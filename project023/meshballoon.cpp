//==========================================================
//
// ���b�V���̐����D���� [meshballoon.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "meshballoon.h"
#include "texture.h"
#include "manager.h"
#include "renderer.h"
#include "slow.h"
#include "game.h"
#include "meshfield.h"
#include "bullet.h"
#include "wet.h"
#include "particle.h"

// �}�N����`
#define TEXTUREFILE_DATA	"data\\TEXTURE\\balloon001.jpg"		//�e�N�X�`���f�[�^
#define GRAVITY	(-0.1f)		// �d��
#define SWELL_CNT	(5)		// �c��ރJ�E���g
#define SWELL_MOVE	(20.0f)	// �c��ޗ�
#define SHRINK_CNT	(2)		// �k�ރJ�E���g
#define SHRINK_MOVE	(-3.0f)	// �k�ޗ�
#define NUM_EXPLOWATER	(20)	// �����Ԃ���
#define SIZEUP_WIDTH	(20)	// ��
#define MIN_SIZE	(60.0f)	// �Œ�T�C�Y

//==========================================================
// �R���X�g���N�^
//==========================================================
CMeshBalloon::CMeshBalloon() : CObjectMesh(6)
{
	m_pMtxParent = NULL;
	m_fHeight = 0.0f;
	m_fHeightRot = 0.0f;
	m_fLength = 0.0f;
	m_fRot = 0.0f;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fStateCnt = 0.0f;
	m_State = STATE_NONE;
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CMeshBalloon::~CMeshBalloon()
{

}

//==========================================================
// ����������
//==========================================================
HRESULT CMeshBalloon::Init(void)
{
	m_State = STATE_NONE;
	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CMeshBalloon::Uninit(void)
{
	//���_�o�b�t�@�̔p��
	CObjectMesh::Uninit();
}

//==========================================================
// �X�V����
//==========================================================
void CMeshBalloon::Update(void)
{
	if (m_pMtxParent != NULL)
	{// �e�����݂��Ă���ꍇ
		return;
	}

	// �ړ�
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float fHeight = CGame::GetMeshField()->GetHeight(GetPosition(), nor);
	m_move.y += GRAVITY * CManager::GetSlow()->Get();
	pos += m_move * CManager::GetSlow()->Get();

	if (pos.y < fHeight + m_fLength)
	{// �n�ʂɐG�ꂽ
		pos.y = fHeight + m_fLength;
		m_move.y *= -0.6f;
		m_move.x *= 0.5f;
		m_move.z *= 0.5f;

		if (m_State == STATE_NONE)
		{// �j���O�̏ꍇ
			m_State = STATE_SHRINK;
			m_fStateCnt = SWELL_CNT;
		}
	}

	SetPosition(pos);

	// ��Ԃ��Ƃ̍X�V
	UpdateState();
}

//==========================================================
// �`�揈��
//==========================================================
void CMeshBalloon::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	//���C�e�B���O���I�t�ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	if (m_pMtxParent == NULL)
	{// �e�����݂��Ȃ�
		// �`��
		CObjectMesh::Draw();
	}
	else
	{// �e�����݂���
		// �}�g���b�N�X�ݒ�
		SetParentMtx();
	}

	//���C�e�B���O���I���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
}

//==========================================================
// ���_���ݒ�
//==========================================================
void CMeshBalloon::SetVtxInfo(void)
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

		float fHeightRot = m_fHeightRot * (nCntVtx / (nNumWidth + 1));

		if (fHeightRot > D3DX_PI || fHeightRot < -D3DX_PI)
		{//-3.14�`3.14�͈̔͊O�̏ꍇ
			if (fHeightRot > D3DX_PI)
			{
				fHeightRot += (-D3DX_PI * 2);
			}
			else if (fHeightRot < -D3DX_PI)
			{
				fHeightRot += (D3DX_PI * 2);
			}
		}

		//���_���W
		m_pVtx[nCntVtx].pos.x = (cosf(fHeightRot) * cosf(fRot)) * m_fLength;
		m_pVtx[nCntVtx].pos.y = sinf(fHeightRot) * m_fLength;
		m_pVtx[nCntVtx].pos.z = (cosf(fHeightRot) * sinf(fRot)) * m_fLength;

		// �x�N�g�������߂�
		vecDir = pos - m_pVtx[nCntVtx].pos;

		//�x�N�g���𐳋K������
		D3DXVec3Normalize(&vecDir, &vecDir);

		//�@��
		m_pVtx[nCntVtx].nor = vecDir;

		//�F
		m_pVtx[nCntVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		m_pVtx[nCntVtx].tex = D3DXVECTOR2((1.0f / nNumWidth) * (nCntVtx % (nNumWidth + 1)), 1.0f - ((1.0f / nNumHeight) * (nCntVtx / (nNumWidth + 1))));
	}

	// ���_�ݒ�
	SetVtx();
}

//==========================================================
// ����
//==========================================================
CMeshBalloon *CMeshBalloon::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot,
	float fLength, float fHeight, const int nPriority, const int nWidth, const int nHeight)
{
	CMeshBalloon *pMeshWall = NULL;	// ���b�V���t�B�[���h�̃|�C���^
	CTexture *pTexture = CManager::GetTexture();	// �e�N�X�`���ւ̃|�C���^

	// �������̊m��
	pMeshWall = new CMeshBalloon;

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
		pMeshWall->m_fRot = (-D3DX_PI * 2) / nWidth;

		// �c�����̊p�x�����߂�
		pMeshWall->m_fHeightRot = (-D3DX_PI * 2) / (nHeight);

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
void CMeshBalloon::SetSize(float fLength, float fHeight)
{
	// �T�C�Y�ݒ�
	m_fLength = fLength;
	m_fHeight = fHeight;

	// ���_���ݒ�
	SetVtxInfo();
}

//==========================================================
// ���a���Z
//==========================================================
void CMeshBalloon::AddLength(float fAddLength)
{
	// �T�C�Y�ݒ�
	m_fLength += fAddLength;

	if (m_fLength < 0.0f)
	{
		m_fLength = 0.0f;
	}

	// ���_���ݒ�
	SetVtxInfo();
}

//==========================================================
// �e�q�֌W�̑��݂���}�g���b�N�X�ݒ�
//==========================================================
void CMeshBalloon::SetParentMtx(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	//�f�o�C�X�ւ̃|�C���^���擾
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxParent;			// �e�̃}�g���b�N�X���
	CSlow *pSlow = CManager::GetSlow();
	D3DXVECTOR3 pos = GetPosition(), rot = GetRotation();
	D3DXMATRIX *pMtx = GetMtx();

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(pMtx);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(pMtx, pMtx, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(pMtx, pMtx, &mtxTrans);

	if (m_pMtxParent != NULL)
	{// �o���Ă���ꍇ
		mtxParent = *m_pMtxParent;

		//�p�[�c�̃}�g���b�N�X�Ɛe�̃}�g���b�N�X���������킹��
		D3DXMatrixMultiply(pMtx,
			pMtx, &mtxParent);
	}

	// �}�g���b�N�X�ݒ�
	SetMtx(*pMtx);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, pMtx);

	// �`��
	NotMtxDraw();
}

//==========================================================
// ��Ԃ��Ƃ̍X�V����
//==========================================================
void CMeshBalloon::UpdateState(void)
{
	D3DXVECTOR3 nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	switch (m_State)
	{
	case STATE_NONE:

		break;

	case STATE_SHRINK:

		AddLength(SHRINK_MOVE * CManager::GetSlow()->Get());
		m_fStateCnt -= CManager::GetSlow()->Get();

		if (m_fStateCnt <= 0.0f)
		{
			m_State = STATE_SWELL;	// ������ԂɕύX
			m_fStateCnt = SWELL_CNT;
		}

		break;

	case STATE_SWELL:

		AddLength(SWELL_MOVE * CManager::GetSlow()->Get());
		m_fStateCnt -= CManager::GetSlow()->Get();

		if (m_fStateCnt <= 0.0f)
		{
			// �e�̔���
			CBullet *pBullet = NULL;
			pBullet = CBullet::Create(GetPosition(),
				D3DXVECTOR3(0.0f, 2.0f, 0.0f), CBullet::TYPE_GRAVITY);

			pBullet->SetSize(m_fLength * 5, 150.0f);
			pBullet->SetLife(300.0f);

			float fMultiRot = 1.0f / NUM_EXPLOWATER;
			int nAddPar = (m_fLength - MIN_SIZE) / SIZEUP_WIDTH;
			int nAddWater = nAddPar * NUM_EXPLOWATER;

			//�����Ԃ��̐���
			for (int nCnt = 0; nCnt < nAddWater; nCnt++)
			{
				// ���W�̐ݒ�
				D3DXVECTOR3 pos = GetPosition();
				D3DXVECTOR3 move;
				float fRand = (float)(rand() % 628 - 314) * 0.01f;

				//�ړ��ʂ̐ݒ�
				move.x = (-cosf(-D3DX_PI + D3DX_PI * 2 * (fMultiRot * nCnt))) * (rand() % 15);
				move.y = rand() % 100 * 0.11f;
				move.z = (-sinf(-D3DX_PI + D3DX_PI * 2 * (fMultiRot * nCnt))) * (rand() % 15);

				pBullet = CBullet::Create(pos,
					move, CBullet::TYPE_EXPLOSION);
				pBullet->SetLife(300.0f);
			}

			float fHeight = CGame::GetMeshField()->GetHeight(GetPosition(), nor);

			// �G��Ղ̐���
			CWet::Create(D3DXVECTOR3(GetPosition().x, fHeight + 0.05f, GetPosition().z), m_fLength, m_fLength);
			CWet::Create(D3DXVECTOR3(GetPosition().x, fHeight + 0.05f, GetPosition().z), m_fLength, m_fLength);

			// �p�[�e�B�N���̐���
			for (int nCnt = 0; nCnt < nAddPar + 1; nCnt++)
			{
				CParticle::Create(D3DXVECTOR3(GetPosition().x, fHeight, GetPosition().z), CEffect::TYPE_BALEXPLOSION);
			}

			CParticle::Create(D3DXVECTOR3(GetPosition().x, fHeight + 0.05f, GetPosition().z), CEffect::TYPE_SMAKE);

			// �I������
			Uninit();
		}

		break;
	}
}