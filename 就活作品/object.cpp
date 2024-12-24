//==========================
// 
// オブジェクト管理[object.cpp]
// Author Yuki Goto
//
//==========================

//include
#include"object.h"

//静的メンバの初期化
int CObject::m_nNumAll = 0;
CObject* CObject::m_apObject[PRIORITY][MAX_OBJECT] = {};
CObject* CObject::m_pTop[PRIORITY] = {};//最初のオブジェクト
CObject* CObject::m_pCur[PRIORITY] = {};//最後尾のオブジェクト
//========================
//描画優先設定
//========================
CObject::CObject(int nPriority) :m_nID(0), m_pNext(nullptr), m_pPrev(nullptr), m_bDeath(false)
{
	m_Type = TYPE::NONE;//オブジェクトタイプ
	
	m_nPriority = nPriority;//描画優先度設定

	if (m_pTop[m_nPriority] == nullptr)
	{//最初のオブジェクトが登録されてない

		m_pTop[m_nPriority] = this;//最初のオブジェクトに登録
		m_pCur[m_nPriority] = this;//現在のオブジェクトに登録
	}
	else if(m_pTop[m_nPriority] != nullptr)
	{//最初のオブジェクトが登録されている

		m_pPrev = m_pCur[m_nPriority];//前のオブジェクトに最後尾のオブジェクトを登録
		m_pPrev->m_pNext = this;//前のオブジェクトの次に自分を登録
		m_pCur[m_nPriority] = this;//最後尾のオブジェクトに自分を登録
	}

	

	/*for (int i = 0; i < MAX_OBJECT; i++)
	{
		if (m_apObject[m_nPriority][i] == nullptr)
		{
			m_apObject[m_nPriority][i] = this;
			m_nID = i;
			m_nNumAll++;
			break;
		}
	}*/

}

//========================
//デストラクタ
//========================
CObject::~CObject()
{
	
}

//========================
//全オブジェクト解放
//========================
void CObject::ReleaseAll(void)
{
	/*for (int nPriority = 0; nPriority < PRIORITY; nPriority++)
	{
		for (int obj = 0; obj < MAX_OBJECT; obj++)
		{
			if (m_apObject[nPriority][obj] != nullptr)
			{
				m_apObject[nPriority][obj]->Uninit();
				m_apObject[i]->Release();
				m_apObject[nPriority][obj] = nullptr;
			}
		}
	}*/

	for (int i = 0; i < PRIORITY; i++)
	{
		CObject* pObj = m_pTop[i];

		while (pObj != nullptr)
		{
			CObject* pNext = pObj->m_pNext;

			pObj->Uninit();
			
			pObj = pNext;
		}
	}
	

	//死亡フラグが立ってるオブジェクトを削除
	ReleseDeath();
}

//========================
//全オブジェクト更新
//========================
void CObject::UpdateAll(void)
{
	/*for (int nPriority = 0; nPriority < PRIORITY; nPriority++)
	{
		for (int obj = 0; obj < MAX_OBJECT; obj++)
		{
			if (m_apObject[nPriority][obj] != nullptr)
			{
				m_apObject[nPriority][obj]->Update();
			}
		}
	}*/

	for (int i = 0; i < PRIORITY; i++)
	{
		CObject* pObj = m_pTop[i];

		while (pObj != nullptr)
		{
			CObject* pNext = pObj->m_pNext;

			pObj->Update();

			pObj = pNext;
		}

	}
	
	//死亡フラグが立ってるオブジェクトを削除
	ReleseDeath();
}

//========================
//全オブジェクト描画
//========================
void CObject::DrawAll(void)
{
	/*for (int nPriority = 0; nPriority < PRIORITY; nPriority++)
	{
		for (int obj = 0; obj < MAX_OBJECT; obj++)
		{
			if (m_apObject[nPriority][obj] != nullptr)
			{
				m_apObject[nPriority][obj]->Draw();
			}
		}
	}*/

	//死亡フラグが立ってるオブジェクトを削除
	ReleseDeath();

	for (int i = 0; i < PRIORITY; i++)
	{
		CObject* pObj = m_pTop[i];

		while (pObj != nullptr)
		{
			CObject* pNext = pObj->m_pNext;

			pObj->Draw();

			pObj = pNext;
		}
	}
}

//========================
//自分自身の解放
//========================
void CObject::Release(void)
{
	/*int nID = m_nID;
	int nPriority = m_nPriority;*/

	/*if (m_apObject[nPriority][nID] != nullptr)
	{
		delete m_apObject[nPriority][nID];
		m_apObject[nPriority][nID] = nullptr;
		m_nNumAll--;
	}*/

	//死亡フラグを立てる
	SwitchDeath();
}

//========================
//オブジェクト取得
//========================
CObject* CObject::GetObj(CObject* Object, int priority)
{
	if (Object != nullptr)
	{
		return Object->m_pNext;
	}

	return m_pTop[priority];
}

//========================
//タイプ取得
//========================
CObject::TYPE CObject::GetType(void)
{
	return m_Type;
}

//========================
//タイプ設定
//========================
void CObject::SetType(TYPE type)
{
	m_Type = type;
}

//========================
//次のオブジェクトを取得
//========================
CObject* CObject::GetNextObj()
{
	return m_pNext;
}

//========================
//前のオブジェクトを取得
//========================
CObject* CObject::GetPrevObj()
{
	return m_pPrev;
}

//========================
//死亡フラグの切り替え
//========================
void CObject::SwitchDeath()
{
	m_bDeath = true;
}

//========================
//死亡フラグが立ってるオブジェクト削除
//========================
void CObject::ReleseDeath()
{

	for (int i = 0; i < PRIORITY; i++)
	{
		CObject* pObj = m_pTop[i];

		while (pObj != nullptr)
		{
			CObject* pNext = pObj->m_pNext;

			if (pObj->m_bDeath)
			{
				pObj->DisengageList();//フラグから削除
				delete pObj;
			}
			pObj = pNext;
		}
	}
}

//========================
//リストから切り離す
//========================
void CObject::DisengageList()
{
	if (m_pTop[m_nPriority] == this)
	{//自分が最初のオブジェクト

		if (m_pNext != nullptr)
		{//次のオブジェクトがある

			//最初のオブジェクトを次のオブジェクトに変える
			m_pTop[m_nPriority] = m_pNext;
			m_pNext->m_pPrev = nullptr;
		}
		if (m_pNext == nullptr)
		{
			m_pTop[m_nPriority] = nullptr;
			m_pCur[m_nPriority] = nullptr;
		}
	}
	else if (m_pCur[m_nPriority] == this)
	{//自分が最後のオブジェクト

		//前のオブジェクトを最後に登録する
		m_pCur[m_nPriority] = m_pPrev;
		m_pPrev->m_pNext = nullptr;

	}
	else
	{
		if (m_pPrev != nullptr)
		{
			//前のオブジェクトに登録されている次のオブジェクトを自分の次にする
			m_pPrev->m_pNext = m_pNext;
		}
		
		if (m_pNext != nullptr)
		{//次のオブジェクトがある

			//次のオブジェクトに登録されてる前のオブジェクトを自分の前にする
			m_pNext->m_pPrev = m_pPrev;
		}
	}
}