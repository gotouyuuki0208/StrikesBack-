//==========================
// 
// �I�u�W�F�N�g�z�u[edit.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"edit.h"
#include"manager.h"
#include"buil.h"
#include"apartment.h"
#include"conveni.h"
#include"house.h"
#include"house_white.h"
#include"pole.h"
#include"boss.h"
#include"hitenemy.h"
#include"weaponenemy.h"
#include"fild.h"
#include"shingoki.h"
#include"fence.h"
#include"garden.h"
#include"construction_fence.h"
#include"school.h"
#include"bicycleparking.h"
#include"bigweapon.h"
#include"smallweapon.h"
#include"bat.h"
#include"bicycle.h"
#include"pipe.h"
#include"corridorfloor.h"
#include"corridorwall.h"
#include"shoerack.h"
#include"curb.h"
#include"room_door.h"
#include"board.h"
#include"entrance.h"
#include"gym_front.h"
#include"gym_wall.h"
#include"gym_entrance.h"
#include"gym_wall_top.h"
#include"basketgoal.h"
#include"jihanki.h"
#include"wall.h"
#include"enemymovepoint.h"
#include"gymdoor.h"
#include"syokaki.h"
#include"stagechangepoint.h"
#include"cone.h"
#include"gymfild.h"
#include"gymceiling.h"

//�ÓI�����o������
const float CEdit::MOVE = 1.0f;//�ړ���
const float CEdit::SCALE = 0.5f;//�X�P�[��
//==========================
// �R���X�g���N�^
//==========================
CEdit::CEdit():
m_EditObject(nullptr),//���ݕҏW���Ă���I�u�W�F�N�g
m_EditMode(false),//�ҏW���[�h
m_ObjectType(0),//�I�u�W�F�N�g�̎��
m_EditObjectKeep{},//�ҏW���̃I�u�W�F�N�g��ۑ�
m_MoveDirection(false),//�ړ�����
m_SwitchInput(false),//���͕��@
m_move(false),//�ړ��̕ҏW
m_Camera(false)//�J�����̈ʒu
{
	m_Object.clear();//�v�f��S�č폜
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//==========================
// �f�X�g���N�^
//==========================
CEdit::~CEdit()
{

}

//==========================
// ����������
//==========================
HRESULT CEdit::Init()
{
	m_EditObject = SetType();//�I�u�W�F�N�g�̎�ނ�ݒ�

	return S_OK;
}

//==========================
// �X�V����
//==========================
void CEdit::Update()
{
	if (!m_move)
	{
		//�ړ�����
		Move();
	}
	else
	{
		//�����̕ύX
		Rotate();
	}
	
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_8))
	{//WS�̈ړ�������ύX
		m_move = !m_move;
	}

	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_9))
	{//�J�����̈ʒu��ύX
		m_Camera = !m_Camera;
	}

	//�X�P�[���ύX
	Scale();

	//�ҏW���[�h�؂�ւ�
	SwitchEditMode();

	if (m_EditMode)
	{//�z�u�ς݃I�u�W�F�N�g��ҏW

		//�I�u�W�F�N�g��ύX
		ChangeObject();
	}
	
	//�I�u�W�F�N�g�̎�ނ�ύX
	ChangeType();

	if (m_EditObject != nullptr)
	{
		if (!m_Camera)
		{
			CManager::GetInstance()->GetCamera()->Move(m_EditObject->GetPos());//�J�����ړ�
		}
		else
		{
			CManager::GetInstance()->GetCamera()->Overhead(m_EditObject->GetPos());//�J�����ړ�
		}

		m_EditObject->SetPos(m_pos);//�I�u�W�F�N�g�̈ʒu���ړ�
		m_EditObject->SetScale(m_scale);//�I�u�W�F�N�g�̑傫����ύX
		m_EditObject->SetRot(m_rot);//�I�u�W�F�N�g�̌�����ύX
	}

	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_M))
	{
		int Stage = static_cast<int>(CManager::GetInstance()->GetStageManager()->GetStage());
		Save(Stage);
	}

	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_V))
	{//�X�e�[�W�؂�ւ�
		StageChange();
	}
}

//==========================
//�I������
//==========================
void CEdit::Uninit()
{
	m_Object.clear();//�v�f��S�č폜

	m_EditObject = nullptr;//���ݕҏW���Ă���I�u�W�F�N�g
	m_EditMode = false;//�ҏW���[�h
	m_ObjectType = 0;//�I�u�W�F�N�g�̎��
	m_EditObjectKeep = {};//�ҏW���̃I�u�W�F�N�g��ۑ�
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//==========================
//���͏���
//==========================
void CEdit::Move()
{
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_0))
	{//WS�̈ړ�������ύX
		m_MoveDirection = !m_MoveDirection;
	}
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_DOWNARROW))
	{//���͕��@�؂�ւ�
		m_SwitchInput = !m_SwitchInput;
	}

	float Move = MOVE;
	if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_LSHIFT))
	{
		Move = Move * 10;
	}

	if (!m_SwitchInput)
	{
		if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_W))
		{//��(��)�ֈړ�
			if (!m_MoveDirection)
			{
				m_pos.z += Move;
			}
			else
			{
				m_pos.y += Move;
			}
		}
		else if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_A))
		{//���ֈړ�
			m_pos.x -= Move;
		}
		else if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_S))
		{//��O(��)�ֈړ�
			if (!m_MoveDirection)
			{
				m_pos.z -= Move;
			}
			else
			{
				m_pos.y -= Move;
			}
		}
		else if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_D))
		{//�E�ֈړ�
			m_pos.x += Move;
		}
	}
	else
	{
		if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_W))
		{//��(��)�ֈړ�
			if (!m_MoveDirection)
			{
				m_pos.z += Move;
			}
			else
			{
				m_pos.y += Move;
			}
		}
		else if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_A))
		{//���ֈړ�
			m_pos.x -= Move;
		}
		else if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_S))
		{//��O(��)�ֈړ�
			if (!m_MoveDirection)
			{
				m_pos.z -= Move;
			}
			else
			{
				m_pos.y -= Move;
			}
		}
		else if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_D))
		{//�E�ֈړ�
			m_pos.x += Move;
		}
	}

	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_SPACE))
	{//�z�u
		m_Object.push_back(m_EditObject);//���݂̃I�u�W�F�N�g��ۑ�
		m_EditObject = SetType();//�V�����I�u�W�F�N�g�𐶐�
	}
}

//==========================
//������ς���
//==========================
void CEdit::Rotate()
{
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_W))
	{//������
		m_rot.y = D3DX_PI;
	}
	else if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_A))
	{//������
		m_rot.y = D3DX_PI / 2;
	}
	else if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_S))
	{//��O����
		m_rot.y = 0;
	}
	else if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_D))
	{//�E����
		m_rot.y = -D3DX_PI / 2;
	}
}

//==========================
//�X�P�[���ύX
//==========================
void CEdit::Scale()
{
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_1))
	{//�傫��
		m_scale.x += SCALE;
		m_scale.y += SCALE;
		m_scale.z += SCALE;
	}
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_2))
	{//������
		if (m_scale.x >= 1.0f)
		{
			m_scale.x -= SCALE;
			m_scale.y -= SCALE;
			m_scale.z -= SCALE;
		}
	}
}

//==========================
//�I�u�W�F�N�g��ύX
//==========================
void CEdit::ChangeObject()
{
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_3))
	{//�O�̃I�u�W�F�N�g

		if (m_Objectite != m_Object.begin())
		{//�ŏ��̃I�u�W�F�N�g����Ȃ�

			m_Objectite--;//�O�̃I�u�W�F�N�g�Ɉړ�
			m_EditObject = *m_Objectite;//�I�u�W�F�N�g�̏����擾
			m_pos = m_EditObject->GetPos();
			m_scale = m_EditObject->GetScale();
			m_rot = m_EditObject->GetRot();
		}
	}
	else if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_4))
	{//���̃I�u�W�F�N�g
		
		m_Objectite++;//���̃I�u�W�F�N�g�Ɉړ�

		if (m_Objectite == m_Object.end())
		{//�Ō�̂Ƃ�
			m_Objectite--;
		}

		m_EditObject = *m_Objectite;//�I�u�W�F�N�g�̏����擾
		m_pos = m_EditObject->GetPos();
		m_scale = m_EditObject->GetScale();
		m_rot = m_EditObject->GetRot();
	}
	else if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_5))
	{//��ԑO�̃I�u�W�F�N�g

		m_Objectite = m_Object.begin();//�ŏ��̃I�u�W�F�N�g�Ɉړ�

		m_EditObject = *m_Objectite;//�I�u�W�F�N�g�̏����擾
		m_pos = m_EditObject->GetPos();
		m_scale = m_EditObject->GetScale();
		m_rot = m_EditObject->GetRot();
	}
	else if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_6))
	{//��ԍŌ�̃I�u�W�F�N�g

		//�Ō�̃I�u�W�F�N�g�Ɉړ�
		m_Objectite = m_Object.end();
		m_Objectite--;

		m_EditObject = *m_Objectite;//�I�u�W�F�N�g�̏����擾
		m_pos = m_EditObject->GetPos();
		m_scale = m_EditObject->GetScale();
		m_rot = m_EditObject->GetRot();
	}
	else if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_7))
	{//�I�u�W�F�N�g�̍폜

		if (m_Object.size() <= 1)
		{//�v�f�������

			m_Object.clear();//�v�f���폜
			m_EditObject->Uninit();//�I�u�W�F�N�g�̍폜
			
			//�V�K�z�u���[�h�ɕύX
			m_EditMode = false;
			m_ObjectType = m_EditObjectKeep.ObjectType;
			m_EditObject = SetType();//�I�u�W�F�N�g�̎�ނ�ݒ�
			m_pos = m_EditObjectKeep.pos;
			m_scale = m_EditObjectKeep.scale;
			m_rot = m_EditObjectKeep.rot;
			return;
		}

		if (m_Objectite != m_Object.begin())
		{//�ŏ��̃I�u�W�F�N�g����Ȃ�

			//�I�u�W�F�N�g���폜���đO�̃I�u�W�F�N�g�Ɉړ�
			m_Objectite--;
			m_Object.erase(next(m_Objectite));
		}
		else
		{//�ŏ��̃I�u�W�F�N�g

			//�I�u�W�F�N�g���폜���Ď��̃I�u�W�F�N�g�Ɉړ�
			m_Objectite++;
			m_Object.erase(prev(m_Objectite));
		}

		m_EditObject->Uninit();//�I�u�W�F�N�g���폜
		m_EditObject = *m_Objectite;//�I�u�W�F�N�g�̏����擾
		m_pos = m_EditObject->GetPos();
		m_scale = m_EditObject->GetScale();
		m_rot = m_EditObject->GetRot();

	}
}

//==========================
//�I�u�W�F�N�g�̎�ނ�ύX
//==========================
CObjectgame* CEdit::SetType()
{
	CObjectgame* object = nullptr;

	switch (m_ObjectType)
	{
	case 0:
		object = CBuil::Create(m_pos, m_scale, m_rot);
		break;

	case 1:
		object = CApartment::Create(m_pos, m_scale, m_rot);
		break;

	case 2:
		object = CConveni::Create(m_pos, m_scale, m_rot);
		break;

	case 3:
		object = CHouse::Create(m_pos, m_scale, m_rot);
		break;

	case 4:
		object = CFild::Create(m_pos, D3DXVECTOR3(1000.0f, 0.0f, 1000.0f), m_rot);
		break;

	case 5:
		object = CBoss::Create(m_pos, m_scale);
		break;

	case 6:
		object = CHitEnemy::Create(m_pos, m_scale);
		break;

	case 7:
		object = CWeaponEnemy::Create(m_pos, m_scale);
		break;

	case 8:
		object = CPole::Create(m_pos, m_scale, m_rot);
		break;

	case 9:
		object = CHouseWhite::Create(m_pos, m_scale, m_rot);
		break;

	case 10:
		object = CShingoki::Create(m_pos, m_scale, m_rot);
		break;

	case 11:
		object = CFence::Create(m_pos, m_scale, m_rot);
		break;

	case 12:
		object = CGarden::Create(m_pos, m_scale, m_rot);
		break;

	case 13:
		object = CConstruction::Create(m_pos, m_scale, m_rot);
		break;

	case 14:
		object = CSchool::Create(m_pos, m_scale, m_rot);
		break;

	case 15:
		object = CBParking::Create(m_pos, m_scale, m_rot);
		break;

	case 16:
		object = CBicycle::Create(m_pos, m_scale, m_rot);
		break;

	case 17:
		object = CBat::Create(m_pos, m_scale, m_rot);
		break;

	case 18:
		object = CPipe::Create(m_pos, m_scale, m_rot);
		break;

	case 19:
		object = CCorridorfloor::Create(m_pos, m_scale, m_rot);
		break;

	case 20:
		object = CCorridorWall::Create(m_pos, m_scale, m_rot);
		break;

	case 21:
		object = CShoerack::Create(m_pos, m_scale, m_rot);
		break;

	case 22:
		object = CCurb::Create(m_pos, D3DXVECTOR3(10.0f, 0.0f, 100.0f), m_rot);
		break;

	case 23:
		object = CRoomDoor::Create(m_pos, m_scale, m_rot);
		break;

	case 24:
		object = CBoard::Create(m_pos, m_scale, m_rot);
		break;

	case 25:
		object = CEntrance::Create(m_pos, m_scale, m_rot);
		break;

	case 26:
		object = CGymfront::Create(m_pos, m_scale, m_rot);
		break;

	case 27:
		object = CGymwall::Create(m_pos, m_scale, m_rot);
		break;

	case 28:
		object = CGymentrance::Create(m_pos, m_scale, m_rot);
		break;
		
	case 29:
		object = CGymwalltop::Create(m_pos, m_scale, m_rot);
		break;

	case 30:
		object = CBasketgoal::Create(m_pos, m_scale, m_rot);
		break;

	case 31:
		object = CJihanki::Create(m_pos, m_scale, m_rot);
		break;

	case 32:
		object = CWall::Create(m_pos, m_scale, m_rot);
		break;
		
	case 33:
		object = CEnemyMovePoint::Create(m_pos, D3DXVECTOR3(10.0f, 0.0f, 10.0f), m_rot);
		break;

	case 34:
		object = CGymDoor::Create(m_pos, m_scale, m_rot);
		break;

	case 35:
		object = CSyokaki::Create(m_pos, m_scale, m_rot);
		break;
		
	case 36:
		object = CStageChangePoint::Create(m_pos, D3DXVECTOR3(10.0f, 0.0f, 10.0f));
		break;

	case 37:
		object = CCone::Create(m_pos, m_scale, m_rot);
		break;

	case 38:
		object = CGymFild::Create(m_pos, D3DXVECTOR3(1000.0f, 0.0f, 1000.0f), m_rot);
		break;
		

	case 39:
		object = CGymCeiling::Create(m_pos, m_scale, m_rot);
		break;
		
	default:
		m_ObjectType = 0;
		object = CBuil::Create(m_pos, m_scale, m_rot);
		break;
	}
	
	

	return object;
}

//==========================
//�I�u�W�F�N�g�̎�ނ�ݒ�
//==========================
void CEdit::ChangeType()
{
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_RIGHTARROW))
	{
		m_ObjectType++;
		m_EditObject->Uninit();
		m_EditObject = nullptr;
		m_EditObject = SetType();//�I�u�W�F�N�g�̎�ނ�ݒ�
	
		if (m_EditMode)
		{//�z�u�ς݃I�u�W�F�N�g��ҏW��

			if (m_Objectite != m_Object.begin())
			{//�ŏ��̃I�u�W�F�N�g����Ȃ�

				m_Objectite--;//�O�̗v�f�Ɉړ�
				m_Object.erase(next(m_Objectite));//���̗v�f���폜
				m_Object.insert(next(m_Objectite), m_EditObject);//�ҏW���̃I�u�W�F�N�g�����ɑ}��
				m_Objectite++;//���̗v�f�Ɉړ�
			}
			else
			{//�ŏ��̃I�u�W�F�N�g�̂Ƃ�

				m_Object.push_front(m_EditObject);//�ŏ��ɕҏW���I�u�W�F�N�g��}��
				m_Objectite--;//�O�̗v�f�Ɉړ�
				m_Object.erase(next(m_Objectite));//���̗v�f���폜
			}
		}
	}
	else if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_LEFTARROW))
	{
		m_ObjectType--;
		m_EditObject->Uninit();
		m_EditObject = nullptr;
		m_EditObject = SetType();//�I�u�W�F�N�g�̎�ނ�ݒ�

		if (m_EditMode)
		{
			if (m_Objectite != m_Object.begin())
			{
				m_Objectite--;
				m_Object.erase(next(m_Objectite));
				m_Object.insert(next(m_Objectite), m_EditObject);
				m_Objectite++;
			}
			else
			{
				m_Object.push_front(m_EditObject);
				m_Objectite--;
				m_Object.erase(next(m_Objectite));
			}
		}
	}
}

//==========================
//����ۑ�
//==========================
void CEdit::KeepInfo()
{
	m_EditObjectKeep.pos = m_EditObject->GetPos();
	m_EditObjectKeep.scale = m_EditObject->GetScale();
	m_EditObjectKeep.rot = m_EditObject->GetRot();
	m_EditObjectKeep.ObjectType = m_ObjectType;

	m_EditObject->Uninit();
	m_EditObject = nullptr;
}

//==========================
//�ҏW���[�h�̐؂�ւ�
//==========================
void CEdit::SwitchEditMode()
{
	if (m_Object.size() <= 0)
	{
		return;
	}

	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_UPARROW))
	{
		if (!m_EditMode)
		{
			m_EditMode = true;
			KeepInfo();//����ۑ�
			m_Objectite = m_Object.begin();
			m_EditObject = *m_Objectite;
			m_pos = m_EditObject->GetPos();
			m_scale = m_EditObject->GetScale();
			m_rot = m_EditObject->GetRot();
		}
		else
		{
			m_EditMode = false;
			m_ObjectType = m_EditObjectKeep.ObjectType;
			m_EditObject = SetType();//�I�u�W�F�N�g�̎�ނ�ݒ�
			m_pos = m_EditObjectKeep.pos;
			m_scale = m_EditObjectKeep.scale;
			m_rot = m_EditObjectKeep.rot;
		}
	}
}

//==========================
//�X�e�[�W��ύX
//==========================
void CEdit::StageChange()
{
	CManager::GetInstance()->GetStageManager()->SetStage();
	
	//���X�g�̑S�ẴI�u�W�F�N�g�폜
	DeleteAll();

	//���̃X�e�[�W���擾
	int Stage = static_cast<int>(CManager::GetInstance()->GetStageManager()->GetStage());

	//�X�e�[�W��ǂݍ���
	Load(Stage);

	CManager::GetInstance()->GetStageManager()->ChangeReset();
}

//==========================
//���X�g�̑S�ẴI�u�W�F�N�g���폜
//==========================
void CEdit::DeleteAll()
{
	m_Objectite = m_Object.begin();

	while (1)
	{
		if (m_Objectite == m_Object.end())
		{
			m_Object.clear();//�v�f��S�č폜
			CObject::ReleaseAll();
			break;
		}

		CObject* obj = *m_Objectite;
		
		obj->Uninit();
		m_Objectite++;
	}
}

//==========================
//�z�u����ǂݍ���
//==========================
void CEdit::Load(int Stage)
{
	FildLoad(Stage);//�t�B�[���h�̏���ǂݍ���
	EnemyLoad(Stage);//�G�̔z�u����ǂݍ���
	BuildingLoad(Stage);//�����̏���ǂݍ���
	WeaponLoad(Stage);//����̏���ǂݍ���
	ItemLoad(Stage);//�A�C�e���̏���ǂݍ���
}

//==========================
//�z�u���������o��5
//==========================
void CEdit::Save(int Stage)
{
	EnemySave(Stage);//�G�̔z�u���������o��
	BuildingSave(Stage);//�����̔z�u���������o��
	WeaponSave(Stage);//����̔z�u���������o��
	FildSave(Stage);//�t�B�[���h�̔z�u���������o��
	ItemSave(Stage);//�A�C�e���z�u���������o��
}

//==========================
//�G�̔z�u����ǂݍ���
//==========================
void CEdit::EnemyLoad(int Stage)
{
	ifstream inputfile;

	switch (Stage)
	{
	case 0:
		inputfile.open("data\\DATAFILE\\EnemyData.txt");//�e�L�X�g�t�@�C�����J��
		break;

	case 1:
		inputfile.open("data\\DATAFILE\\EnemyDataSecond.txt");//�e�L�X�g�t�@�C�����J��
		break;

	case 2:
		inputfile.open("data\\DATAFILE\\EnemyDataLast.txt");//�e�L�X�g�t�@�C�����J��
		break;
	
	default:
		break;
	}
	
	string Data;
	
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 sclse = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	int EnemyType = 0;

	if (inputfile)
	{
		while (getline(inputfile, Data, ':'))//����ǂݍ���
		{
			if (Data.find("END_DATA") != string::npos)
			{
				switch (EnemyType)
				{
				case 1:
					m_Object.push_back(CBoss::Create(pos, sclse));
					break;
				case 2:
					m_Object.push_back(CHitEnemy::Create(pos, sclse));
					break;
				case 3:
					m_Object.push_back(CWeaponEnemy::Create(pos, sclse));
					break;

				default:
					break;
				}
			}
			if (Data.find("pos_x") != string::npos)
			{
				inputfile >> pos.x;
			}
			if (Data.find("pos_y") != string::npos)
			{
				inputfile >> pos.y;
			}
			if (Data.find("pos_z") != string::npos)
			{
				inputfile >> pos.z;
			}
			if (Data.find("enemytype") != string::npos)
			{
				inputfile >> EnemyType;
			}
			if (Data.find("scale_x") != string::npos)
			{
				inputfile >> sclse.x;
			}
			if (Data.find("scale_y") != string::npos)
			{
				inputfile >> sclse.y;
			}
			if (Data.find("scale_z") != string::npos)
			{
				inputfile >> sclse.z;
			}
			Data.clear();
		}

		inputfile.close();//�t�@�C�������
	}
}

//==========================
//�G�̔z�u���������o��
//==========================
void CEdit::EnemySave(int Stage)
{
	CObjectgame* Data = nullptr;

	list<CObjectgame*>::iterator iterator;
	iterator = m_Object.begin();

	ofstream outputfile;//�e�L�X�g�t�@�C�����J��

	switch (Stage)
	{
	case 0:
		outputfile.open("data\\DATAFILE\\EnemyData.txt");//�e�L�X�g�t�@�C�����J��
		break;

	case 1:
		outputfile.open("data\\DATAFILE\\EnemyDataSecond.txt");//�e�L�X�g�t�@�C�����J��
		break;

	case 2:
		outputfile.open("data\\DATAFILE\\EnemyDataLast.txt");//�e�L�X�g�t�@�C�����J��
		break;

	default:
		break;
	}

	if (outputfile)
	{
		while (1)
		{
			if (iterator == m_Object.end())
			{
				break;
			}

			Data = *iterator;

			if (Data->GetType() != CObject::TYPE::ENEMY)
			{
				iterator++;
				continue;
			}
			
			CEnemy* pEnemy = dynamic_cast<CEnemy*>(Data);

			D3DXVECTOR3 pos = pEnemy->GetPos();//�ʒu���擾
			D3DXVECTOR3 scale = pEnemy->GetScale();//�X�P�[�����擾
			int EnemyType = static_cast<int>(pEnemy->GetEnemyType());//�G�̎�ނ��擾

			outputfile << "pos_x:" << pos.x << endl;
			outputfile << "pos_y:" << pos.y << endl;
			outputfile << "pos_z:" << pos.z << endl;
			outputfile << "scale_x:" << scale.x << endl;
			outputfile << "scale_y:" << scale.y << endl;
			outputfile << "scale_z:" << scale.z << endl;
			outputfile << "enemytype:" << EnemyType << endl;

			outputfile << "END_DATA" << endl << endl;

			iterator++;
		}

		outputfile.close();
	}
}

//==========================
//�����̔z�u����ǂݍ���
//==========================
void CEdit::BuildingLoad(int Stage)
{
	ifstream inputfile;

	switch (Stage)
	{
	case 0:
		inputfile.open("data\\DATAFILE\\BuildingData.txt");//�e�L�X�g�t�@�C�����J��
		break;

	case 1:
		inputfile.open("data\\DATAFILE\\BuildingDataSecond.txt");//�e�L�X�g�t�@�C�����J��
		break;

	case 2:
		inputfile.open("data\\DATAFILE\\BuildingDataLast.txt");//�e�L�X�g�t�@�C�����J��
		break;

	default:
		break;
	}

	string Data;

	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 sclse = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	int BuildingType = 0;

	if (inputfile)
	{
		while (getline(inputfile, Data, ':'))//����ǂݍ���
		{
			if (Data.find("END_DATA") != string::npos)
			{
				switch (BuildingType)
				{
				case 1:
					m_Object.push_back(CBuil::Create(pos, sclse, rot));
					break;

				case 2:
					m_Object.push_back(CApartment::Create(pos, sclse, rot));
					break;

				case 3:
					m_Object.push_back(CConveni::Create(pos, sclse, rot));
					break;

				case 4:
					m_Object.push_back(CHouse::Create(pos, sclse, rot));
					break;

				case 5:
					m_Object.push_back(CHouseWhite::Create(pos, sclse, rot));
					break;

				case 6:
					m_Object.push_back(CPole::Create(pos, sclse, rot));
					break;

				case 7:
					m_Object.push_back(CShingoki::Create(pos, sclse, rot));
					break;

				case 8:
					m_Object.push_back(CFence::Create(pos, sclse, rot));
					break;

				case 9:
					m_Object.push_back(CGarden::Create(pos, sclse, rot));
					break;

				case 10:
					m_Object.push_back(CConstruction::Create(pos, sclse, rot));
					break;

				case 11:
					m_Object.push_back(CSchool::Create(pos, sclse, rot));
					break;

				case 12:
					m_Object.push_back(CBParking::Create(pos, sclse, rot));
					break;

				case 13:
					m_Object.push_back(CCorridorfloor::Create(pos, sclse, rot));
					break;

				case 14:
					m_Object.push_back(CCorridorWall::Create(pos, sclse, rot));
					break;

				case 15:
					m_Object.push_back(CShoerack::Create(pos, sclse, rot));
					break;
					
				case 16:
					m_Object.push_back(CRoomDoor::Create(pos, sclse, rot));
					break;

				case 17:
					m_Object.push_back(CBoard::Create(pos, sclse, rot));
					break;

				case 18:
					m_Object.push_back(CEntrance::Create(pos, sclse, rot));
					break;

				case 19:
					m_Object.push_back(CGymfront::Create(pos, sclse, rot));
					break;

				case 20:
					m_Object.push_back(CGymwall::Create(pos, sclse, rot));
					break;

				case 21:
					m_Object.push_back(CGymentrance::Create(pos, sclse, rot));
					break;

				case 22:
					m_Object.push_back(CGymwalltop::Create(pos, sclse, rot));
					break;

				case 23:
					m_Object.push_back(CBasketgoal::Create(pos, sclse, rot));
					break;

				case 24:
					m_Object.push_back(CWall::Create(pos, sclse, rot));
					break;

				case 25:
					m_Object.push_back(CGymDoor::Create(pos, sclse, rot));
					break;

				case 26:
					m_Object.push_back(CGymCeiling::Create(pos, sclse, rot));
					break;
				default:
					break;
				}
			}
			if (Data.find("pos_x") != string::npos)
			{
				inputfile >> pos.x;
			}
			if (Data.find("pos_y") != string::npos)
			{
				inputfile >> pos.y;
			}
			if (Data.find("pos_z") != string::npos)
			{
				inputfile >> pos.z;
			}
			if (Data.find("buildingtype") != string::npos)
			{
				inputfile >> BuildingType;
			}
			if (Data.find("scale_x") != string::npos)
			{
				inputfile >> sclse.x;
			}
			if (Data.find("scale_y") != string::npos)
			{
				inputfile >> sclse.y;
			}
			if (Data.find("scale_z") != string::npos)
			{
				inputfile >> sclse.z;
			}
			if (Data.find("rot_x") != string::npos)
			{
				inputfile >> rot.x;
			}
			if (Data.find("rot_y") != string::npos)
			{
				inputfile >> rot.y;
			}
			if (Data.find("rot_z") != string::npos)
			{
				inputfile >> rot.z;
			}
			Data.clear();
		}

		inputfile.close();//�t�@�C�������
	}
}

//==========================
//�����̔z�u���������o��
//==========================
void CEdit::BuildingSave(int Stage)
{
	CObjectgame* Data = nullptr;

	list<CObjectgame*>::iterator iterator;
	iterator = m_Object.begin();

	ofstream outputfile;//�e�L�X�g�t�@�C�����J��

	switch (Stage)
	{
	case 0:
		outputfile.open("data\\DATAFILE\\BuildingData.txt");//�e�L�X�g�t�@�C�����J��
		break;

	case 1:
		outputfile.open("data\\DATAFILE\\BuildingDataSecond.txt");//�e�L�X�g�t�@�C�����J��
		break;

	case 2:
		outputfile.open("data\\DATAFILE\\BuildingDataLast.txt");//�e�L�X�g�t�@�C�����J��
		break;

	default:
		break;
	}

	if (outputfile)
	{
		while (1)
		{
			if (iterator == m_Object.end())
			{
				break;
			}

			Data = *iterator;

			if (Data->GetType() != CObject::TYPE::BUILDING)
			{
				iterator++;
				continue;
			}

			CBuilding* pBuilding = dynamic_cast<CBuilding*>(Data);

			D3DXVECTOR3 pos = pBuilding->GetPos();//�ʒu���擾
			D3DXVECTOR3 scale = pBuilding->GetScale();//�X�P�[�����擾
			D3DXVECTOR3 rot = pBuilding->GetRot();//�������擾
			int BuildingType = static_cast<int>(pBuilding->GetBuildingType());//�G�̎�ނ��擾

			outputfile << "pos_x:" << pos.x << endl;
			outputfile << "pos_y:" << pos.y << endl;
			outputfile << "pos_z:" << pos.z << endl;
			outputfile << "scale_x:" << scale.x << endl;
			outputfile << "scale_y:" << scale.y << endl;
			outputfile << "scale_z:" << scale.z << endl;
			outputfile << "rot_x:" << rot.x << endl;
			outputfile << "rot_y:" << rot.y << endl;
			outputfile << "rot_z:" << rot.z << endl;
			outputfile << "buildingtype:" << BuildingType << endl;

			outputfile << "END_DATA" << endl << endl;

			iterator++;
		}

		outputfile.close();
	}
}

//==========================
//����̔z�u����ǂݍ���
//==========================
void CEdit::WeaponLoad(int Stage)
{
	ifstream inputfile;

	switch (Stage)
	{
	case 0:
		inputfile.open("data\\DATAFILE\\WeaponData.txt");//�e�L�X�g�t�@�C�����J��
		break;

	case 1:
		inputfile.open("data\\DATAFILE\\WeaponDataSecond.txt");//�e�L�X�g�t�@�C�����J��
		break;

	case 2:
		inputfile.open("data\\DATAFILE\\WeaponDataLast.txt");//�e�L�X�g�t�@�C�����J��
		break;

	default:
		break;
	}

	string Data;

	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 sclse = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	int WeaponType = 0;
	int Type = 0;
	
	if (inputfile)
	{
		while (getline(inputfile, Data, ':'))//����ǂݍ���
		{
			if (Data.find("END_DATA") != string::npos)
			{
				if (WeaponType == 1)
				{
					switch (Type)
					{
					case 1:
						m_Object.push_back(CBicycle::Create(pos, sclse,rot));
						break;
						
					case 2:
						m_Object.push_back(CCone::Create(pos, sclse, rot));
						break;

					default:
						break;
					}
				}
				else
				{
					switch (Type)
					{
					case 1:
						m_Object.push_back(CBat::Create(pos, sclse, rot));
						break;

					case 2:
						m_Object.push_back(CPipe::Create(pos, sclse, rot));
						break;

					case 3:
						m_Object.push_back(CSyokaki::Create(pos, sclse, rot));
						break;

					default:
						break;
					}
				}
			}
			if (Data.find("pos_x") != string::npos)
			{
				inputfile >> pos.x;
			}
			if (Data.find("pos_y") != string::npos)
			{
				inputfile >> pos.y;
			}
			if (Data.find("pos_z") != string::npos)
			{
				inputfile >> pos.z;
			}
			if (Data.find("weapontype") != string::npos)
			{
				inputfile >> WeaponType;
			}
			if (Data.find("Type") != string::npos)
			{
				inputfile >> Type;
			}
			if (Data.find("scale_x") != string::npos)
			{
				inputfile >> sclse.x;
			}
			if (Data.find("scale_y") != string::npos)
			{
				inputfile >> sclse.y;
			}
			if (Data.find("scale_z") != string::npos)
			{
				inputfile >> sclse.z;
			}
			if (Data.find("rot_x") != string::npos)
			{
				inputfile >> rot.x;
			}
			if (Data.find("rot_y") != string::npos)
			{
				inputfile >> rot.y;
			}
			if (Data.find("rot_z") != string::npos)
			{
				inputfile >> rot.z;
			}
			Data.clear();
		}

		inputfile.close();//�t�@�C�������
	}
}

//==========================
//����̔z�u���������o��
//==========================
void CEdit::WeaponSave(int Stage)
{
	CObjectgame* Data = nullptr;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 scale;
	D3DXVECTOR3 rot;
	int type;

	list<CObjectgame*>::iterator iterator;
	iterator = m_Object.begin();

	ofstream outputfile;//�e�L�X�g�t�@�C�����J��

	switch (Stage)
	{
	case 0:
		outputfile.open("data\\DATAFILE\\WeaponData.txt");//�e�L�X�g�t�@�C�����J��
		break;

	case 1:
		outputfile.open("data\\DATAFILE\\WeaponDataSecond.txt");//�e�L�X�g�t�@�C�����J��
		break;

	case 2:
		outputfile.open("data\\DATAFILE\\WeaponDataLast.txt");//�e�L�X�g�t�@�C�����J��
		break;

	default:
		break;
	}

	if (outputfile)
	{
		while (1)
		{
			if (iterator == m_Object.end())
			{
				break;
			}

			Data = *iterator;

			if (Data->GetType() != CObject::TYPE::WEAPON)
			{
				iterator++;
				continue;
			}

			CWeapon* pWeapon = dynamic_cast<CWeapon*>(Data);
			int weapontype = static_cast<int>(pWeapon->GetWeaponType());//����̑傫�����擾

			if (weapontype == 1)
			{
				CBigWeapon* pBigWeapon = dynamic_cast<CBigWeapon*>(pWeapon);
			
				pos = pBigWeapon->GetPos();//�ʒu���擾
				scale = pBigWeapon->GetScale();//�X�P�[�����擾
				rot = pBigWeapon->GetRot();//�������擾
				type = static_cast<int>(pBigWeapon->GetBigWeapon());
			}
			else
			{
				CSmallWeapon*pSmallWeapon= dynamic_cast<CSmallWeapon*>(pWeapon);

				pos = pSmallWeapon->GetPos();//�ʒu���擾
				scale = pSmallWeapon->GetScale();//�X�P�[�����擾
				rot = pSmallWeapon->GetRot();//�������擾
				type = static_cast<int>(pSmallWeapon->GetSmallWeapon());
			}

			outputfile << "pos_x:" << pos.x << endl;
			outputfile << "pos_y:" << pos.y << endl;
			outputfile << "pos_z:" << pos.z << endl;
			outputfile << "scale_x:" << scale.x << endl;
			outputfile << "scale_y:" << scale.y << endl;
			outputfile << "scale_z:" << scale.z << endl;
			outputfile << "rot_x:" << rot.x << endl;
			outputfile << "rot_y:" << rot.y << endl;
			outputfile << "rot_z:" << rot.z << endl;
			outputfile << "weapontype:" << weapontype << endl;
			outputfile << "Type:" << type << endl;
			outputfile << "END_DATA" << endl << endl;

			iterator++;
		}

		outputfile.close();
	}
}

//==========================
//�A�C�e���̔z�u����ǂݍ���
//==========================
void CEdit::ItemLoad(int Stage)
{
	ifstream inputfile;//�e�L�X�g�t�@�C�����J��
	string Data;

	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 sclse = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	int type = 0;

	switch (Stage)
	{
	case 0:
		inputfile.open("data\\DATAFILE\\ItemData.txt");//�e�L�X�g�t�@�C�����J��
		break;

	case 1:
		inputfile.open("data\\DATAFILE\\ItemDataSecond.txt");//�e�L�X�g�t�@�C�����J��
		break;

	case 2:
		inputfile.open("data\\DATAFILE\\ItemDataLast.txt");//�e�L�X�g�t�@�C�����J��
		break;

	default:
		break;
	}

	if (inputfile)
	{
		while (getline(inputfile, Data, ':'))//����ǂݍ���
		{
			if (Data.find("END_DATA") != string::npos)
			{
				m_Object.push_back(CJihanki::Create(pos, sclse, rot));
			}
			if (Data.find("pos_x") != string::npos)
			{
				inputfile >> pos.x;
			}
			if (Data.find("pos_y") != string::npos)
			{
				inputfile >> pos.y;
			}
			if (Data.find("pos_z") != string::npos)
			{
				inputfile >> pos.z;
			}
			if (Data.find("scale_x") != string::npos)
			{
				inputfile >> sclse.x;
			}
			if (Data.find("scale_y") != string::npos)
			{
				inputfile >> sclse.y;
			}
			if (Data.find("scale_z") != string::npos)
			{
				inputfile >> sclse.z;
			}
			if (Data.find("rot_x") != string::npos)
			{
				inputfile >> rot.x;
			}
			if (Data.find("rot_y") != string::npos)
			{
				inputfile >> rot.y;
			}
			if (Data.find("rot_z") != string::npos)
			{
				inputfile >> rot.z;
			}
			if (Data.find("type") != string::npos)
			{
				inputfile >> type;
			}
			Data.clear();
		}

		inputfile.close();//�t�@�C�������
	}

}

//==========================
//�A�C�e���̔z�u���������o��
//==========================
void CEdit::ItemSave(int Stage)
{
	ofstream outputfile;
	CObjectgame* Data = nullptr;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 scale;
	D3DXVECTOR3 rot;

	list<CObjectgame*>::iterator iterator;
	iterator = m_Object.begin();

	switch (Stage)
	{
	case 0:
		outputfile.open("data\\DATAFILE\\ItemData.txt");//�e�L�X�g�t�@�C�����J��
		break;

	case 1:
		outputfile.open("data\\DATAFILE\\ItemDataSecond.txt");//�e�L�X�g�t�@�C�����J��
		break;

	case 2:
		outputfile.open("data\\DATAFILE\\ItemDataLast.txt");//�e�L�X�g�t�@�C�����J��
		break;

	default:
		break;
	}


	if (outputfile)
	{
		while (1)
		{
			if (iterator == m_Object.end())
			{
				break;
			}

			Data = *iterator;

			if (Data->GetType() != CObject::TYPE::JIHANKI)
			{
				iterator++;
				continue;
			}

			CJihanki* pJihan = dynamic_cast<CJihanki*>(Data);

			pos = pJihan->GetPos();//�ʒu���擾
			scale = pJihan->GetScale();
			rot = pJihan->GetRot();

			outputfile << "pos_x:" << pos.x << endl;
			outputfile << "pos_y:" << pos.y << endl;
			outputfile << "pos_z:" << pos.z << endl;
			outputfile << "scale_x:" << scale.x << endl;
			outputfile << "scale_y:" << scale.y << endl;
			outputfile << "scale_z:" << scale.z << endl;
			outputfile << "rot_x:" << rot.x << endl;
			outputfile << "rot_y:" << rot.y << endl;
			outputfile << "rot_z:" << rot.z << endl;
			outputfile << "END_DATA" << endl << endl;

			iterator++;
		}

		outputfile.close();
	}
}

//==========================
//�t�B�[���h�̔z�u����ǂݍ���
//==========================
void CEdit::FildLoad(int Stage)
{

	ifstream inputfile;//�e�L�X�g�t�@�C�����J��
	string Data;

	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 sclse = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	int type = 0;

	switch (Stage)
	{
	case 0:
		inputfile.open("data\\DATAFILE\\FildData.txt");//�e�L�X�g�t�@�C�����J��
		break;

	case 1:
		inputfile.open("data\\DATAFILE\\FildDataSecond.txt");//�e�L�X�g�t�@�C�����J��
		break;

	case 2:
		inputfile.open("data\\DATAFILE\\FildDataLast.txt");//�e�L�X�g�t�@�C�����J��
		break;

	default:
		break;
	}

	if (inputfile)
	{
		while (getline(inputfile, Data, ':'))//����ǂݍ���
		{
			if (Data.find("END_DATA") != string::npos)
			{
				switch (type)
				{
				case 1:
					m_Object.push_back(CFild::Create(pos, sclse, rot));
					break;

				case 2:
					m_Object.push_back(CCurb::Create(pos, sclse, rot));
					break;

				case 3:
					m_Object.push_back(CEnemyMovePoint::Create(pos, sclse, rot));
					break;

				case 4:
					m_Object.push_back(CStageChangePoint::Create(pos, sclse));
					break;

				case 5:
					m_Object.push_back(CGymFild::Create(pos, sclse,rot));
					break;

				default:
					break;
				}
				
			}
			if (Data.find("pos_x") != string::npos)
			{
				inputfile >> pos.x;
			}
			if (Data.find("pos_y") != string::npos)
			{
				inputfile >> pos.y;
			}
			if (Data.find("pos_z") != string::npos)
			{
				inputfile >> pos.z;
			}
			if (Data.find("scale_x") != string::npos)
			{
				inputfile >> sclse.x;
			}
			if (Data.find("scale_y") != string::npos)
			{
				inputfile >> sclse.y;
			}
			if (Data.find("scale_z") != string::npos)
			{
				inputfile >> sclse.z;
			}
			if (Data.find("rot_x") != string::npos)
			{
				inputfile >> rot.x;
			}
			if (Data.find("rot_y") != string::npos)
			{
				inputfile >> rot.y;
			}
			if (Data.find("rot_z") != string::npos)
			{
				inputfile >> rot.z;
			}
			if (Data.find("type") != string::npos)
			{
				inputfile >> type;
			}
			Data.clear();
		}

		inputfile.close();//�t�@�C�������
	}
}

//==========================
//�t�B�[���h�̔z�u���������o��
//==========================
void CEdit::FildSave(int Stage)
{
	ofstream outputfile;
	CObjectgame* Data = nullptr;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 scale;
	D3DXVECTOR3 rot;

	list<CObjectgame*>::iterator iterator;
	iterator = m_Object.begin();

	switch (Stage)
	{
	case 0:
		outputfile.open("data\\DATAFILE\\FildData.txt");//�e�L�X�g�t�@�C�����J��
		break;

	case 1:
		outputfile.open("data\\DATAFILE\\FildDataSecond.txt");//�e�L�X�g�t�@�C�����J��
		break;

	case 2:
		outputfile.open("data\\DATAFILE\\FildDataLast.txt");//�e�L�X�g�t�@�C�����J��
		break;

	default:
		break;
	}
	

	if (outputfile)
	{
		while (1)
		{
			if (iterator == m_Object.end())
			{
				break;
			}

			Data = *iterator;

			if (Data->GetType() != CObject::TYPE::FILD)
			{
				iterator++;
				continue;
			}

			CFild* pFild = dynamic_cast<CFild*>(Data);

			pos = pFild->GetPos();//�ʒu���擾
			scale = D3DXVECTOR3(1000.0f, 0.0f, 1000.0f);
			int fildtype = static_cast<int>(pFild->GetFildType());
			rot = pFild->GetRot();

			if (fildtype != 1)
			{
				scale = D3DXVECTOR3(10.0f, 0.0f, 100.0f);
			}
			if (fildtype == 3)
			{
				scale = D3DXVECTOR3(10.0f, 0.0f, 10.0f);
			}
			if (fildtype == 5)
			{
				scale = D3DXVECTOR3(1000.0f, 0.0f, 1000.0f);
			}
			outputfile << "pos_x:" << pos.x << endl;
			outputfile << "pos_y:" << pos.y << endl;
			outputfile << "pos_z:" << pos.z << endl;
			outputfile << "scale_x:" << scale.x << endl;
			outputfile << "scale_y:" << scale.y << endl;
			outputfile << "scale_z:" << scale.z << endl;
			outputfile << "rot_x:" << rot.x << endl;
			outputfile << "rot_y:" << rot.y << endl;
			outputfile << "rot_z:" << rot.z << endl;
			outputfile << "type:" << fildtype << endl;
			outputfile << "END_DATA" << endl << endl;

			iterator++;
		}

		outputfile.close();
	}
}