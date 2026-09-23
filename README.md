# nsx-segger-rtt

SEGGER RTT V8.58.0 as an NSX runtime module. `RTT/` and `Config/` hold a
byte-identical subset of the upstream tree (`SOURCE.md` records tag, commit,
and checksums); `CMakeLists.txt` wraps them as the `nsx::segger_rtt` target.
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

Per-SoC buffer placement (`NSX_MEM_*` sections from `nsx-core`) arrives in
the next PR.

## Dependencies

- `nsx-cmsis-core` — CMSIS core headers.
- `nsx-core` — `NSX_MEM_*` placement macros.
