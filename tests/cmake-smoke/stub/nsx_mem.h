/* Smoke stub; nsx-core owns the real header. */
#ifndef NSX_MEM_H
#define NSX_MEM_H

#ifdef AM_PART_APOLLO510
#define NSX_CACHE_HAS_EXPLICIT_DCACHE 1
#else
#define NSX_CACHE_HAS_EXPLICIT_DCACHE 0
#endif

#ifdef NSX_SMOKE_SRAM_BSS
#define NSX_MEM__HAS_SRAM_BSS 1
#define NSX_MEM__SEC_SRAM_BSS ".sram_bss"
#else
#define NSX_MEM__HAS_SRAM_BSS 0
#endif

#endif
