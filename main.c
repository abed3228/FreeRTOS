#include "init.h"

int main(void) {

  // Always first initialise the main application.
  init_main();

  while (1) {
    printf("Hello World\n");
    sleep(1);
  }
  return 0;
}
