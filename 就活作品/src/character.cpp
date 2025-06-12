//==========================
// 
// �L�����N�^�[[character.h]
// Author Yuki Goto
//
//==========================
#include"character.h"

const int CCharacter::PRIORITY = 1;//�`�揇

//==========================
//�R���X�g���N�^
//==========================
CCharacter::CCharacter(int nPriority):
CMotionModel(nPriority),//���R���X�g���N�^
m_state(STATE::NEUTRAL),//���݂̏��
m_nLife(0),//����
m_Damage(false),//�_���[�W��Ԕ���
m_DamageMove(D3DXVECTOR3(0.0f,0.0f,0.0f)),//������їp�̈ړ��l
m_visual(nullptr)//�����蔻��̉���
{

}

//==========================
//�f�X�g���N�^
//==========================
CCharacter::~CCharacter()
{

}

//==========================
//����������
//==========================
HRESULT CCharacter::Init()
{
	//�����ݒ�
	CMotionModel::Init();

	return S_OK;
}

//==========================
//�I������
//==========================
void CCharacter::Uninit()
{
	if (m_visual != nullptr)
	{
		m_visual->Uninit();
		m_visual = nullptr;
	}

	//�I������
	CMotionModel::Uninit();
}

//==========================
//�X�V����
//==========================
void CCharacter::Update()
{
	//�X�V����
	CMotionModel::Update();
}

//==========================
//�`�揈��
//==========================
void CCharacter::Draw()
{
	//�`�揈��
	CMotionModel::Draw();
}

//==========================
//��e���̐�����я���
//==========================
void CCharacter::DamegeBlow(D3DXVECTOR3 pos)
{
	if (GetState() != STATE::GUARD)
	{
		SetMotion(MOTION_TYPE::DAMAGEBLOW);
	}

	float angle = atan2f(GetPos().x - pos.x, GetPos().z - pos.z);
	m_DamageMove = D3DXVECTOR3(sinf(angle) * 15.0f, GetMove().y, cosf(angle) * 15.0f);
}

//==========================
//�����̐ݒ�
//==========================
void CCharacter::SetLife(int life)
{
	m_nLife = life;
}

//==========================
//�����̎擾
//==========================
int CCharacter::GetLife()
{
	return m_nLife;
}

//==========================
//�_���[�W����̎擾
//==========================
bool CCharacter::GetDamage()
{
	return m_Damage;
}

//==========================
//�_���[�W����̕ύX
//==========================
void CCharacter::SetDamage(bool damege)
{
	m_Damage = damege;
}

//==========================
//��Ԃ̐ݒ�
//==========================
void CCharacter::SetState(STATE state)
{
	m_state = state;
}

//==========================
//��Ԃ̎擾
//==========================
CCharacter::STATE CCharacter::GetState()
{
	return m_state;
}

//==========================
//��e���̓����蔻��̉���
//==========================
void CCharacter::DamageVisual(int PartsNum, float Radius)
{
	GetParts(PartsNum)->CreateVisual(D3DXVECTOR3(GetParts(PartsNum)->GetMtxWorld()._41, GetParts(PartsNum)->GetMtxWorld()._42, GetParts(PartsNum)->GetMtxWorld()._43), Radius);
}

//==========================
//�����蔻��̉�������
//==========================
void CCharacter::SetVisual()
{
	if (m_visual == nullptr)
	{
		//m_visual = CCollisionVisual::Create(GetPos(), GetRadius());
	}
}

//==========================
//������їp�̈ړ��l�ݒ�
//==========================
void CCharacter::SetDamegeBlow(D3DXVECTOR3 move)
{
	m_DamageMove = move;
}

//==========================
//������їp�̈ړ��l�擾
//==========================
D3DXVECTOR3& CCharacter::GetDamegeBlow()
{
	return m_DamageMove;
}