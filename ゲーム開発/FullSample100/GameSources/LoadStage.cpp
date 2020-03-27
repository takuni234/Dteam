/*!
@file LoadStage.cpp
@brief ���[�h�X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	���[�h�X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	bool LoadStage::m_Loaded = false;
	std::mutex LoadStage::mtx;

	//���\�[�X���[�h�p�̃X���b�h�i�X�^�e�B�b�N�֐��j
	void LoadStage::LoadResourceFunc() {
		mtx.lock();
		m_Loaded = false;
		mtx.unlock();

		wstring DataDir;
		//�e�Q�[���͈ȉ��̂悤�Ƀf�[�^�f�B���N�g�����擾���ׂ�
		App::GetApp()->GetDataDirectory(DataDir);
		wstring strTexture = DataDir + L"sky.jpg";
		App::GetApp()->RegisterTexture(L"SKY_TX", strTexture);
		strTexture = DataDir + L"trace.png";
		App::GetApp()->RegisterTexture(L"TRACE_TX", strTexture);
		strTexture = DataDir + L"number.png";
		App::GetApp()->RegisterTexture(L"NUMBER_TX", strTexture);
		strTexture = DataDir + L"spark.png";
		App::GetApp()->RegisterTexture(L"SPARK_TX", strTexture);
		strTexture = DataDir + L"fire.png";
		App::GetApp()->RegisterTexture(L"FIRE_TX", strTexture);
		strTexture = DataDir + L"StageMessage.png";
		App::GetApp()->RegisterTexture(L"MESSAGE_TX", strTexture);
		strTexture = DataDir + L"Text_Gray.png";
		App::GetApp()->RegisterTexture(L"HELPTEXT_TX", strTexture);
		//�T�E���h
		wstring CursorWav = DataDir + L"cursor.wav";
		App::GetApp()->RegisterWav(L"cursor", CursorWav);
		//BGM
		wstring strMusic = DataDir + L"nanika .wav";
		App::GetApp()->RegisterWav(L"Nanika", strMusic);

		mtx.lock();
		m_Loaded = true;
		mtx.unlock();

	}

	void LoadStage::CreateViewLight() {
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(Vec3(0.0f, 2.0f, -3.0f));
		PtrCamera->SetAt(Vec3(0.0f, 0.0f, 0.0f));
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();

	}

	//�X�v���C�g�̍쐬
	void LoadStage::CreateTitleSprite() {
		AddGameObject<Sprite>(L"WAIT_TX", Vec2(300.0f, 150.0f), Vec3(450.0f,-400.0f,0.0f));
		AddGameObject<SerialAnimeSprite>(L"LOADTEST_TX", true,
			Vec2(256.0f, 256.0f), Vec2(400.0f, -200.0f), 4, 1, 0.1f);
	}

	//������
	void LoadStage::OnCreate() {
		wstring DataDir;
		//�e�Q�[���͈ȉ��̂悤�Ƀf�[�^�f�B���N�g�����擾���ׂ�
		App::GetApp()->GetDataDirectory(DataDir);
		//���҂����������̃e�N�X�`���݂̂����œo�^
		wstring strTexture = DataDir + L"wait.png";
		App::GetApp()->RegisterTexture(L"WAIT_TX", strTexture);
		strTexture = DataDir + L"movetest.png";
		App::GetApp()->RegisterTexture(L"MOVETEST_TX", strTexture);
		strTexture = DataDir + L"�^���N.png";
		App::GetApp()->RegisterTexture(L"LOADTEST_TX", strTexture);
		strTexture = DataDir + L"trace.png";
		App::GetApp()->RegisterTexture(L"TRACE_TX", strTexture);
		//���̃��\�[�X��ǂݍ��ރX���b�h�̃X�^�[�g
		std::thread LoadThread(LoadResourceFunc);
		//�I���܂ł͑҂��Ȃ�
		LoadThread.detach();

		CreateViewLight();
		//�X�v���C�g�̍쐬
		CreateTitleSprite();
	}

	//�X�V
	void LoadStage::OnUpdate() {
		if (m_Loaded) {
			//���\�[�X�̃��[�h���I��������^�C�g���X�e�[�W�Ɉڍs
			App::GetApp()->GetScene<Scene>()->ChangeScene(SceneKey::Title);
		}
	}


}
//end basecross
