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

//===============================================
// �^�C�g���N���X�̒�`(�h���N���X)
//===============================================
class CResult : public CScene
{
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
	static CScore *GetScore() { return m_pScore; }
	static void SetScore(int nValue) { m_nScore = nValue; }

private:

	static CScore *m_pScore;
	static int m_nScore;
};

#endif