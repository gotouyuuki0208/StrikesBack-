//==========================
// 
// �X�e�[�W�Ǘ�[stagemanager.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"stagemanager.h"
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
#include"corridorExit.h"
#include"corridorceiling.h"
#include"illumination.h"
#include"sky.h"

//==========================
//�R���X�g���N�^
//==========================
CStageManager::CStageManager():
m_Stage(STAGE::STAGE_FIRST),
m_Change(false),//�X�e�[�W�؂�ւ�蔻��
m_DarkBg(nullptr),//�Ó]���邽�߂̍��|���S��
m_Rast(0),//�ŏI�X�e�[�W�̔ԍ�
m_player(nullptr),//�v���C���[�̏��
m_PlalyerHPGauge(nullptr),//�v���C���[��HP�Q�[�W�̏��
m_playerlife(0)
{
	m_Rast = static_cast<int>(STAGE::STAGE_BOSS);
	m_DarkBg = CDarkBg::Create();

	m_Obj.clear();
}

//==========================
//�f�X�g���N�^
//==========================
CStageManager::~CStageManager()
{
	
}

//==========================
//�I������
//==========================
void CStageManager::Uninit()
{
	if (m_DarkBg != nullptr)
	{
		m_DarkBg->CObject2D::Uninit();
		delete m_DarkBg;
		m_DarkBg = nullptr;
	}

	m_player = nullptr;
	m_PlalyerHPGauge = nullptr;

	m_Obj.clear();
}

//==========================
//�X�e�[�W��ݒ�
//==========================
void CStageManager::SetStage()
{
	int stage = static_cast<int>(m_Stage);

	if (stage >= m_Rast)
	{
		stage = -1;
	}

	m_Stage = static_cast<STAGE>(stage + 1);
	m_Change = true;
	m_DarkBg->SetFade();
}

//==========================
//�X�e�[�W���擾
//==========================
CStageManager::STAGE CStageManager::GetStage()
{
	return m_Stage;
}

//==========================
//�؂�ւ�蔻����擾
//==========================
bool CStageManager::GetChange()
{
	return m_Change;
}

//==========================
//�؂�ւ�蔻������Z�b�g
//==========================
void CStageManager::ChangeReset()
{
	m_Change = false;
}

//==========================
//�I�u�W�F�N�g�ύX�^�C�~���O
//==========================
bool CStageManager::ChangeObject()
{
	if (m_DarkBg->GetCor() >= 1.0f)
	{
		return true;
	}

	return false;
}

//==========================
//�X�e�[�W�����Z�b�g
//==========================
void CStageManager::StageReset()
{
	m_Obj.clear();
	m_Stage = STAGE::STAGE_FIRST;
}

//==========================
//�v���C���[��HP�Q�[�W�̍X�V
//==========================
void CStageManager::HPGaugeUpdate()
{
	m_PlalyerHPGauge->SetHP(m_player->GetLife());
}

//==========================
//�X�e�[�W�̐؂�ւ�
//==========================
void CStageManager::ChangeStage()
{
	CGameManager* pGemeManeger = CManager::GetInstance()->GetGameManager();

	if (GetChange()&&ChangeObject())
	{//�X�e�[�W���؂�ւ���Ă�Ƃ�

		//�X�e�[�W�𐶐�
		DeleteAll();//�S�ẴI�u�W�F�N�g���폜
		Load();//�I�u�W�F�N�g��ǂݍ���
		CManager::GetInstance()->GetCamera()->Init();//�J�����̏���������

		//���݂̃X�e�[�W���擾
		int StageNum = static_cast<int>(GetStage());

		if (StageNum == 2)
		{
			//pGemeManeger->SetDirection();//���o���J�n
			pGemeManeger->SetChange();
			pGemeManeger->GetBossInfo();//�{�X�̏����擾
			m_player->SetPos(D3DXVECTOR3(-736.0f, 0.0f, 600.0f));//�v���C���[�̈ʒu��ύX
			m_player->SetPosOld(D3DXVECTOR3(0.0f, 0.0f, 0.0f));//�v���C���[�̑O��̈ʒu��ύX
		}
		else
		{
			m_player->SetPos(D3DXVECTOR3(0.0f, 0.0f, 100.0f));//�v���C���[�̈ʒu��ύX
			m_player->SetPosOld(D3DXVECTOR3(0.0f, 0.0f, 0.0f));//�v���C���[�̑O��̈ʒu��ύX
		}

		m_player->DeleteWeapon();//�����Ă��镐�������
		m_player->SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));//�v���C���[�̌�����ύX

		ChangeReset();
	}
}

//==========================
//�S�ẴI�u�W�F�N�g���폜
//==========================
void CStageManager::DeleteAll()
{
	//���X�g�̍ŏ��̗v�f���擾
	m_ObjIte = m_Obj.begin();

	while (1)
	{
		if (m_ObjIte == m_Obj.end())
		{
			m_Obj.clear();//�v�f��S�č폜
			break;
		}

		CObject* obj = *m_ObjIte;

		if (obj != nullptr)
		{
			obj->Uninit();
		}

		m_ObjIte++;
	}
}

//==========================
//�I�u�W�F�N�g���폜
//==========================
void CStageManager::DeleteObj(CObjectgame& obj)
{
	//���X�g�̍ŏ��̗v�f���擾
	list<CObjectgame*>::iterator Ite = m_Obj.begin();

	while (1)
	{
		if (Ite == m_Obj.end())
		{
			break;
		}

		CObject* Obj = *Ite;

		if (Obj == &obj)
		{
			Ite = m_Obj.erase(Ite);
			break;
		}
		else
		{
			Ite++;
		}
	}
}

//==========================
//�X�e�[�W�̓ǂݍ���
//==========================
void CStageManager::Load()
{
	if (m_Stage == STAGE::STAGE_FIRST)
	{
		CSky::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2000.0f, 2000.0f, 2000.0f));
		m_player = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f));
		m_PlalyerHPGauge = CPlayerHPGauge::Create(D3DXVECTOR3(10.0f, 20.0f, 0.0f), 10, 300, m_player->GetLife());
	}

	FildLoad();//�t�B�[���h�̏���ǂݍ���
	//EnemyLoad();//�G�̏���ǂݍ���
	WeaponLoad();//����̏���ǂݍ���
	BuildingLoad();//�����̏���ǂݍ���
	ItemLoad();//�A�C�e���̏���ǂݍ���
}

//==========================
//�t�B�[���h�̏���ǂݍ���
//==========================
void CStageManager::FildLoad()
{
	ifstream inputfile;//�e�L�X�g�t�@�C�����J��
	string Data;
	int stage = static_cast<int>(m_Stage);

	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 sclse = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	int type = 0;

	switch (stage)
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
					m_Obj.push_back(CFild::Create(pos, sclse, rot));
					break;

				case 2:
					m_Obj.push_back(CCurb::Create(pos, sclse, rot));
					break;

				case 3:
					m_Obj.push_back(CEnemyMovePoint::Create(pos, sclse, rot));
					break;

				case 4:
					m_Obj.push_back(CStageChangePoint::Create(pos, sclse));
					break;

				case 5:
					m_Obj.push_back(CGymFild::Create(pos, sclse, rot));
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
//�G�̔z�u����ǂݍ���
//==========================
void CStageManager::EnemyLoad()
{
	ifstream inputfile;
	int stage = static_cast<int>(m_Stage);

	switch (stage)
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
					m_Obj.push_back(CBoss::Create(pos, sclse));
					break;
				case 2:
					m_Obj.push_back(CHitEnemy::Create(pos, sclse));
					break;
				case 3:
					m_Obj.push_back(CWeaponEnemy::Create(pos, sclse));
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
//�����̏���ǂݍ���
//==========================
void CStageManager::BuildingLoad()
{
	ifstream inputfile;
	int stage = static_cast<int>(m_Stage);

	switch (stage)
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
					m_Obj.push_back(CBuil::Create(pos, sclse, rot));
					break;

				case 2:
					m_Obj.push_back(CApartment::Create(pos, sclse, rot));
					break;

				case 3:
					m_Obj.push_back(CConveni::Create(pos, sclse, rot));
					break;

				case 4:
					m_Obj.push_back(CHouse::Create(pos, sclse, rot));
					break;

				case 5:
					m_Obj.push_back(CHouseWhite::Create(pos, sclse, rot));
					break;

				case 6:
					m_Obj.push_back(CPole::Create(pos, sclse, rot));
					break;

				case 7:
					m_Obj.push_back(CShingoki::Create(pos, sclse, rot));
					break;

				case 8:
					m_Obj.push_back(CFence::Create(pos, sclse, rot));
					break;

				case 9:
					m_Obj.push_back(CGarden::Create(pos, sclse, rot));
					break;

				case 10:
					m_Obj.push_back(CConstruction::Create(pos, sclse, rot));
					break;

				case 11:
					m_Obj.push_back(CSchool::Create(pos, sclse, rot));
					break;

				case 12:
					m_Obj.push_back(CBParking::Create(pos, sclse, rot));
					break;

				case 13:
					m_Obj.push_back(CCorridorfloor::Create(pos, sclse, rot));
					break;

				case 14:
					m_Obj.push_back(CCorridorWall::Create(pos, sclse, rot));
					break;

				case 15:
					m_Obj.push_back(CShoerack::Create(pos, sclse, rot));
					break;

				case 16:
					m_Obj.push_back(CRoomDoor::Create(pos, sclse, rot));
					break;

				case 17:
					m_Obj.push_back(CBoard::Create(pos, sclse, rot));
					break;

				case 18:
					m_Obj.push_back(CEntrance::Create(pos, sclse, rot));
					break;

				case 19:
					m_Obj.push_back(CGymfront::Create(pos, sclse, rot));
					break;

				case 20:
					m_Obj.push_back(CGymwall::Create(pos, sclse, rot));
					break;

				case 21:
					m_Obj.push_back(CGymentrance::Create(pos, sclse, rot));
					break;

				case 22:
					m_Obj.push_back(CGymwalltop::Create(pos, sclse, rot));
					break;

				case 23:
					m_Obj.push_back(CBasketgoal::Create(pos, sclse, rot));
					break;

				case 24:
					m_Obj.push_back(CWall::Create(pos, sclse, rot));
					break;

				case 25:
					m_Obj.push_back(CGymDoor::Create(pos, sclse, rot));
					break;

				case 26:
					m_Obj.push_back(CGymCeiling::Create(pos, sclse, rot));
					break;
				
				case 27:
					m_Obj.push_back(CCorridorExit::Create(pos, sclse, rot));
					break;
				
				case 28:
					m_Obj.push_back(CCorridorceiling::Create(pos, sclse, rot));
					break;

				case 29:
					m_Obj.push_back(CIllumination::Create(pos, sclse, rot));
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
//����̏���ǂݍ���
//==========================
void CStageManager::WeaponLoad()
{
	ifstream inputfile;
	int stage = static_cast<int>(m_Stage);

	switch (stage)
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
						m_Obj.push_back(CBicycle::Create(pos, sclse, rot));
						break;

					case 2:
						m_Obj.push_back(CCone::Create(pos, sclse, rot));
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
						m_Obj.push_back(CBat::Create(pos, sclse, rot));
						break;

					case 2:
						m_Obj.push_back(CPipe::Create(pos, sclse, rot));
						break;

					case 3:
						m_Obj.push_back(CSyokaki::Create(pos, sclse, rot));
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
//�A�C�e���̏���ǂݍ���
//==========================
void CStageManager::ItemLoad()
{
	ifstream inputfile;//�e�L�X�g�t�@�C�����J��
	string Data;

	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 sclse = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	int type = 0;
	int stage = static_cast<int>(m_Stage);

	switch (stage)
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
				m_Obj.push_back(CJihanki::Create(pos, sclse, rot));
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