//===============================================
//
// �t�F�[�h�̏����S�� [fade.h]
// Author : Ibuki Okusada
//
//===============================================
#include "fade.h"

//�O���[�o���錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL;	//���_�o�b�t�@�ւ̃|�C���^

//===============================================
// �R���X�g���N�^
//===============================================
CFade::CFade(const int nPriOrity) : CObject2D(nPriOrity)
{
	// �l�̃N���A
	m_state = STATE_NONE;
	m_Col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

//===============================================
// �f�X�g���N�^
//===============================================
CFade::~CFade()
{

}

//===============================================
// ����������
//===============================================
HRESULT CFade::Init(CScene::MODE modeNext)
{
	// �|���S���̐���
	CObject2D::Init();

	// �T�C�Y�ݒ�
	SetPosition(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
	SetSize(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);

	//���[�h�̐ݒ�
	Set(modeNext);

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CFade::Uninit(void)
{
	CObject2D::Uninit();
}

//===============================================
// �X�V����
//===============================================
void CFade::Update(void)
{
	if (m_state != STATE_NONE)
	{//�������Ă��Ȃ���ԈȊO
		if (m_state == STATE_IN)
		{//�t�F�[�h�C�����
			m_Col.a -= 1.0f / 30;	//�����ɋ߂Â��Ă���

			if (m_Col.a <= 0.0f)
			{//���S�ɓ����ɂȂ����ꍇ
				m_Col.a = 0.0f;	//�����x�𓧖���
				m_state = STATE_NONE;	//�������Ă��Ȃ���Ԃ�
			}
		}
		else if (m_state == STATE_OUT)
		{//�t�F�[�h�A�E�g���
			m_Col.a += 1.0f / 30;	//�s�����ɋ߂Â��Ă���

			if (m_Col.a >= 1.0f)
			{//���S�ɕs�����ɂȂ����ꍇ

				m_Col.a = 1.0f;	//�����x��s������

				//���[�h�̐ݒ�(���̉�ʂɈڍs)
				CManager::SetMode(m_modeNext);
				return;
			}
		}
	}

	SetCol(m_Col);
}

//===============================================
// �`�揈��
//===============================================
void CFade::Draw(void)
{
	if (m_state != STATE_NONE)
	{
		CObject2D::Draw();
	}
}

//===============================================
// ���̉�ʐݒ�
//===============================================
void CFade::Set(CScene::MODE modeNext)
{
	if (m_state != STATE_OUT)
	{
		m_state = STATE_OUT;	//�t�F�[�h�A�E�g��Ԃ�
		m_modeNext = modeNext;	//���̉��(���[�h)��
		m_Col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//�����ɐݒ�
	}
}

//===============================================
// ��Ԑݒ�
//===============================================
void CFade::SetState(STATE state)
{
	if (m_state == state)
	{// ���݂Ǝw�肳�ꂽ��Ԃ�����
		return;
	}

	m_state = state;

	switch (m_state)
	{
	case STATE_NONE:
		m_Col.a = 0.0f;
		break;

	case STATE_IN:
		m_Col.a = 1.0f;
		break;

	case STATE_OUT:
		m_Col.a = 0.0f;
		break;

	default:

		break;
	}

	SetCol(m_Col);
}

//===============================================
// ����
//===============================================
CFade *CFade::Create(CScene::MODE modeNext)
{
	CFade *pFade = NULL;

	pFade = new CFade;

	if (pFade != NULL)
	{
		pFade->Init(modeNext);
		pFade->SetState(STATE_IN);
	}

	return pFade;
}