//==========================================================
//
// �G�̏��� [enemy.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _ENEMY_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _ENEMY_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "main.h"
#include "object.h"

// �O���錾
class CCharacter;
class CShadow;
class CObjectBillboard;

//==========================================================
// �v���C���[�̃N���X��`(�h���N���X)
//==========================================================
class CEnemy : public CObject
{
private:	// �����������A�N�Z�X�\�Ȓ�`

	// ���\����
	typedef struct
	{
		D3DXVECTOR3 pos;		// �ʒu
		D3DXVECTOR3 rot;		// ����
		D3DXVECTOR3 move;		// �ړ���
		D3DXVECTOR3 posOld;		// �ݒ�ʒu
		D3DXMATRIX mtxWorld;	// ���[���h�}�g���b�N�X
	}INFO;

public:	// �N�ł��A�N�Z�X�\

	CEnemy(int nPriOrity = 1);
	~CEnemy();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	HRESULT Init(const char *pName);	// �I�[�o�[���[�h
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEnemy *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 move,
		const char *pBodyName, const int nPriority = 4);

	// �����o�֐�(�ݒ�)
	void SetMove(const D3DXVECTOR3 move) { m_Info.move = move; }
	void SetPosition(const D3DXVECTOR3 pos) { m_Info.pos = pos; }
	void SetRotation(const D3DXVECTOR3 rot) { m_Info.rot = rot; }

	// �����o�֐�(�擾)
	D3DXVECTOR3 GetMove(void) { return m_Info.move; }
	D3DXVECTOR3 GetPosition(void) { return m_Info.pos; }
	D3DXVECTOR3 GetRotation(void) { return m_Info.rot; }
	D3DXMATRIX *GetMtx(void) { return &m_Info.mtxWorld; }

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	void Controller(void);

	// �����o�ϐ�
	CCharacter *m_pBody;	// �㔼�g
	float m_fMoveCnt;		// �ړ��J�E���g
	float m_fStateCnt;		// ��ԊǗ��J�E���g
	INFO m_Info;			// �������g�̏��
	bool m_bMove;			// �ړ��������ǂ���
	float m_fRotMove;		// ���݂̊p�x
	float m_fRotDiff;		// �ړI�̊p�x
	float m_fRotDest;		// �p�x�v�Z
	CShadow *pShadow;		// �e
	CObjectBillboard *m_pBillState;	// ��ԕ\���p�r���{�[�h
};

#endif