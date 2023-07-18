//==========================================================
//
// ���b�N�I���̏��� [lockon.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _LOCKON_H_
#define _LOCKON_H_

#include "billboard.h"

// �O���錾
class CModel;
class CObject;

//**********************************************************
// ���b�N�I���N���X�̒�`
//**********************************************************
class CLockOn : public CObjectBillboard
{
private:	// �����������A�N�Z�X�\

	// �˒��\����
	typedef struct
	{
		D3DXVECTOR3 pos;		// �ʒu
		D3DXVECTOR3 rot;		// ����
		D3DXMATRIX mtxWorld;	// ���[���h�}�g���b�N�X
	}DISTANCE;

public:	// �N�ł��A�N�Z�X�\

	CLockOn(int nPriOrity = 5);	// �R���X�g���N�^
	~CLockOn();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetParent(D3DXMATRIX *pMtx);
	void SetDistance(float fLength, float fAngle);
	bool GetLock(void) { return m_bLock; }
	void SetLock(bool bLock) { m_bUse = bLock; }
	static CLockOn *Create(D3DXMATRIX *pMtx);
	CObject *GetTag(void);

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	void LockOn(void);
	void SetDisMtx(DISTANCE *pDis);

	CObject *m_pObj;		// ���b�N�I�����郂�f��
	D3DXMATRIX *m_pMtx;		// �e�̃}�g���b�N�X
	DISTANCE m_DisL;		// ��������
	DISTANCE m_DisR;		// �E������
	float m_fLength;		// ����
	float m_fAngle;			// �p�x
	bool m_bLock;			// ���b�N�I�����Ă��邩�ǂ���
	bool m_bUse;			// �g�p���邩�ǂ���
};

#endif

