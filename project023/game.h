//===============================================
//
// �Q�[����ʂ̊Ǘ����� [game.h]
// Author : Ibuki Okusada
//
//===============================================
#ifndef _GAME_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _GAME_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "manager.h"

// �O���錾
class CScore;
class CTime;
class CPlayer;
class CCamera;
class CLight;
class CFileLoad;
class CEditor;
class CSlow;
class CObject3D;
class CMeshField;
class CPause;

//===============================================
// �Q�[���N���X�̒�`(�h���N���X)
//===============================================
class CGame : public CScene
{
public:

	// �����o�֐�
	CGame();	// �R���X�g���N�^
	~CGame();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �����o�֐�(�|�C���^)
	static CScore *GetScore(void);
	static CTime *GetTime(void);
	static CPlayer *GetPlayer(void);
	static CSlow *GetSlow(void);
	static CMeshField *GetMeshField(void);
	static void SetMesh(CMeshField *pMesh) { m_pMeshField = pMesh; }
	static CFileLoad *GetFileLoad(void);
	static CPause *GetPause(void);
	void DataReset(void);

private:

	static CFileLoad *m_pFileLoad;		// �t�@�C���ǂݍ��݂̃|�C���^
	static CScore *m_pScore;			// �X�R�A�̃|�C���^
	static CTime *m_pTime;				// �^�C���̃|�C���^
	static CPlayer *m_pPlayer;			// �v���C���[�̃|�C���^
	static CSlow *m_pSlow;				// �X���[�̃|�C���^
	static CMeshField *m_pMeshField;	// ���b�V���t�B�[���h�̃|�C���^
	static CPause *m_pPause;			// �|�[�Y�̃|�C���^
	static CCamera *m_pMapCamera;		// �~�j�}�b�v�p�J����
};

#endif