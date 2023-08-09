//==========================================================
//
// ���b�Z�[�W�\���̏��� [message.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _MESSAGE_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _MESSAGE_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "object2D.h"

//==========================================================
// �I�u�W�F�N�g(2D)�̃N���X��`(�h���N���X)
//==========================================================
class CMessage : public CObject2D
{
public:	// �N�ł��A�N�Z�X�\

	//CMessage();	// �R���X�g���N�^
	CMessage(int nPriority = 7);	// �f�t�H���g�����R���X�g���N�^
	virtual ~CMessage();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CMessage *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const int nPriority = 7);

private:	// �����������A�N�Z�X�\

	// �����o�ϐ�
	D3DXCOLOR m_col;	// �F
};

#endif