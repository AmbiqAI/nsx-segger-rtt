#!/bin/sh
# Assert RTT symbols land in one section.
set -eu
elf=$1
want=$2
status=0
for sym in _SEGGER_RTT _acUpBuffer _acDownBuffer; do
    got=$(arm-none-eabi-objdump -t "$elf" | awk -v s="$sym" '$NF == s { print $(NF-2) }')
    echo "$sym in ${got:-<missing>} (want $want)"
    [ "$got" = "$want" ] || status=1
done
exit $status
