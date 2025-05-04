//==========================
// 
// ステージ管理[stagemanager.cpp]
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
//コンストラクタ
//==========================
CStageManager::CStageManager():
m_Stage(STAGE::STAGE_FIRST),
m_Change(false),//ステージ切り替わり判定
m_DarkBg(nullptr),//暗転するための頃ポリゴン
m_Rast(0),//最終ステージの番号
m_player(nullptr),//プレイヤーの情報
m_PlalyerHPGauge(nullptr),//プレイヤーのHPゲージの情報
m_playerlife(0)
{
	m_Rast = static_cast<int>(STAGE::STAGE_BOSS);
	m_DarkBg = CDarkBg::Create();

	m_Obj.clear();
}

//==========================
//デストラクタ
//==========================
CStageManager::~CStageManager()
{
	
}

//==========================
//終了処理
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
//ステージを設定
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
//ステージを取得
//==========================
CStageManager::STAGE CStageManager::GetStage()
{
	return m_Stage;
}

//==========================
//切り替わり判定を取得
//==========================
bool CStageManager::GetChange()
{
	return m_Change;
}

//==========================
//切り替わり判定をリセット
//==========================
void CStageManager::ChangeReset()
{
	m_Change = false;
}

//==========================
//オブジェクト変更タイミング
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
//ステージをリセット
//==========================
void CStageManager::StageReset()
{
	m_Obj.clear();
	m_Stage = STAGE::STAGE_FIRST;
}

//==========================
//プレイヤーのHPゲージの更新
//==========================
void CStageManager::HPGaugeUpdate()
{
	m_PlalyerHPGauge->SetHP(m_player->GetLife());
}

//==========================
//ステージの切り替え
//==========================
void CStageManager::ChangeStage()
{
	CGameManager* pGemeManeger = CManager::GetInstance()->GetGameManager();

	if (GetChange()&&ChangeObject())
	{//ステージが切り替わってるとき

		//ステージを生成
		DeleteAll();//全てのオブジェクトを削除
		Load();//オブジェクトを読み込む
		CManager::GetInstance()->GetCamera()->Init();//カメラの情報を初期化

		//現在のステージを取得
		int StageNum = static_cast<int>(GetStage());

		if (StageNum == 2)
		{
			//pGemeManeger->SetDirection();//演出を開始
			pGemeManeger->SetChange();
			pGemeManeger->GetBossInfo();//ボスの情報を取得
			m_player->SetPos(D3DXVECTOR3(-736.0f, 0.0f, 600.0f));//プレイヤーの位置を変更
			m_player->SetPosOld(D3DXVECTOR3(0.0f, 0.0f, 0.0f));//プレイヤーの前回の位置を変更
		}
		else
		{
			m_player->SetPos(D3DXVECTOR3(0.0f, 0.0f, 100.0f));//プレイヤーの位置を変更
			m_player->SetPosOld(D3DXVECTOR3(0.0f, 0.0f, 0.0f));//プレイヤーの前回の位置を変更
		}

		m_player->DeleteWeapon();//持っている武器を消す
		m_player->SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));//プレイヤーの向きを変更

		ChangeReset();
	}
}

//==========================
//全てのオブジェクトを削除
//==========================
void CStageManager::DeleteAll()
{
	//リストの最初の要素を取得
	m_ObjIte = m_Obj.begin();

	while (1)
	{
		if (m_ObjIte == m_Obj.end())
		{
			m_Obj.clear();//要素を全て削除
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
//オブジェクトを削除
//==========================
void CStageManager::DeleteObj(CObjectgame& obj)
{
	//リストの最初の要素を取得
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
//ステージの読み込み
//==========================
void CStageManager::Load()
{
	if (m_Stage == STAGE::STAGE_FIRST)
	{
		CSky::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2000.0f, 2000.0f, 2000.0f));
		m_player = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f));
		m_PlalyerHPGauge = CPlayerHPGauge::Create(D3DXVECTOR3(10.0f, 20.0f, 0.0f), 10, 300, m_player->GetLife());
	}

	FildLoad();//フィールドの情報を読み込む
	//EnemyLoad();//敵の情報を読み込む
	WeaponLoad();//武器の情報を読み込む
	BuildingLoad();//建物の情報を読み込む
	ItemLoad();//アイテムの情報を読み込む
}

//==========================
//フィールドの情報を読み込む
//==========================
void CStageManager::FildLoad()
{
	ifstream inputfile;//テキストファイルを開く
	string Data;
	int stage = static_cast<int>(m_Stage);

	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 sclse = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	int type = 0;

	switch (stage)
	{
	case 0:
		inputfile.open("data\\DATAFILE\\FildData.txt");//テキストファイルを開く
		break;

	case 1:
		inputfile.open("data\\DATAFILE\\FildDataSecond.txt");//テキストファイルを開く
		break;

	case 2:
		inputfile.open("data\\DATAFILE\\FildDataLast.txt");//テキストファイルを開く
		break;

	default:
		break;
	}

	if (inputfile)
	{
		while (getline(inputfile, Data, ':'))//情報を読み込む
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

		inputfile.close();//ファイルを閉じる
	}
}

//==========================
//敵の配置情報を読み込む
//==========================
void CStageManager::EnemyLoad()
{
	ifstream inputfile;
	int stage = static_cast<int>(m_Stage);

	switch (stage)
	{
	case 0:
		inputfile.open("data\\DATAFILE\\EnemyData.txt");//テキストファイルを開く
		break;

	case 1:
		inputfile.open("data\\DATAFILE\\EnemyDataSecond.txt");//テキストファイルを開く
		break;

	case 2:
		inputfile.open("data\\DATAFILE\\EnemyDataLast.txt");//テキストファイルを開く
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
		while (getline(inputfile, Data, ':'))//情報を読み込む
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

		inputfile.close();//ファイルを閉じる
	}

}

//==========================
//建物の情報を読み込む
//==========================
void CStageManager::BuildingLoad()
{
	ifstream inputfile;
	int stage = static_cast<int>(m_Stage);

	switch (stage)
	{
	case 0:
		inputfile.open("data\\DATAFILE\\BuildingData.txt");//テキストファイルを開く
		break;

	case 1:
		inputfile.open("data\\DATAFILE\\BuildingDataSecond.txt");//テキストファイルを開く
		break;

	case 2:
		inputfile.open("data\\DATAFILE\\BuildingDataLast.txt");//テキストファイルを開く
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
		while (getline(inputfile, Data, ':'))//情報を読み込む
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

		inputfile.close();//ファイルを閉じる
	}
}

//==========================
//武器の情報を読み込む
//==========================
void CStageManager::WeaponLoad()
{
	ifstream inputfile;
	int stage = static_cast<int>(m_Stage);

	switch (stage)
	{
	case 0:
		inputfile.open("data\\DATAFILE\\WeaponData.txt");//テキストファイルを開く
		break;

	case 1:
		inputfile.open("data\\DATAFILE\\WeaponDataSecond.txt");//テキストファイルを開く
		break;

	case 2:
		inputfile.open("data\\DATAFILE\\WeaponDataLast.txt");//テキストファイルを開く
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
		while (getline(inputfile, Data, ':'))//情報を読み込む
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

		inputfile.close();//ファイルを閉じる
	}
}

//==========================
//アイテムの情報を読み込む
//==========================
void CStageManager::ItemLoad()
{
	ifstream inputfile;//テキストファイルを開く
	string Data;

	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 sclse = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	int type = 0;
	int stage = static_cast<int>(m_Stage);

	switch (stage)
	{
	case 0:
		inputfile.open("data\\DATAFILE\\ItemData.txt");//テキストファイルを開く
		break;

	case 1:
		inputfile.open("data\\DATAFILE\\ItemDataSecond.txt");//テキストファイルを開く
		break;

	case 2:
		inputfile.open("data\\DATAFILE\\ItemDataLast.txt");//テキストファイルを開く
		break;

	default:
		break;
	}

	if (inputfile)
	{
		while (getline(inputfile, Data, ':'))//情報を読み込む
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

		inputfile.close();//ファイルを閉じる
	}
}