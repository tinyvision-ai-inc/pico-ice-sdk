#include <stdio.h>
#include "Vtop.h"
#include "vsim.h"

#define CLK_SYS_PERIOD 30
#define CLK_SYS_PHASE 3

int
main(int argc, char **argv)
{
    vsim_init(argc, argv);

    for (nanosecond_t ns = 100; ns < 100 * 1000; ns++) {
        if (POSEDGE(ns, CLK_SYS_PERIOD, CLK_SYS_PHASE)) {
            vsim->clk_i = 1;
            vsim_eval();
        }
        if (NEGEDGE(ns, CLK_SYS_PERIOD, CLK_SYS_PHASE)) {
            vsim->clk_i = 0;
            vsim_eval();
        }
        vsim_tick(ns);
    }
    vsim_finish();
    return 0;
}
