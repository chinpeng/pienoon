// Copyright 2014 Google Inc. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "precompiled.h"
#include <vector>
#include "common.h"
#include "controller.h"
#include "sdl_controller.h"
#include "timeline_generated.h"
#include "character_state_machine_def_generated.h"

namespace fpl {
namespace splat {

void SdlController::Initialize(InputSystem* input_system,
                               const ControlScheme* scheme) {
  input_system_ = input_system;
  scheme_ = scheme;
}

void SdlController::AdvanceFrame() {
  for (auto it = scheme_->keybinds.begin();
       it != scheme_->keybinds.end(); ++it) {
    bool pressed = input_system_->GetButton(it->physical_input).went_down();
    SetLogicalInputs(it->logical_input, pressed);
  }
}

// static
const ControlScheme* ControlScheme::GetDefaultControlScheme(int i) {
  static const Keybind kKeyBinds0[] = {
    { SDLK_w, LogicalInputs_ThrowPie },
    { SDLK_s, LogicalInputs_Deflect },
    { SDLK_a, LogicalInputs_Left },
    { SDLK_d, LogicalInputs_Right }
  };

  static const Keybind kKeyBinds1[] = {
    { SDLK_i, LogicalInputs_ThrowPie },
    { SDLK_k, LogicalInputs_Deflect },
    { SDLK_j, LogicalInputs_Left },
    { SDLK_l, LogicalInputs_Right }
  };

  static const Keybind kKeyBinds2[] = {
    { SDLK_UP, LogicalInputs_ThrowPie },
    { SDLK_DOWN, LogicalInputs_Deflect },
    { SDLK_LEFT, LogicalInputs_Left },
    { SDLK_RIGHT, LogicalInputs_Right }
  };

  static const Keybind kKeyBinds3[] = {
    { SDLK_KP_8, LogicalInputs_ThrowPie },
    { SDLK_KP_5, LogicalInputs_Deflect },
    { SDLK_KP_4, LogicalInputs_Left },
    { SDLK_KP_6, LogicalInputs_Right }
  };

  static const ControlScheme kDefaultSchemes[] = {
    { std::vector<Keybind>(kKeyBinds0, &kKeyBinds0[ARRAYSIZE(kKeyBinds0)]) },
    { std::vector<Keybind>(kKeyBinds1, &kKeyBinds1[ARRAYSIZE(kKeyBinds1)]) },
    { std::vector<Keybind>(kKeyBinds2, &kKeyBinds2[ARRAYSIZE(kKeyBinds2)]) },
    { std::vector<Keybind>(kKeyBinds3, &kKeyBinds3[ARRAYSIZE(kKeyBinds3)]) }
  };

  return &kDefaultSchemes[i % ARRAYSIZE(kDefaultSchemes)];
}

}  // splat
}  // fpl
