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
class CEnemy;
class CObject;

//**********************************************************
// ���b�N�I���N���X�̒�`
//**********************************************************
class CLockOn : public CObjectBillboard
{
public:		// �N�ł��A�N�Z�X�\�Ȓ�`

	// ���b�N�I�����
	typedef enum 
	{
		TYPE_NONE = 0,	// �����Ȃ�
		TYPE_TARGET,	// �P�̃��b�N�I��
		TYPE_MULTI,		// multi���b�N�I��
		TYPE_MAX
	}TYPE;

public:	// �N�ł��A�N�Z�X�\

	CLockOn(int nPriOrity = 5);	// �R���X�g���N�^
	~CLockOn();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetParent(D3DXMATRIX *pMtx);
	bool GetLock(void) { return m_bLock; }
	void SetLock(bool bLock) { m_bUse = bLock; }
	static CLockOn *Create(D3DXMATRIX *pMtx, TYPE type = TYPE_TARGET);
	CObject *GetTag(void);
	void SetTag(CEnemy *pEnemy) { m_pObj = pEnemy; }
	static void Check(CEnemy *pObject);
	void DeathCheck(void);
	static void MultiDeath(void);
	static CLockOn *GetTop(void) { return m_pTop; }
	CLockOn *GetNext(void) { return m_pNext; }
	CEnemy *GetEnemy(void) { return m_pObj; }
	TYPE GetType(void) { return m_type; }
	bool GetDeath(void) { return m_bDeath; }

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	void LockOn(void);

	static CLockOn *m_pTop;	// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
	static CLockOn *m_pCur;	// �Ō���̃I�u�W�F�N�g�ւ̃|�C���^
	CLockOn *m_pPrev;		// �O�̃I�u�W�F�N�g�ւ̃|�C���^
	CLockOn *m_pNext;		// ���̃I�u�W�F�N�g�ւ̃|�C���^
	CEnemy *m_pObj;		// ���b�N�I�����郂�f��
	D3DXMATRIX *m_pMtx;		// �e�̃}�g���b�N�X
	bool m_bLock;			// ���b�N�I�����Ă��邩�ǂ���
	bool m_bUse;			// �g�p���邩�ǂ���
	bool m_bDeath;			// ���S�t���O
	TYPE m_type;			// ���b�N�I�����
};

#endif

