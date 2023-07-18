//==========================================================
//
// �^�C���̏��� [time.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _TIME_H_	// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _TIME_H_	// ��d�C���N���[�h�h�~�p�}�N�����`

#include "main.h"

// �O���錾
class CNumber;

//==========================================================
// �e�N�X�`���X���C�h�I�u�W�F�N�g(2D)�̃N���X��`(�h���N���X)
//==========================================================
class CTime
{
public:	// ��������֐�(�N�ł��A�N�Z�X�\)

	CTime();	// �R���X�g���N�^
	~CTime();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CTime *Create(D3DXVECTOR3 pos);

	// �����o�֐�
	void Add(int nValue);
	void Set(int nValue);

	// �����o�֐�(�擾)
	int GetNum(void) { return m_nNum; }

private:	// �����������A�N�Z�X�\

	// �}�N����`
	#define NUM_PLACE	(4)	// �X�R�A�̌���

	// �����o�֐�
	void SetValue(void);

	// �����o�ϐ�
	CNumber *m_apNumber[NUM_PLACE];			// �����̃|�C���^
	D3DXVECTOR3 m_pos;	// ���W
	int m_nNum;	// ���݂̒l
	int m_nAnimTimer;	// 1�b�J�E���g
	int m_nIdxTexture;	// �e�N�X�`���ԍ�
	
};

#endif
