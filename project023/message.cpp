//==========================================================
//
// ���b�Z�[�W�\���̏��� [message.cpp]
// Author : Ibuki Okusada
//
//==========================================================
#include "message.h"
#include "manager.h"
#include "game.h"

//===============================================
// �}�N����`
//===============================================
#define VTX	(4)	// ���_��
#define WIDTH	(100.0f)	// ��
#define HEIGHT	(100.0f)	// ����
#define POS_X	(300.0f)	// X���W
#define POS_Y	(300.0f)	// Y���W
#define TEX_FILENAME "data\\TEXTURE\\meteor001.png"	// �e�N�X�`����

//====================================================================================
// �I�u�W�F�N�g2D�N���X
//====================================================================================
//===============================================
// �R���X�g���N�^
//===============================================
//CMessage::CMessage()
//{
//	// �l���N���A����
//	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	m_fLength = 0.0f;
//	m_fAngle = 0.0f;
//	m_fWidth = 0.0f;
//	m_fHeight = 0.0f;
//}

//===============================================
// �R���X�g���N�^(�I�[�o�[���[�h)
//===============================================
CMessage::CMessage(int nPriority) : CObject2D(nPriority)
{
	// �l���N���A����
}

//===============================================
// �f�X�g���N�^
//===============================================
CMessage::~CMessage()
{

}

//===============================================
// ����������
//===============================================
HRESULT CMessage::Init(void)
{
	CObject2D::Init();

	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CMessage::Uninit(void)
{
	CObject2D::Uninit();
}

//===============================================
// �X�V����
//===============================================
void CMessage::Update(void)
{
	m_col.a -= 0.02f;

	if (m_col.a < 0.0f)
	{
		Uninit();
	}
	else
	{
		SetCol(m_col);
	}
}

//===============================================
// �`�揈��
//===============================================
void CMessage::Draw(void)
{
	CObject2D::Draw();
}

//===============================================
// ���_���ݒ�
//===============================================
CMessage *CMessage::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const int nPriority)
{
	CMessage *pObject2D = NULL;

	// �I�u�W�F�N�g2D�̐���
	pObject2D = new CMessage(nPriority);

	if (pObject2D != NULL)
	{// �����ł����ꍇ
		// ����������
		pObject2D->Init();

		pObject2D->SetPosition(pos);

		pObject2D->SetRotation(rot);

		pObject2D->SetLength(300.0f, 100.0f);

		// ��ސݒ�
		pObject2D->SetType(TYPE_NONE);
	}
	else
	{// �����Ɏ��s�����ꍇ
		return NULL;
	}

	return pObject2D;
}
