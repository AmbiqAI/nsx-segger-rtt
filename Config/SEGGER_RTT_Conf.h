/*
 * NSX RTT placement policy; see README.
 *
 * Copyright (c) 2026, Ambiq. BSD 3-Clause, see LICENSE.
 */

#ifndef NSX_SEGGER_RTT_CONF_H
#define NSX_SEGGER_RTT_CONF_H

#include "nsx_mem.h"

#ifndef NSX_CACHE_HAS_EXPLICIT_DCACHE
#error "nsx-core too old: NSX_CACHE_HAS_EXPLICIT_DCACHE missing"
#endif

/* Cached SRAM: keep default TCM .bss. */
#if !NSX_CACHE_HAS_EXPLICIT_DCACHE && NSX_MEM__HAS_SRAM_BSS
#ifndef SEGGER_RTT_SECTION
#define SEGGER_RTT_SECTION NSX_MEM__SEC_SRAM_BSS
#endif
#endif

#include "upstream/SEGGER_RTT_Conf.h"

#endif
