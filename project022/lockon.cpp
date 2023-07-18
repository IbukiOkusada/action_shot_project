//==========================================================
//
// ���b�N�I���̏��� [lockon.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "lockon.h"
#include "manager.h"
#include "texture.h"
#include "debugproc.h"
#include "renderer.h"
#include "objectX.h"
#include "model.h"
#include "camera.h"

//==========================================================
// �R���X�g���N�^
//==========================================================
CLockOn::CLockOn(int nPriOrity) : CObjectBillboard(nPriOrity)
{
	// �l�̃N���A
	m_bLock = false;
	m_DisL.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_DisL.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_DisR.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_DisR.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fLength = 0.0f;
	m_fAngle = 0.0f;
	m_pMtx = NULL;
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CLockOn::~CLockOn()
{

}

//==========================================================
// ����������
//==========================================================
HRESULT CLockOn::Init(void)
{
	// �r���{�[�h�̏�����
	CObjectBillboard::Init();

	// �F��ύX
	SetVtx(D3DXCOLOR(1.0f, 1.0f, 0.5f, 1.0f));

	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CLockOn::Uninit(void)
{
	// �I��
	CObjectBillboard::Uninit();
}

//==========================================================
// �X�V����
//==========================================================
void CLockOn::Update(void)
{
	if (m_bUse == false)
	{
		return;
	}

	CCamera *pCamera = CManager::GetCamera();		// �J�����̃|�C���^
	D3DXVECTOR3 CamRot = pCamera->GetRotation();	// �J�����̊p�x

	// ���b�N�I������
	LockOn();

	if (m_pMtx != NULL)
	{
		m_DisL.pos.x = m_pMtx->_41 + cosf(m_DisL.rot.z + CamRot.y + (-m_fAngle)) * m_fLength;
		m_DisL.pos.y = m_pMtx->_42 + 0.0f;
		m_DisL.pos.z = m_pMtx->_43 + sinf(m_DisL.rot.z + CamRot.y + (-m_fAngle)) * m_fLength;

		m_DisR.pos.x = m_pMtx->_41 + cosf(m_DisR.rot.z + CamRot.y + (m_fAngle)) * m_fLength;
		m_DisR.pos.y = m_pMtx->_42 + 0.0f;
		m_DisR.pos.z = m_pMtx->_43 + sinf(m_DisR.rot.z + CamRot.y + (m_fAngle)) * m_fLength;
	}

	// �}�g���b�N�X�X�V
	SetDisMtx(&m_DisL);
	SetDisMtx(&m_DisR);
}

//==========================================================
// �`�揈��
//==========================================================
void CLockOn::Draw(void)
{
	if (m_bUse == false || m_bLock == false)
	{
		return;
	}

	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	//���C�e�B���O���I�t�ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//Z�e�X�g�𖳌�������
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	CObjectBillboard::Draw();

	//���C�e�B���O���I�t�ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//Z�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

//==========================================================
// �͈͐ݒ�
//==========================================================
void CLockOn::SetDistance(float fLength, float fAngle)
{
	m_fAngle = fAngle;
	m_fLength = fLength;

	m_DisL.pos.x = sinf(m_DisL.rot.z + D3DX_PI * 0.25f + (-fAngle)) * fLength;
	m_DisL.pos.y = 0.0f;
	m_DisL.pos.z = cosf(m_DisL.rot.z + D3DX_PI * 0.25f + (-fAngle)) * fLength;

	m_DisR.pos.x = sinf(m_DisR.rot.z + D3DX_PI * 0.25f + (fAngle)) * fLength;
	m_DisR.pos.y = 0.0f;
	m_DisR.pos.z = cosf(m_DisR.rot.z + D3DX_PI * 0.25f + (fAngle)) * fLength;
}

//==========================================================
// ����
//==========================================================
CLockOn *CLockOn::Create(D3DXMATRIX *pMtx)
{
	CLockOn *pLock = NULL;

	// ����
	pLock = new CLockOn();

	if (pLock == NULL)
	{// �m�ۂł��Ȃ������ꍇ
		return NULL;
	}

	// ����������
	pLock->Init();

	// �e�̃}�g���b�N�X�ݒ�
	pLock->SetParent(pMtx);

	// �e�N�X�`���w��
	pLock->BindTexture(CTexture::TYPE_LOCKON);

	return pLock;
}

//==========================================================
// ���b�N�I���^�[�Q�b�g�ݒ�
//==========================================================
void CLockOn::LockOn(void)
{
	CObject *pOldObj = NULL;
	int nCnt = 0;
	int nCntObj = 0;

	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		CObject *pObj = CObject::GetTop(nCntPri);	// �擪���擾

		while (pObj != NULL)
		{// �g�p����Ă��Ȃ���Ԃ܂�

			CObject *pObjectNext = pObj->GetNext();	// ���̃I�u�W�F�N�g�ւ̃|�C���^���擾

			if (pObj == NULL)
			{// �g�p����Ă��Ȃ��ꍇ
				pObj = pObjectNext;	// ���̃I�u�W�F�N�g�Ɉړ�
				continue;
			}

			if (pObj->GetType() != CObject::TYPE_ENEMY)
			{// ��ނ����f���ł͂Ȃ��ꍇ
				pObj = pObjectNext;	// ���̃I�u�W�F�N�g�Ɉړ�
				continue;
			}

			if (pObj->GetDeath() == false)
			{
				D3DXVECTOR3 ObjPos = pObj->GetPosition();

				D3DXVECTOR3 vec1, vec2;	//����p�ϐ�
				D3DXVECTOR3 vecToPos;	//����p�ϐ�
				float fMaxField;		//����p
				float fField, fField2;
				float fRate, fRate2;	//����p�ϐ�

				// �v���C���[���画�苗���ւ̃x�N�g�������߂�
				vec1 = D3DXVECTOR3(m_DisL.mtxWorld._41 - m_pMtx->_41, m_DisL.mtxWorld._42 - m_pMtx->_42, m_DisL.mtxWorld._43 - m_pMtx->_43);
				vec2 = D3DXVECTOR3(m_DisR.mtxWorld._41 - m_pMtx->_41, m_DisR.mtxWorld._42 - m_pMtx->_42, m_DisR.mtxWorld._43 - m_pMtx->_43);

				// ���݂̍��W�̃x�N�g�������߂�
				vecToPos = D3DXVECTOR3(ObjPos.x - m_pMtx->_41,
					ObjPos.y - m_pMtx->_42,
					ObjPos.z - m_pMtx->_43);

				// �ʐς����߂�
				fMaxField = (vec1.x * vec2.z) - (vec1.z * vec2.x);

				// ���݂̈ʒu�Ƃ̖ʐς����߂�
				fField = (vecToPos.x * vec2.z) - (vecToPos.z * vec2.x);
				fField2 = (vecToPos.z * vec1.x) - (vecToPos.x * vec1.z);

				// ��_�̊��������߂�
				fRate = fField / fMaxField;
				fRate2 = fField2 / fMaxField;

				if (fRate >= 0.0f && fRate <= 1.0f && fRate2 >= 0.0f && fRate2 <= 1.0f && (fRate + fRate2) <= 1.0f)
				{// �O�p�|���S���̒��ɂ���
					if (pOldObj != NULL)
					{// ��ԋ߂��I�u�W�F�N�g������ꍇ

						D3DXVECTOR3 OldPos = pOldObj->GetPosition();

						// ��ԋ߂����f���ƃv���C���[�̋��������߂�
						float fOldObjLength =
							sqrtf((OldPos.x - m_pMtx->_41) * (OldPos.x - m_pMtx->_41)
								+ (OldPos.y - m_pMtx->_42) * (OldPos.y - m_pMtx->_42)
								+ (OldPos.z - m_pMtx->_43) * (OldPos.z - m_pMtx->_43));

						// ����̃��f���ƃv���C���[�̋��������߂�
						float fObjLength =
							sqrtf((ObjPos.x - m_pMtx->_41) * (ObjPos.x - m_pMtx->_41)
								+ (ObjPos.y - m_pMtx->_42) * (ObjPos.y - m_pMtx->_42)
								+ (ObjPos.z - m_pMtx->_43) * (ObjPos.z - m_pMtx->_43));

						if (fObjLength < fOldObjLength)
						{// ����̃��f���̕����߂��ꍇ
							pOldObj = pObj;	// ��ԋ߂����f����ύX
						}
					}
					else
					{// �O�񃂃f�����o���Ă��Ȃ��ꍇ
						pOldObj = pObj;
					}
				}
			}

			pObj = pObjectNext;	// ���̃I�u�W�F�N�g�Ɉړ�
		}
	}

	if (pOldObj != NULL)
	{// �g�p����Ă���ꍇ
		SetPosition(D3DXVECTOR3(pOldObj->GetPosition().x, pOldObj->GetPosition().y + 30.0f, pOldObj->GetPosition().z));
		SetSize(20.0f, 20.0f);
		m_bLock = true;
		m_pObj = pOldObj;
	}
	else
	{
		m_bLock = false;
		SetSize(0.0f, 0.0f);
		m_pObj = NULL;
	}
}

//==========================================================
// �͈̓}�g���b�N�X�ύX
//==========================================================
void CLockOn::SetDisMtx(DISTANCE *pDis)
{
	D3DXMATRIX mtxRot, mtxTrans, mtxParent;	//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&pDis->mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, pDis->rot.y, pDis->rot.x, pDis->rot.z);
	D3DXMatrixMultiply(&pDis->mtxWorld, &pDis->mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, pDis->pos.x, pDis->pos.y, pDis->pos.z);
	D3DXMatrixMultiply(&pDis->mtxWorld, &pDis->mtxWorld, &mtxTrans);
}

//==========================================================
// �g�p����e�}�g���b�N�X��ݒ�
//==========================================================
void CLockOn::SetParent(D3DXMATRIX *pMtx)
{
	// �e�̃}�g���b�N�X���w��
	m_pMtx = pMtx;
}

//==========================================================
// �g�p����e�}�g���b�N�X��ݒ�
//==========================================================
CObject *CLockOn::GetTag(void)
{
	if (m_pObj != NULL)
	{
		if (m_pObj->GetDeath() == false)
		{
			CObject *pObj = m_pObj;
			return pObj;
		}
	}

	return NULL;
}