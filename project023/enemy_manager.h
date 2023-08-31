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
public:		// �N�ł��A�N�Z�X�\

	CEnemyManager();	// �R���X�g���N�^
	~CEnemyManager();	// �f�X�g���N�^

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Spawn(int nSetNum);

private:	// �����������A�N�Z�X�\

	int m_nMaxEnemy;	// ���݂̃G�l�~�[�ő吔
};

#endif
