//===============================================
//
// �����̏��� [exploion.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "explosion.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "debugproc.h"
#include "bullet.h"
#include "texture.h"

//===============================================
// �}�N����`
//===============================================
#define VTX	(4)	// ���_��
#define WIDTH	(50.0f)	// ��
#define HEIGHT	(50.0f)	// ����
#define ANIMTIMER		(5)		//��R�}�i�ގ���
#define MAX_ANIMPATTERN	(8)	//�A�j���[�V�����̍ő�p�^�[����
#define MAX_HEIFGHTPATTERN	(8)	//�A�j���[�V�����̍ő剡�p�^�[����

//===============================================
// �R���X�g���N�^
//===============================================
CExplosion::CExplosion()
{
	// �l���N���A����
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
}

//===============================================
// �R���X�g���N�^(�I�[�o�[���[�h)
//===============================================
CExplosion::CExplosion(const D3DXVECTOR3 pos)
{
	// �l���N���A����
	SetPosition(pos);
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
}

//===============================================
// �f�X�g���N�^
//===============================================
CExplosion::~CExplosion()
{

}

//===============================================
// ����������
//===============================================
HRESULT CExplosion::Init(void)
{
	// �I�u�W�F�N�g�̏���������
	CObjectBillboard::Init();

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CExplosion::Uninit(void)
{
	// �I�u�W�F�N�g�̏I������
	CObjectBillboard::Uninit();
}

//===============================================
// �X�V����
//===============================================
void CExplosion::Update(void)
{
	// ���_���ݒ�
	SetVtx(m_nPatternAnim, MAX_HEIFGHTPATTERN, MAX_ANIMPATTERN / MAX_HEIFGHTPATTERN);

	// �v���C���[����
	Controller();
}

//===============================================
// �`�揈��
//===============================================
void CExplosion::Draw(void)
{
	CObjectBillboard::Draw();
}

//===============================================
// ���_���ݒ�
//===============================================
CExplosion *CExplosion::Create(D3DXVECTOR3 pos)
{
	CExplosion *pExplosion = NULL;
	CTexture *pTexture = CManager::GetTexture();	// �e�N�X�`���ւ̃|�C���^

	// �I�u�W�F�N�g2D�̐���
	pExplosion = new CExplosion(pos);

	if (pExplosion != NULL)
	{// �����ł����ꍇ

		// ����������
		pExplosion->Init();

		// ��ނ̐ݒ�
		pExplosion->SetType(TYPE_EXPLOSION);

		// �e�N�X�`���ݒ�
		pExplosion->SetVtx(pExplosion->m_nPatternAnim, MAX_HEIFGHTPATTERN, MAX_ANIMPATTERN / MAX_HEIFGHTPATTERN);

		// �e�N�X�`���̊��蓖��
		pExplosion->BindTexture(pTexture->Regist(CTexture::GetFileName(CTexture::TYPE_EXPLOSION)));
	}
	else
	{// �����Ɏ��s�����ꍇ
		return NULL;
	}

	return pExplosion;
}

//===============================================
// ���쏈��
//===============================================
void CExplosion::Controller(void)
{
 	m_nCounterAnim++;	//�J�E���^�[�����Z

	if (m_nCounterAnim % ANIMTIMER == 0)
	{// �A�j���[�V�����^�C�}�[�̒l�𒴂����ꍇ

		m_nCounterAnim = 0;

		m_nPatternAnim++;	//�p�^�[��No.���X�V

		if (m_nPatternAnim >= MAX_ANIMPATTERN)
		{// �Ō�܂ŃA�j���[�V���������ꍇ
			Uninit();
		}
	}
}
