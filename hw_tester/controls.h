#ifndef CONTROLS_H
#define CONTROLS_H

#define M1     ((PIN_CONTROL & (1 << P_M1))     == 0)
#define MREQ   ((PIN_CONTROL & (1 << P_MREQ))   == 0)
#define IORQ   ((PIN_CONTROL & (1 << P_IORQ))   == 0)
#define RD     ((PIN_CONTROL & (1 << P_RD))     == 0)
#define WR     ((PIN_CONTROL & (1 << P_WR))     == 0)
#define RFSH   ((PIN_CONTROL & (1 << P_RFSH))   == 0)
#define HALT   ((PIN_CONTROL & (1 << P_HALT))   == 0) 
#define BUSACK ((PIN_CONTROL & (1 << P_BUSACK)) == 0)

#endif