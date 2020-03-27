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
			if (keyState.m_bPushKeyTbl[VK_SPACE]) {
				Obj->OnPushX();
				return;
			}
			if (keyState.m_bPressedKeyTbl['C']) {
				Obj->OnPushY();
				return;
			}
			auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			if (cntlVec[0].bConnected) {
				if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {

				}				
				if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B) {

				}
				if (cntlVec[0].wButtons & XINPUT_GAMEPAD_X) {
					Obj->OnPushX();
				}
				if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_Y) {

				}
			}
		}
	};
}

//end basecross

