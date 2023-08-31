//==========================================================
//
// �G�̏o���Ǘ����� [enemy_manager.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _ENEMY_MANAGER_H_
#define _ENEMY_MANAGER_H_

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

private:	// �����������A�N�Z�X�\

	void Spawn(void);
	int m_nMaxEnemy;	// ���݂̃G�l�~�[�ő吔
};

#endif
