#include <sys/time.h>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <sys/sensors.h>
#include <string.h>
#include <stdio.h>
#include <err.h>
#include <errno.h>

int get_acpibat_index(void);

int main() {

  int index;

  if ((index = get_acpibat_index()) == -1) {
    return -1;
  }

  printf("acpibat index %d\n", index);

  return 0;
}

int get_acpibat_index() {
  int mib[3], index, cmp;
  struct sensordev sndev;
  size_t sdlen = sizeof(sndev);
  char devname[] = "acpibat";

  mib[0] = CTL_HW;
  mib[1] = HW_SENSORS;

  for (index = 0; ; index++) {
    mib[2] = index;
    if (sysctl(mib, 3, &sndev, &sdlen, NULL, 0) == -1) {
      if (errno == ENXIO)
        continue;
      if (errno == ENOENT)
        break;
    }

    if (memcmp((char *)devname, (char *)sndev.xname, sizeof(devname) - 1) == 0) {
      return index;
    }
  }

  return -1;
}
