//==========================
// 
// 敵の移動地点[enemymovepoint.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "enemymovepoint.h"
#include "manager.h"
#include "texture.h"

//静的メンバ初期化
const int CEnemyMovePoint::PRIORITY = 0;//描画順

//==========================
//コンストラクタ
//==========================
CEnemyMovePoint::CEnemyMovePoint(int nPriority) :
	CFild(nPriority)
{

}

//==========================
//デストラクタ
//==========================
CEnemyMovePoint::~CEnemyMovePoint()
{

}

//==========================
//初期化処理
//==========================
HRESULT CEnemyMovePoint::Init()
{
	//初期設定
	CFild::Init();

	return S_OK;
}

//==========================
//終了処理
//==========================
void CEnemyMovePoint::Uninit()
{
	//終了処理
	CFild::Uninit();
}

//==========================
//更新処理
//==========================
void CEnemyMovePoint::Update()
{
	//更新処理
	CFild::Update();
}

//==========================
//描画処理
//==========================
void CEnemyMovePoint::Draw()
{
#ifdef _DEBUG

	//描画処理
	CFild::Draw();

#endif

}

//==========================
//オブジェクト生成
//==========================
CEnemyMovePoint* CEnemyMovePoint::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot)
{
	//インスタンス生成
	CEnemyMovePoint* pEnemyMovePoint = DBG_NEW CEnemyMovePoint;

	//位置の設定
	pEnemyMovePoint->SetPos(D3DXVECTOR3(pos.x, 0.5f, pos.z));

	//大きさの設定
	pEnemyMovePoint->SetSize(size);

	//大きさの設定
	pEnemyMovePoint->SetRot(rot);

	//色の設定
	pEnemyMovePoint->SetCor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));

	//初期化処理
	pEnemyMovePoint->Init();

	//テクスチャ設定
	/*CTexture* pTex = CManager::GetInstance()->GetTexture();
	pEnemyMovePoint->m_nTexIdx = pTex->Regist("data\\TEXTURE\\blood.png");
	pEnemyMovePoint->BindTexture(pTex->GetAdress(pEnemyMovePoint->m_nTexIdx));*/

	//タイプ設定
	pEnemyMovePoint->SetType(TYPE::FILD);
	pEnemyMovePoint->SetFild(FILDTYPE::ENEMYMOVEPOINT);

	return pEnemyMovePoint;
}