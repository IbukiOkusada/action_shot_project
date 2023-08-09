//==========================================================
//
// �J�����̏����S�� [camera.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _CAMERA_H_		 // ���̃}�N������`����Ă��Ȃ��ꍇ
#define _CAMERA_H_		 // ��d�C���N���[�h�h�~�p�}�N�����`

#include "main.h"		//main.h�Œ�`���Ă�����̂��K�v�Ȃ���include

// �}�N����`
#define MAX_CAMERA_ROTZ (D3DX_PI * 0.9f)	// �J�����ő�p�x
#define MIN_CAMERA_ROTZ (D3DX_PI * 0.22f)	// �J�����ő�p�x

//**********************************************************
// �J�����N���X�̒�`
//**********************************************************
class CCamera
{
public:	// �N�ł��A�N�Z�X�\�Ȓ�`

	enum MODE
	{
		MODE_NORMAL = 0,	// �ʏ�
		MODE_SLOWGUN,		// �X���[�p�x�������
		MODE_SLOWSHW,		// �V�����[
		MODE_MAX
	};

public:	// �N�ł��A�N�Z�X�\
	CCamera();	// �R���X�g���N�^
	~CCamera();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);
	void Pursue(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);
	void Setting(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);
	void SetRot(const D3DXVECTOR3 rot);
	void SerMode(MODE mode) { m_mode = mode; }
	void SetOldRot(D3DXVECTOR3 rot) { m_SlowOldRot = rot; }
	void MoveV(void);
	void MouseCamera(void);
	void MoveVR(void);

	// �����o�֐�
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	D3DXVECTOR3 GetPositionV(void) { return m_posV; }
	D3DXVECTOR3 GetPositionR(void) { return m_posR; }

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	void MoveR(void);
	void SetV(void);
	void SetR(void);
	void Edit(void);
	void Slow(void);
	void SlowShw(void);

	// �����o�ϐ�
	D3DXMATRIX m_mtxView;		// �r���[�}�g���b�N�X
	D3DXMATRIX m_mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X
	D3DXVECTOR3 m_posV;			// ���_
	D3DXVECTOR3 m_posR;			// �����_
	D3DXVECTOR3 m_vecU;			// ������x�N�g��
	D3DXVECTOR3 m_rot;			// ����
	D3DXVECTOR3 m_SlowOldRot;	// �X���[�O�̌���
	MODE m_mode;				// ���[�h
	float m_fMulScore;			// �X�R�A�{��
	float m_fLength;			// ���_�ƒ����_�̋���
};

#endif