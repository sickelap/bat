#include <sys/time.h>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <sys/sensors.h>
#include <string.h>
#include <stdio.h>
#include <err.h>
#include <errno.h>

int main() {
  int mib[3], i, cmp;
  struct sensordev sndev;
  size_t sdlen = sizeof(sndev);
  char devname[] = "acpibat";

  mib[0] = CTL_HW;
  mib[1] = HW_SENSORS;

  for (i = 0; ; i++) {
    mib[2] = i;
    if (sysctl(mib, 3, &sndev, &sdlen, NULL, 0) == -1) {
      if (errno == ENXIO)
        continue;
      if (errno == ENOENT)
        break;
    }

    cmp = memcmp((char *)devname, (char *)sndev.xname, sizeof(devname) - 1);
//    printf("%s, %s, %d, (%lu)\n", devname, sndev.xname, cmp, sizeof(devname) - 1);
    if (cmp == 0) {
      printf("[%d] %s\n", i, sndev.xname);
    }
  }

  return 0;
}
