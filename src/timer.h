#include <time.h>
#include <stdio.h>
#include <stdint.h>

#include "ev.h"
#if EV_MULTIPLICITY
# define EV_DEFAULT_DEC EV_P = EV_DEFAULT
#else
# define EV_DEFAULT_DEC ev_default_loop(0)
#endif
ev_timer timeout_watcher;
ev_timer repeate_watcher;
ev_timer oneshot_watcher;

// another callback, this time for a time-out
static void timeout_cb (EV_P_ ev_timer *w, int revents)
{
        (void) w;
        (void) revents;
        printf("timeout at %ju\n", (uintmax_t)time(NULL));

        /* this causes the innermost ev_run to stop iterating */
        ev_break(EV_A_ EVBREAK_ONE);
}
static void repeate_cb (EV_P_ ev_timer *w, int revents)
{
        (void) w;
        (void) revents;
        printf("repeate at %ju\n", (uintmax_t)time(NULL));
}
static void oneshot_cb (EV_P_ ev_timer *w, int revents)
{
        (void) w;
        (void) revents;
        printf("oneshot at %ju\n", (uintmax_t)time(NULL));
        ev_timer_stop(EV_A_ w);
}