//==========================================================
//
// �v���C���[�̏��� [player.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _PLAYER_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _PLAYER_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "main.h"
#include "object.h"

// �O���錾
class CShadow;
class CCharacter;
class CWaist;
class CObject2D;
class CObjectBillboard;
class CModel;
class CLockOn;
class CMeshOrbit;

//==========================================================
// �v���C���[�̃N���X��`(�h���N���X)
//==========================================================
class CPlayer : public CObject
{
private:	// �����������A�N�Z�X�\�Ȓ�`

	// �㔼�g���[�V������
	typedef enum
	{
		BMOTION_NEUTRAL = 0,	// �ҋ@���[�V����
		BMOTION_WALK,			// ���s���[�V����
		BMOTION_JUMP,			// �W�����v���[�V����
		BMOTION_LAND,			// ���n���[�V����
		BMOTION_TWINATK,		// �񒚎ˌ����[�V����
		BMOTION_SHWATK,			// �V�����[�ˌ����[�V����
		BMOTION_SLOWATK,		// �X���[���񒚎ˌ����[�V����
		BMOTION_SLOWSHW,		// �X���[���V�����[�ˌ����[�V����
		BMOTION_MAX
	}BMOTION;

	// �����g���[�V������
	typedef enum
	{
		LMOTION_NEUTRAL = 0,	// �ҋ@���[�V����
		LMOTION_WALK,			// ���s���[�V����
		LMOTION_JUMP,			// �W�����v���[�V����
		LMOTION_LAND,			// ���n���[�V����
		LMOTION_MAX
	}LMOTION;

	// ������
	typedef enum
	{
		WEAPON_GUNL = 0,		// �񒚍�
		WEAPON_GUNR,			// �񒚉E
		WEAPON_SHOWER,			// �V�����[
		WEAPON_MAX
	}WEAPON;

	// �U�����@
	typedef enum
	{
		ATK_GUN = 0,	// ��
		ATK_SHOWER,		// �V�����[
		ATK_MAX
	}ATK;

	// ���\����
	typedef struct
	{
		D3DXVECTOR3 pos;		// �ʒu
		D3DXVECTOR3 rot;		// ����
		D3DXVECTOR3 move;		// �ړ���
		D3DXVECTOR3 posOld;		// �ݒ�ʒu
		D3DXMATRIX mtxWorld;	// ���[���h�}�g���b�N�X
	}INFO;

public:	// �N�ł��A�N�Z�X�\

	//CPlayer();	// �R���X�g���N�^
	CPlayer(const D3DXVECTOR3 pos);	// �R���X�g���N�^(�I�[�o�[���[�h)
	CPlayer(int nPriOrity = 1);
	~CPlayer();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	HRESULT Init(const char *pBodyName, const char *pLegName);	// �I�[�o�[���[�h
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CPlayer *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 move, 
	const char *pBodyName, const char *pLegName, const int nPriority = 4);

	// �����o�֐�(�ݒ�)
	void SetMove(const D3DXVECTOR3 move) { m_Info.move = move; }
	void SetPosition(const D3DXVECTOR3 pos) { m_Info.pos = pos; }
	void SetRotation(const D3DXVECTOR3 rot) { m_Info.rot = rot; }
	void AddSlowTime(int nAddTime = 10);

	// �����o�֐�(�擾)
	D3DXVECTOR3 GetMove(void) { return m_Info.move; }
	D3DXVECTOR3 GetPosition(void) { return m_Info.pos; }
	D3DXVECTOR3 GetRotation(void) { return m_Info.rot; }

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	void Controller(void);
	void Attack(void);
	void SetBodyRot(void);
	void Move(void);
	void Jump(void);
	void Slow(void);
	void SlowShw(void);
	void SlowGun(void);
	void SetGageColor(float fRate);
	void Particle(void);

	// �����o�ϐ�
	CWaist *m_pWaist;		// ��
	CCharacter *m_pBody;	// �㔼�g
	CCharacter *m_pLeg;		// �����g
	CModel *m_pWeaponL;		// ���퍶
	CModel *m_pWeaponR;		// ����E
	CObject2D *m_pSlowGage;	// �X���[�Q�[�W
	CMeshOrbit *m_pOrbit;	// �O��
	INFO m_Info;			// �������g�̏��
	bool m_bJump;			// �W�����v�������ǂ���
	bool m_bAttack;			// �U�����Ă��邩�ǂ���
	float m_fAttackTimer;	// �U���^�C�}�[
	int m_nAttackHand;		// �U�������
	ATK m_WepType;			// ������������
	ATK m_WepTypeOld;		// �ύX�O�̕�����
	bool m_bMove;			// �ړ��������ǂ���
	int m_nSlowTime;		// �X���[�\����
	bool m_bActiveSlow;		// �X���[���͂ł��邩�ۂ�
	bool m_bSlow;			// �X���[��Ԃ��ۂ�
	bool m_bLock;			// ���b�N�I�����Ă��邩�ۂ�
	float m_fRotMove;		// ���݂̊p�x
	float m_fRotDiff;		// �ړI�̊p�x
	float m_fRotDest;		// �p�x�v�Z
	CShadow *pShadow;		// �e
	CLockOn *m_pLockon;		// ���b�N�I��
	static const D3DXVECTOR3 SetWepPos[WEAPON_MAX];	// ����ݒ�ʒu
	static const int m_aWepTimer[ATK_MAX];			// �U���^�C�}�[
	int m_aWepNum[WEAPON_MAX];						// ����t�@�C���ǂݍ��ݔԍ�
	static const char *m_apFileName[WEAPON_MAX];	// ����t�@�C����
};

#endif
