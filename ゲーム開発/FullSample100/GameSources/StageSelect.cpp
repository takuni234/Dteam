/*!
@file StageSelect.cpp
@brief �X�e�[�W�Z���N�g����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	�X�e�[�W�Z���N�g�N���X����
	//--------------------------------------------------------------------------------------
	void StageSelect::CreateViewLight() {
		const Vec3 eye(0.0f, 5.0f, -5.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
	}

	void StageSelect::CreateSelectSprite() {
		auto ptrSprite = AddGameObject<Sprite>(L"Stage1_TX", Vec2(1280.0f, 800.0f), Vec3(0.0f));
		SetSharedGameObject(L"StageTXSprite", ptrSprite);
	}

	void StageSelect::OnCreate() {
		try {
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			CreateSelectSprite();
			auto XAPtr = App::GetApp()->GetXAudio2Manager();
			m_BGM = XAPtr->Start(L"Nanika", XAUDIO2_LOOP_INFINITE, 0.1f);
		}
		catch (...) {
			throw;
		}
	}

	void StageSelect::OnUpdate() {
		//���͂���l��ύX
		StageSelectKeyInput();
		//�e�N�X�`�����X�V
		UpdateSpriteTX();
		//�V�[���J��
		ChangeStageSceneSelected();
	}

	void StageSelect::StageSelectKeyInput() {
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();

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
				auto elapsedTime = App::GetApp()->GetElapsedTime();
				m_Time += elapsedTime;
				if (m_Time > 0.3f) {
					m_InputOnce = false;
					m_Time = 0.0f;
				}
			}
			if (CntlVec[0].fThumbLX <= 0.05f && CntlVec[0].fThumbLX >= -0.05f) {
				m_InputOnce = false;
				m_Time = 0.0f;
			}
		}
		else if (!(KeyState.m_bPressedKeyTbl[VK_LEFT] && KeyState.m_bPressedKeyTbl[VK_RIGHT])) {
			if (KeyState.m_bPressedKeyTbl[VK_RIGHT]) {
				m_SelectNum++;
			}
			if (KeyState.m_bPressedKeyTbl[VK_LEFT]) {
				m_SelectNum--;
			}
		}
		if (m_SelectNum <= 0) {
			m_SelectNum = static_cast<int>(SelectKey::Max);
		}
		m_SelectKey = SelectKey(m_SelectNum % static_cast<int>(SelectKey::Max));
	}

	void StageSelect::OnDestroy() {
		//BGM�̃X�g�b�v
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
		default:
			break;
		}
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
				ptrScene->SetLimitTime(90.0f); // Stage1.csv�ł̐�������
				ptrScene->SetStageCSVKey(L"Stage1.csv");
				break;
			case SelectKey::Stage2:
				ptrScene->SetLimitTime(3.0f);
				ptrScene->SetStageCSVKey(L"TestStage2.csv");
				break;
			default:
				break;
			}
			App::GetApp()->GetScene<Scene>()->ChangeScene(SceneKey::Game);
		}
	}
}
//end basecross
