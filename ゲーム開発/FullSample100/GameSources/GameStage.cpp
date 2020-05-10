/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------
	void GameStage::CreateViewLight() {
		const Vec3 eye(0.0f, 10.0f, -5.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<PlayerCamera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	void GameStage::CreateStageCellMap() {
		float  PieceSize = 0.2f;
		auto Ptr = AddGameObject<StageCellMap>(Vec3(-3.5f*0.2, -0.5f, -3.5f*0.2), PieceSize, 7, 7);
		//セルマップの区画を表示する場合は以下の設定
		Ptr->SetDrawActive(true);
		//さらにセルのインデックスとコストを表示する場合は以下の設定
		//Ptr->SetCellStringActive(true);
		SetSharedGameObject(L"StageCellMap", Ptr);
		//セルマップへのボックスのコスト設定
		SetCellMapCost();
	}
	void GameStage::SetCellMapCost() {
		auto PtrCellmap = GetSharedGameObject<StageCellMap>(L"StageCellMap");
		//セルマップからセルの配列を取得
		auto& CellVec = PtrCellmap->GetCellVec();
		//CellVec={
		//	{4,4,4,4,4,4,4},
		//	{4,4,4,4,4,4,4},
		//	{4,4,4,4,4,4,4},
		//	{4,4,4,4,4,4,4},
		//	{4,4,4,4,4,4,4},
		//	{4,4,4,4,4,4,4},
		//	{4,4,4,4,4,4,4},
		//};
		
	}
	void GameStage::OnCreate() {
		try {
			SetPhysicsActive(true);
			//ビューとライトの作成
			CreateViewLight();
			auto ground = AddGameObject<FixedBox>(Vec3(30.0f, 1.0f, 30.0f), Vec3(0.0f), Vec3(0.0f, -1.0f, 0.0f));
			ground->AddTag(L"Ground");

			auto player = AddGameObject<Player>(Vec3(0.25f), Vec3(0.0f), Vec3(0.0f, 1.0f, 0.0f));
			SetSharedGameObject(L"Player", player);

			AddGameObject<RescurNomalTarget>(Vec3(1, 0, 1), Vec3(0.25f), Vec3(0));
			AddGameObject<RescurTarget_1>(Vec3(-2, 0, -2), Vec3(0.25f), Vec3(0));
			AddGameObject<IncreaseObject>(Vec3(0,0,0));


			//BGM
			auto XAPtr = App::GetApp()->GetXAudio2Manager();
			//m_BGM = XAPtr->Start(L"", XAUDIO2_LOOP_INFINITE, 0.1f);
			CreateSharedObjectGroup(L"PlayerBullet");
		}
		catch (...) {
			throw;
		}
	}

	void GameStage::UpdateStage() {
		m_InputHandler.PushHandle(GetThis<GameStage>());
		if (m_IsUpdate) {
			Stage::UpdateStage();
		}
	}

	void GameStage::OnDestroy() {
		//BGMのストップ
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}

	void GameStage::OnPushStart() {
		if (m_IsUpdate) {
			m_IsUpdate = false;
		}
		else {
			m_IsUpdate = true;
		}
	}
}
//end basecross
