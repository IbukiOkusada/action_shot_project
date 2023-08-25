//==========================================================
//
// ���b�V���̐����D���� [meshballoon.h]
// Author : Ibuki Okusada
//
//==========================================================

#ifndef _MESHBALLOON_H_	// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _MESHBALLOON_H_	// ��d�C���N���[�h�h�~�p�}�N�����`

#include "main.h"
#include "mesh.h"

//**********************************************************
// ���b�V���h�[���N���X�̒�`(�h���N���X)
//**********************************************************
class CMeshBalloon : public CObjectMesh
{
public:		// �N�ł��A�N�Z�X�\�Ȓ�`

	// ���
	enum TYPE
	{
		TYPE_PINK = 0,	// �s���N�F
		TYPE_BLUE,		// �F
		TYPE_MAX
	};

	// ���D�����ݒ���
	typedef struct
	{
		D3DXVECTOR3 pos;	// �ʒu
		D3DXVECTOR3 rot;	// ����
		float fLength;		// ���a
		float fHeight;		// ����
		int nPriority;		// �D�揇��
		int nWidth;			// ��
		int nHeight;		// ����
	}SET;

private:	// �����������A�N�Z�X�\�Ȓ�`

	enum STATE
	{
		STATE_NONE = 0,	// �����Ȃ����
		STATE_SHRINK,	// �c���O�̏k�ޏ��
		STATE_SWELL,	// �c��ޏ��
		STATE_MAX
	};

public:		// �N�ł��A�N�Z�X�\

	CMeshBalloon();	// �R���X�g���N�^
	~CMeshBalloon();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetVtxInfo(void);
	static CMeshBalloon *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, float fLength, float fHeight, const int nPriority = 3, const int nWidth = 1, const int nHeight = 1);
	void SetParent(D3DXMATRIX *pMtx) { m_pMtxParent = pMtx; }
	void AddLength(float fAddLength);
	void SetMove(D3DXVECTOR3 move) { m_move = move;}
	float GetLength(void) { return m_fLength; }

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	void SetSize(float fLength, float fHeight);
	void SetParentMtx(void);
	void UpdateState(void);

	// �����o�֐�
	float m_fHeight;	// ����
	float m_fLength;	// ����
	float m_fRot;		// �꒸�_�̊p�x
	float m_fHeightRot;	// y���p�x
	D3DXVECTOR3 m_move;	// �ړ���
	D3DXMATRIX *m_pMtxParent;	// �e�̃}�g���b�N�X
	STATE m_State;		// ���
	float m_fStateCnt;	// ��ԑJ�ڃJ�E���g
};

#endif