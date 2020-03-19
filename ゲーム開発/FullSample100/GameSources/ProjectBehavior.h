/*!
@file ProjectBehavior.h
@brief プロジェク定義の行動クラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	template<typename T>
	struct InputHandler {
		void PushHandle(const shared_ptr<T>& Obj) {
			auto keyState = App::GetApp()->GetInputDevice().GetKeyState();
			if (keyState.m_bPressedKeyTbl['B']) {
				Obj->OnPushA();
				return;
			}
			if (keyState.m_bPressedKeyTbl['M']) {
				Obj->OnPushB();
				return;
			}
			if (keyState.m_bPressedKeyTbl[VK_SPACE]) {
				Obj->OnPushX();
				return;
			}
			if (keyState.m_bPressedKeyTbl['C']) {
				Obj->OnPushY();
				return;
			}
			auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			if (cntlVec[0].bConnected) {
				switch (cntlVec[0].wPressedButtons)
				{
				case XINPUT_GAMEPAD_A:
					Obj->OnPushA();
					break;
				case XINPUT_GAMEPAD_B:
					Obj->OnPushB();
					break;
				case XINPUT_GAMEPAD_X:
					Obj->OnPushX();
					break;
				case XINPUT_GAMEPAD_Y:
					Obj->OnPushY();
					break;
				default:
					break;
				}
			}
		}
	};
}

//end basecross

