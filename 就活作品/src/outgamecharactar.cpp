//==========================
// 
// アウトゲームのキャラクター[outgamecharactar.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "outgamecharactar.h"
#include "manager.h"
#include "model.h"

//静的メンバ初期化
const int COutGameChara::PRIORITY = 1;//描画順

//==========================
//コンストラクタ
//==========================
COutGameChara::COutGameChara(int nPriority) :CMotionModel(nPriority)
{

}

//==========================
//デストラクタ
//==========================
COutGameChara::~COutGameChara()
{

}

//==========================
//初期化処理
//==========================
HRESULT COutGameChara::Init()
{
	//初期設定
	CMotionModel::Init();

	return S_OK;
}

//==========================
//終了処理
//==========================
void  COutGameChara::Uninit()
{
	//終了処理
	CMotionModel::Uninit();
}

//==========================
//更新処理
//==========================
void COutGameChara::Update()
{
	//更新処理
	CMotionModel::Update();
	Motion();

	if (CManager::GetInstance()->GetScene()->GetScene() == CScene::MODE::RESULT)
	{
		SetMotion(MOTION_TYPE::MOVE);
	}
}

//==========================
//描画処理
//==========================
void COutGameChara::Draw()
{
	//描画処理
	CMotionModel::Draw();
}

//==========================
//オブジェクト生成
//==========================
COutGameChara* COutGameChara::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//インスタンス生成
	COutGameChara* pOutGameChara = DBG_NEW COutGameChara;

	//位置の設定
	pOutGameChara->SetPos(pos);

	//初期化処理
	pOutGameChara->Init();

	//向きの設定
	pOutGameChara->SetRot(D3DXVECTOR3(0.0f, 3.14f, 0.0));

	//半径の設定
	pOutGameChara->SetRadius(15.0f);

	//ファイルを読み込む
	pOutGameChara->LoadFile("data\\MOTION\\outgame_player.txt", scale);

	return pOutGameChara;
}