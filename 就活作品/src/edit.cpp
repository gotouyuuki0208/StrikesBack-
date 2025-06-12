//==========================
// 
// オブジェクト配置[edit.cpp]
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
#include"corridorExit.h"
#include"corridorceiling.h"
#include"illumination.h"
#include"arrowpoint.h"
#include"wavewall.h"

using json = nlohmann::json;

//静的メンバ初期化
const float CEdit::MOVE = 1.0f;//移動量
const float CEdit::SCALE = 0.5f;//スケール
//==========================
// コンストラクタ
//==========================
CEdit::CEdit():
m_EditObject(nullptr),//現在編集しているオブジェクト
m_EditMode(false),//編集モード
m_ObjectType(0),//オブジェクトの種類
m_EditObjectKeep{},//編集中のオブジェクトを保存
m_MoveDirection(false),//移動方向
m_SwitchInput(false),//入力方法
m_move(false),//移動の編集
m_Camera(false),//カメラの位置
m_ChangeScale(false),//スケールの変更
m_ChangePosNum(1.0f),//移動値
m_ChangeScaleNum(1.0f),
m_wave(0)
{
	m_Object.clear();//要素を全て削除
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_camerapos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//==========================
// デストラクタ
//==========================
CEdit::~CEdit()
{

}

//==========================
// 初期化処理
//==========================
HRESULT CEdit::Init()
{
	m_EditObject = SetType();//オブジェクトの種類を設定

	return S_OK;
}

//==========================
// 更新処理
//==========================
void CEdit::Update()
{
	//ImGuiのウィンドウを生成
	CreateImGuiWindow();
}

//==========================
//終了処理
//==========================
void CEdit::Uninit()
{
	m_Object.clear();//要素を全て削除

	m_EditObject = nullptr;//現在編集しているオブジェクト
	m_EditMode = false;//編集モード
	m_ObjectType = 0;//オブジェクトの種類
	m_EditObjectKeep = {};//編集中のオブジェクトを保存
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//==========================
//ImGuiのウィンドウを生成
//==========================
void CEdit::CreateImGuiWindow()
{
	ObjectImGui();//オブジェクトを操作するImGui

	CameraImGui();//カメラを操作するImGui
}

//==========================
//オブジェクトに関する操作
//==========================
void CEdit::ObjectImGui()
{
	ImGui::Begin("edit");//"Obuject"という名前のウィンドウを作成

	Move();					//位置の変更
	Rotate();				//向きの変更
	Scale();				//スケール変更
	Content();				//オブジェクトの編集

	ImGui::End();
}

//==========================
//カメラに関する操作
//==========================
void CEdit::CameraImGui()
{
	ImGui::Begin("Camera");//"Camera"という名前のウィンドウを作成

	CameraFollow();	//カメラ追従設定

	ImGui::End();
}

//==========================
//カメラが追従設定
//==========================
void CEdit::CameraFollow()
{
	//カメラの情報を取得
	CCamera* pCamera = CManager::GetInstance()->GetCamera();
	static bool OldCameraType = false;//斬回のカメラの状態

	//カメラ追従のチェックボックス
	ImGui::Checkbox("overhead", &m_Camera);//位置を変更

	if(m_Camera&& !OldCameraType)
	{//カメラの位置が上からに切り替わった時だけ
		m_camerapos = { m_EditObject->GetPos().x,m_EditObject->GetPos().y +2000.0f ,m_EditObject->GetPos().z+ pCamera->Z_DISTANCE };							//現在の位置を取得
	}

	if (m_Camera)
	{
		//カメラが正面追従
		CameraPos();	//位置の設定
		OldCameraType = true;
	}
	else
	{
		pCamera->Move(m_EditObject->GetPos());
		OldCameraType = false;
	}
}

//==========================
//カメラの位置
//==========================
void CEdit::CameraPos()
{
	//カメラの情報を取得
	CCamera* pCamera = CManager::GetInstance()->GetCamera();

	//y座標の変更する
	ImGui::SetNextItemWidth(100.0f);
	ImGui::DragFloat("CameraPosY", &m_camerapos.y, 1.0f);

	pCamera->SetEditPos(m_camerapos, m_EditObject->GetPos());	//位置を変更
}

//==========================
//入力処理
//==========================
void CEdit::Move()
{
	if (!ImGui::CollapsingHeader("Position"))
	{
		return;
	}
	ImGui::SetNextItemWidth(100.0f);							//横幅を変更
	ImGui::InputFloat("MoveNum", &m_ChangePosNum);				//移動値を変更

	m_pos = m_EditObject->GetPos();								//現在の位置を取得

	//x座標の変更する
	ImGui::SetNextItemWidth(100.0f);							//横幅を変更
	ImGui::DragFloat("ObjectPosX", &m_pos.x, m_ChangePosNum);	//数値を変更するUI
	ImGui::SameLine();											//次のUIを同じ行に表示
	if (ImGui::Button("PosX+"))									//
	{
		m_pos.x += m_ChangePosNum;
	}
	ImGui::SameLine();											//次のUIを同じ行に表示
	if (ImGui::Button("PosX-"))									//位置のリセットをするボタン
	{
		m_pos.x -= m_ChangePosNum;
	}

	//y座標の変更する
	ImGui::SetNextItemWidth(100.0f);
	ImGui::DragFloat("ObjectPosY", &m_pos.y, m_ChangePosNum);
	ImGui::SameLine();											//次のUIを同じ行に表示
	if (ImGui::Button("PosY+"))									//
	{
		m_pos.y += m_ChangePosNum;
	}
	ImGui::SameLine();											//次のUIを同じ行に表示
	if (ImGui::Button("PosY-"))									//位置のリセットをするボタン
	{
		m_pos.y -= m_ChangePosNum;
	}

	//z座標の変更する
	ImGui::SetNextItemWidth(100.0f);
	ImGui::DragFloat("ObjectPosZ", &m_pos.z, m_ChangePosNum);	//z座標の変更する
	ImGui::SameLine();											//次のUIを同じ行に表示
	if (ImGui::Button("PosZ+"))									//
	{
		m_pos.z += m_ChangePosNum;
	}
	ImGui::SameLine();											//次のUIを同じ行に表示
	if (ImGui::Button("PosZ-"))									//位置のリセットをするボタン
	{
		m_pos.z -= m_ChangePosNum;
	}

	if (ImGui::Button("PosReset"))								//位置のリセットをするボタン
	{

		m_pos = { 0.0f,0.0f,0.0f };
	}

	m_EditObject->SetPos(m_pos);								//位置を変更
}

//==========================
//向きを変える
//==========================
void CEdit::Rotate()
{
	if (!ImGui::CollapsingHeader("Rotation"))
	{
		return;
	}
	m_rot = m_EditObject->GetRot();			//現在の位置を取得

	//y座標の変更する
	ImGui::SetNextItemWidth(100.0f);
	if (ImGui::Button("Back"))						//
	{
		m_rot.y = D3DX_PI;
	}
	ImGui::SameLine();								//次のUIを同じ行に表示
	if (ImGui::Button("Left"))						//位置のリセットをするボタン
	{
		m_rot.y = D3DX_PI / 2;
	}
	ImGui::SameLine();								//次のUIを同じ行に表示
	if (ImGui::Button("Right"))						//位置のリセットをするボタン
	{
		m_rot.y = -D3DX_PI / 2;
	}
	ImGui::SameLine();								//次のUIを同じ行に表示
	if (ImGui::Button("Front"))						//位置のリセットをするボタン
	{
		m_rot.y = 0.0f;
	}

	m_EditObject->SetRot(m_rot);					//位置を変更

}

//==========================
//スケール変更
//==========================
void CEdit::Scale()
{
	if (!ImGui::CollapsingHeader("Scale"))
	{
		return;
	}

	ImGui::SetNextItemWidth(100.0f);				//横幅を変更
	ImGui::InputFloat("ScaleNum", &m_ChangeScaleNum);//移動値を変更

	m_scale = m_EditObject->GetScale();		//現在の位置を取得

	//x座標の変更する
	ImGui::SetNextItemWidth(100.0f);				//横幅を変更
	if (ImGui::Button("Scale+"))					//
	{
		m_scale.x += m_ChangeScaleNum;
		m_scale.y += m_ChangeScaleNum;
		m_scale.z += m_ChangeScaleNum;
	}
	ImGui::SameLine();								//次のUIを同じ行に表示
	if (ImGui::Button("Scale-"))					//位置のリセットをするボタン
	{
		m_scale.x -= m_ChangeScaleNum;
		m_scale.y -= m_ChangeScaleNum;
		m_scale.z -= m_ChangeScaleNum;
	}
	if (ImGui::Button("Scalex+"))					//位置のリセットをするボタン
	{
		m_scale.x += m_ChangeScaleNum;
	}
	ImGui::SameLine();								//次のUIを同じ行に表示
	if (ImGui::Button("Scalex-"))					//位置のリセットをするボタン
	{
		m_scale.x -= m_ChangeScaleNum;
	}
	if (ImGui::Button("Scaley+"))					//位置のリセットをするボタン
	{
		m_scale.y += m_ChangeScaleNum;
	}
	ImGui::SameLine();								//次のUIを同じ行に表示
	if (ImGui::Button("Scaley-"))					//位置のリセットをするボタン
	{
		m_scale.y -= m_ChangeScaleNum;
	}
	if (ImGui::Button("Scalez+"))					//位置のリセットをするボタン
	{
		m_scale.z += m_ChangeScaleNum;
	}
	ImGui::SameLine();								//次のUIを同じ行に表示
	if (ImGui::Button("Scalez-"))					//位置のリセットをするボタン
	{
		m_scale.z -= m_ChangeScaleNum;
	}
	m_EditObject->SetScale(m_scale);

}

//==========================
//オブジェクトの編集
//==========================
void CEdit::Content()
{
	if (!ImGui::CollapsingHeader("Content"))
	{//開かれていない

		return;
	}

	if (ImGui::Button("placement"))			//配置
	{
		m_Object.push_back(m_EditObject);	//現在のオブジェクトを保存
		m_EditObject = SetType();			//新しいオブジェクトを生成
	}

	ImGui::SameLine();
	if (ImGui::Button("ChangeObject"))		//オブジェクトの種類を変更
	{
		ChangeType();
	}

	ImGui::SetNextItemWidth(100.0f);				//横幅を変更
	ImGui::InputInt("wave", &m_wave);				//移動値を変更

	//編集モード変更のチェックボックス
	if (ImGui::Checkbox("PlacedObjects", &m_EditMode))
	{
		//オブジェクトを変更
		SwitchEditMode();
	}

	if (ImGui::Button("PreviousObject"))		//オブジェクトの種類を変更
	{
		if (m_EditMode)
		{
			if (m_Objectite != m_Object.begin())
			{//最初のオブジェクトじゃない
				m_Objectite--;//前のオブジェクトに移動
				m_EditObject = *m_Objectite;//オブジェクトの情報を取得
				m_pos = m_EditObject->GetPos();
				m_scale = m_EditObject->GetScale();
				m_rot = m_EditObject->GetRot();
			}
		}
	}

	ImGui::SameLine();								//次のUIを同じ行に表示
	if (ImGui::Button("NextObject"))		//オブジェクトの種類を変更
	{
		if (m_EditMode)
		{
			m_Objectite++;//次のオブジェクトに移動

			if (m_Objectite == m_Object.end())
			{//最後のとき
				m_Objectite--;
			}

			m_EditObject = *m_Objectite;//オブジェクトの情報を取得
			m_pos = m_EditObject->GetPos();
			m_scale = m_EditObject->GetScale();
			m_rot = m_EditObject->GetRot();
		}
	}

	if (ImGui::Button("FirstObject"))		//オブジェクトの種類を変更
	{
		if (m_EditMode)
		{
			m_Objectite = m_Object.begin();//最初のオブジェクトに移動

			m_EditObject = *m_Objectite;//オブジェクトの情報を取得
			m_pos = m_EditObject->GetPos();
			m_scale = m_EditObject->GetScale();
			m_rot = m_EditObject->GetRot();
		}
	}

	ImGui::SameLine();								//次のUIを同じ行に表示
	if (ImGui::Button("LastObject"))		//オブジェクトの種類を変更
	{
		if (m_EditMode)
		{
			//最後のオブジェクトに移動
			m_Objectite = m_Object.end();
			m_Objectite--;

			m_EditObject = *m_Objectite;//オブジェクトの情報を取得
			m_pos = m_EditObject->GetPos();
			m_scale = m_EditObject->GetScale();
			m_rot = m_EditObject->GetRot();
		}
	}

	if (ImGui::Button("DeleteObject"))		//オブジェクトの種類を変更
	{
		if (m_EditMode)
		{
			if (m_Object.size() <= 1)
			{//要素が一つだけ

				m_Object.clear();//要素を削除
				m_EditObject->Uninit();//オブジェクトの削除

				//新規配置モードに変更
				m_EditMode = false;
				m_ObjectType = m_EditObjectKeep.ObjectType;
				m_EditObject = SetType();//オブジェクトの種類を設定
				m_pos = m_EditObjectKeep.pos;
				m_scale = m_EditObjectKeep.scale;
				m_rot = m_EditObjectKeep.rot;
				return;
			}

			if (m_Objectite != m_Object.begin())
			{//最初のオブジェクトじゃない

				//オブジェクトを削除して前のオブジェクトに移動
				m_Objectite--;
				m_Object.erase(next(m_Objectite));
			}
			else
			{//最初のオブジェクト

				//オブジェクトを削除して次のオブジェクトに移動
				m_Objectite++;
				m_Object.erase(prev(m_Objectite));
			}

			m_EditObject->Uninit();//オブジェクトを削除
			m_EditObject = *m_Objectite;//オブジェクトの情報を取得
			m_pos = m_EditObject->GetPos();
			m_scale = m_EditObject->GetScale();
			m_rot = m_EditObject->GetRot();
		}
	}

	if (ImGui::Button("StageChange"))		//オブジェクトの種類を変更
	{
		StageChange();
	}

	ImGui::SameLine();								//次のUIを同じ行に表示
	if (ImGui::Button("Save"))//オブジェクトの種類を変更
	{
		Save();
	}
}

//==========================
//オブジェクトの種類を変更
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
		object = CHitEnemy::Create(m_pos, m_scale, m_wave);
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
		
	case 40:
		object = CCorridorExit::Create(m_pos, m_scale, m_rot);
		break;

	case 41:
		object = CCorridorceiling::Create(m_pos, m_scale, m_rot);
		break;

	case 42:
		object = CIllumination::Create(m_pos, m_scale, m_rot);
		break;

	case 43:
		object = CWaveWall::Create(m_pos, m_scale, m_rot, m_wave);
		break;

	case 44:
		object = CArrowPoint::Create(m_pos, m_scale);
		break;

	default:
		m_ObjectType = 0;
		object = CBuil::Create(m_pos, m_scale, m_rot);
		break;
	}
	
	return object;
}

//==========================
//オブジェクトの種類を設定
//==========================
void CEdit::ChangeType()
{

	m_ObjectType++;
	m_EditObject->Uninit();
	m_EditObject = nullptr;
	m_EditObject = SetType();//オブジェクトの種類を設定

	if (m_EditMode)
	{//配置済みオブジェクトを編集中

		if (m_Objectite != m_Object.begin())
		{//最初のオブジェクトじゃない

			m_Objectite--;//前の要素に移動
			m_Object.erase(next(m_Objectite));//次の要素を削除
			m_Object.insert(next(m_Objectite), m_EditObject);//編集中のオブジェクトを次に挿入
			m_Objectite++;//次の要素に移動
		}
		else
		{//最初のオブジェクトのとき

			m_Object.push_front(m_EditObject);//最初に編集中オブジェクトを挿入
			m_Objectite--;//前の要素に移動
			m_Object.erase(next(m_Objectite));//次の要素を削除
		}
	}

}

//==========================
//情報を保存
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
//編集モードの切り替え
//==========================
void CEdit::SwitchEditMode()
{
	if (m_Object.size() <= 0)
	{
		return;
	}

	if (!m_EditMode)
	{
		m_ObjectType = m_EditObjectKeep.ObjectType;
		m_EditObject = SetType();//オブジェクトの種類を設定
		m_pos = m_EditObjectKeep.pos;
		m_scale = m_EditObjectKeep.scale;
		m_rot = m_EditObjectKeep.rot;
	}
	else
	{
		KeepInfo();//情報を保存
		m_Objectite = m_Object.begin();
		m_EditObject = *m_Objectite;
		m_pos = m_EditObject->GetPos();
		m_scale = m_EditObject->GetScale();
		m_rot = m_EditObject->GetRot();
	}

}

//==========================
//ステージを変更
//==========================
void CEdit::StageChange()
{
	//リストの全てのオブジェクト削除
	DeleteAll();

	CManager::GetInstance()->GetStageManager()->SetStage();

	//ステージを読み込む
	Load();

	CManager::GetInstance()->GetStageManager()->ChangeReset();
}

//==========================
//リストの全てのオブジェクトを削除
//==========================
void CEdit::DeleteAll()
{
	m_Objectite = m_Object.begin();

	while (1)
	{
		if (m_Objectite == m_Object.end())
		{
			m_Object.clear();//要素を全て削除
			break;
		}

		CObject* obj = *m_Objectite;
		
		obj->Uninit();
		m_Objectite++;
	}
}

//==========================
//配置情報を読み込む
//==========================
void CEdit::Load()
{
	JsonFildLoad();
	JsonEnemyLoad();//敵の配置情報を読み込む
	JsonWeaponLoad();//武器の情報を読み込む
	JsonItemLoad();//アイテムの情報を読み込む
	JsonBuildingLoad();//建物の情報を読み込む
}

//==========================
//配置情報を書き出す
//==========================
void CEdit::Save()
{
	//JsonEnemySave();//敵の情報
	JsonFildSave();//地面の情報
	//JsonWeaponSave();//武器の情報
	//JsonItemSave();//アイテムの情報
	JsonBuildingSave();//建物の情報
}

//==========================
//フィールドの配置情報を書き出す
//==========================
void CEdit::JsonFildSave()
{
	list<CObjectgame*>::iterator iterator;
	CObjectgame* Data = nullptr;
	D3DXVECTOR3 pos, scale, rot;
	json jsonArray = json::array();

	//ステージを取得
	int Stage = static_cast<int>(CManager::GetInstance()->GetStageManager()->GetStage());
	
	//jsonファイルを作成
	ofstream writing_file;
	std::string filename = "Fild" + std::to_string(Stage) + ".json";
	std::string filepath = "data\\DATAFILE\\" + filename;
	writing_file.open(filepath, ios::out);

	for (iterator = m_Object.begin(); iterator != m_Object.end(); iterator++)
	{
		Data = *iterator;

		if (Data->GetType() != CObject::TYPE::FILD)
		{
			continue;
		}

		CFild* pFild = dynamic_cast<CFild*>(Data);

		pos = pFild->GetPos();//位置を取得
		rot = pFild->GetRot();//向きを取得
		scale = pFild->GetScale();//スケールを取得
		int fildtype = static_cast<int>(pFild->GetFildType());
		scale = D3DXVECTOR3(1000.0f, 0.0f, 1000.0f);

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

		json jsondata =
		{
			{"POS.x",pos.x,},
			{"POS.y",pos.y,},
			{"POS.z",pos.z,},
			{"ROT.x",rot.x,},
			{"ROT.y",rot.y,},
			{"ROT.z",rot.z,},
			{"SCALE.x",scale.x,},
			{"SCALE.y",scale.y,},
			{"SCALE.z",scale.z,},
			{"TYPE",fildtype}
		};

		jsonArray.push_back(jsondata);
	}
	
	//作成したファイルに内容を書き込む
	writing_file << jsonArray.dump(4);

	writing_file.close();
}

//==========================
//フィールドの配置情報を読み込む
//==========================
void CEdit::JsonFildLoad()
{
	//ステージを取得
	int Stage = static_cast<int>(CManager::GetInstance()->GetStageManager()->GetStage());
	D3DXVECTOR3 pos,scale,rot;
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
			m_Object.push_back(CFild::Create(pos, scale, rot));
			break;

		case 2:
			m_Object.push_back(CCurb::Create(pos, scale, rot));
			break;

		case 3:
			m_Object.push_back(CEnemyMovePoint::Create(pos, scale, rot));
			break;

		case 4:
			m_Object.push_back(CStageChangePoint::Create(pos, scale));
			break;

		case 5:
			m_Object.push_back(CGymFild::Create(pos, scale, rot));
			break;

		default:
			break;
		}
	}

	inputfile.close();
}

//==========================
//敵の配置情報を書き出す
//==========================
void CEdit::JsonEnemySave()
{
	//ステージを取得
	int Stage = static_cast<int>(CManager::GetInstance()->GetStageManager()->GetStage());

	list<CObjectgame*>::iterator iterator;
	CObjectgame* Data = nullptr;
	D3DXVECTOR3 pos, scale, rot;
	json jsonArray = json::array();

	//jsonファイルを作成
	ofstream writing_file;
	std::string filename = "Enemy" + std::to_string(Stage) + ".json";
	std::string filepath = "data\\DATAFILE\\" + filename;


	writing_file.open(filepath, ios::out);

	for (iterator = m_Object.begin(); iterator != m_Object.end(); iterator++)
	{
		Data = *iterator;

		if (Data->GetType() != CObject::TYPE::ENEMY)
		{
			continue;
		}

		CEnemy* pEnemy = dynamic_cast<CEnemy*>(Data);

		pos = pEnemy->GetPos();//位置を取得
		rot = pEnemy->GetRot();//向きを取得
		scale = pEnemy->GetScale();//スケールを取得
		int EnemyType = static_cast<int>(pEnemy->GetEnemyType());//敵の種類を取得
		int Wave = pEnemy->GetActionWave();

		json jsondata =
		{
			{"POS.x",pos.x},
			{"POS.y",pos.y},
			{"POS.z",pos.z},
			{"SCALE.x",scale.x},
			{"SCALE.y",scale.y},
			{"SCALE.z",scale.z},
			{"TYPE",EnemyType},
			{"WAVE",Wave}
		};

		jsonArray.push_back(jsondata);
	}

	//作成したファイルに内容を書き込む
	writing_file << jsonArray.dump(4);

	writing_file.close();
}

//==========================
//敵の配置情報を読み込む
//==========================
void CEdit::JsonEnemyLoad()
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
			m_Object.push_back(CBoss::Create(pos, scale));
			break;
		case 2:
			m_Object.push_back(CHitEnemy::Create(pos, scale, wave));
			break;
		case 3:
			m_Object.push_back(CWeaponEnemy::Create(pos, scale));
			break;

		default:
			break;
		}
	}

	inputfile.close();
}

//==========================
//武器の配置情報を書き出す
//==========================
void CEdit::JsonWeaponSave()
{
	//ステージを取得
	int Stage = static_cast<int>(CManager::GetInstance()->GetStageManager()->GetStage());

	list<CObjectgame*>::iterator iterator;
	CObjectgame* Data = nullptr;
	D3DXVECTOR3 pos = { 0.0f,0.0f,0.0f }, scale = { 0.0f,0.0f,0.0f }, rot = {0.0f,0.0f,0.0f};
	json jsonArray = json::array();
	int type = 0;

	//jsonファイルを作成
	ofstream writing_file;
	std::string filename = "Weapon" + std::to_string(Stage) + ".json";
	std::string filepath = "data\\DATAFILE\\" + filename;
	writing_file.open(filepath, ios::out);

	for (iterator = m_Object.begin(); iterator != m_Object.end(); iterator++)
	{
		Data = *iterator;

		if (Data->GetType() != CObject::TYPE::WEAPON)
		{
			continue;
		}

		CWeapon* pWeapon = dynamic_cast<CWeapon*>(Data);
		int weapontype = static_cast<int>(pWeapon->GetWeaponType());//武器の大きさを取得

		if (weapontype == 1)
		{
			CBigWeapon* pBigWeapon = dynamic_cast<CBigWeapon*>(pWeapon);

			pos = pBigWeapon->GetPos();//位置を取得
			scale = pBigWeapon->GetScale();//スケールを取得
			rot = pBigWeapon->GetRot();//向きを取得
			type = static_cast<int>(pBigWeapon->GetBigWeapon());
		}
		else
		{
			CSmallWeapon* pSmallWeapon = dynamic_cast<CSmallWeapon*>(pWeapon);

			pos = pSmallWeapon->GetPos();//位置を取得
			scale = pSmallWeapon->GetScale();//スケールを取得
			rot = pSmallWeapon->GetRot();//向きを取得
			type = static_cast<int>(pSmallWeapon->GetSmallWeapon());
		}

		json jsondata =
		{
			{"POS.x",pos.x},
			{"POS.y",pos.y},
			{"POS.z",pos.z},
			{"ROT.x",rot.x},
			{"ROT.y",rot.y},
			{"ROT.z",rot.z},
			{"SCALE.x",scale.x},
			{"SCALE.y",scale.y},
			{"SCALE.z",scale.z},
			{"TYPE",type},
			{"WEAPONTYPE",weapontype}
		};

		jsonArray.push_back(jsondata);
	}

	//作成したファイルに内容を書き込む
	writing_file << jsonArray.dump(4);

	writing_file.close();
}

//==========================
//武器の配置情報を読み込む
//==========================
void CEdit::JsonWeaponLoad()
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
				m_Object.push_back(CBicycle::Create(pos, scale, rot));
				break;

			case 2:
				m_Object.push_back(CCone::Create(pos, scale, rot));
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
				m_Object.push_back(CBat::Create(pos, scale, rot));
				break;

			case 2:
				m_Object.push_back(CPipe::Create(pos, scale, rot));
				break;

			case 3:
				m_Object.push_back(CSyokaki::Create(pos, scale, rot));
				break;

			default:
				break;
			}
		}
	}

	inputfile.close();
}

//==========================
//アイテムの配置情報を書き出す
//==========================
void CEdit::JsonItemSave()
{
	//ステージを取得
	int Stage = static_cast<int>(CManager::GetInstance()->GetStageManager()->GetStage());

	list<CObjectgame*>::iterator iterator;
	CObjectgame* Data = nullptr;
	D3DXVECTOR3 pos, scale, rot;
	json jsonArray = json::array();

	//jsonファイルを作成
	ofstream writing_file;
	std::string filename = "Item" + std::to_string(Stage) + ".json";
	std::string filepath = "data\\DATAFILE\\" + filename;
	writing_file.open(filepath, ios::out);

	for (iterator = m_Object.begin(); iterator != m_Object.end(); iterator++)
	{
		Data = *iterator;

		if (Data->GetType() != CObject::TYPE::JIHANKI)
		{
			continue;
		}

		CJihanki* pJihan = dynamic_cast<CJihanki*>(Data);

		pos = pJihan->GetPos();//位置を取得
		scale = pJihan->GetScale();
		rot = pJihan->GetRot();

		json jsondata =
		{
			{"POS.x",pos.x},
			{"POS.y",pos.y},
			{"POS.z",pos.z},
			{"ROT.x",rot.x},
			{"ROT.y",rot.y},
			{"ROT.z",rot.z},
			{"SCALE.x",scale.x},
			{"SCALE.y",scale.y},
			{"SCALE.z",scale.z},
		};

		jsonArray.push_back(jsondata);
	}

	//作成したファイルに内容を書き込む
	writing_file << jsonArray.dump(4);

	writing_file.close();
}

//==========================
//アイテムの配置情報を読み込む
//==========================
void CEdit::JsonItemLoad()
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
	

		m_Object.push_back(CJihanki::Create(pos, scale, rot));
	}

	inputfile.close();
}

//==========================
//建物の配置情報を書き出す
//==========================
void CEdit::JsonBuildingSave()
{
	//ステージを取得
	int Stage = static_cast<int>(CManager::GetInstance()->GetStageManager()->GetStage());

	list<CObjectgame*>::iterator iterator;
	CObjectgame* Data = nullptr;
	D3DXVECTOR3 pos, scale, rot;
	json jsonArray = json::array();

	//jsonファイルを作成
	ofstream writing_file;
	std::string filename = "Building" + std::to_string(Stage) + ".json";
	std::string filepath = "data\\DATAFILE\\" + filename;
	writing_file.open(filepath, ios::out);

	for (iterator = m_Object.begin(); iterator != m_Object.end(); iterator++)
	{
		Data = *iterator;

		if (Data->GetType() != CObject::TYPE::BUILDING)
		{
			continue;
		}

		CBuilding* pBuilding = dynamic_cast<CBuilding*>(Data);
		json JsonData;

		pos = pBuilding->GetPos();//位置を取得
		scale = pBuilding->GetScale();
		rot = pBuilding->GetRot();
		int BuildingType = static_cast<int>(pBuilding->GetBuildingType());//敵の種類を取得

		JsonData["POS"] =
		{
			{"x",pos.x},
			{"y",pos.y},
			{"z",pos.z}
		};

		JsonData["ROT"] =
		{
			{"x",rot.x},
			{"y",rot.y},
			{"z",rot.z}
		};

		JsonData["SCALE"] =
		{
			{"x",scale.x},
			{"y",scale.y},
			{"z",scale.z}
		};

		JsonData["TYPE"] =
		{
			{"type",BuildingType}
		};

		if (BuildingType == 30)
		{
			CWaveWall* pwall = dynamic_cast<CWaveWall*>(pBuilding);
			int wave = pwall->GetMyWave();

			JsonData["WAVE"] =
			{
				{"wave",wave}
			};
		}

		jsonArray.push_back(JsonData);
	}

	//作成したファイルに内容を書き込む
	writing_file << jsonArray.dump(4);

	writing_file.close();

	ifstream inputfile;

	
}

//==========================
//建物の配置情報を読み込む
//==========================
void CEdit::JsonBuildingLoad()
{
	D3DXVECTOR3 pos, scale, rot;
	int type;
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
		pos.x = JsonData["POS"].value("x", 0.0f);
		pos.y = JsonData["POS"].value("y", 0.0f);
		pos.z = JsonData["POS"].value("z", 0.0f);
		rot.x = JsonData["ROT"].value("x", 0.0f);
		rot.y = JsonData["ROT"].value("y", 0.0f);
		rot.z = JsonData["ROT"].value("z", 0.0f);
		scale.x = JsonData["SCALE"].value("x", 0.0f);
		scale.y = JsonData["SCALE"].value("y", 0.0f);
		scale.z = JsonData["SCALE"].value("z", 0.0f);
		type = JsonData["TYPE"].value("type", 0.0f);

		switch (type)
		{
		case 1:
			m_Object.push_back(CBuil::Create(pos, scale, rot));
			break;

		case 2:
			m_Object.push_back(CApartment::Create(pos, scale, rot));
			break;

		case 3:
			m_Object.push_back(CConveni::Create(pos, scale, rot));
			break;

		case 4:
			m_Object.push_back(CHouse::Create(pos, scale, rot));
			break;

		case 5:
			m_Object.push_back(CHouseWhite::Create(pos, scale, rot));
			break;

		case 6:
			m_Object.push_back(CPole::Create(pos, scale, rot));
			break;

		case 7:
			m_Object.push_back(CShingoki::Create(pos, scale, rot));
			break;

		case 8:
			m_Object.push_back(CFence::Create(pos, scale, rot));
			break;

		case 9:
			m_Object.push_back(CGarden::Create(pos, scale, rot));
			break;

		case 10:
			m_Object.push_back(CConstruction::Create(pos, scale, rot));
			break;

		case 11:
			m_Object.push_back(CSchool::Create(pos, scale, rot));
			break;

		case 12:
			m_Object.push_back(CBParking::Create(pos, scale, rot));
			break;

		case 13:
			m_Object.push_back(CCorridorfloor::Create(pos, scale, rot));
			break;

		case 14:
			m_Object.push_back(CCorridorWall::Create(pos, scale, rot));
			break;

		case 15:
			m_Object.push_back(CShoerack::Create(pos, scale, rot));
			break;

		case 16:
			m_Object.push_back(CRoomDoor::Create(pos, scale, rot));
			break;

		case 17:
			m_Object.push_back(CBoard::Create(pos, scale, rot));
			break;

		case 18:
			m_Object.push_back(CEntrance::Create(pos, scale, rot));
			break;

		case 19:
			m_Object.push_back(CGymfront::Create(pos, scale, rot));
			break;

		case 20:
			m_Object.push_back(CGymwall::Create(pos, scale, rot));
			break;

		case 21:
			m_Object.push_back(CGymentrance::Create(pos, scale, rot));
			break;

		case 22:
			m_Object.push_back(CGymwalltop::Create(pos, scale, rot));
			break;

		case 23:
			m_Object.push_back(CBasketgoal::Create(pos, scale, rot));
			break;

		case 24:
			m_Object.push_back(CWall::Create(pos, scale, rot));
			break;

		case 25:
			m_Object.push_back(CGymDoor::Create(pos, scale, rot));
			break;

		case 26:
			m_Object.push_back(CGymCeiling::Create(pos, scale, rot));
			break;

		case 27:
			m_Object.push_back(CCorridorExit::Create(pos, scale, rot));
			break;

		case 28:
			m_Object.push_back(CCorridorceiling::Create(pos, scale, rot));
			break;

		case 29:
			m_Object.push_back(CIllumination::Create(pos, scale, rot));
			break;

		case 30:
			m_Object.push_back(CWaveWall::Create(pos, scale, rot, 0));
			break;

		default:
			break;
		}
	}

	inputfile.close();
}