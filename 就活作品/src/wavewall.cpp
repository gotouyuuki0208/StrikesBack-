//==========================
// 
// ウェーブで消える壁[wavewall.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"wavewall.h"
#include"model.h"
#include"manager.h"

//静的メンバ初期化
const int CWaveWall::PRIORITY = 2;//描画順

//==========================
//コンストラクタ
//==========================
CWaveWall::CWaveWall(int nPriority) :
	CBuilding(nPriority),
	m_MyWave(0)
{

}

//==========================
//デストラクタ
//==========================
CWaveWall::~CWaveWall()
{

}

//==========================
//初期化処理
//==========================
HRESULT CWaveWall::Init()
{
	//初期設定
	CBuilding::Init();

	return S_OK;
}

//==========================
//終了処理
//==========================
void  CWaveWall::Uninit()
{
	//終了処理
	CBuilding::Uninit();
}

//==========================
//更新処理
//==========================
void CWaveWall::Update()
{
	//更新処理
	CObjectX::Update();

	int rot = static_cast<int>(GetRot().y);

	if (rot == 1 || rot == -1)
	{
		//プレイヤーとの当たり判定
		ColisionPlayerWide();
	}
	else
	{
		//プレイヤーとの当たり判定
		ColisionPlayer();
	}

	//現在のウェーブを取得
	int NowWave = CManager::GetInstance()->GetGameManager()->GetWave();

	if (m_MyWave < NowWave)
	{//自分のウェーブより先

		//自分を削除する
		CManager::GetInstance()->GetStageManager()->DeleteObj(*this);

		//削除
		Uninit();
	}
	
}

//==========================
//描画処理
//==========================
void CWaveWall::Draw()
{
	//if (CManager::GetInstance()->GetDebug()->GetEdit())
	{
		//描画処理
		CBuilding::Draw();
	}
}

//==========================
//オブジェクト生成
//==========================
CWaveWall* CWaveWall::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 rot, int wave)
{
	//インスタンス生成
	CWaveWall* pConveni = DBG_NEW CWaveWall;

	//位置の設定
	pConveni->SetPos(pos);

	//向きの設定
	pConveni->SetRot(rot);

	//スケールの設定
	pConveni->SetScale(scale);

	//モデルの生成
	CModel* pModel = CManager::GetInstance()->GetModel();
	pConveni->SetModelIdx(pModel->Regist("data\\MODEL\\wall.x"));
	pConveni->BindModel(pModel->GetMeshAdress(pConveni->GetModelIdx()),
		pModel->GetBuffMatAdress(pConveni->GetModelIdx()),
		pModel->GetNumMatAdress(pConveni->GetModelIdx()),
		pModel->GetTexIdx(pConveni->GetModelIdx()));

	//初期化処理
	pConveni->Init();

	//タイプを設定
	pConveni->SetType(TYPE::BUILDING);
	pConveni->SetBuildingType(BUILDING_TYPE::WAVEWALL);

	//自分のウェーブを保存
	pConveni->m_MyWave = wave;

	return pConveni;
}

//==========================
//自分のウェーブを取得
//==========================
int CWaveWall::GetMyWave()
{
	return m_MyWave;
}