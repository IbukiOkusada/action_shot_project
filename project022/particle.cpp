//===============================================
//
// �e�̏��� [particle.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "particle.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "debugproc.h"
#include "explosion.h"
#include "enemy.h"

//===============================================
// �}�N����`
//===============================================
#define LIFE	(30)		// ����

//===============================================
// �R���X�g���N�^
//===============================================
CParticle::CParticle()
{

}

//===============================================
// �f�X�g���N�^
//===============================================
CParticle::~CParticle()
{

}

//===============================================
// ����
//===============================================
void CParticle::Create(D3DXVECTOR3 pos, CEffect::TYPE type)
{
	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	Set(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), type);
}

//===============================================
// ���_���ݒ�
//===============================================
void CParticle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, CEffect::TYPE type)
{
	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	Set(pos, move, type);
}

//===============================================
// �ݒ�
//===============================================
void CParticle::Set(D3DXVECTOR3 Defpos, D3DXVECTOR3 Defmove, CEffect::TYPE type)
{
	D3DXVECTOR3 pos = {};
	D3DXVECTOR3 move = {};	// �ړ���
	D3DXCOLOR col = {};	// �F
	float fRadius = 0.0f;
	float fLife = 0;
	D3DXVECTOR3 nor;

	// �ړ��x�N�g�������߂�
	D3DXVec3Normalize(&nor, &Defmove);	// �x�N�g���𐳋K������

	int nMoveX = (int)(D3DX_PI * nor.x) * 100;
	int nMoveY = (int)(D3DX_PI * nor.y) * 100;
	int nMoveZ = (int)(D3DX_PI * nor.z) * 100;

	switch (type)
	{
	case CEffect::TYPE_NONE:	// �����Ȃ�
		
	break;

	case CEffect::TYPE_BULLET:	// �e

		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			// ���W�̐ݒ�
			pos = Defpos;

			float fCol = (float)(rand() % 3) / 10.0f + 0.3f;

			//�ړ��ʂ̐ݒ�
			move.x = sinf((float)(rand() % (nMoveX + 1) - (nMoveX / 2)) / 100.0f) * ((float)(rand() % 51 - 25)) * 0.1f;
			move.y = cosf((float)(rand() % (nMoveY + 1) - (nMoveY / 2)) / 100.0f) * ((float)(rand() % 51 - 25)) * 0.1f;
			move.z = sinf((float)(rand() % (nMoveZ + 1) - (nMoveZ / 2)) / 100.0f) * ((float)(rand() % 51 - 25)) * 0.1f;

			//�F�̐ݒ�
			col = D3DXCOLOR(fCol, fCol + 0.1f, 1.0f, 1.0f);

			//���a�̐ݒ�
			fRadius = 5.0f;

			//�����̐ݒ�
			fLife = 10.0f;

			CEffect::Create(Defpos, move, col, fRadius, fLife, type);
		}

		break;

	case CEffect::TYPE_EXPLOSION:	// ����

		for (int nCnt = 0; nCnt < 8; nCnt++)
		{
			// ���W�̐ݒ�
			pos = Defpos;

			//�ړ��ʂ̐ݒ�
			move.x = sinf((float)(rand() % 629 - 314) / 100.0f) * ((float)(rand() % 100)) / 50.0f;
			move.y = ((float)(rand() % 100)) / 10.0f + 3.0f;
			move.z = cosf((float)(rand() % 629 - 314) / 100.0f) * ((float)(rand() % 100)) / 50.0f;

			//�F�̐ݒ�
			col = D3DXCOLOR(0.4f, (float)(rand() % 6) / 10.0f + 0.4f, 1.0f, 1.0f);

			//���a�̐ݒ�
			fRadius = 10.0f;

			//�����̐ݒ�
			fLife = 75.0f;

			CEffect::Create(Defpos, move, col, fRadius, fLife, type);
		}

		break;

	case CEffect::TYPE_DUST:	// ����

		for (int nCnt = 0; nCnt < 1; nCnt++)
		{
			// ���W�̐ݒ�
			pos = Defpos;

			//�ړ��ʂ̐ݒ�
			move.x = sinf((float)(rand() % 629 - 314) / 100.0f) * ((float)(rand() % 10 - 1)) / 10.0f;
			move.y = cosf((float)(rand() % 629 - 314) / 100.0f) * ((float)(rand() % 10 - 1)) / 10.0f;

			//�F�̐ݒ�
			col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

			//���a�̐ݒ�
			fRadius = (float)(rand() % 20);

			//�����̐ݒ�
			fLife = 20.0f;

			CEffect::Create(Defpos, move, col, fRadius, fLife, type);
		}

		break;

	case CEffect::TYPE_SHWBULLET:	// �e

		for (int nCnt = 0; nCnt < 15; nCnt++)
		{
			// ���W�̐ݒ�
			pos = Defpos;

			float fCol = (float)(rand() % 5) / 10.0f + 0.1f;

			//�ړ��ʂ̐ݒ�
			move.x = -cosf(Defmove.y + -D3DX_PI * 0.15f + D3DX_PI * 0.3f * ((rand() % 10) * 0.1f)) * 5.0f;
			move.y = rand() % 300 * 0.01f;
			move.z = -sinf(Defmove.y + -D3DX_PI * 0.15f + D3DX_PI * 0.3f * ((rand() % 10) * 0.1f)) * 5.0f;

			//�F�̐ݒ�
			col = D3DXCOLOR(fCol, fCol + 0.1f, 1.0f, 1.0f);

			//���a�̐ݒ�
			fRadius = 15.0f;

			//�����̐ݒ�
			fLife = 100.0f;

			CEffect::Create(Defpos, move, col, fRadius, fLife, type);
		}

		break;
	}
}