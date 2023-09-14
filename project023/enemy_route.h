//==========================================================
//
// �G�̏��H�Ǘ����� [enemy_route.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _ENEMY_ROUTE_H_
#define _ENEMY_ROUTE_H_

#define MAX_ROUTE	(64)	// �s���p�^�[���ő吔
#define ROUTE_NAME	(256)

//==========================================================
// �G�̏o���Ǘ��N���X�̒�`(���N���X)
//==========================================================
class CEnemyRoute
{
public:

	// ���H���\����
	struct Route
	{
		D3DXVECTOR3 StartPos;	// �J�n�n�_
		D3DXVECTOR3 StartRot;	// �J�n����
		D3DXVECTOR3 *pPoint;	// �`�F�b�N�|�C���g
		float fMove;			// �ړ����x
		int nNumPoint;	// �|�C���g����
	};

private:

	// �ۑ����p�\����
	struct RouteData
	{
		Route route;	// ���H���
		char aName[ROUTE_NAME];	// ���O����
	};

public:		// �N�ł��A�N�Z�X�\

	CEnemyRoute();	// �R���X�g���N�^
	~CEnemyRoute();	// �f�X�g���N�^

	HRESULT Init(void);
	void Uninit(void);
	Route *SetAddress(const char *pFileName);
	Route *SetAddress(const int nIdx);
	int Regist(const char *pFileName);
	bool Load(Route *pRoute, const char *pFileName);

private:	// �����������A�N�Z�X�\

	RouteData *m_apRoute[MAX_ROUTE];	// ���[�g�̍ő吔
	int m_nNumAll;	// ����
};

#endif