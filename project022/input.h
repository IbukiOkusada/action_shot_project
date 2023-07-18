//==========================================================
//
//���̓f�o�C�X���� [input.h]
//Author ����ɐ�
//
//==========================================================
#ifndef _INPUT_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _INPUT_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "main.h"

//==========================================================
//�}�N����`
//==========================================================
#define NUM_KEY_MAX	(256)	//�L�[�̍ő吔

//==========================================================
//���N���X�̒�`(���̓f�o�C�X)
//==========================================================
class CInput
{
public:	// �N�ł��A�N�Z�X�\
	
	CInput();	// �R���X�g���N�^
	virtual ~CInput();	// �f�X�g���N�^

	// �����o�֐�
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;

protected:	// �h���N���X������A�N�Z�X�\
	static LPDIRECTINPUT8 m_pInput;	//DirectInput�I�u�W�F�N�g�ւ̃|�C���^
	LPDIRECTINPUTDEVICE8 m_pDevice;	//���̓f�o�C�X�ւ̃|�C���^

private:	// ���������A�N�Z�X�\

};

//==========================================================
//�h���N���X�̒�`(�L�[�{�[�h)
//==========================================================
class CInputKeyboard : public CInput
{
public:	// �N�ł��A�N�Z�X�\

	CInputKeyboard();	// �R���X�g���N�^
	~CInputKeyboard();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
	bool GetRelease(int nKey);
	bool GetRepeat(int nKey);

private:	// ���������A�N�Z�X�\

	// �����o�ϐ�
	BYTE m_aKeyState[NUM_KEY_MAX];	//�v���X���
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];	//�g���K�[���
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];	//�����[�X���
	BYTE m_aKeyStateRepeat[NUM_KEY_MAX];	//���s�[�g���
	int m_aRepeatCnt[NUM_KEY_MAX];	// ���s�[�g�^�C�}�[
};

//==========================================================
//�h���N���X�̒�`(�}�E�X)
//==========================================================
class CInputMouse : public CInput
{
public:	// �N�ł��A�N�Z�X�\

	//�}�E�X
	typedef enum
	{
		BUTTON_LBUTTON = 0,	//���N���b�N
		BUTTON_RBUTTON,		//�E�N���b�N
		BUTTON_WHEEL,		//�z�C�[��
		BUTTON_MAX
	}BUTTON;

	CInputMouse();	// �R���X�g���N�^
	~CInputMouse();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
	bool GetRelease(int nKey);
	bool GetRepeat(int nKey);
	D3DXVECTOR3 GetCousorMove();

private:	// ���������A�N�Z�X�\

	// �����o�ϐ�
	DIMOUSESTATE2 m_State;	//�v���X���
	DIMOUSESTATE2 m_Trigger;	//�g���K�[���
	DIMOUSESTATE2 m_Release;	//�����[�X���
	DIMOUSESTATE2 m_Repeat;	//���s�[�g���
	POINT m_Point;			//�J�[�\���|�C���^�[
};

// �L�l�N�g
#endif
