#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(demo, LOG_LEVEL_DBG);

#define STACK_SIZE 1024

#define PRIO_HIGH 3
#define SLEEP_HIGH 100
#define PRIO_MED 5
#define SLEEP_MED 200
#define PRIO_LOW 7
#define SLEEP_LOW 300
#define PRIO_COOP (-1)
#define ITERATION_COOP 5
#define COOP_K_BUSY 200

void high_fn(void *p1, void *p2, void *p3) {
  while (1) {
    LOG_INF("T_HIGH running PRIO %d", PRIO_HIGH);
    k_msleep(SLEEP_HIGH);
  }
}

void med_fn(void *p1, void *p2, void *p3) {

  while (1) {
    LOG_INF("T_MED running PRIO: %d", PRIO_MED);
    k_msleep(SLEEP_MED);
  }
}

void low_fn(void *p1, void *p2, void *p3) {
  while (1) {
    LOG_INF("T_LOW running. PRIO: %d", PRIO_LOW);
    k_msleep(SLEEP_LOW);
  }
}

void coop_fn(void *p1, void *p2, void *p3) {

  for (int i = 0; i < ITERATION_COOP; i++) {
    k_busy_wait(COOP_K_BUSY);
    LOG_INF("T_COOP running. PRIO: %d . iterations: {%d/5}", PRIO_COOP, i + 1);
  }
  LOG_INF("T_COOP yielding now");
  k_yield();
}

K_THREAD_DEFINE(t_low_fn, STACK_SIZE, low_fn, NULL, NULL, NULL, PRIO_LOW, 0, 0);
K_THREAD_DEFINE(t_med_fn, STACK_SIZE, med_fn, NULL, NULL, NULL, PRIO_MED, 0, 0);
K_THREAD_DEFINE(t_high_fn, STACK_SIZE, high_fn, NULL, NULL, NULL, PRIO_HIGH, 0,
                0);
K_THREAD_DEFINE(t_coop_fn, STACK_SIZE, coop_fn, NULL, NULL, NULL, PRIO_COOP, 0,
                0);

int main(void) {

  LOG_INF("=== Build working intuition for Ready vs Waiting and k_yield vs "
          "k_sleep ===");
  LOG_INF("Thread LOW: priority %d, sleeps %d ms", PRIO_LOW, SLEEP_LOW);
  LOG_INF("Thread MED: priority %d, sleeps %d ms", PRIO_MED, SLEEP_MED);
  LOG_INF("Thread HIGH: priority %d, sleeps %d ms", PRIO_HIGH, SLEEP_HIGH);
  LOG_INF("Thread COOP: priority %d, iterations %d ", PRIO_COOP,
          ITERATION_COOP);

  return 0;
}
