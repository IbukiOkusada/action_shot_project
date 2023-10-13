//==========================================================
//
// �t�B���^�[�̏��� [filter.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _FILTER_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _FILTER_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "object2D.h"

//==========================================================
// �t�B���^�[�̃N���X��`(�h���N���X)
//==========================================================
class CFilter : public CObject2D
{
public:

	// �g�p���
	enum TYPE
	{
		TYPE_SLOWGUN = 0,	// �񒚌��e�X���[
		TYPE_SLOWSHW,		// �V�����[�X���[
		TYPE_MAX
	};

private:	// �����������A�N�Z�X�\
	// ���
	enum STATE
	{
		STATE_NONE = 0,	// �����Ȃ�
		STATE_NORMAL,	// �ʏ�
		STATE_START,	// �J�n
		STATE_END,		// �I��
	};

public:	// �N�ł��A�N�Z�X�\

	//CFilter();	// �R���X�g���N�^
	CFilter(int nPriority = 7);	// �f�t�H���g�����R���X�g���N�^
	virtual ~CFilter();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CFilter *Create(TYPE type);
	D3DXCOLOR GetCol(void);

private:	// �����������A�N�Z�X�\

	// �����o�ϐ�
	D3DXCOLOR m_col;	// �F
	float m_fSpeed;		// �T�C�Y�ύX
	float m_fCola;		// �����x�ύX��
	STATE m_state;		// ���
};

//==========================================================
// �z���t�B���^�[�N���X
//==========================================================
class CHeatFilter : public CObject2D
{
public:	// �N�ł��A�N�Z�X�\

	//CFilter();	// �R���X�g���N�^
	CHeatFilter(int nPriority = 7);	// �f�t�H���g�����R���X�g���N�^
	~CHeatFilter();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CHeatFilter *Create();
	void SetFil(float fDiff);

private:	// �����������A�N�Z�X�\

	// �����o�ϐ�
	D3DXCOLOR m_col;	// �F
	D3DXVECTOR3 m_move;	// �ړ���
	float m_fTex;		// �e�N�X�`�����W
};

#endif