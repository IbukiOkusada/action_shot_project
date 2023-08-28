//==========================================================
//
// �^�[�Q�b�g�l���̏��� [target.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _TARGET_H_	// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _TARGET_H_	// ��d�C���N���[�h�h�~�p�}�N�����`

#include "main.h"

// �O���錾
class CNumber;

// �}�N����`
#define NUM_TARGET	(3)	// �X�R�A�̌���

//==========================================================
// �^�[�Q�b�g�N���X�̒�`(���N���X)
//==========================================================
class CTarget
{
public:	// ��������֐�(�N�ł��A�N�Z�X�\)

	CTarget();	// �R���X�g���N�^
	~CTarget();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CTarget *Create(D3DXVECTOR3 pos);

	// �����o�֐�
	void Add(int nValue);
	void Set(int nValue);
	void SetColor(D3DXCOLOR col);

	// �����o�֐�(�擾)
	int GetNum(void) { return m_nNum; }

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	void SetValue(void);

	// �����o�ϐ�
	CNumber *m_apNumber[NUM_TARGET];	// �����̃|�C���^
	D3DXVECTOR3 m_pos;	// ���W
	int m_nNum;			// ���݂̒l
	int m_nIdxTexture;	// �e�N�X�`���ԍ�
	
};

#endif
