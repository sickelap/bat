#include <sys/time.h>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <sys/sensors.h>
#include <sys/ioctl.h>
#include <machine/apmvar.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <err.h>
#include <strings.h>

int main() {
	int fd;
	struct apm_power_info power;

	bzero(&power, sizeof power);
	power.battery_state = APM_BATT_UNKNOWN;
	power.ac_state = APM_AC_UNKNOWN;

	fd = open("/dev/apm", O_RDONLY);
	if (ioctl(fd, APM_IOC_GETPOWER, &power) == -1)
		err(1, "ioctl: apm");

	printf("battery_state = %hhu\n", power.battery_state);
	printf("ac_state = %hhu\n", power.ac_state);
	printf("battery_life = %hhu\n", power.battery_life);
	printf("spare1 = %hhu\n", power.spare1);
	printf("minutes_left = %d\n", power.minutes_left);
	printf("spare2[0] = %d\n", power.spare2[0]);
	printf("spare2[1] = %d\n", power.spare2[1]);
	printf("spare2[2] = %d\n", power.spare2[2]);
	printf("spare2[3] = %d\n", power.spare2[3]);
	printf("spare2[4] = %d\n", power.spare2[4]);
	printf("spare2[5] = %d\n", power.spare2[5]);

	close(fd);

	return 0;
}
