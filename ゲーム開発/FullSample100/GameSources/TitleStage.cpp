/*!
@file TitleStage.cpp
@brief �^�C�g���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	�^�C�g���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	void TitleStage::CreateViewLight() {
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

	//�_�ł���X�v���C�g�쐬
	void TitleStage::CreatePushSprite() {
		float textScale = 100.0f;
		//�䗦
		auto textRatio = Vec2(3.7f, 1.0f);
		textRatio *= textScale;
		AddGameObject<PushSprite>(L"MESSAGE_TX", true,
			textRatio, Vec3(0.0f, -200.0f, 0.0f));
	}

	void TitleStage::CreateSprite() {
		float logoScale = 300.0f;
		//�䗦
		auto logoRatio = Vec2(3.7f, 1.0f);
		logoRatio *= logoScale;
		//�^�C�g���摜
		AddGameObject<Sprite>(L"TITLELOGO_TX", true, logoRatio, Vec3(0.0f, 120.0f, 0.0f));

		//�X�e�[�W�̔w�i
		auto ptrSprite = AddGameObject<Sprite>(L"TITLE_BACKGROUND_TX", Vec2(1280.0f, 800.0f), Vec3(0.0f));
		ptrSprite->SetDrawLayer(-1);
	}

	void TitleStage::OnCreate() {
		try {
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			CreateSprite();
			CreatePushSprite();
			auto XAPtr = App::GetApp()->GetXAudio2Manager();
			m_BGM = XAPtr->Start(L"REISCUE_BGM", XAUDIO2_LOOP_INFINITE, 0.1f);
		}
		catch (...) {
			throw;
		}
	}

	void TitleStage::OnUpdate() {
		auto CntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();

		bool start =
			CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_START ||
			CntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B ||
			KeyState.m_bPressedKeyTbl[VK_SPACE];

		if (start) {
			auto ptrXA = App::GetApp()->GetXAudio2Manager();
			ptrXA->Start(L"DECISION_WAV", 0, 0.1f);
			App::GetApp()->GetScene<Scene>()->ChangeScene(SceneKey::Select);
		}
	}

	void TitleStage::OnDestroy() {
		//BGM�̃X�g�b�v
		auto XAPtr = App::GetApp()->GetXAudio2Manager();
		XAPtr->Stop(m_BGM);
	}

}
//end basecross
