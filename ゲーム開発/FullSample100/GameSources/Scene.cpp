
/*!
@file Scene.cpp
@brief シーン実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------
	void Scene::OnCreate(){
		try {
			//クリアする色を設定
			Col4 Col;
			Col.set(31.0f / 255.0f, 30.0f / 255.0f, 71.0f / 255.0f, 255.0f / 255.0f);
			SetClearColor(Col);
			//自分自身にイベントを送る
			//これにより各ステージやオブジェクトがCreate時にシーンにアクセスできる
			ChangeScene(SceneKey::Load);
		}
		catch (...) {
			throw;
		}
	}

	Scene::~Scene() {
	}

	void Scene::OnEvent(const shared_ptr<Event>& event) {
		if (event->m_MsgStr == L"ToGameStage") {
			//最初のアクティブステージの設定
			ResetActiveStage<GameStage>();
		}
		else if (event->m_MsgStr == L"ToTitleStage") {
			ResetActiveStage<TitleStage>();
		}
		else if (event->m_MsgStr == L"ToStageSelect") {
			ResetActiveStage<StageSelect>();
		}
		else if (event->m_MsgStr == L"ToResultStage") {
			ResetActiveStage<ResultStage>();
		}
		else if (event->m_MsgStr == L"ToLoadStage") {
			ResetActiveStage<LoadStage>();
		}
		else if (event->m_MsgStr == L"ToGameOverStage") {
			ResetActiveStage<GameOverStage>();
		}
		else if (event->m_MsgStr == L"ToCopyrightInfoStage") {
			ResetActiveStage<CopyrightInfoStage>();
		}
	}

	void Scene::ChangeScene(SceneKey key) {
		switch (key)
		{
		case SceneKey::Title:
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToTitleStage");
			break;
		case SceneKey::Select:
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToStageSelect");
			break;
		case SceneKey::Game:
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToGameStage");
			break;
		case SceneKey::Result:
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToResultStage");
			break;
		case SceneKey::GameOver:
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToGameOverStage");
			break;
		case SceneKey::Load:
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToLoadStage");
			break;		
		case SceneKey::CopyrightInfo:
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToCopyrightInfoStage");
			break;
		default:
			break;
		}
	}
}
//end basecross
