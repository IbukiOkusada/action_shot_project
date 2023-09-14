//===============================================
//
// �G�̏��� [enemy.cpp]
// Author : Ibuki Okusada
//
//===============================================
#include "enemy.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "debugproc.h"
#include "shadow.h"
#include "character.h"
#include "motion.h"
#include "slow.h"
#include "model.h"
#include "billboard.h"
#include "meshfield.h"
#include "texture.h"
#include "slow.h"
#include "bullet.h"
#include "particle.h"
#include "score.h"
#include "lockon.h"
#include "game.h"
#include "player.h"
#include "meshcylinder.h"
#include "target.h"
#include "thermo.h"

//===============================================
// �}�N����`
//===============================================
#define MOVE			(2.0f)	// �ړ���
#define STATE_CNT		(300)	// ��ԊǗ��J�E���g
#define DAMINTERVAL		(5)		// �_���[�W�C���^�[�o��
#define MAX_LIFE		(210)	// �̗�
#define STATE_LINE		(70)
#define HOTINTERVAL		(10)	// �M���Ǐ�ԃC���^�[�o��
#define LEAVECNT		(120)	// �ޏ�^�C�}�[
#define LEAVEMOVE		(3.0f)	// �ޏꎞ�̈ړ���
#define COOLDOWNCNT		(160)	// �ޏ�O�ҋ@�J�E���g

const char *CEnemy::m_apFileName[NUM_ROUTE]
{
	"data\\TXT\\enemy\\walk\\route000.txt",
	"data\\TXT\\enemy\\walk\\route001.txt",
	"data\\TXT\\enemy\\walk\\route002.txt",
	"data\\TXT\\enemy\\walk\\route003.txt",
	"data\\TXT\\enemy\\walk\\route004.txt",
	"data\\TXT\\enemy\\walk\\route005.txt",
	"data\\TXT\\enemy\\walk\\route006.txt",
	"data\\TXT\\enemy\\walk\\route007.txt",
	"data\\TXT\\enemy\\walk\\route008.txt",
	"data\\TXT\\enemy\\walk\\route009.txt",
	"data\\TXT\\enemy\\walk\\route010.txt",
	"data\\TXT\\enemy\\walk\\route011.txt",
	"data\\TXT\\enemy\\walk\\route012.txt",
	"data\\TXT\\enemy\\walk\\route013.txt",
	"data\\TXT\\enemy\\walk\\route014.txt",
	"data\\TXT\\enemy\\walk\\route015.txt",
	"data\\TXT\\enemy\\walk\\route016.txt",
	"data\\TXT\\enemy\\walk\\route017.txt",
	"data\\TXT\\enemy\\walk\\route018.txt",
	"data\\TXT\\enemy\\walk\\route019.txt",
	"data\\TXT\\enemy\\walk\\route020.txt",
	"data\\TXT\\enemy\\walk\\route021.txt",
	"data\\TXT\\enemy\\walk\\route022.txt",
	"data\\TXT\\enemy\\walk\\route023.txt",
	"data\\TXT\\enemy\\walk\\route024.txt",
	"data\\TXT\\enemy\\walk\\route025.txt",
	"data\\TXT\\enemy\\walk\\route026.txt",
	"data\\TXT\\enemy\\park\\route000.txt",
	"data\\TXT\\enemy\\park\\route001.txt",
	"data\\TXT\\enemy\\park\\route002.txt",
	"data\\TXT\\enemy\\park\\route003.txt",
	"data\\TXT\\enemy\\park\\route004.txt",
	"data\\TXT\\enemy\\park\\route005.txt",
	"data\\TXT\\enemy\\park\\route006.txt",
	"data\\TXT\\enemy\\park\\route007.txt",
	"data\\TXT\\enemy\\park\\route008.txt",
	"data\\TXT\\enemy\\park\\route009.txt",
	"data\\TXT\\enemy\\park\\route010.txt",
	"data\\TXT\\enemy\\park\\route011.txt",
	"data\\TXT\\enemy\\park\\route012.txt",
	"data\\TXT\\enemy\\park\\route013.txt",
};

//===============================================
// �ÓI�����o�ϐ��錾
//===============================================
const int CEnemy::m_aParticleCounter[STATE_MAX] =
{
	30,
	30,
	30,
	30,
	30,
};

//===============================================
// �R���X�g���N�^(�I�[�o�[���[�h)
//===============================================
CEnemy::CEnemy(int nPriOrity)
{
	// �l���N���A����
	m_Info.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fRotMove = 0.0f;
	m_fRotDiff = 0.0f;
	m_fRotDest = 0.0f;
	m_pShadow = NULL;
	m_pBody = NULL;
	m_fStateCnt = 0;
	m_state = STATE_NORMAL;
	m_fLife = 0.0f;
	m_Interval.fHot = 0;
	m_Interval.fDamage = 0;
	m_pLockOn = NULL;
	m_pThermo = NULL;
	m_pRoute = NULL;
	m_nTargetPoint = 0;
}

//===============================================
// �f�X�g���N�^
//===============================================
CEnemy::~CEnemy()
{

}

//===============================================
// ����������
//===============================================
HRESULT CEnemy::Init(void)
{
	return S_OK;
}

//===============================================
// ����������(�I�[�o�[���[�h)
//===============================================
HRESULT CEnemy::Init(const char *pName)
{
	CTexture *pTexture = CManager::GetTexture();

	// ���̂̐ݒ�
	if (pName != NULL)
	{// �t�@�C���������݂��Ă���
		m_pBody = CCharacter::Create(pName);
		m_pBody->SetParent(&m_Info.mtxWorld);

		if (m_pBody->GetMotion() != NULL)
		{
			// �������[�V�����̐ݒ�
			m_pBody->GetMotion()->InitSet(1);
		}
	}

	m_fLife = (float)(rand() % STATE_LINE) + 0.1f;

	// ���x�\���̐���
	if (m_pThermo == NULL)
	{
		m_pThermo = CThermo::Create();
	}

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CEnemy::Uninit(void)
{
	// ���̂̏I������
	if (m_pBody != NULL)
	{
		m_pBody->Uninit();
		delete m_pBody;
		m_pBody = NULL;
	}

	// �e�̏I��
	if (m_pShadow != NULL)
	{
		m_pShadow->Uninit();
		m_pShadow = NULL;
	}

	// ���b�N�I���̏I��
	if (m_pLockOn != NULL)
	{
		m_pLockOn->Uninit();
		m_pLockOn = NULL;
	}

	// ���x�\���̏I��
	if (m_pThermo != NULL)
	{
		m_pThermo->Uninit();
		m_pThermo = NULL;
	}

	// ���b�N�I���m�F
	CBullet::Check(this);
	CLockOn::Check(this);

	// �p��
	Release();
}

//===============================================
// �X�V����
//===============================================
void CEnemy::Update(void)
{
	// �O��̍��W���擾
	m_Info.posOld = GetPosition();

	// ���̍X�V
	if (m_pBody != NULL)
	{// �g�p����Ă���ꍇ
		m_pBody->Update();
	}

	// �v���C���[����
	Controller();

	if (m_pShadow != NULL)
	{
		m_pShadow->SetPosition(D3DXVECTOR3(m_pBody->GetParts(0)->GetMtxWorld()->_41, m_Info.pos.y, m_pBody->GetParts(0)->GetMtxWorld()->_43));
	}

	// ��Ԃ��ƂɍX�V
	switch (m_state)
	{
	case STATE_NORMAL:

		UpdateNormal();
		break;

	case STATE_HOT:

		UpdateNormal();
		break;

	case STATE_HEAT:

		UpdateHeat();
		break;

	case STATE_DEFCOOL:

		UpdateCool();
		break;

	case STATE_COOL:

		UpdateCool();
		break;

	case STATE_COOLDOWN:

		UpdateCoolDown();
		break;

	case STATE_DOWN:

		UpdateDown();
		break;
	}

	// ���x�\���ݒ�
	SetThermo();

	if (m_nTargetPoint >= m_pRoute->nNumPoint)
	{
		m_state = STATE_DEFCOOL;
		m_fStateCnt = LEAVECNT;
		m_nTargetPoint = 0;
	}
}


//===============================================
// �`�揈��
//===============================================
void CEnemy::Draw(void)
{
	SetCol();

	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	//�f�o�C�X�ւ̃|�C���^���擾
	CTexture *pTexture = CManager::GetTexture();	// �e�N�X�`���ւ̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_Info.mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Info.rot.y, m_Info.rot.x, m_Info.rot.z);
	D3DXMatrixMultiply(&m_Info.mtxWorld, &m_Info.mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_Info.pos.x, m_Info.pos.y, m_Info.pos.z);
	D3DXMatrixMultiply(&m_Info.mtxWorld, &m_Info.mtxWorld, &mtxTrans);
	
	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_Info.mtxWorld);

	// ���̂̕`��
	if (m_pBody != NULL)
	{
		m_pBody->Draw();
	}
}

//===============================================
// ����
//===============================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, const char *pBodyName, const int nPriority)
{
	CEnemy *pEnemy = NULL;
	CXFile *pModelFile = CManager::GetModelFile();

	// �I�u�W�F�N�g2D�̐���
	pEnemy = new CEnemy(nPriority);

	if (pEnemy != NULL)
	{// �����ł����ꍇ

		// ����������
		pEnemy->Init(pBodyName);

		// ���W�ݒ�
		pEnemy->SetPosition(pos);

		// �����ݒ�
		pEnemy->SetRotation(rot);

		// �ړ��ʐݒ�
		pEnemy->SetMove(move);

		// ��ނ̐ݒ�
		pEnemy->SetType(TYPE_ENEMY);

		// �e�̐ݒ�
		pEnemy->m_pShadow = CShadow::Create(pos, 30.0f, 30.0f);

		// �r���{�[�h�̐ݒ�
		//pEnemy->m_pBillState = CObjectBillboard::Create();
	}
	else
	{// �����Ɏ��s�����ꍇ
		return NULL;
	}

	return pEnemy;
}

//===============================================
// ����
//===============================================
CEnemy *CEnemy::Create(const char *pBodyName, const int nPriority)
{
	CEnemy *pEnemy = NULL;
	CXFile *pModelFile = CManager::GetModelFile();

	// �I�u�W�F�N�g2D�̐���
	pEnemy = new CEnemy(nPriority);

	if (pEnemy != NULL)
	{// �����ł����ꍇ

	 // ����������
		pEnemy->Init(pBodyName);

		// ��ނ̐ݒ�
		pEnemy->SetType(TYPE_ENEMY);

		// ���H�̐ݒ�
		pEnemy->m_pRoute = CManager::GetScene()->GetEnemyRoute()->SetAddress(m_apFileName[rand() % NUM_ROUTE]);

		// �ݒ�
		pEnemy->SetPosition(pEnemy->m_pRoute->StartPos);
		pEnemy->SetRotation(pEnemy->m_pRoute->StartRot);

		// �e�̐ݒ�
		pEnemy->m_pShadow = CShadow::Create(pEnemy->GetPosition(), 30.0f, 30.0f);

		float fRotDest;	//���݂̈ړ��ʁA�ڕW�̈ړ������A�ڕW�܂ł̍���

		fRotDest = atan2f(pEnemy->m_Info.pos.x - pEnemy->m_pRoute->pPoint[pEnemy->m_nTargetPoint].x,
			pEnemy->m_Info.pos.z - pEnemy->m_pRoute->pPoint[pEnemy->m_nTargetPoint].z);	//�ڕW�ւ̌���
		pEnemy->m_Info.rot.y = fRotDest;

		D3DXVECTOR3 vec;
		vec.x = pEnemy->m_pRoute->pPoint[pEnemy->m_nTargetPoint].x - pEnemy->m_Info.pos.x;
		vec.y = pEnemy->m_pRoute->pPoint[pEnemy->m_nTargetPoint].y - pEnemy->m_Info.pos.y;
		vec.z = pEnemy->m_pRoute->pPoint[pEnemy->m_nTargetPoint].z - pEnemy->m_Info.pos.z;

		D3DXVec3Normalize(&vec, &vec);	// �x�N�g���𐳋K������

		pEnemy->m_Info.move.x = vec.x * pEnemy->m_pRoute->fMove;
		pEnemy->m_Info.move.y = vec.y * pEnemy->m_pRoute->fMove;
		pEnemy->m_Info.move.z = vec.z * pEnemy->m_pRoute->fMove;
		pEnemy->m_Info.posOld = pEnemy->m_Info.pos;
	}
	else
	{// �����Ɏ��s�����ꍇ
		return NULL;
	}

	return pEnemy;
}

//===============================================
// ���쏈��
//===============================================
void CEnemy::Controller(void)
{
	// �ݒ肳�ꂽ�ړ��ʂ����Z����
	m_pBody->GetMotion()->BlendSet(1);

	if (m_pRoute != NULL)
	{
		m_Info.pos += m_Info.move;

		if ((m_Info.posOld.x >= m_pRoute->pPoint[m_nTargetPoint].x && m_Info.pos.x < m_pRoute->pPoint[m_nTargetPoint].x) ||
			(m_Info.pos.x > m_pRoute->pPoint[m_nTargetPoint].x && m_Info.posOld.x <= m_pRoute->pPoint[m_nTargetPoint].x) ||
			(m_Info.posOld.z >= m_pRoute->pPoint[m_nTargetPoint].z && m_Info.pos.z < m_pRoute->pPoint[m_nTargetPoint].z) ||
			(m_Info.pos.z > m_pRoute->pPoint[m_nTargetPoint].z && m_Info.posOld.z <= m_pRoute->pPoint[m_nTargetPoint].z))
		{
			m_Info.pos = m_pRoute->pPoint[m_nTargetPoint];
			m_nTargetPoint++;

			if (m_nTargetPoint < m_pRoute->nNumPoint && m_state != STATE_DEFCOOL)
			{
				float fRotDest;	//���݂̈ړ��ʁA�ڕW�̈ړ������A�ڕW�܂ł̍���

				fRotDest = atan2f(m_Info.pos.x - m_pRoute->pPoint[m_nTargetPoint].x,
					m_Info.pos.z - m_pRoute->pPoint[m_nTargetPoint].z);	//�ڕW�ւ̌���
				m_Info.rot.y = fRotDest;

				D3DXVECTOR3 vec;
				vec.x = m_pRoute->pPoint[m_nTargetPoint].x - m_Info.pos.x;
				vec.y = m_pRoute->pPoint[m_nTargetPoint].y - m_Info.pos.y;
				vec.z = m_pRoute->pPoint[m_nTargetPoint].z - m_Info.pos.z;

				D3DXVec3Normalize(&vec, &vec);	// �x�N�g���𐳋K������

				m_Info.move.x = vec.x * m_pRoute->fMove;
				m_Info.move.y = vec.y * m_pRoute->fMove;
				m_Info.move.z = vec.z * m_pRoute->fMove;
				m_Info.posOld = m_Info.pos;
			}
		}
	}

	D3DXVECTOR3 nor;
	float fHeight = CMeshField::GetHeight(m_Info.pos);

	if (m_Info.move.y == 0.0f)
	{
		m_Info.pos.y = fHeight;
	}

	SetPosition(m_Info.pos);
	SetRotation(m_Info.rot);
	SetCol();
}

//===============================================
// �q�b�g����
//===============================================
void CEnemy::Hit(float fDamage)
{
	if (m_Interval.fDamage <= 0)
	{
		m_fLife -= fDamage;

		if (m_fLife < 0)
		{
			m_fLife = 0;
		}

		if (m_state != STATE_DEFCOOL)
		{// �󂯂Ȃ���ԈȊO
			// ��Ԑݒ�
			SetState();

			m_Interval.fDamage = DAMINTERVAL;
		}
	}
}

//===============================================
// ��Ԑݒ�
//===============================================
void CEnemy::SetState(void)
{
	// �c��̗͂ɂ���ď�Ԃ�ݒ�
	if (m_fLife <= 0)
	{// 0�ȉ�
		m_state = STATE_COOLDOWN;
		m_fStateCnt = COOLDOWNCNT;

		CParticle::Create(D3DXVECTOR3(GetMtx()->_41,
			GetMtx()->_42,
			GetMtx()->_43), CEffect::TYPE_EXPLOSION);

		CMeshSmake *pMesh;

		pMesh = CMeshSmake::Create(GetPosition(), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 37.0f, 2.0f, 3, 10, 10);

		pMesh->BindTexture(CManager::GetTexture()->Regist("data\\TEXTURE\\smake001.jpg"));

		pMesh = CMeshSmake::Create(GetPosition(), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 35.0f, 3.0f, 3, 10, 10);

		pMesh->BindTexture(CManager::GetTexture()->Regist("data\\TEXTURE\\smake000.jpg"));
	}
	else if (m_fLife < STATE_LINE * STATE_HOT)
	{//���Ƃ�������
		m_state = STATE_NORMAL;
	}
	else if (m_fLife >= STATE_LINE * STATE_HOT && m_fLife < STATE_LINE * STATE_HEAT)
	{// �܂��c���Ă���
		m_state = STATE_HOT;
	}
	else if (m_fLife >= STATE_LINE * STATE_HEAT && m_state == STATE_HOT)
	{// �قƂ�ǎc���Ă���
		m_state = STATE_HEAT;
	}
}

//===============================================
// ��Ԃ��Ƃ̃p�[�e�B�N���ݒ�
//===============================================
void CEnemy::SetParticle(void)
{
	D3DXMATRIX mtxProjection;
	D3DXMATRIX mtxView;
	D3DXMATRIX mtxWorld;
	D3DXVECTOR3 ScreenPos;
	D3DVIEWPORT9 Viewport;

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	pDevice->GetTransform(D3DTS_PROJECTION, &mtxProjection);	// �v���W�F�N�V�����}�g���b�N�X���擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);				// �r���[�}�g���b�N�X���擾
	pDevice->GetViewport(&Viewport);							// �r���[�|�[�g���擾

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	// ���[���h���W����X�N���[�����W�ɕϊ�����
	D3DXVec3Project(&ScreenPos, &GetPosition(), &Viewport, &mtxProjection, &mtxView, &mtxWorld);

	if (ScreenPos.x < 0.0f || ScreenPos.x > SCREEN_WIDTH || 
		ScreenPos.y < 0.0f || ScreenPos.y > SCREEN_HEIGHT || ScreenPos.z >= 1.0f)
	{// ��ʂɕ`�悳��Ă��Ȃ�
		return;
	}

	/*switch (m_state)
	{
	case STATE_NORMAL:
		CParticle::Create(D3DXVECTOR3(m_pBody->GetParts(3)->GetMtxWorld()->_41,
			m_pBody->GetParts(3)->GetMtxWorld()->_42,
			m_pBody->GetParts(3)->GetMtxWorld()->_43),
			CEffect::TYPE_SWEAT);
		break;

	case STATE_HOT:
		CParticle::Create(D3DXVECTOR3(m_pBody->GetParts(3)->GetMtxWorld()->_41,
			m_pBody->GetParts(3)->GetMtxWorld()->_42,
			m_pBody->GetParts(3)->GetMtxWorld()->_43),
			CEffect::TYPE_SWEAT);
		break;

	case STATE_HEAT:
		CParticle::Create(D3DXVECTOR3(m_pBody->GetParts(3)->GetMtxWorld()->_41,
			m_pBody->GetParts(3)->GetMtxWorld()->_42 + 12.0f,
			m_pBody->GetParts(3)->GetMtxWorld()->_43),
			CEffect::TYPE_HEAT);
		break;
	}

	for (int nCnt = 0; nCnt < m_state + 1; nCnt++)
	{
		CParticle::Create(D3DXVECTOR3(m_pBody->GetParts(3)->GetMtxWorld()->_41,
			m_pBody->GetParts(3)->GetMtxWorld()->_42 + 12.0f,
			m_pBody->GetParts(3)->GetMtxWorld()->_43),
			CEffect::TYPE_HEATHAZE);
	}*/
}

//===============================================
// �F�ݒ�
//===============================================
void CEnemy::SetCol(void)
{
	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	col.g = 1.0f - (float)(m_fLife / MAX_LIFE);
	col.b = 1.0f - (float)(m_fLife / MAX_LIFE);

	for (int nCnt = 0; nCnt < m_pBody->GetNumParts(); nCnt++)
	{
		if (m_pBody->GetParts(nCnt) != NULL)
		{
			if (m_fLife >= STATE_LINE)
			{
				if (m_state == STATE_DOWN)
				{
					col.a = (float)(m_fStateCnt / LEAVECNT);
					m_pShadow->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, col.a));
				}

				m_pBody->GetParts(nCnt)->SetChangeCol(true, col);
			}
			else
			{
				if (m_state == STATE_COOL)
				{// �ޏꒆ
					// �����x��ύX
					col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					col.a = (float)(m_fStateCnt / LEAVECNT);
					
					m_pBody->GetParts(nCnt)->SetChangeCol(true, col);
					m_pShadow->SetCol(col);
				}
				else
				{
					m_pBody->GetParts(nCnt)->SetChangeCol(false);
				}
			}
		}
	}
}

//===============================================
// �ʏ펞�̍X�V����
//===============================================
void CEnemy::UpdateNormal(void)
{
	if (m_fStateCnt < STATE_CNT)
	{
		m_fStateCnt += CManager::GetSlow()->Get();
	}

	// �̉��ݒ�
	SetBodyTemp();

	// �p�[�e�B�N���C���^�[�o��
	m_Interval.fParticle += CManager::GetSlow()->Get();

	if (m_Interval.fParticle >= m_aParticleCounter[m_state])
	{
		SetParticle();
		m_Interval.fParticle = 0.0f;
	}
}

//===============================================
// �������Ƃ��̍X�V����
//===============================================
void CEnemy::UpdateCool(void)
{
	m_fStateCnt -= CManager::GetSlow()->Get();

	if (m_fStateCnt <= 0.0f)
	{// �J�ڃ^�C�}�[�K��l
		Uninit();
	}
}

//===============================================
// �������Ȃ�������̍X�V����
//===============================================
void CEnemy::UpdateCoolDown(void)
{
	CPlayer *pPlayer = CManager::GetScene()->GetPlayer();
	m_fStateCnt -= CManager::GetSlow()->Get();

	Controller();

	if (m_fStateCnt <= 0.0f)
	{
		m_state = STATE_NORMAL;
		m_fStateCnt = LEAVECNT;
		m_fLife = 0.1f;

		if (pPlayer != NULL)
		{
			pPlayer->AddSlowTime();
		}
	}
}

//===============================================
// �M���Ǐ�Ԃ̍X�V����
//===============================================
void CEnemy::UpdateHeat(void)
{
	// �̉��ݒ�
	SetBodyTemp();

	if (m_fLife >= MAX_LIFE)
	{// ���E�܂ŗ����ꍇ
		m_state = STATE_DOWN;
		m_fStateCnt = LEAVECNT;
	}

	// �p�[�e�B�N���C���^�[�o��
	m_Interval.fParticle += CManager::GetSlow()->Get();

	if (m_Interval.fParticle >= m_aParticleCounter[m_state])
	{
		SetParticle();
		m_Interval.fParticle = 0.0f;
	}
}

//===============================================
// �_�E�����̍X�V����
//===============================================
void CEnemy::UpdateDown(void)
{
	m_fStateCnt -= CManager::GetSlow()->Get();

	if (m_fStateCnt <= 0.0f)
	{// �J�ڃ^�C�}�[�K��l
		Uninit();
	}
}

//===============================================
// �̉��ݒ�
//===============================================
void CEnemy::SetBodyTemp(void)
{
	return;
	// �_���[�W�C���^�[�o��
	if (m_Interval.fDamage > 0)
	{
		m_Interval.fDamage -= CManager::GetSlow()->Get();
	}

	if (m_state != STATE_DEFCOOL)
	{
		if (CMeshField::GetAreaHot(GetPosition()) == true)
		{
			// �̉��㏸�C���^�[�o��
			m_Interval.fHot += CManager::GetSlow()->Get();
		}
		else
		{
			m_Interval.fHot += 0.2f * CManager::GetSlow()->Get();
		}

		if (m_Interval.fHot >= HOTINTERVAL)
		{
			m_Interval.fHot = 0;
			m_fLife += CManager::GetSlow()->Get();

			if (m_fLife > MAX_LIFE)
			{
				m_fLife = MAX_LIFE;
			}
		}

		// ��ԍX�V
		SetState();
	}
}

//===============================================
// ���x�\���ݒ�
//===============================================
void CEnemy::SetThermo(void)
{
	if (m_pThermo == NULL)
	{
		return;
	}

	// �̉��ɍ��킹�ĐF��ݒ�
	D3DXCOLOR thermoCol = D3DXCOLOR(0.9f, 0.25f, 0.25f, 1.0f);	// ���x�\���̐F
	thermoCol.a = (float)(m_fLife / MAX_LIFE) * 0.7f;
	m_pThermo->SetColor(thermoCol);

	// ���W�ݒ�
	D3DXVECTOR3 pos = GetPosition();
	pos.y = 100.0f;
	m_pThermo->SetPosition(pos);

	// �T�C�Y�ݒ�
	m_pThermo->SetpVtx(1450.0f, 1450.0f);
}