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

#ifndef KERNEL_OS_HPP
#define KERNEL_OS_HPP

#ifndef OS_VERSION
#define OS_VERSION "v?.?.?"
#endif

#include <string>

#include <common>

#include "../hw/pit.hpp"

/**
 *  The entrypoint for OS services
 *
 *  @note For device access, see Dev
 */
class OS {
public:   
  using rsprint_func = delegate<void(const char*, size_t)>;
  
  /* Get the version of the os */
  static inline std::string version()
  { return std::string(OS_VERSION); }
  
  /** Clock cycles since boot. */
  static inline uint64_t cycles_since_boot() {
    uint64_t ret;
    __asm__ volatile ("rdtsc":"=A"(ret));
    return ret;
  }
  
  /** Uptime in seconds. */
  static double uptime();
    
  /**
   *  Write a cstring to serial port. @todo Should be moved to Dev::serial(n).
   *
   *  @param ptr: The string to write to serial port
  */
  static size_t rsprint(const char* ptr);
  static size_t rsprint(const char* ptr, const size_t len);
  
  /**
   *  Write a character to serial port. @todo Should be moved Dev::serial(n)
   *
   *  @param c: The character to print to serial port
   */
  static void rswrite(const char c);

  /** Start the OS.  @todo Should be `init()` - and not accessible from ABI */
  static void start();

  /**
   *  Halt until next inerrupt.
   *
   *  @Warning If there is no regular timer interrupt (i.e. from PIT / APIC)
   *  we'll stay asleep.
   */
  static void halt();
  
  /**
   *  Set handler for secondary serial output.
   *
   *  This handler is called in addition to writing to the serial port.
   */
  static void set_rsprint(rsprint_func func) {
    rsprint_handler_ = func;
  }
  
private:  
  /** Indicate if the OS is running. */
  static bool power_;
  
  /** The main event loop. Check interrupts, timers etc., and do callbacks. */
  static void event_loop();
  
  static MHz cpu_mhz_;
  
  static rsprint_func rsprint_handler_;

  // Prohibit copy and move operations
  OS(OS&)  = delete;
  OS(OS&&) = delete;
  
  // Prohibit construction
  OS() = delete;
}; //< OS

#endif //< KERNEL_OS_HPP