//==========================================================
//
// �X���[���̃��b�N�I������ [slow_lockon.h]
// Author : Ibuki Okusada
//
//==========================================================

#include "object3D.h"

// �O���錾
class CModel;
class CEnemy;
class CObject;

//**********************************************************
// ���b�N�I���N���X�̒�`
//**********************************************************
class CSlowLock : public CObject3D
{
public:	// �N�ł��A�N�Z�X�\

	CSlowLock(int nPriOrity = 5);	// �R���X�g���N�^
	~CSlowLock();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CSlowLock *Create(void);
	TYPE GetType(void) { return m_type; }

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	void LockOn(void);
	void Controller(void);

	float m_fLength;		// ����
	TYPE m_type;			// ���b�N�I�����
};
