//===============================================
//
// �}�l�[�W���[�̏��� [manager.h]
// Author : Ibuki Okusada
//
//===============================================
#ifndef _MANAGER_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _MANAGER_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "main.h"

// �O���錾
class CRenderer;
class CInputKeyboard;
class CInputMouse;
class CInputPad;
class CDebugProc;
class CSound;
class CCamera;
class CLight;
class CTexture;
class CXFile;
class CFileLoad;
class CEditor;
class CSlow;
class CFade;

//===============================================
// �V�[���N���X�̒�`
//===============================================
class CScene
{
public:

	// ���[�h�񋓌^
	enum MODE
	{
		MODE_TITLE = 0,	// �^�C�g�����
		MODE_GAME,		// �Q�[�����
		MODE_RESULT,	// ���U���g���
		MODE_MAX
	};

	CScene();
	~CScene();

	// �����o�֐�
	static CScene *Create(MODE mode);
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	void SetMode(MODE mode) { m_mode = mode; }
	MODE GetMode(void) { return m_mode; }

private:
	MODE m_mode;	// ���[�h
};

//===============================================
// �}�l�[�W���[�N���X�̒�`
//===============================================
class CManager
{
public:	// �N�ł��A�N�Z�X�\

	CManager();	// �R���X�g���N�^
	~CManager();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CRenderer *GetRenderer(void);
	static CInputKeyboard *GetInputKeyboard(void);
	static CInputMouse *GetInputMouse(void);
	static CInputPad *GetInputPad(void);
	static CDebugProc *GetDebugProc(void);
	static CSound *GetSound(void);
	static CCamera *GetCamera(void);
	static CLight *GetLight(void);
	static CTexture *GetTexture(void);
	static CXFile *GetModelFile(void);
	static CEditor *GetEditor(void);
	static CSlow *GetSlow(void);
	static CFade *GetFade(void);
	static void SetMode(CScene::MODE mode);
	static CScene::MODE GetMode(void) { return m_pScene->GetMode(); }

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	static void DataReset(void);

	// �ÓI�����o�ϐ�
	static CRenderer *m_pRenderer;	// �����_���[�̃|�C���^
	static CInputKeyboard *m_pInputKeyboard;	// �L�[�{�[�h�̃|�C���^
	static CInputMouse *m_pInputMouse;	// �}�E�X�̃|�C���^
	static CInputPad *m_pInputPad;	// �p�b�h�̃|�C���^
	static CDebugProc *m_pDebugProc;	// �f�o�b�O�\���̃|�C���^
	static CCamera *m_pCamera;		// �J�����̃|�C���^
	static CLight *m_pLight;		// ���C�g�̃|�C���^
	static CTexture *m_pTexture;	// �e�N�X�`���̃|�C���^
	static CXFile *m_pModelFile;	// X�t�@�C���̃|�C���^
	static CSound *m_pSound;		// �T�E���h�̃|�C���^
	static CEditor *m_pEditor;		// �G�f�B�^�[�̃|�C���^
	static CSlow *m_pSlow;			// �X���[�̃|�C���^
	static CScene *m_pScene;		// �V�[���̃|�C���^
	static CFade *m_pFade;			// �t�F�[�h�̃|�C���^
};


#endif

