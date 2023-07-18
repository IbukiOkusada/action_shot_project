//==========================================================
//
//���b�V���\���̋O�Տ��� [meshorbit.cpp]
//Author Ibuki Okusada
//
//==========================================================
#include "meshorbit.h"
#include "parts.h"

//==========================================================
//�O���[�o���ϐ�
//==========================================================
MeshOrbit g_MeshOrbit;	//�O�Ղ̏��

//==========================================================
//�O�Ղ̏���������
//==========================================================
void InitMeshOrbit(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		//�f�o�C�X�ւ̃|�C���^

	//�e��ϐ��̏�����
	g_MeshOrbit.pMtxParent = &GetBody()->mtxWorld;
	g_MeshOrbit.aOffSet[0] = D3DXVECTOR3(0.0f, 100.0f, 0.0f);
	g_MeshOrbit.aOffSet[1] = D3DXVECTOR3(0.0f, 30.0f, 0.0f);
	g_MeshOrbit.aCol[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_MeshOrbit.aCol[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * MAX_MESH,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_MeshOrbit.pVtxBuff,
		NULL);

	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_MeshOrbit.pVtxBuff->Lock(
		0,
		0,
		(void**)&pVtx,
		0);

	//���_���W�̐ݒ�(��������E��O�Ɍ������Ē��_����ݒ肷��
	for (int nCntpVtx = 0; nCntpVtx < MAX_MESH; nCntpVtx++)
	{
		//���_���W
		pVtx[nCntpVtx].pos = g_MeshOrbit.aPosPoint[nCntpVtx];

		//�@��
		pVtx[nCntpVtx].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//�F
		pVtx[nCntpVtx].col = g_MeshOrbit.aColPoint[nCntpVtx];

		//�e�N�X�`��
		pVtx[nCntpVtx].tex = D3DXVECTOR2(0.0f, 0.0f);
	}

	//���_�o�b�t�@���A�����b�N����
	g_MeshOrbit.pVtxBuff->Unlock();
}

//==========================================================
//�O�Ղ̏I������
//==========================================================
void UninitMeshOrbit(void)
{
	//���_�o�b�t�@�̔p��
	if (g_MeshOrbit.pMtxParent != NULL)
	{
		g_MeshOrbit.pMtxParent = NULL;
	}

	//���_�o�b�t�@�̔p��
	if (g_MeshOrbit.pVtxBuff != NULL)
	{
		g_MeshOrbit.pVtxBuff->Release();
		g_MeshOrbit.pVtxBuff = NULL;
	}
}

//==========================================================
//�O�Ղ̍X�V����
//==========================================================
void UpdateMeshOrbit(void)
{

}

//==========================================================
//�O�Ղ̕`�揈��
//==========================================================
void DrawMeshOrbit(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		//�f�o�C�X�ւ̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X

	//���C�e�B���O���I�t�ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�J�����O�I���ɂ���

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_MeshOrbit.aMtxWorldPoint[0]);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_MeshOrbit.aOffSet[0].x, g_MeshOrbit.aOffSet[0].y, g_MeshOrbit.aOffSet[0].z);
	D3DXMatrixMultiply(&g_MeshOrbit.aMtxWorldPoint[0], &g_MeshOrbit.aMtxWorldPoint[0], &mtxTrans);

	//�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���������킹��
	D3DXMatrixMultiply(&g_MeshOrbit.aMtxWorldPoint[0],
		&g_MeshOrbit.aMtxWorldPoint[0], g_MeshOrbit.pMtxParent);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_MeshOrbit.aMtxWorldPoint[0]);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_MeshOrbit.aMtxWorldPoint[1]);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_MeshOrbit.aOffSet[1].x, g_MeshOrbit.aOffSet[1].y, g_MeshOrbit.aOffSet[1].z);
	D3DXMatrixMultiply(&g_MeshOrbit.aMtxWorldPoint[1], &g_MeshOrbit.aMtxWorldPoint[1], &mtxTrans);

	//�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���������킹��
	D3DXMatrixMultiply(&g_MeshOrbit.aMtxWorldPoint[1],
		&g_MeshOrbit.aMtxWorldPoint[1], g_MeshOrbit.pMtxParent);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_MeshOrbit.aMtxWorldPoint[1]);

	//�ۑ����Ă���������炷
	for (int nCntMesh = 2; nCntMesh < MAX_MESH; nCntMesh++)
	{
		g_MeshOrbit.aPosPoint[nCntMesh] = g_MeshOrbit.aPosPoint[nCntMesh - 2];
		g_MeshOrbit.aCol[nCntMesh] = g_MeshOrbit.aCol[nCntMesh - 2];
	}

	//�ŐV�̏�����
	g_MeshOrbit.aPosPoint[0].x = g_MeshOrbit.aMtxWorldPoint[0]._41;
	g_MeshOrbit.aPosPoint[0].y = g_MeshOrbit.aMtxWorldPoint[0]._42;
	g_MeshOrbit.aPosPoint[0].z = g_MeshOrbit.aMtxWorldPoint[0]._43;
	g_MeshOrbit.aColPoint[0] = g_MeshOrbit.aCol[0];

	g_MeshOrbit.aPosPoint[1].x = g_MeshOrbit.aMtxWorldPoint[1]._41;
	g_MeshOrbit.aPosPoint[1].y = g_MeshOrbit.aMtxWorldPoint[1]._42;
	g_MeshOrbit.aPosPoint[1].z = g_MeshOrbit.aMtxWorldPoint[1]._43;
	g_MeshOrbit.aColPoint[1] = g_MeshOrbit.aCol[1];

	//���b�V���\���̋O�Ղ�`��

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(
		0,
		g_MeshOrbit.pVtxBuff,
		0,
		sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	for (int nCntParts = 0; nCntParts < MAX_MESH; nCntParts++)
	{
		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_MeshOrbit.aMtxWorldPoint[nCntParts % 2]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
			0,
			nCntParts //���_���\���̂̃T�C�Y
			);
	}

	//�J�����O�I�t�ɂ���

	//���C�e�B���O���I���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}