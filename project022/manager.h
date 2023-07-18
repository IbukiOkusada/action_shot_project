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
class CDebugProc;
class CMultiBg;
class CSound;
class CScore;
class CTime;
class CPlayer;
class CCamera;
class CLight;
class CTexture;
class CXFile;
class CFileLoad;
class CEditor;
class CSlow;
class CObject3D;
class CMeshField;

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
	static CDebugProc *GetDebugProc(void);
	static CMultiBg *GetMultiBg(void);
	static CSound *GetSound(void);
	static CScore *GetScore(void);
	static CTime *GetTime(void);
	static CPlayer *GetPlayer(void);
	static CCamera *GetCamera(void);
	static CLight *GetLight(void);
	static CTexture *GetTexture(void);
	static CXFile *GetModelFile(void);
	static CFileLoad *GetFileLoad(void);
	static CEditor *GetEditor(void);
	static CSlow *GetSlow(void);
	static CObject3D *GetObject3D(void);
	static CMeshField *GetMeshField(void);
	static void SetMesh(CMeshField *pMesh) { m_pMeshField = pMesh; }

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	void ItemReset(void);

	// �ÓI�����o�ϐ�
	static CRenderer *m_pRenderer;	// �����_���[�̃|�C���^
	static CInputKeyboard *m_pInputKeyboard;	// �L�[�{�[�h�̃|�C���^
	static CInputMouse *m_pInputMouse;	// �}�E�X�̃|�C���^
	static CDebugProc *m_pDebugProc;	// �f�o�b�O�\���̃|�C���^
	static CMultiBg *m_pBg;			// �w�i�̃|�C���^
	static CSound *m_pSound;		// �T�E���h�̃|�C���^
	static CScore *m_pScore;		// �X�R�A�̃|�C���^
	static CTime *m_pTime;			// �^�C���̃|�C���^
	static CPlayer *m_pPlayer;		// �v���C���[�̃|�C���^
	static CCamera *m_pCamera;		// �J�����̃|�C���^
	static CLight *m_pLight;		// ���C�g�̃|�C���^
	static CTexture *m_pTexture;	// �e�N�X�`���̃|�C���^
	static CXFile *m_pModelFile;	// X�t�@�C���̃|�C���^
	static CFileLoad *m_pFileLoad;	// �t�@�C���ǂݍ��݂̃|�C���^
	static CEditor *m_pEditor;		// �G�f�B�^�[�̃|�C���^
	static CSlow *m_pSlow;			// �X���[�̃|�C���^
	static CObject3D *m_pObject3D;
	static CMeshField *m_pMeshField;
};


#endif

