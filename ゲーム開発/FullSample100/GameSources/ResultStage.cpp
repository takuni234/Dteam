/*!
@file ResultStage.cpp
@brief リザルトステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	リザルトステージクラス実体
	//--------------------------------------------------------------------------------------
	void ResultStage::CreateViewLight() {
		const Vec3 eye(0.0f, 5.0f, -5.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	//点滅するスプライト作成
	void ResultStage::CreatePushSprite() {
		//スコア
		auto ptrScore = AddGameObject<ScoreSprite>(1,
			L"NUMBER_TX",
			true,
			Vec2(70.0f, 140.0f),
			Vec3(120.0f, 200.0f, 0.0f));
		ptrScore->SetScore(static_cast<float>(m_SelectNum));
		SetSharedGameObject(L"ResultScoreSprite", ptrScore);
		//ステージ内で取得可能な最大スコア
		auto ptrMaxScore = AddGameObject<ScoreSprite>(1,
			L"NUMBER_TX",
			true,
			Vec2(70.0f, 140.0f),
			Vec3(300.0f, 200.0f, 0.0f));
		ptrMaxScore->SetScore(static_cast<float>(m_SelectNum));
		SetSharedGameObject(L"MaxResultScoreSprite", ptrMaxScore);
		//ステージの背景
		auto ptrSprite = AddGameObject<Sprite>(L"RESULT_BACKGROUND_TX", Vec2(1280.0f, 800.0f), Vec3(0.0f));
		ptrSprite->SetDrawLayer(-3);
		//「救出対象」
		ptrSprite = AddGameObject<Sprite>(L"SURVIVOR_UI_TX", Vec2(100.0f, 100.0f), Vec3(40.0f, 200.0f, 0.0));
		//UIフレーム「□」
		ptrSprite = AddGameObject<Sprite>(L"RESULT_FRAME1_TX", Vec2(1280.0f, 800.0f), Vec3(0.0f));
		ptrSprite->SetDrawLayer(-2);
		//UIフレーム「＝」
		ptrSprite = AddGameObject<Sprite>(L"RESULT_FRAME2_TX", Vec2(1280.0f, 800.0f), Vec3(0.0f, 200.0f,0.0));
		ptrSprite->SetDrawLayer(-1);
		//「助けた人数」
		ptrSprite = AddGameObject<Sprite>(L"SCORE_TX", Vec2(600.0f, 200.0f), Vec3(-200.0f, 200.0f,0.0));
		ptrSprite->SetDrawLayer(0);
		//「/」
		ptrSprite = AddGameObject<Sprite>(L"SLASH_TX", Vec2(840.0f, 280.0f), Vec3(210.0f, 200.0f,0.0));
		ptrSprite->SetDrawLayer(0);
	}

	void ResultStage::CreateSprite() {
		CreateSharedObjectGroup(L"ResultSprite");
		//配置する位置（全体）
		Vec3 DefultPos(0.0f,0.0f,0.0f);
		for (int i = 0; i < static_cast<int>(ResultStageMenuKey::Max); i++) {
			Vec2 createScale(450.0f, 150.0f);
			Vec3 createPos(Vec3(0.0f, -i * 100.0f, 0.0f) + DefultPos);
			wstring txKey;
			switch (static_cast<ResultStageMenuKey>(i))
			{
				//「次のステージへ」の画像
			case ResultStageMenuKey::NextStage:
				txKey = L"TONEXTSTAGE_TX";
				break;
				// 「ステージセレクトへ」の画像
			case ResultStageMenuKey::Select:
				txKey = L"TOSTAGESELECT_TX";
				break;
				// 「リトライ」の画像
			case ResultStageMenuKey::Retry:
				txKey = L"TORETRY_TX";
				break;
				// 「タイトルへ」の画像
			case ResultStageMenuKey::Title:
				txKey = L"TOTITLE_TX";
				break;
			default:
				//エラー
				txKey = L"SKY_TX";
				createScale = Vec2(100.0f);
				break;
			}
			auto ptrSprite = AddGameObject<Sprite>(txKey, createScale, createPos);
			m_ResultSpriteDefultScale.push_back(ptrSprite->GetComponent<Transform>()->GetScale());
			m_ResultSpritePos.push_back(createPos);
			GetSharedObjectGroup(L"ResultSprite")->IntoGroup(ptrSprite);
		}

		auto ptrCursol = AddGameObject<Sprite>(L"LEFTARROWCURSOL_TX", Vec2(50.0f));
		ptrCursol->SetPosition(DefultPos + Vec3(-(m_ResultSpriteDefultScale[static_cast<int>(ResultStageMenuKey::Select)].x + ptrCursol->GetScale().x) * 0.5f, 0.0f,0.0f));
		SetSharedGameObject(L"ResultCursor", ptrCursol);
	}

	void ResultStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();
			CreatePushSprite();
			CreateSprite();
			auto XAPtr = App::GetApp()->GetXAudio2Manager();
			m_BGM = XAPtr->Start(L"REISCUE_BGM", XAUDIO2_LOOP_INFINITE, 0.1f);
		}
		catch (...) {
			throw;
		}
	}

	void ResultStage::OnUpdate() {
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		StageSelectKeyInput();
		bool start =
			CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_START ||
			CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B ||
			KeyState.m_bPressedKeyTbl[VK_SPACE];

		UpdateCursor();

		if (start) {
			ChangeStageSceneSelected();
		}
	}

	void ResultStage::OnDestroy() {
		//BGMのストップ
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}

	void ResultStage::StageSelectKeyInput() {
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		auto elapsedTime = App::GetApp()->GetElapsedTime();

		if (CntlVec[0].bConnected) {
			if (!m_InputOnce) {
				if (CntlVec[0].fThumbLY >= 0.9f) {
					m_SelectNum--;
					m_InputOnce = true;
				}
				else if (CntlVec[0].fThumbLY <= -0.9f) {
					m_SelectNum++;
					m_InputOnce = true;
				}
			}
			else {
				m_Time += elapsedTime;
				if (m_Time > 0.3f) {
					m_InputOnce = false;
					m_Time = 0.0f;
				}
			}
			if (CntlVec[0].fThumbLY <= 0.05f && CntlVec[0].fThumbLY >= -0.05f) {
				m_InputOnce = false;
				m_Time = 0.0f;
			}
		}
		else if (!(KeyState.m_bPushKeyTbl['S'] && KeyState.m_bPushKeyTbl['D'])) {
			if (!m_InputOnce) {
				if (KeyState.m_bPushKeyTbl['S']) {
					m_SelectNum++;
					m_InputOnce = true;
				}
				if (KeyState.m_bPushKeyTbl['W']) {
					m_SelectNum--;
					m_InputOnce = true;
				}
			}
			else {
				m_Time += elapsedTime;
				if (m_Time > 0.3f) {
					m_InputOnce = false;
					m_Time = 0.0f;
				}
			}
			if (KeyState.m_bUpKeyTbl['S'] && KeyState.m_bUpKeyTbl['W']) {
				m_InputOnce = false;
				m_Time = 0.0f;
			}
		}

		if (m_SelectNum <= 0) {
			m_SelectNum = static_cast<int>(ResultStageMenuKey::Max);
		}
		m_MenuKey = ResultStageMenuKey(m_SelectNum % static_cast<int>(ResultStageMenuKey::Max));
	}

	void ResultStage::UpdateCursor() {
		auto ptrScene = App::GetApp()->GetScene<Scene>();
		GetSharedGameObject<ScoreSprite>(L"ResultScoreSprite")->SetScore(ptrScene->GetRescueCount());
		GetSharedGameObject<ScoreSprite>(L"MaxResultScoreSprite")->SetScore(ptrScene->GetAllMember());
		auto ptrCursor = GetSharedGameObject<Sprite>(L"ResultCursor");
		auto ptrTrans = ptrCursor->GetComponent<Transform>();
		ptrTrans->SetPosition(m_ResultSpritePos[static_cast<int>(m_MenuKey)] + Vec3((m_ResultSpriteDefultScale[static_cast<int>(m_MenuKey)].x + ptrTrans->GetScale().x) * 0.5f, 0.0f, 0.0f));
	}

	void ResultStage::ChangeStageSceneSelected() {
		auto ptrScene = App::GetApp()->GetScene<Scene>();
		auto key = ptrScene->GetCurrentSceneKey();
		switch (m_MenuKey)
		{
		case ResultStageMenuKey::NextStage:
			switch (key)
			{
			case SelectKey::Stage1:
				ptrScene->SetLimitTime(120.0f);
				ptrScene->SetCurrentSceneKey(static_cast<SelectKey>(static_cast<int>(key) + 1));
				ptrScene->SetStageCSVKey(L"Stage2.csv");
				ptrScene->ChangeScene(SceneKey::Game);
				break;
			case SelectKey::Stage2:
				ptrScene->SetLimitTime(200.0f);
				ptrScene->SetCurrentSceneKey(static_cast<SelectKey>(static_cast<int>(key) + 1));
				ptrScene->SetStageCSVKey(L"SaveData25.csv");
				ptrScene->ChangeScene(SceneKey::Game);
				break;
			case static_cast<SelectKey>((static_cast<int>(SelectKey::Max) - 1)): // 最後のキー
				ptrScene->SetCurrentSceneKey(static_cast<SelectKey>(0)); // 最初のキー(0)で初期化
				ptrScene->ChangeScene(SceneKey::Title);
				break;
			default:
				break;
			}
			break;
		case ResultStageMenuKey::Select:
			ptrScene->ChangeScene(SceneKey::Select);
			break;
		case ResultStageMenuKey::Retry:
			ptrScene->ChangeScene(SceneKey::Game);
			break;
		case ResultStageMenuKey::Title:
			ptrScene->ChangeScene(SceneKey::Title);
			break;
		default:
			break;
		}
	}
}
//end basecross
