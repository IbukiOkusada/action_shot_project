//===============================================
//
// ���U���g��ʂ̊Ǘ����� [result.h]
// Author : Ibuki Okusada
//
//===============================================
#ifndef _RESULT_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _RESULT_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "manager.h"

class CScore;
class CFileLoad;
class CMeshDome;

//===============================================
// �^�C�g���N���X�̒�`(�h���N���X)
//===============================================
class CResult : public CScene
{
private:

	// �X�R�A�񋓌^
	enum SCORE
	{
		SCORE_SUV = 0,
		SCORE_DEAD,
		SCORE_ALL,
		SCORE_MAX
	};

public:

	// �����o�֐�
	CResult();	// �R���X�g���N�^
	~CResult();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �����o�֐�(�擾)
	static void SetSuv(int nValue) { m_nSuvNum = nValue; }
	static void SetDead(int nValue) { m_nDeadNum = nValue; }

private:

	CFileLoad *m_pFileLoad;		// �t�@�C���ǂݍ��݂̃|�C���^
	CMeshDome *m_pMeshSky;		// ��p
	CScore *m_apScore[SCORE_MAX];
	CScore *m_apNum[SCORE_ALL];
	int m_nTimer;
	static int m_nSuvNum;
	static int m_nDeadNum;
};

#endif