#include "SEGGER_RTT.h"

#if RTT_USE_ASM != 0
#error "The module must propagate RTT_USE_ASM=0 to consumers"
#endif

int main(void) {
    SEGGER_RTT_WriteString(0, "nsx-segger-rtt smoke\n");
    SEGGER_RTT_WriteSkipNoLock(0, "ok", 2);
    return 0;
}
