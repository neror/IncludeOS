// This file is a part of the IncludeOS unikernel - www.includeos.org
//
// Copyright 2015 Oslo and Akershus University College of Applied Sciences
// and Alfred Bratterud
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

#include <hw/pic.hpp>

uint16_t PIC::irq_mask_ {0xFFFB};

void PIC::init() noexcept {
  OS::outb(master_ctrl, master_icw1);
  OS::outb(slave_ctrl,  slave_icw1);
  OS::outb(master_mask, master_icw2);
  OS::outb(slave_mask,  slave_icw2);
  OS::outb(master_mask, master_icw3);
  OS::outb(slave_mask,  slave_icw3);
  OS::outb(master_mask, master_icw4);
  OS::outb(slave_mask,  slave_icw4);

  set_intr_mask(irq_mask_);
}
