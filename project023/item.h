//==========================================================
//
// �A�C�e���̏��� [item.h]
// Author : Ibuki Okusada
//
//==========================================================
#ifndef _ITEM_H_		// ���̃}�N������`����Ă��Ȃ��ꍇ
#define _ITEM_H_		// ��d�C���N���[�h�h�~�p�}�N�����`

#include "main.h"
#include "object2D.h"

//==========================================================
// �A�C�e���̃N���X��`(�h���N���X)
//==========================================================
class CItem : public CObject2D
{
public:	// �N�ł��A�N�Z�X�\

	// ��ޗ񋓌^�̒�`
	typedef enum
	{
		TYPE_MOON = 0,	// ��
		TYPE_DIAMOND,	// ���
		TYPE_MAX
	}TYPE;

	//CItem();	// �R���X�g���N�^
	CItem(int Priority = 4);
	~CItem();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CItem *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, TYPE type);

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	void Controller(void);
	bool Collision(D3DXVECTOR3 pos);

	// �����o�ϐ�
	int m_nIdxTexture;
	static const char *m_apTextureFileName[];	// �t�@�C����
	int m_nType;			// ���
};

#endif
