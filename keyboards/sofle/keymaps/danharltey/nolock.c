#include "nolock.h"

#ifndef NO_LOCK_PRESS_INTERVAL
#define NO_LOCK_PRESS_INTERVAL 150000
#endif
// uint32_t
static deferred_token timer_token = INVALID_DEFERRED_TOKEN;

static uint32_t no_lock_callback(uint32_t trigger_time, void* cb_arg) {
  tap_code(KC_NUM_LOCK);
  return NO_LOCK_PRESS_INTERVAL;
}

bool no_lock_is_active(void) { 
    return timer_token != INVALID_DEFERRED_TOKEN;
}

void toggle_no_lock(void) {
    if (timer_token == INVALID_DEFERRED_TOKEN) {
        timer_token = defer_exec(NO_LOCK_PRESS_INTERVAL, no_lock_callback, NULL);
    }
    else {
        cancel_deferred_exec(timer_token);
        timer_token = INVALID_DEFERRED_TOKEN;
    }
}
