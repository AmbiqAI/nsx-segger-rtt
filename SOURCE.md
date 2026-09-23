# SEGGER RTT sources

- Upstream: https://github.com/SEGGERMicro/RTT
- Tag: `V8.58.0`
- Commit: `4d8feab3150f86f37a9d323ddc88d6cdf5673072`
- Files are copied unchanged; `LICENSE.md` is upstream's license.

Verify with `grep -E '^[0-9a-f]{64}  ' SOURCE.md | sha256sum -c`:

```
caf3d20bc2def30e176f937a56c878a363dec3cd805334ea8173f22e097f1106  RTT/SEGGER_RTT.c
b8b6c29abd72c42082502306fe7cdaa0ca90ca2a9b7821dceaa3b023b75f4d95  RTT/SEGGER_RTT.h
d2af82ee107fba25157e850109ed9da38243d234f5b70a1039a5c37a0579a054  RTT/SEGGER_RTT_ConfDefaults.h
d02ef83f826dd29cddb466adca6c75dbdd71128f18bc6bef1113ca0127944d6f  Config/SEGGER_RTT_Conf.h
e033779c697246a7a89eb411eca41cabb791dbf0b23619cfbd6d42429191baa8  LICENSE.md
```
