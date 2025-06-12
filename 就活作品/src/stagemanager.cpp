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
#include"player.h"
#include"darkbg.h"
#include"wavewall.h"
using json = nlohmann::json;

//==========================
//�R���X�g���N�^
//==========================
CStageManager::CStageManager():
m_Stage(STAGE::STAGE_FIRST),//�X�e�[�W�̔ԍ�
m_Change(false),//�X�e�[�W�؂�ւ�蔻��
m_DarkBg(nullptr),//�Ó]���邽�߂̍��|���S��
m_Rast(0),//�ŏI�X�e�[�W�̔ԍ�
m_player(nullptr)//�v���C���[�̏��
{
	//�ŏI�X�e�[�W�̔ԍ�
	m_Rast = static_cast<int>(STAGE::STAGE_BOSS);

	//�Ó]�̂��߂̍��|���S���𐶐�
	m_DarkBg = CDarkBg::Create();

	//���X�g��������
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
	{//���|���S�����폜

		m_DarkBg->CObject2D::Uninit();
		delete m_DarkBg;
		m_DarkBg = nullptr;
	}

	//�v���C���[�̏�������
	m_player = nullptr;

	//���X�g���폜
	m_Obj.clear();
}

//==========================
//�X�e�[�W��ݒ�
//==========================
void CStageManager::SetStage()
{
	//���݂̃X�e�[�W�ԍ����擾
	int stage = static_cast<int>(m_Stage);

	if (stage >= m_Rast)
	{//�X�e�[�W�ԍ����ŏI�X�e�[�W

		stage = 0;
	}

	//�X�e�[�W�����̃X�e�[�W�ɕύX
	m_Stage = static_cast<STAGE>(stage + 1);

	//�X�e�[�W�̐؂�ւ�蔻��
	m_Change = true;

	//�t�F�[�h���J�n
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
	if (m_DarkBg->GetCol() >= 1.0f)
	{//��ʂ����S�ɈÂ�

		return true;
	}

	return false;
}

//==========================
//�X�e�[�W�����Z�b�g
//==========================
void CStageManager::StageReset()
{
	//�o�^����Ă���I�u�W�F�N�g�̏�������
	m_Obj.clear();

	//���݂̃X�e�[�W���X�e�[�W1�ɖ߂�
	m_Stage = STAGE::STAGE_FIRST;
}

//==========================
//�X�e�[�W�̐؂�ւ�
//==========================
void CStageManager::ChangeStage()
{
	
	if (GetChange()&&ChangeObject())
	{//�X�e�[�W���؂�ւ���Ă��ĉ�ʂ��Â��Ȃ��Ă�

		//�Q�[���}�l�[�W���[�̏����擾
		CGameManager* pGemeManeger = CManager::GetInstance()->GetGameManager();

		//�J�����̏����擾
		CCamera* pCamera = CManager::GetInstance()->GetCamera();

		//�X�e�[�W�𐶐�
		DeleteAll();//�S�ẴI�u�W�F�N�g���폜
		Load();//�I�u�W�F�N�g��ǂݍ���

		//�J�����̏���������
		pCamera->Init();

		//���݂̃X�e�[�W���擾
		int StageNum = static_cast<int>(GetStage());

		if (StageNum == 3)
		{//�{�X�X�e�[�W�̎�

			pGemeManeger->SetDirection();//���o���ɕύX
			m_player->SetPos({ -736.0f, 0.0f, 600.0f });//�v���C���[�̈ʒu��ύX
			m_player->SetPosOld({ 0.0f, 0.0f, 0.0f });//�v���C���[�̑O��̈ʒu��ύX
		}
		else
		{//�X�e�[�W2
			m_player->SetPos({ 0.0f, 0.0f, 100.0f });//�v���C���[�̈ʒu��ύX
			m_player->SetPosOld({ 0.0f, 0.0f, 0.0f });//�v���C���[�̑O��̈ʒu��ύX
		}

		//�����Ă��镐�������
		m_player->DeleteWeapon();
		
		//�X�e�[�g�̕ύX
		m_player->StageChangeState();
		
		//�v���C���[�̌�����ύX
		m_player->SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));

		//�؂�ւ�蔻������Z�b�g
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

	for (list<CObjectgame*>::iterator Ite = m_Obj.begin(); Ite != m_Obj.end(); Ite++)
	{
		CObject* obj = *Ite;

		if (obj != nullptr)
		{
			obj->Uninit();
		}
	}
	
	m_Obj.clear();//�v�f��S�č폜
}

//==========================
//�I�u�W�F�N�g���폜
//==========================
void CStageManager::DeleteObj(CObjectgame& obj)
{
	for (list<CObjectgame*>::iterator Ite = m_Obj.begin(); Ite != m_Obj.end(); Ite++)
	{
		CObject* Obj = *Ite;

		if (Obj == &obj)
		{
			Ite = m_Obj.erase(Ite);
			break;
		}
	}
}

//==========================
//�X�e�[�W�̓ǂݍ���
//==========================
void CStageManager::Load()
{
	if (m_Stage == STAGE::STAGE_FIRST)
	{//�ŏ��̃X�e�[�W

		//��ƃv���C���[�𐶐�
		CSky::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2000.0f, 2000.0f, 2000.0f));
		m_player = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f));
	}

	JsonFildLoad();		//�t�B�[���h�̏���ǂݍ���
	JsonEnemyLoad();	//�G�̏���ǂݍ���
	JsonWeaponLoad();	//����̏���ǂݍ���
	JsonBuildingLoad();	//�����̏���ǂݍ���
	JsonItemLoad();		//�A�C�e���̏���ǂݍ���
}

//==========================
//�����̔z�u����ǂݍ���
//==========================
void CStageManager::JsonBuildingLoad()
{
	D3DXVECTOR3 pos, scale, rot;
	int type,wave;
	ifstream inputfile;

	//�X�e�[�W���擾
	int Stage = static_cast<int>(CManager::GetInstance()->GetStageManager()->GetStage());

	std::string filename = "Building" + std::to_string(Stage) + ".json";
	std::string filepath = "data\\DATAFILE\\" + filename;

	inputfile.open(filepath);//�e�L�X�g�t�@�C�����J��
	json jsonarray;
	inputfile >> jsonarray;

	for (const auto& JsonData : jsonarray)
	{
		//�ǂݍ��񂾃f�[�^�����ꂼ��̕ϐ��ɑ������
		pos.x = JsonData["POS"].value("x",0.0f);
		pos.y = JsonData["POS"].value("y",0.0f);
		pos.z = JsonData["POS"].value("z",0.0f);
		rot.x = JsonData["ROT"].value("x",0.0f);
		rot.y = JsonData["ROT"].value("y",0.0f);
		rot.z = JsonData["ROT"].value("z",0.0f);
		scale.x = JsonData["SCALE"].value("x",0.0f);
		scale.y = JsonData["SCALE"].value("y",0.0f);
		scale.z = JsonData["SCALE"].value("z",0.0f);
		type = JsonData["TYPE"].value("type", 0.0f);

		if (JsonData.contains("WAVE"))
		{
			wave = JsonData["WAVE"].value("wave", 0.0f);
		}

		switch (type)
		{
		case 1:
			m_Obj.push_back(CBuil::Create(pos, scale, rot));
			break;

		case 2:
			m_Obj.push_back(CApartment::Create(pos, scale, rot));
			break;

		case 3:
			m_Obj.push_back(CConveni::Create(pos, scale, rot));
			break;

		case 4:
			m_Obj.push_back(CHouse::Create(pos, scale, rot));
			break;

		case 5:
			m_Obj.push_back(CHouseWhite::Create(pos, scale, rot));
			break;

		case 6:
			m_Obj.push_back(CPole::Create(pos, scale, rot));
			break;

		case 7:
			m_Obj.push_back(CShingoki::Create(pos, scale, rot));
			break;

		case 8:
			m_Obj.push_back(CFence::Create(pos, scale, rot));
			break;

		case 9:
			m_Obj.push_back(CGarden::Create(pos, scale, rot));
			break;

		case 10:
			m_Obj.push_back(CConstruction::Create(pos, scale, rot));
			break;

		case 11:
			m_Obj.push_back(CSchool::Create(pos, scale, rot));
			break;

		case 12:
			m_Obj.push_back(CBParking::Create(pos, scale, rot));
			break;

		case 13:
			m_Obj.push_back(CCorridorfloor::Create(pos, scale, rot));
			break;

		case 14:
			m_Obj.push_back(CCorridorWall::Create(pos, scale, rot));
			break;

		case 15:
			m_Obj.push_back(CShoerack::Create(pos, scale, rot));
			break;

		case 16:
			m_Obj.push_back(CRoomDoor::Create(pos, scale, rot));
			break;

		case 17:
			m_Obj.push_back(CBoard::Create(pos, scale, rot));
			break;

		case 18:
			m_Obj.push_back(CEntrance::Create(pos, scale, rot));
			break;

		case 19:
			m_Obj.push_back(CGymfront::Create(pos, scale, rot));
			break;

		case 20:
			m_Obj.push_back(CGymwall::Create(pos, scale, rot));
			break;

		case 21:
			m_Obj.push_back(CGymentrance::Create(pos, scale, rot));
			break;

		case 22:
			m_Obj.push_back(CGymwalltop::Create(pos, scale, rot));
			break;

		case 23:
			m_Obj.push_back(CBasketgoal::Create(pos, scale, rot));
			break;

		case 24:
			m_Obj.push_back(CWall::Create(pos, scale, rot));
			break;

		case 25:
			m_Obj.push_back(CGymDoor::Create(pos, scale, rot));
			break;

		case 26:
			m_Obj.push_back(CGymCeiling::Create(pos, scale, rot));
			break;

		case 27:
			m_Obj.push_back(CCorridorExit::Create(pos, scale, rot));
			break;

		case 28:
			m_Obj.push_back(CCorridorceiling::Create(pos, scale, rot));
			break;

		case 29:
			m_Obj.push_back(CIllumination::Create(pos, scale, rot));
			break;

		case 30:
			m_Obj.push_back(CWaveWall::Create(pos, scale, rot, wave));
			break;

		default:
			break;
		}
	}

	inputfile.close();
}

//==========================
//�A�C�e���̔z�u����ǂݍ���
//==========================
void CStageManager::JsonItemLoad()
{
	D3DXVECTOR3 pos, scale, rot;
	ifstream inputfile;

	//�X�e�[�W���擾
	int Stage = static_cast<int>(CManager::GetInstance()->GetStageManager()->GetStage());

	std::string filename = "Item" + std::to_string(Stage) + ".json";
	std::string filepath = "data\\DATAFILE\\" + filename;

	inputfile.open(filepath);//�e�L�X�g�t�@�C�����J��
	json jsonarray;
	inputfile >> jsonarray;

	for (const auto& JsonData : jsonarray)
	{
		//�ǂݍ��񂾃f�[�^�����ꂼ��̕ϐ��ɑ������
		pos.x = JsonData["POS.x"].get<float>();
		pos.y = JsonData["POS.y"].get<float>();
		pos.z = JsonData["POS.z"].get<float>();
		rot.x = JsonData["ROT.x"].get<float>();
		rot.y = JsonData["ROT.y"].get<float>();
		rot.z = JsonData["ROT.z"].get<float>();
		scale.x = JsonData["SCALE.x"].get<float>();
		scale.y = JsonData["SCALE.y"].get<float>();
		scale.z = JsonData["SCALE.z"].get<float>();


		m_Obj.push_back(CJihanki::Create(pos, scale, rot));
	}

	inputfile.close();
}

//==========================
//����̔z�u����ǂݍ���
//==========================
void CStageManager::JsonWeaponLoad()
{
	//�X�e�[�W���擾
	int Stage = static_cast<int>(CManager::GetInstance()->GetStageManager()->GetStage());

	D3DXVECTOR3 pos, scale, rot;
	int type, weapontype;
	ifstream inputfile;

	std::string filename = "Weapon" + std::to_string(Stage) + ".json";
	std::string filepath = "data\\DATAFILE\\" + filename;

	inputfile.open(filepath);//�e�L�X�g�t�@�C�����J��
	json jsonarray;
	inputfile >> jsonarray;

	for (const auto& JsonData : jsonarray)
	{
		//�ǂݍ��񂾃f�[�^�����ꂼ��̕ϐ��ɑ������
		pos.x = JsonData["POS.x"].get<float>();
		pos.y = JsonData["POS.y"].get<float>();
		pos.z = JsonData["POS.z"].get<float>();
		rot.x = JsonData["ROT.x"].get<float>();
		rot.y = JsonData["ROT.y"].get<float>();
		rot.z = JsonData["ROT.z"].get<float>();
		scale.x = JsonData["SCALE.x"].get<float>();
		scale.y = JsonData["SCALE.y"].get<float>();
		scale.z = JsonData["SCALE.z"].get<float>();
		type = JsonData["TYPE"].get<int>();
		weapontype = JsonData["WEAPONTYPE"].get<int>();

		if (weapontype == 1)
		{
			switch (type)
			{
			case 1:
				m_Obj.push_back(CBicycle::Create(pos, scale, rot));
				break;

			case 2:
				m_Obj.push_back(CCone::Create(pos, scale, rot));
				break;

			default:
				break;
			}
		}
		else
		{
			switch (type)
			{
			case 1:
				m_Obj.push_back(CBat::Create(pos, scale, rot));
				break;

			case 2:
				m_Obj.push_back(CPipe::Create(pos, scale, rot));
				break;

			case 3:
				m_Obj.push_back(CSyokaki::Create(pos, scale, rot));
				break;

			default:
				break;
			}
		}
	}

	inputfile.close();
}

//==========================
//�G�̔z�u����ǂݍ���
//==========================
void CStageManager::JsonEnemyLoad()
{
	//�X�e�[�W���擾
	int Stage = static_cast<int>(CManager::GetInstance()->GetStageManager()->GetStage());

	D3DXVECTOR3 pos, scale, rot;
	int type,wave;
	ifstream inputfile;

	std::string filename = "Enemy" + std::to_string(Stage) + ".json";
	std::string filepath = "data\\DATAFILE\\" + filename;

	inputfile.open(filepath);//�e�L�X�g�t�@�C�����J��
	json jsonarray;
	inputfile >> jsonarray;

	for (const auto& JsonData : jsonarray)
	{
		//�ǂݍ��񂾃f�[�^�����ꂼ��̕ϐ��ɑ������
		pos.x = JsonData["POS.x"].get<float>();
		pos.y = JsonData["POS.y"].get<float>();
		pos.z = JsonData["POS.z"].get<float>();
		scale.x = JsonData["SCALE.x"].get<float>();
		scale.y = JsonData["SCALE.y"].get<float>();
		scale.z = JsonData["SCALE.z"].get<float>();
		type = JsonData["TYPE"].get<int>();
		wave = JsonData["WAVE"].get<int>();
		switch (type)
		{
		case 1:
			m_Obj.push_back(CBoss::Create(pos, scale));
			break;
		case 2:
			m_Obj.push_back(CHitEnemy::Create(pos, scale, wave));
			break;
		case 3:
			m_Obj.push_back(CWeaponEnemy::Create(pos, scale));
			break;

		default:
			break;
		}
	}

	inputfile.close();
}

//==========================
//�t�B�[���h�̔z�u����ǂݍ���
//==========================
void CStageManager::JsonFildLoad()
{
	//�X�e�[�W���擾
	int Stage = static_cast<int>(CManager::GetInstance()->GetStageManager()->GetStage());
	D3DXVECTOR3 pos, scale, rot;
	int type;
	ifstream inputfile;
	std::string filename = "Fild" + std::to_string(Stage) + ".json";
	std::string filepath = "data\\DATAFILE\\" + filename;
	inputfile.open(filepath);//�e�L�X�g�t�@�C�����J��
	json jsonarray;
	inputfile >> jsonarray;

	for (const auto& JsonData : jsonarray)
	{
		//�ǂݍ��񂾃f�[�^�����ꂼ��̕ϐ��ɑ������
		pos.x = JsonData["POS.x"].get<float>();
		pos.y = JsonData["POS.y"].get<float>();
		pos.z = JsonData["POS.z"].get<float>();
		rot.x = JsonData["ROT.x"].get<float>();
		rot.y = JsonData["ROT.y"].get<float>();
		rot.z = JsonData["ROT.z"].get<float>();
		scale.x = JsonData["SCALE.x"].get<float>();
		scale.y = JsonData["SCALE.y"].get<float>();
		scale.z = JsonData["SCALE.z"].get<float>();
		type = JsonData["TYPE"].get<int>();

		switch (type)
		{
		case 1:
			m_Obj.push_back(CFild::Create(pos, scale, rot));
			break;

		case 2:
			m_Obj.push_back(CCurb::Create(pos, scale, rot));
			break;

		case 3:
			m_Obj.push_back(CEnemyMovePoint::Create(pos, scale, rot));
			break;

		case 4:
			m_Obj.push_back(CStageChangePoint::Create(pos, scale));
			break;

		case 5:
			m_Obj.push_back(CGymFild::Create(pos, scale, rot));
			break;

		default:
			break;
		}
	}

	inputfile.close();
}
