//==========================================================
//
// ���C�g�̏����S�� [light.h]
// Author : Ibuki Okusada
//
//==========================================================
#include "light.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"

//==========================================================
// �R���X�g���N�^
//==========================================================
CLight::CLight()
{
	
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CLight::~CLight()
{

}

//==========================================================
// ����������
//==========================================================
HRESULT CLight::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();		// �f�o�C�X�ւ̃|�C���^���擾
	D3DXVECTOR3 vecDir;		// �ݒ�ύX�p�x�N�g��

	for (int nCntLight = 0; nCntLight < NUM_LIGHT; nCntLight++)
	{
		// ���C�g�̏����N���A����
		ZeroMemory(&m_aLight[nCntLight], sizeof(D3DLIGHT9));

		// ���C�g�̎�ނ�ݒ�
		m_aLight[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

		// ���C�g�̊g�U����ݒ�
		switch (nCntLight)
		{
		case 0:
			m_aLight[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			break;
		case 1:
			m_aLight[nCntLight].Diffuse = D3DXCOLOR(0.65f, 0.65f, 0.65f, 1.0f);
			break;
		case 2:
			m_aLight[nCntLight].Diffuse = D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f);
			break;
		}

		// ���C�g�̕�����ݒ�
		switch (nCntLight)
		{
		case 0:
			//vecDir = D3DXVECTOR3(0.1f, -0.11f, 0.44f);
			//vecDir = D3DXVECTOR3(0.8f, 0.23f, -0.55f);
			vecDir = D3DXVECTOR3(0.22f, -0.87f, -0.44f);
			break;
		case 1:
			vecDir = D3DXVECTOR3(0.8f, 0.23f, -0.55f);
			break;
		case 2:
			vecDir = D3DXVECTOR3(0.89f, -0.11f, 0.44f);
			break;
		}

		D3DXVec3Normalize(&vecDir, &vecDir);	// �x�N�g���𐳋K������
		m_aLight[nCntLight].Direction = vecDir;

		// ���C�g��ݒ肷��
		pDevice->SetLight(nCntLight, &m_aLight[nCntLight]);

		// ���C�g��L��������
		pDevice->LightEnable(nCntLight, TRUE);
	}

	return S_OK;
}

//==========================================================
// �I������
//==========================================================
void CLight::Uninit(void)
{

}

//==========================================================
// �X�V����
//==========================================================
void CLight::Update(void)
{

}