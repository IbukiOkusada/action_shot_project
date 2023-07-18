//==========================================================
//
//���b�V���\���̋O�Տ��� [meshorbit.h]
//Author Ibuki Okusada
//
//==========================================================
#ifndef _MESHORBIT_H_
#define _MESHORBIT_H_

#include "main.h"	//main.h�Œ�`���Ă�����̂��K�v�Ȃ���include

//==========================================================
//�}�N����`
//==========================================================
#define MAX_MESH	(2 * 10 + 2)	//�O�Ղ̒��_��

//==========================================================
//�\���̂̒�`
//==========================================================
//�O��
typedef struct
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;	//���_�o�b�t�@�̃|�C���^
	D3DXMATRIX *pMtxParent;				//�e�̃}�g���b�N�X�̃|�C���^
	D3DXVECTOR3 aOffSet[2];				//���[�̃I�t�Z�b�g
	D3DXCOLOR aCol[2];					//���[�̊�F
	D3DXMATRIX aMtxWorldPoint[2];		//���[�̃��[���h�}�g���b�N�X
	D3DXVECTOR3 aPosPoint[MAX_MESH];	//�v�Z��̊e���_���
	D3DXCOLOR aColPoint[MAX_MESH];		//�e���_�J���[
}MeshOrbit;

//==========================================================
//�v���g�^�C�v�錾
//==========================================================
void InitMeshOrbit(void);
void UninitMeshOrbit(void);
void UpdateMeshOrbit(void);
void DrawMeshOrbit(void);

#endif
