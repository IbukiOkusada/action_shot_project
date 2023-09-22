//==========================================================
//
// �G�̏o���Ǘ����� [enemy_manager.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _ENEMY_MANAGER_H_
#define _ENEMY_MANAGER_H_

#define NUM_AREA	(4)		// �G�̐����ꏊ��

//==========================================================
// �G�̏o���Ǘ��N���X�̒�`(���N���X)
//==========================================================
class CEnemyManager
{
private:

	enum ENEMY
	{
		ENEMY_SOCIETY = 0,
		ENEMY_SOCIETYYW,
		ENEMY_KIDSBOY,
		ENEMY_KIDSGIRL,
		ENEMY_MAX
	};
public:		// �N�ł��A�N�Z�X�\

	CEnemyManager();	// �R���X�g���N�^
	~CEnemyManager();	// �f�X�g���N�^

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void UpdateTutorial(void);
	void Spawn(int nSetNum);
	void AddDead(void) { m_nDeadCounter++; }
	void AddSuv(void) { m_nSuvCounter++; }
	int GetSuv(void) { return m_nSuvCounter; }
	int GetDead(void) { return m_nDeadCounter; }

private:	// �����������A�N�Z�X�\

	int m_nMaxEnemy;	// ���݂̃G�l�~�[�ő吔
	int m_nTimer;		// ����
	int m_nFrameTimer;	// �^�C�}�[�t���[��
	int m_nDeadCounter;	// ���S�l��
	int m_nSuvCounter;	// �����l��
	static const char *m_apEnemyFileName[ENEMY_MAX];
};

#endif
