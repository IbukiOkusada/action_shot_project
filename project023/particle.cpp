//===============================================
//
// �p�[�e�B�N���̏��� [particle.cpp]
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
#include "texture.h"

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
	CEffect::TYPE ParType = type;
	float fRadius = 0.0f;
	float fLife = 0;
	D3DXVECTOR3 nor;
	float fCol = (float)(rand() % 3) / 10.0f + 0.3f;

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

			// ���W�̐ݒ�
		pos = Defpos;

		//�ړ��ʂ̐ݒ�
		move.x = sinf((float)(rand() % 629 - 314) / 100.0f) * ((float)(rand() % 100)) * 0.1f;
		move.y = cosf((float)(rand() % 629 - 314) / 100.0f) * ((float)(rand() % 100)) * 0.1f;
		move.z = cosf((float)(rand() % 629 - 314) / 100.0f) * ((float)(rand() % 100)) * 0.1f;

		//�F�̐ݒ�
		col = D3DXCOLOR(fCol, fCol + 0.1f, 1.0f, 1.0f);

		//���a�̐ݒ�
		fRadius = 3.0f;

		//�����̐ݒ�
		fLife = 10.0f;

		CEffect::Create(Defpos, move, col, fRadius, fLife, type);

		break;

	case CEffect::TYPE_EXPLOSION:	// ����

		for (int nCnt = 0; nCnt < 10; nCnt++)
		{
			// ���W�̐ݒ�
			pos = Defpos;

			//�ړ��ʂ̐ݒ�
			move.x = sinf((float)(rand() % 629 - 314)  * 0.01f) * ((float)(rand() % 100)) * 0.01f;
			move.y = ((float)(rand() % 100)) * 0.001f;
			move.z = cosf((float)(rand() % 629 - 314)  * 0.01f) * ((float)(rand() % 100)) * 0.01f;

			//�F�̐ݒ�
			col = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);

			//���a�̐ݒ�
			fRadius = 20.0f;

			//�����̐ݒ�
			fLife = 80.0f;

			CEffect::Create(Defpos, move + Defmove * 0.5f, col, fRadius, fLife, type);
		}

		break;

	case CEffect::TYPE_DUST:	// ��

		for (int nCnt = 0; nCnt < 15; nCnt++)
		{
			// ���W�̐ݒ�
			pos = Defpos;

			//�ړ��ʂ̐ݒ�
			move.x = sinf((float)(rand() % 629 - 314)  * 0.01f) * ((float)(rand() % 100)) * 0.04f;
			move.y = ((float)(rand() % 100)) * 0.001f;
			move.z = cosf((float)(rand() % 629 - 314)  * 0.01f) * ((float)(rand() % 100)) * 0.04f;

			//�F�̐ݒ�
			col = D3DXCOLOR(0.08f, 0.07f, 0.07f, 1.0f);

			//���a�̐ݒ�
			fRadius = 30.0f;

			//�����̐ݒ�
			fLife = 100.0f;

			CEffect::Create(Defpos, move + Defmove * 0.5f, col, fRadius, fLife, type);
		}

		break;

	case CEffect::TYPE_SHWBULLET:	// �e

		for (int nCnt = 0; nCnt < 3; nCnt++)
		{
			// ���W�̐ݒ�
			pos = Defpos;

			float fCol = (float)(rand() % 5) / 10.0f + 0.1f;

			//�ړ��ʂ̐ݒ�
			move.x = -cosf(Defmove.y + -D3DX_PI * 0.1f + D3DX_PI * 0.2f * ((rand() % 10) * 0.1f)) * 5.0f;
			move.y = rand() % 300 * 0.01f;
			move.z = -sinf(Defmove.y + -D3DX_PI * 0.1f + D3DX_PI * 0.2f * ((rand() % 10) * 0.1f)) * 5.0f;

			//�F�̐ݒ�
			col = D3DXCOLOR(fCol, fCol + 0.25f, 1.0f, 1.0f);

			//���a�̐ݒ�
			fRadius = 5.0f;

			//�����̐ݒ�
			fLife = 100.0f;

			if (nCnt <= 5)
			{// ��ڂ̂�
				ParType = CEffect::TYPE_SHWREF;
			}
			else
			{
				ParType = CEffect::TYPE_SHWBULLET;
			}

			CEffect::Create(Defpos, move, col, fRadius, fLife, ParType);
		}

		break;

	case CEffect::TYPE_SWEAT:	// ��

		fCol = (float)(rand() % 3) / 10.0f + 0.3f;

		for (int nCnt = 0; nCnt < 1; nCnt++)
		{
			// ���W�̐ݒ�
			pos = Defpos;

			pos.x += (float)(rand() % 21 - 10);
			pos.z += (float)(rand() % 21 - 10);

			//�ړ��ʂ̐ݒ�
			move.x = sinf((float)(rand() % 629 - 314) / 100.0f) * ((float)(rand() % 100)) * 0.001f;
			move.y = rand() % 100 * -0.007f;
			move.z = cosf((float)(rand() % 629 - 314) / 100.0f) * ((float)(rand() % 100)) * 0.001f;

			//�F�̐ݒ�
			col = D3DXCOLOR(fCol + 0.5f, fCol + 0.5f, fCol + 0.5f, 1.0f);

			//���a�̐ݒ�
			fRadius = 2.0f;

			//�����̐ݒ�
			fLife = 20.0f;

			CEffect::Create(pos, move, col, fRadius, fLife, type);
		}

		break;

	case CEffect::TYPE_HEAT:	// ���C

		fCol = (float)(rand() % 3) / 10.0f + 0.3f;

		for (int nCnt = 0; nCnt < 1; nCnt++)
		{
			// ���W�̐ݒ�
			pos = Defpos;

			pos.x += (float)(rand() % 21 - 10);
			pos.z += (float)(rand() % 21 - 10);

			//�ړ��ʂ̐ݒ�
			move.x = sinf((float)(rand() % 629 - 314) / 100.0f) * ((float)(rand() % 100)) * 0.002f;
			move.y = rand() % 100 * 0.005f;
			move.z = cosf((float)(rand() % 629 - 314) / 100.0f) * ((float)(rand() % 100)) * 0.002f;
			//�F�̐ݒ�
			col = D3DXCOLOR(fCol + 0.5f, fCol + 0.5f, fCol + 0.5f, 1.0f);

			//���a�̐ݒ�
			fRadius = 10.0f;

			//�����̐ݒ�
			fLife = 100.0f;

			CEffect::Create(pos, move, col, fRadius, fLife, type);
		}

		break;

	case CEffect::TYPE_JUMP:	// �W�����v

		for (int nCnt = 0; nCnt < 10; nCnt++)
		{
			// ���W�̐ݒ�
			pos = Defpos;

			//�ړ��ʂ̐ݒ�
			move.x = sinf((float)(rand() % 629 - 314)  * 0.01f) * ((float)(rand() % 100)) * 0.04f;
			move.y = -0.01f;
			move.z = cosf((float)(rand() % 629 - 314)  * 0.01f) * ((float)(rand() % 100)) * 0.04f;

			// �ړ��x�N�g�������߂�
			D3DXVec3Normalize(&nor, &move);	// �x�N�g���𐳋K������

			pos += nor * 100.0f;
			pos.y = Defpos.y;

			//�F�̐ݒ�
			col = D3DXCOLOR(0.08f, 0.07f, 0.07f, 1.0f);

			//���a�̐ݒ�
			fRadius = 20.0f;

			//�����̐ݒ�
			fLife = 100.0f;

			CEffect::Create(pos, move + Defmove * 0.5f, col, fRadius, fLife, type);
		}

		break;

	case CEffect::TYPE_SWAP:	// �W�����v�̐�

		for (int nCnt = 0; nCnt < 20; nCnt++)
		{
			// ���W�̐ݒ�
			pos = Defpos;

			//�ړ��ʂ̐ݒ�
			move.x = sinf((float)(rand() % 629 - 314)  * 0.01f) * ((float)(rand() % 100)) * 0.04f;
			move.z = cosf((float)(rand() % 629 - 314)  * 0.01f) * ((float)(rand() % 100)) * 0.04f;

			// �ړ��x�N�g�������߂�
			D3DXVec3Normalize(&nor, &move);	// �x�N�g���𐳋K������

			pos += nor * 100.0f;
			pos.y = Defpos.y;

			move = Defmove;

			//�F�̐ݒ�
			col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);

			//���a�̐ݒ�
			fRadius = 5.0f;

			//�����̐ݒ�
			fLife = 100.0f;

			CEffect *pEffect = CEffect::Create(pos, move, col, fRadius, fLife, type);

			pEffect->SetSize(fRadius, 50.0f);
		}

		break;

	case CEffect::TYPE_BALEXPLOSION:	// ���D����

		for (int nCnt = 0; nCnt < 20; nCnt++)
		{
			// ���W�̐ݒ�
			pos = Defpos;

			//�ړ��ʂ̐ݒ�
			move.x = sinf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.2f;
			move.y = ((float)(rand() % 100)) * 0.25f;
			move.z = cosf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.2f;

			//�F�̐ݒ�
			col = D3DXCOLOR(0.4f, 0.4f, rand() % 40 * 0.1f + 0.6f, 1.0f);

			//���a�̐ݒ�
			fRadius = 25.0f;

			//�����̐ݒ�
			fLife = 30.0f;

			CEffect::Create(Defpos, move, col, fRadius, fLife, type);
		}

		break;

	case CEffect::TYPE_SMAKE:	// ��

		for (int nCnt = 0; nCnt < 10; nCnt++)
		{
			// ���W�̐ݒ�
			pos = Defpos;

			//�ړ��ʂ̐ݒ�
			move.x = sinf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.04f;
			move.y = ((float)(rand() % 50)) * 0.1f;
			move.z = cosf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.04f;

			//�F�̐ݒ�
			col = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);

			//���a�̐ݒ�
			fRadius = 55.0f;

			//�����̐ݒ�
			fLife = 75.0f;

			CEffect::Create(Defpos + move, move, col, fRadius, fLife, type);
		}

		break;

	case CEffect::TYPE_SLOWOK:	// ��

								//�ړ��ʂ̐ݒ�
		move.x = sinf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.0025f;
		move.y = ((float)(rand() % 50)) * 0.025f;
		move.z = cosf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.0025f;

		//�F�̐ݒ�
		col = D3DXCOLOR(rand() % 20 * 0.01f + 0.1f, rand() % 20 * 0.01f + 0.4f, rand() % 50 * 0.01f + 0.4f, 0.15f);

		//���a�̐ݒ�
		fRadius = 50.0f;

		//�����̐ݒ�
		fLife = 15.0f;

		CEffect::Create(Defpos + move, move, col, fRadius, fLife, type);

		break;

	case CEffect::TYPE_HEATHAZE:	// ��

			// ���W�̐ݒ�
		pos = Defpos;

		//�ړ��ʂ̐ݒ�
		move.x = sinf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.04f;
		move.y = ((float)(rand() % 50)) * 0.075f;
		move.z = cosf((float)(rand() % 629 - 314) * 0.01f) * ((float)(rand() % 100)) * 0.04f;

		//�F�̐ݒ�
		col = D3DXCOLOR(0.45f, 0.2f, 0.2f, 0.11f);

		//���a�̐ݒ�
		fRadius = 300.0f;

		//�����̐ݒ�
		fLife = 300.0f;

		CEffect *pEffect = CEffect::Create(Defpos + move, move, col, fRadius, fLife, type);
		pEffect->BindTexture(CManager::GetTexture()->Regist(CTexture::GetFileName(CTexture::TYPE_HEATHAZE)));

		break;
	}
}