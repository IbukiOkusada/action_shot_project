//===============================================
//
// ���x�\���̏��� [thermo.h]
// Author : Ibuki Okusada
//
//===============================================
#ifndef _THERMO_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _THERMO_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "object3D.h"

//==========================================================
// �t�B���^�[�̃N���X��`(�h���N���X)
//==========================================================
class CThermo : public CObject3D
{
public:	// �N�ł��A�N�Z�X�\

	CThermo(int nPriority = 3);	// �f�t�H���g�����R���X�g���N�^
	virtual ~CThermo();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CThermo *Create(void);

	// �����o�֐�(�擾)
	D3DXCOLOR GetCol(void) { return m_col; }	// �F���擾

	// �����o�֐�(�ݒ�)
	void SetColor(D3DXCOLOR col) { m_colDiff = col; }	// �F��ݒ�

private:	// �����������A�N�Z�X�\

	D3DXCOLOR m_col;	// �F
	D3DXCOLOR m_colDiff;// �ړI�̐F
	float m_fRadius;	// ���a
};

#endif