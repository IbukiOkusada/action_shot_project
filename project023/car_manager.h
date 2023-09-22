//===============================================
//
// �ԑS�ʂ̊Ǘ�����(car_manager.h)
// Author : Ibuki Okusada
//
//===============================================
#ifndef _CARMANAGER_H_	// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _CARMANAGER_H_	// ��d�C���N���[�h�h�~�p�}�N�����`

// �}�N����`
#define MAX_CAR	(6)

// �O���錾
class CCar;

//===============================================
// �}�l�[�W���[�N���X�̒�`
//===============================================
class CCarManager
{
private:	// ���������A�N�Z�X�\�Ȓ�`

	// �Ԑ���`
	enum LOAD
	{
		LOAD_RIGHT = 0,	// �E�Ԑ�
		LOAD_LEFT,		// ���Ԑ�
		LOAD_MAX
	};

	// �����Ǘ��p�\����
	struct SPAWN
	{
		int nNum;		// �o����
		float fCount;	// �J�E���^�[
		float fDef;		// �K��l
	};

public:	// �N�ł��A�N�Z�X�\

	CCarManager();	// �R���X�g���N�^
	~CCarManager();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	CCar *Collision(D3DXVECTOR3 &pos, D3DXVECTOR3 &posOld, D3DXVECTOR3 &move, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax, bool *pJump);

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	void Spawn(void);
	void Delete(void);
	bool BindList(CCar *pCar, LOAD load);
	void DetachList(CCar *pCar, LOAD load);

	// �ÓI�����o�ϐ���
	static const char *m_apFileName[MAX_CAR];	// �Ԃ̎��
	static const D3DXVECTOR2 m_aShadowSize[MAX_CAR];	// �Ԃ̎�ނ��Ƃ̉e�̃T�C�Y

	// �����o�ϐ�
	SPAWN m_aSpawn[LOAD_MAX];	// �������

	// ���X�g�\���Ǘ��ϐ�
	CCar *m_apTop[LOAD_MAX];	// �擪
	CCar *m_apCur[LOAD_MAX];	// �Ō��
};

#endif
