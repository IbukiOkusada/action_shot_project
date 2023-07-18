//===================================================
//
//�p�[�e�B�N������
//Author ����ɐ�
//
//===================================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "main.h"
#include "effect.h"

#define MAX_PARTICLE	(256)	// �p�[�e�B�N���̍ő吔

// �N���X�̒�`
class CParticle
{
public:	// �N�ł��A�N�Z�X�\

	CParticle();	// �R���X�g���N�^
	~CParticle();	// �f�X�g���N�^

	// �����o�֐�
	static void Create(D3DXVECTOR3 pos, CEffect::TYPE type);
	static void Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, CEffect::TYPE type);

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	static void Set(D3DXVECTOR3 Defpos, D3DXVECTOR3 Defmove, CEffect::TYPE type);
};

#endif
