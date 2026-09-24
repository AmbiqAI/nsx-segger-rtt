# nsx-segger-rtt

SEGGER RTT V8.58.0 as an NSX runtime module. `RTT/` and `Config/upstream/`
hold a byte-identical subset of the upstream tree (`SOURCE.md` records tag,
commit, and checksums); `Config/SEGGER_RTT_Conf.h` is module-owned and
`CMakeLists.txt` wraps them as the `nsx::segger_rtt` target.
Not shipped: `SEGGER_RTT_printf.c` and the ARMv7-M assembly fast path, so
`SEGGER_RTT_printf` is unavailable and the target builds with `RTT_USE_ASM=0`.

## Use it before it reaches the registry

Declare the module in the app's `nsx.yml` and point its project at this repo,
then run `nsx lock` and `nsx sync` (`nsx module register` writes the same
block). Pin `revision` to a release tag such as `v0.1.0` once one exists:

```yaml
modules:
  - name: nsx-segger-rtt

module_registry:
  projects:
    nsx-segger-rtt:
      url: https://github.com/AmbiqAI/nsx-segger-rtt.git
      revision: main
  modules:
    nsx-segger-rtt:
      project: nsx-segger-rtt
      revision: main
      metadata: nsx-module.yaml
```

Link the target and include `SEGGER_RTT.h`:

```cmake
target_link_libraries(your_target PRIVATE nsx::segger_rtt)
```

## Buffer sizing

SEGGER sizes channel 0 at compile time and ignores the buffer passed to
`SEGGER_RTT_ConfigUpBuffer(0, ...)` / `SEGGER_RTT_ConfigDownBuffer(0, ...)`.
Size channel 0 through the CMake cache variables. They reach only the
module's own compile of `SEGGER_RTT.c`; an app's own `BUFFER_SIZE_UP` define
has no effect on the channel-0 buffer.

| Cache variable                    | Default |
| --------------------------------- | ------- |
| `NSX_SEGGER_RTT_BUFFER_SIZE_UP`   | 1024    |
| `NSX_SEGGER_RTT_BUFFER_SIZE_DOWN` | 16      |

Channels 1 and above take caller-provided storage as usual.

## Buffer placement

`Config/SEGGER_RTT_Conf.h` picks where the control block and channel-0
buffers live, then includes the upstream configuration file. It reads two
`nsx_mem.h` flags from `nsx-core`:

- `NSX_CACHE_HAS_EXPLICIT_DCACHE` set (the Cortex-M55 Apollo5 / Apollo510 /
  Apollo330P parts): `SEGGER_RTT_SECTION` stays undefined, so everything
  lands in non-cached TCM `.bss`. Shared SRAM is cached on these parts and
  RTT runs with `SEGGER_RTT_CPU_CACHE_LINE_SIZE` 0, so J-Link's background
  SWD reads would see stale ring data there.
- Otherwise, `NSX_MEM__HAS_SRAM_BSS` set (the cacheless Cortex-M4 Apollo4):
  `SEGGER_RTT_SECTION` becomes `NSX_MEM__SEC_SRAM_BSS`, keeping the buffers
  out of scarce TCM. SEGGER derives `SEGGER_RTT_BUFFER_SECTION` from it.
- Everything else (Apollo3, unknown parts): undefined, default `.bss`.

New parts inherit the policy from their `nsx_mem.h` entry. `tests/cmake-smoke`
compiles all three cases against a stub `nsx_mem.h` and checks the section
each RTT symbol lands in.

## Dependencies

- `nsx-cmsis-core` — CMSIS core headers.
- `nsx-core` — `nsx_mem.h`, which `Config/SEGGER_RTT_Conf.h` includes for
  the `NSX_MEM__*` placement macros.
