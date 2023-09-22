//===============================================
//
// �A�C�e���̏��� [item.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "item.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "debugproc.h"
#include "explosion.h"
#include "enemy.h"
#include "effect.h"
#include "particle.h"
#include "sound.h"
#include "score.h"
#include "texture.h"

//===============================================
// �}�N����`
//===============================================
#define LIFE	(120)		// ����

//===============================================
// �ÓI�����o�ϐ��錾(�t�@�C����)
//===============================================
const char *CItem::m_apTextureFileName[] =
{
	"data\\TEXTURE\\item000.png",
	"data\\TEXTURE\\item001.png",
};

////===============================================
//// �R���X�g���N�^
////===============================================
//CItem::CItem()
//{
//	// �l�̃N���A
//}

//===============================================
// �R���X�g���N�^(�I�[�o�[���[�h)
//===============================================
CItem::CItem(int nPriority) : CObject2D(nPriority)
{
	// �l�̃N���A
}

//===============================================
// �f�X�g���N�^
//===============================================
CItem::~CItem()
{

}

//===============================================
// ����������
//===============================================
HRESULT CItem::Init(void)
{
	// �I�u�W�F�N�g�̏���������
	CObject2D::Init();

	m_nType = 0;

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CItem::Uninit(void)
{
	// �I�u�W�F�N�g�̏I������
	CObject2D::Uninit();
}

//===============================================
// �X�V����
//===============================================
void CItem::Update(void)
{
	if (Collision(GetPosition()) == true)
	{// ���������ꍇ
		
		return;
	}
	// ���W�X�V
	Controller();

	// ���_���X�V
	//SetVtx();
}

//===============================================
// �`�揈��
//===============================================
void CItem::Draw(void)
{
	CObject2D::Draw();
}

//===============================================
// ���_���ݒ�
//===============================================
CItem *CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, TYPE type)
{
	CTexture *pTexture = CManager::GetTexture();	// �e�N�X�`���̃|�C���^
	CItem *pItem = NULL;

	// �I�u�W�F�N�g2D�̐���
	pItem = new CItem();

	if (pItem != NULL)
	{// �����ł����ꍇ

		// ����������
		pItem->Init();

		// ��ސݒ�
		pItem->m_nType = type;

		// �I�u�W�F�N�g�^�C�v�̐ݒ�
		pItem->SetType(CObject::TYPE_ITEM);

		// ���W�ݒ�
		pItem->SetPosition(pos);

		// �����ݒ�
		pItem->SetRotation(rot);

		// �T�C�Y�ݒ�
		pItem->SetLength(100.0f, 100.0f);

		// �e�N�X�`���̊��蓖��
		pItem->BindTexture(pTexture->Regist(m_apTextureFileName[type]));
	}
	else
	{// �����Ɏ��s�����ꍇ
		return NULL;
	}

	return pItem;
}

//===============================================
// ���쏈��
//===============================================
void CItem::Controller(void)
{
	
}

//===============================================
// �A�C�e���Ƃ̓����蔻��
//===============================================
bool CItem::Collision(D3DXVECTOR3 pos)
{
	//for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	//{
	//	for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
	//	{
	//		CObject *pObj;	// �I�u�W�F�N�g�N���X�̃|�C���^

	//		// �I�u�W�F�N�g�̎擾
	//		pObj = GetObject(nCntPri, nCntObj);

	//		if (pObj != NULL)
	//		{// �g�p����Ă���ꍇ

	//			CObject::TYPE type;	// ���

	//			// �I�u�W�F�N�g�̎�ނ��擾
	//			type = pObj->GetType();

	//			if (type == TYPE_PLAYER)
	//			{// ��ނ��v���C���[�̏ꍇ

	//				D3DXVECTOR3 ObjPos;	// �I�u�W�F�N�g�̍��W

	//				// ���W�̎擾
	//				ObjPos = pObj->GetPosition();

	//				float fObjWidth = 0.0f;
	//				float fObjHeight = 0.0f;

	//				// ���W�̎擾
	//				ObjPos = pObj->GetPosition();
	//				CObject2D *pObj2D = pObj->GetObject2D();

	//				if (pObj2D != NULL)
	//				{
	//					fObjWidth = pObj2D->GetWidth();
	//					fObjHeight = pObj2D->GetHeight();
	//				}

	//				if (pos.x + GetWidth() >= ObjPos.x - fObjWidth && pos.x - GetWidth() <= ObjPos.x + fObjWidth
	//					&& pos.y + GetHeight() >= ObjPos.y - fObjHeight && pos.y - GetHeight() <= ObjPos.y)
	//				{// �G�Əd�Ȃ����ꍇ

	//					// �����̐���
	//					CExplosion::Create(pos);

	//					// �X�R�A�̉��Z
	//					CManager::GetScore()->Add(500);

	//					// �������g�̏I������
	//					Uninit();

	//					return TRUE;	// TRUE��Ԃ�(��������)
	//				}

	//			}
	//		}
	//	}
	//}
	return FALSE;	// FALSE��Ԃ�(���ɂ��������Ă��Ȃ�)
}