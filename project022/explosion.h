//==========================================================
//
// �����̏��� [explosion.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _EXPLOSION_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _EXPLOSION_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "main.h"
#include "billboard.h"

//==========================================================
// �A�j���[�V�����I�u�W�F�N�g(2D)�̃N���X��`(�h���N���X)
//==========================================================
class CExplosion : public CObjectBillboard
{
public:	// �N�ł��A�N�Z�X�\

	CExplosion();	// �R���X�g���N�^
	CExplosion(const D3DXVECTOR3 pos);	// �R���X�g���N�^(�I�[�o�[���[�h)
	~CExplosion();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CExplosion *Create(const D3DXVECTOR3 pos);

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	void Controller(void);

	// �����o�ϐ�
	int m_nCounterAnim;	//�A�j���[�V�����J�E���^�[
	int m_nPatternAnim;	//�A�j���[�V�����p�^�[��No.
};

#endif
