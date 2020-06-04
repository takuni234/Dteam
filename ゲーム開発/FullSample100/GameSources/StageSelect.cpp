/*!
@file StageSelect.cpp
@brief ステージセレクト実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	ステージセレクトクラス実体
	//--------------------------------------------------------------------------------------
	void StageSelect::CreateViewLight() {
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

	void StageSelect::CreateSelectSprite() {
		//「ステージ」のテキスト
		auto ptrStageTx = AddGameObject<Sprite>(L"STAGE_TX", Vec2(600.0f, 200.0f), Vec3(-70.0f,300.0f,0.0f));
		//「0～9」
		auto ptrScore = AddGameObject<ScoreSprite>(1,
			L"NUMBERCOLOR_TX",
			true,
			Vec2(65.0f, 130.0f),
			Vec3(130.0f, 300.0f, 0.0f));
		ptrScore->SetScore(static_cast<int>(SelectKey::Stage1) + 1);

		//ステージのスクリーンショット
		auto ptrSprite = AddGameObject<Sprite>(L"Stage1_TX", Vec2(1280.0f, 800.0f) * 0.5f, Vec3(0.0f));
		SetSharedGameObject(L"StageTXSprite", ptrSprite);

		auto ptrBGSprite = AddGameObject<Sprite>(L"STAGESELECT_BACKGROUND_TX", Vec2(1280.0f, 800.0f), Vec3(0.0f));
		ptrBGSprite->SetDrawLayer(-1);

		//選択カーソル
		auto ptrRArrowCursol = AddGameObject<Sprite>(L"RIGHTARROWCURSOL_TX", m_ArrowCursorScale, Vec3(500.0f,0.0f,0.0f));
		SetSharedGameObject(L"RArrowCursorSprite", ptrRArrowCursol);
		//選択カーソル
		auto ptrLArrowCursol = AddGameObject<Sprite>(L"RIGHTARROWCURSOL_TX", m_ArrowCursorScale, Vec3(0.0f,0.0f,XM_PI), Vec3(-500.0f,0.0f,0.0f));
		SetSharedGameObject(L"LArrowCursorSprite", ptrLArrowCursol);
	}

	void StageSelect::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();
			CreateSelectSprite();
			auto XAPtr = App::GetApp()->GetXAudio2Manager();
			m_BGM = XAPtr->Start(L"REISCUE_BGM", XAUDIO2_LOOP_INFINITE, 0.1f);
		}
		catch (...) {
			throw;
		}
	}

	void StageSelect::OnUpdate() {
		//入力から値を変更
		StageSelectKeyInput();
		//テクスチャを更新
		UpdateSpriteTX();
		//シーン遷移
		ChangeStageSceneSelected();
	}

	void StageSelect::StageSelectKeyInput() {
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		int currentNum = m_SelectNum;
		auto elapsedTime = App::GetApp()->GetElapsedTime();

		if (CntlVec[0].bConnected) {
			if (!m_InputOnce) {
				if (CntlVec[0].fThumbLX >= 0.9f) {
					m_SelectNum++;
					m_InputOnce = true;
				}
				else if (CntlVec[0].fThumbLX <= -0.9f) {
					m_SelectNum--;
					m_InputOnce = true;
				}
			}
			else {
				m_InputTime += elapsedTime;
				if (m_InputTime > 0.3f) {
					m_InputOnce = false;
					m_InputTime = 0.0f;
				}
			}
			if (CntlVec[0].fThumbLX <= 0.05f && CntlVec[0].fThumbLX >= -0.05f) {
				m_InputOnce = false;
				m_InputTime = 0.0f;
			}
		}
		else if (!(KeyState.m_bPressedKeyTbl['A'] && KeyState.m_bPressedKeyTbl['D'])) {
			if (KeyState.m_bPressedKeyTbl['D']) {
				m_SelectNum++;
			}
			if (KeyState.m_bPressedKeyTbl['A']) {
				m_SelectNum--;
			}
		}
		//選択キーが変わったら
		if (currentNum < m_SelectNum) {
			auto ptrSprite = GetSharedGameObject<Sprite>(L"RArrowCursorSprite");
			ptrSprite->SetScale(m_ArrowCursorScale * 0.8f);
			ptrSprite->SetTextureKey(L"CHOICE_RIGHTARROWCURSOL_TX");
			m_RCursorTime = 0.0f;
		}
		else if(m_RCursorTime >= 0.1f) {
			auto ptrSprite = GetSharedGameObject<Sprite>(L"RArrowCursorSprite");
			ptrSprite->SetScale(m_ArrowCursorScale);
			ptrSprite->SetTextureKey(L"RIGHTARROWCURSOL_TX");
		}
		else {
			m_RCursorTime += elapsedTime;
		}
		//選択キーが変わったら
		if (currentNum > m_SelectNum) {
			auto ptrSprite = GetSharedGameObject<Sprite>(L"LArrowCursorSprite");
			ptrSprite->SetScale(m_ArrowCursorScale * 0.8f);
			ptrSprite->SetTextureKey(L"CHOICE_RIGHTARROWCURSOL_TX");
			m_LCursorTime = 0.0f;
		}
		else if(m_LCursorTime >= 0.1f) {
			auto ptrSprite = GetSharedGameObject<Sprite>(L"LArrowCursorSprite");
			ptrSprite->SetScale(m_ArrowCursorScale);
			ptrSprite->SetTextureKey(L"RIGHTARROWCURSOL_TX");
		}
		else {
			m_LCursorTime += elapsedTime;
		}

		if (m_SelectNum <= 0) {
			m_SelectNum = static_cast<int>(SelectKey::Max);
		}
		m_SelectKey = SelectKey(m_SelectNum % static_cast<int>(SelectKey::Max));
	}

	void StageSelect::OnDestroy() {
		//BGMのストップ
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}

	void StageSelect::UpdateSpriteTX() {
		switch (m_SelectKey)
		{
		case SelectKey::Stage1:
			GetSharedGameObject<Sprite>(L"StageTXSprite")->SetTextureKey(L"Stage1_TX");
			break;
		case SelectKey::Stage2:
			GetSharedGameObject<Sprite>(L"StageTXSprite")->SetTextureKey(L"SKY_TX");
			break;
		case SelectKey::Stage3:
			GetSharedGameObject<Sprite>(L"StageTXSprite")->SetTextureKey(L"GROUND_TX");
			break;
		default:
			break;
		}
		auto ptrScoreSprite = GetSharedGameObject<ScoreSprite>(L"ScoreSprite");
		ptrScoreSprite->SetScore(static_cast<int>(m_SelectKey) + 1);
	}

	void StageSelect::ChangeStageSceneSelected() {
		auto ptrScene = App::GetApp()->GetScene<Scene>();
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		bool start =
			CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_START ||
			CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B ||
			KeyState.m_bPressedKeyTbl[VK_SPACE];
		if (start) {
			switch (m_SelectKey)
			{
			case SelectKey::Stage1:
				ptrScene->SetLimitTime(90.0f); // Stage1.csvでの制限時間
				ptrScene->SetStageCSVKey(L"Stage1.csv");
				break;
			case SelectKey::Stage2:
				ptrScene->SetLimitTime(30.0f);
				ptrScene->SetStageCSVKey(L"Stage2.csv");
				break;
			case SelectKey::Stage3:
				ptrScene->SetLimitTime(1.0f);
				ptrScene->SetStageCSVKey(L"Stage2.csv");
				break;
			default:
				break;
			}
			App::GetApp()->GetScene<Scene>()->ChangeScene(SceneKey::Game);
		}
	}
}
//end basecross
