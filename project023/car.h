//==========================================================
//
// �Ԃ̏��� [car.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _CAR_H_	// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _CAR_H_	// ��d�C���N���[�h�h�~�p�}�N�����`

#include "objectX.h"

// �O���錾
class CShadow;

//==========================================================
// �ԃN���X�̒�`(�h���N���X)
//==========================================================
class CCar : public CObjectX
{
public:	// �N�ł��A�N�Z�X�\

	CCar();		// �R���X�g���N�^
	~CCar();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CCar *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *pFileName, const int nPriority = 3);

	// �����o�֐�(�ݒ�)
	void SetMove(D3DXVECTOR3 move) { m_move = move; }
	void SetNext(CCar *pNext) { m_pNext = pNext; }
	void SetPrev(CCar *pPrev) { m_pPrev = pPrev; }
	void SetOldPos(D3DXVECTOR3 posOld) { m_posOld = posOld; }

	// �����o�֐�(�擾)
	D3DXVECTOR3 GetMove(void) { return m_move; }
	D3DXVECTOR3 GetOldPos(void) { return m_posOld; }
	CCar *GetNext(void) { return m_pNext; }
	CCar *GetPrev(void) { return m_pPrev; }
	CShadow *GetShadow(void) { return m_pShadow; }

private:	// �����������A�N�Z�X�\

	// �����o�ϐ�
	D3DXVECTOR3 m_move;	// �ړ���
	D3DXVECTOR3 m_posOld;	// �O��̍��W
	CShadow *m_pShadow;	// �e
	CCar *m_pPrev;	// �O
	CCar *m_pNext;	// ��
};

#endif