//===============================================
//
// �G��Ղ̏��� [wet.h]
// Author : Ibuki Okusada
//
//===============================================
#ifndef _WET_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _WET_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "shadow.h"

//===============================================
// �G��ՃN���X�̒�` (�h���N���X)
//===============================================
class CWet : public CShadow
{
public:		// �N�ł��A�N�Z�X�\

	CWet();		// �R���X�g���N�^
	~CWet();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CWet *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);
	void SetSize(float fWidth, float fHeight);

private:	// �����������A�N�Z�X�\

	// �����o�ϐ�
	float m_fLife;		// ����
	float m_fDefWidth;	// ��
	float m_fDefHeight;	// ����
	D3DXCOLOR m_col;	// �F
};

#endif
