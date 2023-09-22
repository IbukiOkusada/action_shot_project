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
class CSlow;
class CFade;
class CMultiCamera;
class CMapCamera;
class CTime;
class CPlayer;
class CFileLoad;
class CEditor;
class CEnemyRoute;
class CCarManager;
class CEnemyManager;

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
		MODE_TUTORIAL,	// �`���[�g���A�����
		MODE_GAME,		// �Q�[�����
		MODE_RESULT,	// ���U���g���
		MODE_RANKING,	// �����L���O���
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
	virtual CMapCamera *GetMapCamera(void) { return NULL; }
	virtual CTime *GetTime(void) { return NULL; }
	virtual CPlayer *GetPlayer(void) { return NULL; }
	virtual CFileLoad *GetFileLoad(void) { return NULL; }
	virtual CEditor *GetEditor(void) { return NULL; }
	virtual CEnemyRoute *GetEnemyRoute(void) { return NULL; }
	virtual CCarManager *GetCarManager(void) { return NULL; }
	virtual CEnemyManager *GetEnemyManager(void) { return NULL; }
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
	static CSlow *GetSlow(void);
	static CFade *GetFade(void);
	static void SetMode(CScene::MODE mode);
	static CScene::MODE GetMode(void) { return m_pScene->GetMode(); }
	static CScene *GetScene(void) { return m_pScene; }

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	static void DataReset(void);

	// �ÓI�����o�ϐ�
	static CRenderer *m_pRenderer;	// �����_���[�̃|�C���^
	static CInputKeyboard *m_pInputKeyboard;	// �L�[�{�[�h�̃|�C���^
	static CInputMouse *m_pInputMouse;	// �}�E�X�̃|�C���^
	static CInputPad *m_pInputPad;	// �p�b�h�̃|�C���^
	static CDebugProc *m_pDebugProc;	// �f�o�b�O�\���̃|�C���^
	static CMultiCamera *m_pCamera;		// �J�����̃|�C���^
	static CLight *m_pLight;		// ���C�g�̃|�C���^
	static CTexture *m_pTexture;	// �e�N�X�`���̃|�C���^
	static CXFile *m_pModelFile;	// X�t�@�C���̃|�C���^
	static CSound *m_pSound;		// �T�E���h�̃|�C���^
	static CSlow *m_pSlow;			// �X���[�̃|�C���^
	static CScene *m_pScene;		// �V�[���̃|�C���^
	static CFade *m_pFade;			// �t�F�[�h�̃|�C���^
};


#endif

