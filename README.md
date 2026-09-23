# nsx-segger-rtt

SEGGER RTT V8.58.0 as an NSX runtime module. `RTT/` and `Config/` are the
upstream files, unmodified (`SOURCE.md` records tag, commit, and checksums);
`CMakeLists.txt` wraps them as the `nsx::segger_rtt` target.

## Use it before it reaches the registry

Declare the module in the app's `nsx.yml` and point its project at this repo
by tag, then run `nsx lock` and `nsx sync`:

```yaml
modules:
  - name: nsx-segger-rtt

module_registry:
  projects:
    nsx-segger-rtt:
      url: https://github.com/AmbiqAI/nsx-segger-rtt.git
      revision: v0.1.0
  modules:
    nsx-segger-rtt:
      project: nsx-segger-rtt
      revision: v0.1.0
      metadata: nsx-module.yaml
```

Link the target and include `SEGGER_RTT.h`:

```cmake
target_link_libraries(your_target PRIVATE nsx::segger_rtt)
```

## Buffer sizing

SEGGER sizes channel 0 at compile time and ignores the buffer passed to
`SEGGER_RTT_ConfigUpBuffer(0, ...)` / `SEGGER_RTT_ConfigDownBuffer(0, ...)`.
Size channel 0 through the CMake cache variables; they become `PUBLIC`
compile definitions on the target.

| Cache variable                    | Default | Defines           |
| --------------------------------- | ------- | ----------------- |
| `NSX_SEGGER_RTT_BUFFER_SIZE_UP`   | 1024    | `BUFFER_SIZE_UP`  |
| `NSX_SEGGER_RTT_BUFFER_SIZE_DOWN` | 16      | `BUFFER_SIZE_DOWN`|

Channels 1 and above take caller-provided storage as usual.

Per-SoC buffer placement (`NSX_MEM_*` sections from `nsx-core`) arrives in
the next PR.

## Dependencies

- `nsx-cmsis-core` — CMSIS core headers.
- `nsx-core` — memory placement macros (used by the next PR).
