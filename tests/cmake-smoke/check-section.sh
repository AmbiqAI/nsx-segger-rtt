#!/bin/sh
# Assert RTT symbols land in one section.
set -eu
elf=$1
want=$2
up=$3
down=$4
status=0
for sym in _SEGGER_RTT _acUpBuffer _acDownBuffer; do
    got=$(arm-none-eabi-objdump -t "$elf" | awk -v s="$sym" '$NF == s { print $(NF-2) }')
    echo "$sym in ${got:-<missing>} (want $want)"
    [ "$got" = "$want" ] || status=1
done
for spec in "_acUpBuffer:$up" "_acDownBuffer:$down"; do
    sym=${spec%:*}
    want_size=${spec#*:}
    hex=$(arm-none-eabi-nm -S "$elf" | awk -v s="$sym" '$NF == s { print $2 }')
    if [ -z "$hex" ]; then
        echo "$sym missing"
        status=1
    else
        size=$((0x$hex))
        echo "$sym size $size (want $want_size)"
        [ "$size" -eq "$want_size" ] || status=1
    fi
done
exit $status
