//==========================================================
//
// ���b�V���t�B�[���h�̏��� [meshfield.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _MESHFIELD_H_	// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _MESHFIELD_H_	// ��d�C���N���[�h�h�~�p�}�N�����`

#include "main.h"
#include "mesh.h"

//**********************************************************
// ���b�V���t�B�[���h�N���X�̒�`(�h���N���X)
//**********************************************************
class CMeshField : public CObjectMesh
{
public:		// �N�ł��A�N�Z�X�\

	CMeshField();	// �R���X�g���N�^
	~CMeshField();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetVtxInfo(void);
	static CMeshField *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, float fWidth, float fHeight,
		const char *pFileName, const int nWidth = 1, const int nHeight = 1, const int nPriority = 3);
	void Edit(float *pLength, float *pSpeed);
	void UpDownLoad(const char *pFileName);
	static bool GetAreaHot(D3DXVECTOR3 pos);
	static CMeshField *GetArea(D3DXVECTOR3 pos);

	// �����o�֐�(�擾)
	float GetWidth(void) { return m_fWidth; }
	float GetHeight(void) { return m_fHeight; }
	static CMeshField *GetTop(void) { return m_pTop; }
	CMeshField *GetNext(void) { return m_pNext; }
	bool GetHot(void) { return m_bHot; }

	// �����o�֐�(�ݒ�)
	void SetSize(float fWidth, float fHeight);
	float GetHeight(D3DXVECTOR3 pos, D3DXVECTOR3 &normal);
	static float GetHeight(D3DXVECTOR3 pos);
	void SetHot(bool bHot) { m_bHot = bHot; }

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	static CMeshField *m_pTop;	// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
	static CMeshField *m_pCur;	// �Ō���̃I�u�W�F�N�g�ւ̃|�C���^
	CMeshField *m_pPrev;	// �O�̃I�u�W�F�N�g�ւ̃|�C���^
	CMeshField *m_pNext;	// ���̃I�u�W�F�N�g�ւ̃|�C���^
	float m_fWidth;			// ��
	float m_fHeight;		// ����
	bool m_bHot;			// ������Ԃ��ۂ�
};

#endif
