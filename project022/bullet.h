//==========================================================
//
// �e�̏��� [bullet.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _BULLET_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _BULLET_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "main.h"
#include "billboard.h"

//==========================================================
// �e�̃N���X��`(�h���N���X)
//==========================================================
class CBullet : public CObjectBillboard
{
private:	// �����������A�N�Z�X�\�Ȓ�`

	// �\���̂̒�`
	typedef struct
	{
		CObject *pObj;
		float fSpeed;		// ����
	}LockOn;

public:	// �N�ł��A�N�Z�X�\

	// ��ޗ񋓌^�̒�`
	typedef enum
	{
		TYPE_NONE = 0,		// �ʏ�
		TYPE_GRAVITY,		// �d��
		TYPE_MAX
	}TYPE;

	CBullet();	// �R���X�g���N�^
	CBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move);	// �R���X�g���N�^(�I�[�o�[���[�h)
	~CBullet();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, TYPE type);
	void SetLife(float fLife) { m_fLife = fLife; }
	void SetHom(CObject *pObj, float fSpeed);
	static void Check(CObject *pObject, CBullet *pBullet = NULL);
	void DeathCheck(void);

	static int GetNumAll(void) { return m_nNumAll; }

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	void Controller(void);
	bool Collision(D3DXVECTOR3 pos, CObject::TYPE ObjType);

	// �����o�ϐ�
	static CBullet *m_pTop;	// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
	static CBullet *m_pCur;	// �Ō���̃I�u�W�F�N�g�ւ̃|�C���^
	static int m_nNumAll;	// �e�̑���
	CBullet *m_pPrev;		// �O�̃I�u�W�F�N�g�ւ̃|�C���^
	CBullet *m_pNext;		// ���̃I�u�W�F�N�g�ւ̃|�C���^
	D3DXVECTOR3 m_move;		// �ړ���
	LockOn *m_pTarget;		// �z�[�~���O�p
	float m_fLife;			// ����
	float m_fParTimer;		// �p�[�e�B�N���^�C�}�[
	int m_nType;			// ���
	int m_nChangeTimer;		// ��ޕύX�^�C�}�[
	int m_nIdxTexture;		// �e�N�X�`���ԍ�
	bool m_bDeath;
};

#endif
