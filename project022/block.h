//==========================================================
//
// �u���b�N�̏��� [block.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _BLOCK_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _BLOCK_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "main.h"
#include "object2D.h"

#define BLOCK_PRIORITY	(2)

//==========================================================
// �u���b�N�̃N���X��`(�h���N���X)
//==========================================================
class CBlock : public CObject2D
{
public:	// �N�ł��A�N�Z�X�\

	//CBlock();	// �R���X�g���N�^
	CBlock(const D3DXVECTOR3 pos, const int nPriority = BLOCK_PRIORITY);	// �R���X�g���N�^(�I�[�o�[���[�h)
	CBlock(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 move, const int nPriority = BLOCK_PRIORITY);	// �R���X�g���N�^(�I�[�o�[���[�h)
	CBlock(const int nPriority = BLOCK_PRIORITY);
	~CBlock();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBlock *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 move, int nWidthTex = 1, int nHeightTex = 1);
	static HRESULT Load(void);
	static void Unload(void);

	// �����o�֐�(�ݒ�)
	void SetMove(const D3DXVECTOR3 move) { m_move = move; }

	// �����o�֐�(�擾)
	D3DXVECTOR3 GetMove(void) { return m_move; }

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	void Controller(void);

	// �����o�ϐ�
	static const char *apTextureFileName[];	// �t�@�C����
	D3DXVECTOR3 m_move;		// �ړ���
	int m_nIdxTexture;	// �e�N�X�`���ԍ�
	int m_nMoveCnt;
	int m_nWidthTex;	// ��������
	int m_nHeightTex;	// �c������
};

#endif
