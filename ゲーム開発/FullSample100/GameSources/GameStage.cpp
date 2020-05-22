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

	//スコアスプライト作成
	void GameStage::CreateScoreSprite() {
		AddGameObject<ScoreSprite>(3,
			L"NUMBER_TX",
			true,
			Vec2(320.0f, 320.0f),
			Vec3(0.0f, 200.0f, 0.0f));
	}


	void GameStage::CreateObjectB_CSV() {
		//CSVの行単位の配列
		vector<wstring> LineVec;
		//0番目のカラムがL"TilingFixedBox"である行を抜き出す
		ObjCsvfile.GetSelect(LineVec, 0, L"Tx_Box(Clone)");
		for (auto& v : LineVec) {
			//トークン（カラム）の配列
			vector<wstring> torkns;

			Util::WStrToTokenVector(torkns, v, L',');

			Vec3 Pos(
				(float)_wtof(torkns[1].c_str()),
				(float)_wtof(torkns[2].c_str()),
				(float)_wtof(torkns[3].c_str())
			);
			Vec3 Scale(
				(float)_wtof(torkns[4].c_str()),
				(float)_wtof(torkns[5].c_str()),
				(float)_wtof(torkns[6].c_str())
			);
			Vec3 Rot;
			//回転はXM_PIDIV2の文字列になっている場合がある
			Rot.x = (torkns[7] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(torkns[7].c_str());
			Rot.y = (torkns[8] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(torkns[8].c_str());
			Rot.z = (torkns[9] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(torkns[9].c_str());

			Vec3 Rot2(Rot.x - 45 / 3.1415f, Rot.y / 3.1415f, Rot.z - 90 / 3.1415f);
			AddGameObject<Rock>(Vec3(Pos.x, Pos.y - 0.5f, Pos.z), Scale, Rot);
		}

		ObjCsvfile.GetSelect(LineVec, 0, L"Cube");
		for (auto& v : LineVec) {
			//トークン（カラム）の配列
			vector<wstring> torkns;

			Util::WStrToTokenVector(torkns, v, L',');

			Vec3 col_Pos(
				(float)_wtof(torkns[1].c_str()),
				(float)_wtof(torkns[2].c_str()),
				(float)_wtof(torkns[3].c_str())
			);
			Vec3 col_Scale(
				(float)_wtof(torkns[4].c_str()),
				(float)_wtof(torkns[5].c_str()),
				(float)_wtof(torkns[6].c_str())
			);
			Vec3 col_Rot;
			//回転はXM_PIDIV2の文字列になっている場合がある
			col_Rot.x = (torkns[7] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(torkns[7].c_str());
			col_Rot.y = (torkns[8] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(torkns[8].c_str());
			col_Rot.z = (torkns[9] == L"XM_PIDIV2") ? XM_PIDIV2 : (float)_wtof(torkns[9].c_str());

			//Vec3 Rot2(Rot.x - 45 / 3.1415f, Rot.y / 3.1415f, Rot.z - 90 / 3.1415f);
			AddGameObject<CollisionBox>(Vec3(col_Pos.x, col_Pos.y - 0.5f, col_Pos.z), col_Scale,  col_Rot); //-1 * (* 13.74f )
		}

		ObjCsvfile.GetSelect(LineVec, 0, L"Player");
		for (auto& v : LineVec) {
			//トークン（カラム）の配列
			vector<wstring> torkns;

			Util::WStrToTokenVector(torkns, v, L',');
			PlayerPos.x = (float)_wtof(torkns[1].c_str());
			PlayerPos.y = (float)_wtof(torkns[2].c_str());
			PlayerPos.z = (float)_wtof(torkns[3].c_str());

		}

		ObjCsvfile.GetSelect(LineVec, 0, L"RescurTarget_1");
		for (auto& v : LineVec) {
			//トークン（カラム）の配列
			vector<wstring> torkns;

			Util::WStrToTokenVector(torkns, v, L',');
			Vec3 Pos(
				(float)_wtof(torkns[1].c_str()),
				(float)_wtof(torkns[2].c_str()),
				(float)_wtof(torkns[3].c_str())
			);

			AddGameObject<RescurNomalTarget>(Vec3(Pos), Vec3(0.25f), Vec3(0));

		}
		ObjCsvfile.GetSelect(LineVec, 0, L"RescurTarget_2");
		for (auto& v : LineVec) {
			//トークン（カラム）の配列
			vector<wstring> torkns;

			Util::WStrToTokenVector(torkns, v, L',');
			Vec3 Pos(
				(float)_wtof(torkns[1].c_str()),
				(float)_wtof(torkns[2].c_str()),
				(float)_wtof(torkns[3].c_str())
			);

			AddGameObject<RescurTarget_1>(Vec3(Pos), Vec3(0.25f), Vec3(0));
		}
	}

	void GameStage::OnCreate() {
		try {
			wstring detadir;
			App::GetApp()->GetDataDirectory(detadir);
			csvfile_1.SetFileName(detadir + L"Stage_Csv.csv");// GameStageA.csv");
			csvfile_1.ReadCsv();
			csvfile_2.SetFileName(detadir + L"Stage_Csv_2.csv");// GameStageA.csv");
			csvfile_2.ReadCsv();
			ObjCsvfile.SetFileName(detadir + L"SaveData.csv");// SaveData.csv");// GameStageA.csv");
			ObjCsvfile.ReadCsv();

			CreateObjectB_CSV();

			//SetPhysicsActive(true);
			//ビューとライトの作成
			CreateViewLight();

			auto ground = AddGameObject<FixedBox>(Vec3(100.0f, 1.0f, 100.0f), Vec3(0.0f), Vec3(0.0f, -0.5f, 0.0f));
			ground->AddTag(L"Ground");

			auto goalObj = AddGameObject<GoalObject>(Vec3(1.0f), Vec3(0.0f), Vec3(0.0f, 1.0f,0.0f));
			SetSharedGameObject(L"Goal", goalObj);

			auto player = AddGameObject<Player>(Vec3(0.25f), Vec3(0.0f), PlayerPos);// Vec3(0.0f, 1.0f, 0.0f));
			SetSharedGameObject(L"Player", player);



			//AddGameObject<RescurNomalTarget>(Vec3(3.7f, 5, 4.4f), Vec3(0.25f), Vec3(0));
			//AddGameObject<RescurTarget_1>(Vec3(-2,5 , -2), Vec3(0.25f), Vec3(0));
			AddGameObject<IncreaseObject>(Vec3(5,0,0));
			//AddGameObject<CellIncreaseObject>(0.5f,Vec3(5.0f,0.0f, -5.0f), 5);

			CreateScoreSprite();
			//BGM
			auto XAPtr = App::GetApp()->GetXAudio2Manager();
			m_BGM = XAPtr->Start(L"ERUPTION_WAV", XAUDIO2_LOOP_INFINITE, 0.1f);
			CreateSharedObjectGroup(L"PlayerBullet");
		}
		catch (...) {
			throw;
		}
	}


	void GameStage::OnUpdate() {
		float elapsedTime = App::GetApp()->GetElapsedTime();
		m_TotalTime += elapsedTime;
		if (m_TotalTime >= 10000.0f) {
			m_TotalTime = 0.0f;
		}
		//スコアを更新する
		auto ptrScor = GetSharedGameObject<ScoreSprite>(L"ScoreSprite");
		ptrScor->SetScore(m_TotalTime);
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
