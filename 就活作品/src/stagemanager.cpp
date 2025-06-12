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
#include"player.h"
#include"darkbg.h"
#include"wavewall.h"
using json = nlohmann::json;

//==========================
//コンストラクタ
//==========================
CStageManager::CStageManager():
m_Stage(STAGE::STAGE_FIRST),//ステージの番号
m_Change(false),//ステージ切り替わり判定
m_DarkBg(nullptr),//暗転するための黒ポリゴン
m_Rast(0),//最終ステージの番号
m_player(nullptr)//プレイヤーの情報
{
	//最終ステージの番号
	m_Rast = static_cast<int>(STAGE::STAGE_BOSS);

	//暗転のための黒ポリゴンを生成
	m_DarkBg = CDarkBg::Create();

	//リストを初期化
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
	{//黒ポリゴンを削除

		m_DarkBg->CObject2D::Uninit();
		delete m_DarkBg;
		m_DarkBg = nullptr;
	}

	//プレイヤーの情報を消す
	m_player = nullptr;

	//リストを削除
	m_Obj.clear();
}

//==========================
//ステージを設定
//==========================
void CStageManager::SetStage()
{
	//現在のステージ番号を取得
	int stage = static_cast<int>(m_Stage);

	if (stage >= m_Rast)
	{//ステージ番号が最終ステージ

		stage = 0;
	}

	//ステージを次のステージに変更
	m_Stage = static_cast<STAGE>(stage + 1);

	//ステージの切り替わり判定
	m_Change = true;

	//フェードを開始
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
	if (m_DarkBg->GetCol() >= 1.0f)
	{//画面が完全に暗い

		return true;
	}

	return false;
}

//==========================
//ステージをリセット
//==========================
void CStageManager::StageReset()
{
	//登録されているオブジェクトの情報を消す
	m_Obj.clear();

	//現在のステージをステージ1に戻す
	m_Stage = STAGE::STAGE_FIRST;
}

//==========================
//ステージの切り替え
//==========================
void CStageManager::ChangeStage()
{
	
	if (GetChange()&&ChangeObject())
	{//ステージが切り替わっていて画面が暗くなってる

		//ゲームマネージャーの情報を取得
		CGameManager* pGemeManeger = CManager::GetInstance()->GetGameManager();

		//カメラの情報を取得
		CCamera* pCamera = CManager::GetInstance()->GetCamera();

		//ステージを生成
		DeleteAll();//全てのオブジェクトを削除
		Load();//オブジェクトを読み込む

		//カメラの情報を初期化
		pCamera->Init();

		//現在のステージを取得
		int StageNum = static_cast<int>(GetStage());

		if (StageNum == 3)
		{//ボスステージの時

			pGemeManeger->SetDirection();//演出中に変更
			m_player->SetPos({ -736.0f, 0.0f, 600.0f });//プレイヤーの位置を変更
			m_player->SetPosOld({ 0.0f, 0.0f, 0.0f });//プレイヤーの前回の位置を変更
		}
		else
		{//ステージ2
			m_player->SetPos({ 0.0f, 0.0f, 100.0f });//プレイヤーの位置を変更
			m_player->SetPosOld({ 0.0f, 0.0f, 0.0f });//プレイヤーの前回の位置を変更
		}

		//持っている武器を消す
		m_player->DeleteWeapon();
		
		//ステートの変更
		m_player->StageChangeState();
		
		//プレイヤーの向きを変更
		m_player->SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));

		//切り替わり判定をリセット
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

	for (list<CObjectgame*>::iterator Ite = m_Obj.begin(); Ite != m_Obj.end(); Ite++)
	{
		CObject* obj = *Ite;

		if (obj != nullptr)
		{
			obj->Uninit();
		}
	}
	
	m_Obj.clear();//要素を全て削除
}

//==========================
//オブジェクトを削除
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
//ステージの読み込み
//==========================
void CStageManager::Load()
{
	if (m_Stage == STAGE::STAGE_FIRST)
	{//最初のステージ

		//空とプレイヤーを生成
		CSky::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2000.0f, 2000.0f, 2000.0f));
		m_player = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f));
	}

	JsonFildLoad();		//フィールドの情報を読み込む
	JsonEnemyLoad();	//敵の情報を読み込む
	JsonWeaponLoad();	//武器の情報を読み込む
	JsonBuildingLoad();	//建物の情報を読み込む
	JsonItemLoad();		//アイテムの情報を読み込む
}

//==========================
//建物の配置情報を読み込む
//==========================
void CStageManager::JsonBuildingLoad()
{
	D3DXVECTOR3 pos, scale, rot;
	int type,wave;
	ifstream inputfile;

	//ステージを取得
	int Stage = static_cast<int>(CManager::GetInstance()->GetStageManager()->GetStage());

	std::string filename = "Building" + std::to_string(Stage) + ".json";
	std::string filepath = "data\\DATAFILE\\" + filename;

	inputfile.open(filepath);//テキストファイルを開く
	json jsonarray;
	inputfile >> jsonarray;

	for (const auto& JsonData : jsonarray)
	{
		//読み込んだデータをそれぞれの変数に代入する
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
//アイテムの配置情報を読み込む
//==========================
void CStageManager::JsonItemLoad()
{
	D3DXVECTOR3 pos, scale, rot;
	ifstream inputfile;

	//ステージを取得
	int Stage = static_cast<int>(CManager::GetInstance()->GetStageManager()->GetStage());

	std::string filename = "Item" + std::to_string(Stage) + ".json";
	std::string filepath = "data\\DATAFILE\\" + filename;

	inputfile.open(filepath);//テキストファイルを開く
	json jsonarray;
	inputfile >> jsonarray;

	for (const auto& JsonData : jsonarray)
	{
		//読み込んだデータをそれぞれの変数に代入する
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
//武器の配置情報を読み込む
//==========================
void CStageManager::JsonWeaponLoad()
{
	//ステージを取得
	int Stage = static_cast<int>(CManager::GetInstance()->GetStageManager()->GetStage());

	D3DXVECTOR3 pos, scale, rot;
	int type, weapontype;
	ifstream inputfile;

	std::string filename = "Weapon" + std::to_string(Stage) + ".json";
	std::string filepath = "data\\DATAFILE\\" + filename;

	inputfile.open(filepath);//テキストファイルを開く
	json jsonarray;
	inputfile >> jsonarray;

	for (const auto& JsonData : jsonarray)
	{
		//読み込んだデータをそれぞれの変数に代入する
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
//敵の配置情報を読み込む
//==========================
void CStageManager::JsonEnemyLoad()
{
	//ステージを取得
	int Stage = static_cast<int>(CManager::GetInstance()->GetStageManager()->GetStage());

	D3DXVECTOR3 pos, scale, rot;
	int type,wave;
	ifstream inputfile;

	std::string filename = "Enemy" + std::to_string(Stage) + ".json";
	std::string filepath = "data\\DATAFILE\\" + filename;

	inputfile.open(filepath);//テキストファイルを開く
	json jsonarray;
	inputfile >> jsonarray;

	for (const auto& JsonData : jsonarray)
	{
		//読み込んだデータをそれぞれの変数に代入する
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
//フィールドの配置情報を読み込む
//==========================
void CStageManager::JsonFildLoad()
{
	//ステージを取得
	int Stage = static_cast<int>(CManager::GetInstance()->GetStageManager()->GetStage());
	D3DXVECTOR3 pos, scale, rot;
	int type;
	ifstream inputfile;
	std::string filename = "Fild" + std::to_string(Stage) + ".json";
	std::string filepath = "data\\DATAFILE\\" + filename;
	inputfile.open(filepath);//テキストファイルを開く
	json jsonarray;
	inputfile >> jsonarray;

	for (const auto& JsonData : jsonarray)
	{
		//読み込んだデータをそれぞれの変数に代入する
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
