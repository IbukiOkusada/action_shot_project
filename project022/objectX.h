//==========================================================
//
// X�t�@�C�����f���̏����S�� [objectX.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _OBJECTX_H_
#define _OBJECTX_H_

#include "main.h"
#include "object.h"

// �}�N����`
#define NUM_TEXTURE	(64)	// �e�N�X�`���ő吔

//**********************************************************
// X�t�@�C�����f���N���X�̒�`
//**********************************************************
class CObjectX : public CObject
{
public:	// �N�ł��A�N�Z�X�\

	CObjectX(int nPriority = 0);	// �R���X�g���N�^
	~CObjectX();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void BindFile(int nIdx);

	static CObjectX *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *pFileName, const int nPriority = 4);

	// �����o�֐�(�ݒ�)
	void SetPosition(const D3DXVECTOR3 pos);
	void SetRotation(const D3DXVECTOR3 rot);

	// �����o�֐�(�擾)
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	CObject2D *GetObject2D(void) { return NULL; }
	int GetIdx(void) { return m_nIdxModel; }
	int GetModelType(void) { return m_nIdxModel; }

private:	// �����������A�N�Z�X�\
	
	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_rot;		//����
	D3DXMATRIX m_mtxWorld;	//���[���h�}�g���b�N�X
	int m_nIdxModel;		// ���f���ԍ�
};

#endif
