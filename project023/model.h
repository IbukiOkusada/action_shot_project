//==========================================================
//
// �K�w�\���̃��f������ [model.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _MODEL_H_	// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _MODEL_H_	// ��d�C���N���[�h�h�~�p�}�N�����`

#include "main.h"

//**********************************************************
// �K�w�\�����f���N���X
//**********************************************************
class CModel
{
public:	// �N�ł��A�N�Z�X�\

	CModel();	// �R���X�g���N�^
	~CModel();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(const char *pFileName);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CModel *Create(const char *pFileName);
	void SetParent(D3DXMATRIX *pMtx);
	void BindModelFile(int nIdx);

	// �����o�֐�(�擾)
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	D3DXVECTOR3 GetCurrentPosition(void) { return m_CurPos; }
	D3DXVECTOR3 GetCurrentRotation(void) { return m_CurRot; }
	D3DXMATRIX *GetMtxWorld(void) { return &m_mtxWorld; }

	// �����o�֐�(�ݒ�)
	void SetPosition(const D3DXVECTOR3 pos);
	void SetRotation(const D3DXVECTOR3 rot);
	void SetCurrentPosition(const D3DXVECTOR3 pos);
	void SetCurrentRotation(const D3DXVECTOR3 rot);
	void SetChangeCol(const bool bChange, D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

private:	// �����������A�N�Z�X�\

	// �����o�ϐ�
	int m_nIdxModel;		// ���f���ԍ�
	bool m_bChangeCol;		// �F�ύX�����邩�ǂ���
	D3DMATERIAL9 m_ChangeMat;
	D3DXVECTOR3 m_pos;		// �ʒu
	D3DXVECTOR3 m_rot;		// ����
	D3DXVECTOR3 m_CurPos;	// ���݂̈ʒu
	D3DXVECTOR3 m_CurRot;	// ���݂̌���
	D3DXMATRIX m_mtxWorld;	// ���[���h�}�g���b�N�X
	D3DXMATRIX *m_pParentMtx;	// �e�̃��[���h�}�g���b�N�X
};

#endif
