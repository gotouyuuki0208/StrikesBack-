//==========================
// 
// モーションするモデルの描画サンプル[sample_MotionModel.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "sample_MotionModel.h"
#include "manager.h"
#include "model.h"

//静的メンバ初期化
const int CSampleMotionModel::PRIORITY = 1;//描画順

//==========================
//コンストラクタ
//==========================
CSampleMotionModel::CSampleMotionModel(int nPriority) :CMotionModel(nPriority)
{

}

//==========================
//デストラクタ
//==========================
CSampleMotionModel::~CSampleMotionModel()
{

}

//==========================
//初期化処理
//==========================
HRESULT CSampleMotionModel::Init()
{
	//初期設定
	CMotionModel::Init();

	return S_OK;
}

//==========================
//終了処理
//==========================
void  CSampleMotionModel::Uninit()
{
	//終了処理
	CMotionModel::Uninit();
}

//==========================
//更新処理
//==========================
void CSampleMotionModel::Update()
{
	//更新処理
	CMotionModel::Update();
}

//==========================
//描画処理
//==========================
void CSampleMotionModel::Draw()
{
	//描画処理
	CMotionModel::Draw();
}

//==========================
//オブジェクト生成
//==========================
CSampleMotionModel* CSampleMotionModel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	//インスタンス生成
	CSampleMotionModel* pSampleMotionModel = DBG_NEW CSampleMotionModel;

	//位置の設定
	pSampleMotionModel->SetPos(pos);

	//初期化処理
	pSampleMotionModel->Init();

	//半径の設定
	pSampleMotionModel->SetRadius(15.0f);

	//ファイルを読み込む
	pSampleMotionModel->LoadFile("data\\MOTION\\motion_player.txt", scale);

	return pSampleMotionModel;
}