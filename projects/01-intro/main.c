#include "testmod.h"
#include <util/delay.h>

#define DELAY_MS 500

int main(void) {
  configurePortB();
  while(1) {
    _delay_ms(DELAY_MS);
    togglePortB();
  }
}
