#include <sys/time.h>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <sys/sensors.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <err.h>
#include <errno.h>

int get_acpibat(struct sensordev *);

int main() {
	struct sensordev dev;

	if ((get_acpibat(&dev)) == -1) {
		return -1;
	}

	printf("found %s\n", dev.xname);

	return 0;
}

int get_acpibat(struct sensordev *sndev) {
	int mib[3], index, cmp;
	size_t sdlen = sizeof(struct sensordev);
	char devname[] = "acpibat";

	mib[0] = CTL_HW;
	mib[1] = HW_SENSORS;

	for (index = 0; ; index++) {
		mib[2] = index;
		if (sysctl(mib, 3, sndev, &sdlen, NULL, 0) == -1) {
			if (errno == ENXIO)
				continue;
			if (errno == ENOENT)
				break;
		}

		if (strncmp(devname, sndev->xname, strlen(devname)) == 0) {
			return 0;
		}
	}

	return -1;
}
