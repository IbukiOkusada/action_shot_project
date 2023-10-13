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
class CMapCamera;
class CLight;
class CFileLoad;
class CEditor;
class CSlow;
class CObject3D;
class CMeshField;
class CPause;
class CThermo;
class CEnemyManager;
class CCarManager;
class CEnemyRoute;
class CMeshDome;
class CObject2D;
class CHeatFilter;

// �}�N����`
#define NUM_FILTER	(2)

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
	CTime *GetTime(void);
	CPlayer *GetPlayer(void);
	static CSlow *GetSlow(void);
	static CMeshField *GetMeshField(void);
	static void SetMesh(CMeshField *pMesh) { m_pMeshField = pMesh; }
	CFileLoad *GetFileLoad(void);
	static CPause *GetPause(void);
	CEditor *GetEditor(void);
	CMapCamera *GetMapCamera(void) { return m_pMapCamera; }
	CEnemyRoute *GetEnemyRoute(void) { return m_pEnemyRoute; }
	CCarManager *GetCarManager(void) { return m_pCarManager; }
	CEnemyManager *GetEnemyManager(void) { return m_pEnemyManager; }

private:

	void DataReset(void);
	void EnemySet(void);
	void CarSet(void);
	void SkySet(void);

	CFileLoad *m_pFileLoad;			// �t�@�C���ǂݍ��݂̃|�C���^
	static CScore *m_pScore;		// �X�R�A�̃|�C���^
	CTime *m_pTime;					// �^�C���̃|�C���^
	CPlayer *m_pPlayer;				// �v���C���[�̃|�C���^
	static CSlow *m_pSlow;			// �X���[�̃|�C���^
	static CMeshField *m_pMeshField;	// ���b�V���t�B�[���h�̃|�C���^
	static CPause *m_pPause;		// �|�[�Y�̃|�C���^
	CEditor *m_pEditor;				// �G�f�B�^�[�̃|�C���^
	CMapCamera *m_pMapCamera;		// �~�j�}�b�v�p�J����
	CThermo *m_pMapThermo;			// �}�b�v�S�̂̉��x�\��
	CEnemyManager *m_pEnemyManager;	// �G�l�~�[�}�l�[�W���[�̃|�C���^
	CCarManager *m_pCarManager;		// �J�[�}�l�[�W���[�̃|�C���^
	CEnemyRoute *m_pEnemyRoute;		// �G�̏��H�Ǘ��̃|�C���^
	CMeshDome *m_pMeshDome;			// ���b�V���h�[���̃|�C���^
	int m_nMaxEnemy;				// ���݂̃G�l�~�[�ő吔
	CObject2D *m_pStart;			// �X�^�[�g���̕���
	CHeatFilter *m_apFilter[NUM_FILTER];
};

#endif