//==========================================================
//
// �X�R�A�̏��� [score.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _SCORE_H_	// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _SCORE_H_	// ��d�C���N���[�h�h�~�p�}�N�����`

#include "main.h"

// �O���錾
class CNumber;

// �}�N����`
#define NUM_SCORE	(8)	// �X�R�A�̌���

//==========================================================
// �e�N�X�`���X���C�h�I�u�W�F�N�g(2D)�̃N���X��`(�h���N���X)
//==========================================================
class CScore
{
public:	// ��������֐�(�N�ł��A�N�Z�X�\)

	CScore();	// �R���X�g���N�^
	~CScore();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CScore *Create(D3DXVECTOR3 pos);

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
	CNumber *m_apNumber[NUM_SCORE];	// �����̃|�C���^
	D3DXVECTOR3 m_pos;	// ���W
	int m_nNum;	// ���݂̒l
	int m_nIdxTexture;	// �e�N�X�`���ԍ�
	
};

#endif
