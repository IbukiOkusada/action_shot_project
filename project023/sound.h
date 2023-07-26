//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : Ibuki Okusada
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//=============================================================================
// �T�E���h�N���X�̒�`
//=============================================================================
class CSound
{
public:	// �N�ł��A�N�Z�X�\�Ȓ�`

	// ��ޗ�
	typedef enum
	{
		LABEL_BGM000 = 0,	// BGM�Q�[��
		LABEL_SE_BREAK,		// �j��
		LABEL_SE_GET,		// �擾��
		LABEL_MAX,
	} LABEL;

private: // �����������A�N�Z�X�\

	 // �T�E���h���̍\���̒�`
	typedef struct
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	} SOUNDINFO;

public:	// �N�ł��A�N�Z�X�\

	CSound();	// �R���X�g���N�^
	~CSound();	// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT Play(LABEL label);
	void Stop(LABEL label);
	void Stop(void);

private:	// �����������A�N�Z�X�\

	// �����o�֐�
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	// �����o�ϐ�
	static const SOUNDINFO m_aSoundInfo[LABEL_MAX];	// �T�E���h�t�@�C����
	IXAudio2 *m_pXAudio2;							// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice;		// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[LABEL_MAX];	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[LABEL_MAX];					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[LABEL_MAX];					// �I�[�f�B�I�f�[�^�T�C�Y
};

#endif
