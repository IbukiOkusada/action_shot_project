//==========================================================
//
// �J�����̏����S�� [camera.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _CAMERA_H_		 // ���̃}�N������`����Ă��Ȃ��ꍇ
#define _CAMERA_H_		 // ��d�C���N���[�h�h�~�p�}�N�����`

#include "main.h"		//main.h�Œ�`���Ă�����̂��K�v�Ȃ���include

//**********************************************************
// �J�����N���X�̒�`
//**********************************************************
class CCamera
{
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

	// �����o�֐�
	D3DXVECTOR3 GetRotation(void) { return m_rot; }

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	void MoveV(void);
	void MoveVR(void);
	void MoveR(void);
	void SetV(void);
	void SetR(void);
	void Edit(void);
	void MouseCamera(void);

	// �����o�ϐ�
	D3DXMATRIX m_mtxView;		// �r���[�}�g���b�N�X
	D3DXMATRIX m_mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X
	D3DXVECTOR3 m_posV;		// ���_
	D3DXVECTOR3 m_posR;		// �����_
	D3DXVECTOR3 m_vecU;		// ������x�N�g��
	D3DXVECTOR3 m_rot;		// ����
	float m_fLength;		// ���_�ƒ����_�̋���
};

#endif