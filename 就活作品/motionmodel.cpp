//==========================
// 
// モーションするモデルの描画処理[motionmodel.cpp]
// Author Yuki Goto
//
//==========================

//include
#include "motionmodel.h"
#include "manager.h"

//静的メンバ初期化
const int CMotionModel::PRIORITY = 1;//描画順

//==========================
//コンストラクタ
//==========================
CMotionModel::CMotionModel(int nPriority) :CObjectgame(nPriority)
{
	m_Shadow = nullptr;
	m_PartsNum = 0;//モデルパーツを読み込んだ回数

	for (int i = 0; i < MAX_PARTS; i++)
	{
		m_PartsList[i] = nullptr;
		m_FirstMotion[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_FirstMotion[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	for (int i = 0; i < MAX_MOTION; i++)
	{
		m_MotionInfo[i].Loop = 0;
		m_MotionInfo[i].nKeyNum = 0;
		for (int n = 0; n < MAX_PARTS; n++)
		{
			m_MotionInfo[i].aKeySet[n].nFrame = 0;
			for (int j = 0; j < MAX_PARTS; j++)
			{
				m_MotionInfo[i].aKeySet[n].aKey[j].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				m_MotionInfo[i].aKeySet[n].aKey[j].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
		}
	}

	m_nCurKey = 0;//現在のキー番号
	m_nCntMotion = 0;//モーションカウンター
	m_MotionType = MOTION_TYPE::NEUTRAL;
	m_oldMotion = MOTION_TYPE::NEUTRAL;
}

//==========================
//デストラクタ
//==========================
CMotionModel::~CMotionModel()
{

}

//==========================
//初期化処理
//==========================
HRESULT CMotionModel::Init()
{
	SetMotion(MOTION_TYPE::NEUTRAL);

	m_Shadow = CShadow::Create(GetPos(), D3DXVECTOR3(15.0f, 0.0f, 15.0f));

	return S_OK;
}

//==========================
//終了処理
//==========================
void CMotionModel::Uninit()
{
	for (int i = 0; i < MAX_PARTS; i++)
	{
		if (m_PartsList[i] != nullptr)
		{
			m_PartsList[i]->Uninit();
			m_PartsList[i] = nullptr;
		}
	}

	if (m_Shadow != nullptr)
	{
		m_Shadow->Uninit();
		m_Shadow = nullptr;
	}

	Release();
}

//==========================
//更新処理
//==========================
void CMotionModel::Update()
{

	for (int i = 0; i < MAX_PARTS; i++)
	{
		if (m_PartsList[i] != nullptr)
		{
			m_PartsList[i]->Update();
		}
	}

	if (m_Shadow != nullptr)
	{
		m_Shadow->Move(GetPos());
	}
}

//==========================
//描画処理
//==========================
void CMotionModel::Draw()
{
	//行列の生成
	CreateMtx();

	//モデルパーツの描画
	PartsDraw();
}

//==========================
//行列の生成
//==========================
void CMotionModel::CreateMtx()
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//デバイスの取得

	D3DXMATRIX mtxRot, mtxTrans;//計算用マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&GetMtxWorld());

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, GetRot().y, GetRot().x, GetRot().z);
	D3DXMatrixMultiply(&GetMtxWorld(), &GetMtxWorld(), &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);
	D3DXMatrixMultiply(&GetMtxWorld(), &GetMtxWorld(), &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &GetMtxWorld());
}

//==========================
//パーツの描画
//==========================
void CMotionModel::PartsDraw()
{
	for (int i = 0; i < MAX_PARTS; i++)
	{
		if (m_PartsList[i] != nullptr)
		{
			m_PartsList[i]->Draw();
		}
	}
}

//==========================
//モデル生成
//==========================
CMotionModel* CMotionModel::Create()
{
	CMotionModel* pMotionModel = DBG_NEW CMotionModel;

	return pMotionModel;
}

//==========================
//パーツの情報を取得
//==========================
CModelParts* CMotionModel::GetParts(int PartsNum)
{
	return m_PartsList[PartsNum];
}

//==========================
//パーツの生成
//==========================
void CMotionModel::SetParts(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CModelParts* parents, int ModelPartsNum, D3DXVECTOR3 scale)
{
	m_PartsList[m_PartsNum] = CModelParts::Create(pos, rot, parents, ModelPartsNum, scale);
	m_PartsNum++;
}

//==========================
//モデルパーツのマトリックスを取得
//==========================
D3DXMATRIX& CMotionModel::GetPartsMtx(int PartsNum)
{
	return m_PartsList[PartsNum]->GetMtxWorld();
}

//==========================
//パーツの削除
//==========================
void CMotionModel::DeleteParts(int num)
{
	if (m_PartsList[num] != nullptr)
	{
		m_PartsList[num]->Uninit();
		m_PartsList[num] = nullptr;
		m_PartsNum--;
	}
}

//==========================
//パーツが存在するか判定
//==========================
bool CMotionModel::GetPartsExistence(int PartsNum)
{
	if (m_PartsList[PartsNum] == nullptr)
	{
		return false;
	}

	return true;
}

//==========================
//被弾時の色に設定
//==========================
void CMotionModel::SetDamageCor()
{
	for (int i = 0; i < MAX_PARTS; i++)
	{
		if (m_PartsList[i] != nullptr)
		{
			m_PartsList[i]->SetCor();
		}
	}
}

//==========================
//透明度を減らす
//==========================
void CMotionModel::SubTransparency(float col)
{
	for (int i = 0; i < MAX_PARTS; i++)
	{
		if (m_PartsList[i] != nullptr)
		{
			m_PartsList[i]->SetCor();
			m_PartsList[i]->SubCol(col);
		}
	}
}

//==========================
//現在のモーションを取得
//==========================
CMotionModel::MOTION_TYPE CMotionModel::GetMotion()
{
	return m_MotionType;
}

//==========================
//前のモーションを取得
//==========================
CMotionModel::MOTION_TYPE CMotionModel::GetOldMotion()
{
	return m_oldMotion;
}

//==========================
//前のモーションを保存
//==========================
void CMotionModel::SetOldMotion(MOTION_TYPE motion)
{
	m_oldMotion = motion;
}

//==========================
//現在のキー番号取得
//==========================
int CMotionModel::GetKeyNum()
{
	return m_nCurKey;
}

//==========================
//モーションを設定
//==========================
void CMotionModel::SetMotion(MOTION_TYPE MotionType)
{
	if (m_MotionType == MotionType)
	{
		return;
	}

	m_MotionType = MotionType;

	for (int i = 0; i < MAX_PARTS; i++)
	{
		if (m_PartsList[i] != nullptr)
		{
			KeepFirstPos(m_PartsList[i]->GetMotionPos(), i);
			KeepFirstRot(m_PartsList[i]->GetRot(), i);
			//m_FirstMotion[i].pos = m_PartsList[i]->GetMotionPos();
			//m_FirstMotion[i].rot = m_PartsList[i]->GetRot();
		}
	}

	m_nCurKey = 0;//現在のキー番号
	m_nCntMotion = 0;//モーションカウンター
}

//==========================
//モーション処理
//==========================
void CMotionModel::Motion()
{
	//パーツの数値の計算
	CalParts();

	//モーションカウンターを進める
	MotionCountUpdate();

	//モーションの情報を更新
	UpdateMotionInfo();
}

//==========================
//モーションの情報を更新
//==========================
void CMotionModel::UpdateMotionInfo()
{
	if (ExceedMaxFlame())
	{//モーションカウンターが再生フレーム数に達した

		for (int i = 0; i < MAX_PARTS; i++)
		{
			if (m_PartsList[i] != nullptr)
			{
				KeepFirstPos(m_PartsList[i]->GetMotionPos(), i);
				KeepFirstRot(m_PartsList[i]->GetRot(), i);
				//m_FirstMotion[i].pos = m_PartsList[i]->GetMotionPos();
				//m_FirstMotion[i].rot = m_PartsList[i]->GetRot();
			}
		}

		m_nCurKey++;//現在のキー番号を進める
		m_nCntMotion = 0;//カウンターを初期化

		if (m_nCurKey == m_MotionInfo[(int)m_MotionType].nKeyNum)
		{//現在のキー番号がキーの総数になった
			m_nCurKey = 0;//現在のキー番号を0に戻す

			if (m_MotionInfo[(int)m_MotionType].Loop == 0)
			{//現在のモーションがループしないとき

				//今のモーションを保存
				SetOldMotion(GetMotion());

				//待機モーションに変更
				SetMotion(MOTION_TYPE::NEUTRAL);
			}
		}
	}
}

//==========================
//カウンターの更新
//==========================
void CMotionModel::MotionCountUpdate()
{
	m_nCntMotion++;
}

//==========================
//パーツの更新に必要な数値を計算
//==========================
void CMotionModel::CalParts()
{
	for (int nCntModel = 0; nCntModel < MAX_PARTS; nCntModel++)
	{
		if (m_PartsList[nCntModel] != nullptr)
		{
			//現在値を求める
			D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			//パーツの向きを求める
			rot = CalMotionRot(nCntModel);

			//向きの設定
			m_PartsList[nCntModel]->SetRot(rot);

			if (!m_PartsList[nCntModel]->GetExistParent())
			{//親のパーツがないとき

				//パーツの位置を求める
				pos = CalMotionPos(nCntModel);

				//位置の設定
				m_PartsList[nCntModel]->SetMotionPos(pos);
			}
		}
	}
}

//==========================
//モーションのカウンターが再生フレームを超えたか判定
//==========================
bool CMotionModel::ExceedMaxFlame()
{
	if (m_nCntMotion == m_MotionInfo[(int)m_MotionType].aKeySet[m_nCurKey].nFrame)
	{
		return true;
	}

	return false;
}

//==========================
//モーション中のパーツの位置を求める
//==========================
D3DXVECTOR3& CMotionModel::CalMotionPos(int PartsNum)
{
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//相対値を求める
	float Cur = (float)m_nCntMotion / m_MotionInfo[(int)m_MotionType].aKeySet[m_nCurKey].nFrame;

	//位置の差分を求める
	D3DXVECTOR3 diffpos = m_MotionInfo[(int)m_MotionType].aKeySet[m_nCurKey].aKey[PartsNum].pos - m_FirstMotion[PartsNum].pos;

	//現在値を求める
	pos.x = m_FirstMotion[PartsNum].pos.x + (diffpos.x * Cur);
	pos.y = m_FirstMotion[PartsNum].pos.y + (diffpos.y * Cur);
	pos.z = m_FirstMotion[PartsNum].pos.z + (diffpos.z * Cur);

	return pos;
}

//==========================
//モーション中のパーツの向きを求める
//==========================
D3DXVECTOR3& CMotionModel::CalMotionRot(int PartsNum)
{
	D3DXVECTOR3 addrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//相対値を求める
	float Cur = (float)m_nCntMotion / m_MotionInfo[(int)m_MotionType].aKeySet[m_nCurKey].nFrame;

	//向きの差分を求める
	addrot.x = RevisionRot(m_MotionInfo[(int)m_MotionType].aKeySet[m_nCurKey].aKey[PartsNum].rot.x, m_FirstMotion[PartsNum].rot.x, Cur);
	addrot.y = RevisionRot(m_MotionInfo[(int)m_MotionType].aKeySet[m_nCurKey].aKey[PartsNum].rot.y, m_FirstMotion[PartsNum].rot.y, Cur);
	addrot.z = RevisionRot(m_MotionInfo[(int)m_MotionType].aKeySet[m_nCurKey].aKey[PartsNum].rot.z, m_FirstMotion[PartsNum].rot.z, Cur);

	rot.x = m_FirstMotion[PartsNum].rot.x + addrot.x;
	rot.y = m_FirstMotion[PartsNum].rot.y + addrot.y;
	rot.z = m_FirstMotion[PartsNum].rot.z + addrot.z;

	return rot;
}

//==========================
//最初の位置を保存
//==========================
void CMotionModel::KeepFirstPos(D3DXVECTOR3 pos, int PartsNum)
{
	m_FirstMotion[PartsNum].pos = pos;
}

//==========================
//最初の向きを保存
//==========================
void CMotionModel::KeepFirstRot(D3DXVECTOR3 rot, int PartsNum)
{
	m_FirstMotion[PartsNum].rot = rot;
}

//==========================
//ファイルを読み込む
//==========================
void CMotionModel::LoadFile(const char name[256], D3DXVECTOR3 scale)
{
	ifstream inputfile(name);//テキストファイルを開く

	string Data;
	char FileName[256];//モデルのファイルパス
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//位置
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//向き
	int Index = 0;//モデルの番号
	int Parent = 0;//親の番号
	int ModelNum = 0;//モデルの数
	int ModelPartsNum[20];//モデルパーツの番号
	int motionCount = 0;//モーションの数
	int KeySetCount = 0;//キーセットの数
	int KeyCount = 0;//キーの数
	float Radius = 0.0f;//当たり判定の半径

	if (!inputfile)
	{
		return;
	}

	while (1)
	{
		getline(inputfile, Data);

		//モデル数
		if (Data.find("モデル数") != string::npos)
		{
			getline(inputfile, Data);
			inputfile >> Data;
			inputfile >> Data;
			inputfile >> ModelNum;
		}

		//モデルファイル
		if (Data.find("モデルファイル名") != string::npos)
		{
			CModel* pModel = CManager::GetInstance()->GetModel();
			for (int i = 0; i < ModelNum; i++)
			{
				getline(inputfile, Data, '=');
				inputfile >> FileName;
				ModelPartsNum[i] = pModel->Regist(FileName);
			}
		}

		//キャラクター情報
		if (Data.find("PARTSSET") != string::npos)
		{
			while (getline(inputfile, Data, '='))//情報を読み込む
			{
				if (Data.find("INDEX") != string::npos)
				{
					inputfile >> Index;
				}
				if (Data.find("PARENT") != string::npos)
				{
					inputfile >> Parent;
				}
				if (Data.find("POS") != string::npos)
				{
					inputfile >> pos.x;
					inputfile >> pos.y;
					inputfile >> pos.z;
				}
				if (Data.find("ROT") != string::npos)
				{
					inputfile >> rot.x;
					inputfile >> rot.y;
					inputfile >> rot.z;
					inputfile >> Data;

					if (Data.find("END_PARTSSET") != string::npos)
					{
						if (Parent == -1)
						{
							m_PartsList[m_PartsNum] = CModelParts::Create(pos, rot, nullptr, ModelPartsNum[m_PartsNum], scale);
						}
						else
						{
							m_PartsList[m_PartsNum] = CModelParts::Create(pos, rot, m_PartsList[Parent], ModelPartsNum[m_PartsNum], scale);
						}

						m_PartsNum++;
						Data.clear();
						break;
					}
				}
			}
		}

		////当たり判定の情報
		//if (Data.find("COLLISIONSET") != string::npos)
		//{
		//	while (getline(inputfile, Data, '='))//情報を読み込む
		//	{
		//		if (Data.find("INDEX") != string::npos)
		//		{
		//			inputfile >> Index;
		//		}
		//		if (Data.find("PARENT") != string::npos)
		//		{
		//			inputfile >> Parent;
		//		}
		//		if (Data.find("POS") != string::npos)
		//		{
		//			inputfile >> pos.x;
		//			inputfile >> pos.y;
		//			inputfile >> pos.z;
		//		}
		//		if (Data.find("RADIUS") != string::npos)
		//		{
		//			inputfile >> Radius;
		//			break;
		//		}
		//	}
		//	getline(inputfile, Data);
		//	if (Data.find("END_COLLISIONSET") != string::npos)
		//	{
		//		m_PartsList[Index]->CreateVisual(pos, Radius);
		//	}
		//}

		//モーション情報
		if (Data.find("MOTIONSET") != string::npos)
		{
			while (getline(inputfile, Data, '='))//情報を読み込む
			{
				if (Data.find("LOOP") != string::npos)
				{
					inputfile >> m_MotionInfo[motionCount].Loop;
				}
				if (Data.find("NUM_KEY") != string::npos)
				{
					inputfile >> m_MotionInfo[motionCount].nKeyNum;
					break;
				}
			}
			while (getline(inputfile, Data))//情報を読み込む
			{
				if (Data.find("KEYSET") != string::npos)
				{
					while (getline(inputfile, Data, '='))//情報を読み込む
					{
						if (Data.find("FRAME") != string::npos)
						{
							inputfile >> m_MotionInfo[motionCount].aKeySet[KeySetCount].nFrame;
							break;
						}
					}
				}

				if (Data.find("KEY") != string::npos)
				{
					while (getline(inputfile, Data, '='))//情報を読み込む
					{
						if (Data.find("POS") != string::npos)
						{
							inputfile >> m_MotionInfo[motionCount].aKeySet[KeySetCount].aKey[KeyCount].pos.x;
							inputfile >> m_MotionInfo[motionCount].aKeySet[KeySetCount].aKey[KeyCount].pos.y;
							inputfile >> m_MotionInfo[motionCount].aKeySet[KeySetCount].aKey[KeyCount].pos.z;
						}
						if (Data.find("ROT") != string::npos)
						{
							inputfile >> m_MotionInfo[motionCount].aKeySet[KeySetCount].aKey[KeyCount].rot.x;
							inputfile >> m_MotionInfo[motionCount].aKeySet[KeySetCount].aKey[KeyCount].rot.y;
							inputfile >> m_MotionInfo[motionCount].aKeySet[KeySetCount].aKey[KeyCount].rot.z;
							KeyCount++;
							getline(inputfile, Data);
							getline(inputfile, Data);
							getline(inputfile, Data);
							if (Data.find("END_KEYSET") != string::npos)
							{
								KeySetCount++;
								KeyCount = 0;
							}
							break;
						}
					}
				}
				if (Data.find("END_MOTIONSET") != string::npos)
				{
					KeySetCount = 0;
					motionCount++;
					break;
				}
			}
		}

		if (Data.find("END_SCRIPT") != string::npos)
		{
			break;
		}
	}

	inputfile.close();//ファイルを閉じる

}