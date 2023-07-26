//==========================================================
//
// ���d�X�N���[���̔w�i�̏��� [bg.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _BG_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _BG_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "main.h"
#include "object.h"

// �O���錾
class CObject2D;

//==========================================================
// �e�N�X�`���X���C�h�I�u�W�F�N�g(2D)�̃N���X��`(�h���N���X)
//==========================================================
class CMultiBg : public CObject
{
private:	// �����������Ȃ���`

	// �\���̂̒�` (���搶�̃T�|�[�g�L��)
	struct STex
	{
		float fTexU;		// �e�N�X�`��U���W
		float fTexV;		// �e�N�X�`��V���W
		float fMoveU;		// U���W�ړ���
		float fMoveV;		// V���W�ړ���
	};

	// �\���̂̒�`(�������͍̂\���̂ł܂Ƃ߂悤!!!!!!) (���搶�̃T�|�[�g�L��)
	struct SBg	// :  STex �\���̂��p�����ł��邯��const�ł��炩���ߌ��߂��T�C�Y�ł͓�����Ȃ�
	{
		CObject2D *pObject2D;	// �I�u�W�F�N�g
		STex sTex;			// �e�N�X�`�����
	};

public:	// �N�ł��A�N�Z�X�\�Ȓ�`

	// ��ޗ񋓌^�̒�`
	enum TYPE
	{
		TYPE_BACK = 0,	// ��ԉ�
		TYPE_NORMAL,	// �^��
		TYPE_FRONT,		// ��O
		TYPE_MAX
	};

public:	// ��������֐�(�N�ł��A�N�Z�X�\)

	CMultiBg();	// �R���X�g���N�^
	~CMultiBg();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CMultiBg *Create();
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetRotation(void) { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	void SetPosition(const D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRotation(const D3DXVECTOR3 rot){}
	void SetPlayerMove(const D3DXVECTOR3 move);
	CObject2D *GetObject2D(void) { return NULL; }

private:	// �����������A�N�Z�X�\

	// �����o�ϐ�
	float m_aTexU[TYPE_MAX];
	int m_aIdxTexture[TYPE_MAX];	// �e�N�X�`���ԍ�
	static const char *m_apTextureFileName[];	// �t�@�C����
	static const STex apMoveTex[TYPE_MAX];	// ���_���̈ړ���
	D3DXVECTOR3 m_pos;		// ���W
	SBg m_aBg[TYPE_MAX];	// �w�i�̔z��
};

#endif
