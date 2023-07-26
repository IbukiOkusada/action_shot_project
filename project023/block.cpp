//===============================================
//
// �u���b�N�̏��� [block.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "block.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "debugproc.h"
#include "texture.h"

//===============================================
// �ÓI�����o�ϐ��錾(�t�@�C����)
//===============================================
const char *CBlock::apTextureFileName[] =
{
	"data\\TEXTURE\\block000.jpg",
};

//===============================================
// �}�N����`
//===============================================
#define VTX	(4)	// ���_��
#define WIDTH	(30.0f)	// ��
#define HEIGHT	(30.0f)	// ����

//===============================================
// �R���X�g���N�^
//===============================================
//CBlock::CBlock()
//{
//	// �l���N���A����
//}

//===============================================
// �R���X�g���N�^(�I�[�o�[���[�h)
//===============================================
CBlock::CBlock(const D3DXVECTOR3 pos, const int nPriority) : CObject2D(pos)
{
	// �l���N���A����
	
}

//===============================================
// �R���X�g���N�^(�I�[�o�[���[�h)
//===============================================
CBlock::CBlock(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 move, const int nPriority) : CObject2D(pos, rot, nPriority)
{
	// �K��l������
	m_move = move;
}

CBlock::CBlock(const int nPriority) : CObject2D(nPriority)
{
	m_nMoveCnt = 0;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//===============================================
// �f�X�g���N�^
//===============================================
CBlock::~CBlock()
{

}

//===============================================
// ����������
//===============================================
HRESULT CBlock::Init(void)
{
	// �I�u�W�F�N�g�̏���������
	CObject2D::Init();

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CBlock::Uninit(void)
{
	// �I�u�W�F�N�g�̏I������
	CObject2D::Uninit();
}

//===============================================
// �X�V����
//===============================================
void CBlock::Update(void)
{
	// �v���C���[����
	Controller();

	m_nMoveCnt++;

	if (m_nMoveCnt > 180)
	{
		m_nMoveCnt = 0;
		m_move *= -1.0f;
	}

	D3DXVECTOR3 pos = GetPosition();

	pos += m_move;

	SetPosition(pos);

	// ���_���X�V
	SetSize(WIDTH, HEIGHT);
}

//===============================================
// �`�揈��
//===============================================
void CBlock::Draw(void)
{
	CObject2D::Draw();
}

//===============================================
// ���_���ݒ�
//===============================================
CBlock *CBlock::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 move, int nWidthTex, int nHeightTex)
{
	CBlock *pBlock = NULL;
	CTexture *pTexture = CManager::GetTexture();	// �e�N�X�`���ւ̃|�C���^

	// �I�u�W�F�N�g2D�̐���
	pBlock = new CBlock();

	if (pBlock != NULL)
	{// �����ł����ꍇ

		// ����������
		pBlock->Init();

		// ���W�ݒ�
		pBlock->SetPosition(pos);

		// �����ݒ�
		pBlock->SetRotation(rot);

		// �ړ��ʐݒ�
		pBlock->SetMove(move);

		// ��ނ̐ݒ�
		pBlock->SetType(CObject::TYPE_BLOCK);

		pBlock->SetLength(WIDTH, HEIGHT);

		// �e�N�X�`���̊��蓖��
		pBlock->BindTexture(pTexture->Regist(apTextureFileName[0]));
	}
	else
	{// �����Ɏ��s�����ꍇ
		return NULL;
	}

	return pBlock;
}

//===============================================
// ���쏈��
//===============================================
void CBlock::Controller(void)
{
	
}
