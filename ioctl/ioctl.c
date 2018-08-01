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

char *b_state(int state) {
	switch (state) {
		case APM_BATT_HIGH:
			return "HIGH";
		case APM_BATT_LOW:
			return "LOW";
		case APM_BATT_CRITICAL:
			return "CRITICAL";
		case APM_BATT_CHARGING:
			return "CHARGING";
		case APM_BATTERY_ABSENT:
			return "ABSENT";
		case APM_BATT_UNKNOWN:
		default:
			return "UNKNOWN";
	}
}

char *ac_state(int state) {
	switch (state) {
		case APM_AC_OFF:
			return "OFF";
		case APM_AC_ON:
			return "ON";
		case APM_AC_BACKUP:
			return "BCACKUP";
		case APM_AC_UNKNOWN:
		default:
			return "UNKNOWN";
	}
}

int main() {
	int fd;
	struct apm_power_info power;

	bzero(&power, sizeof power);
	power.battery_state = APM_BATT_UNKNOWN;
	power.ac_state = APM_AC_UNKNOWN;

	fd = open("/dev/apm", O_RDONLY);
	if (ioctl(fd, APM_IOC_GETPOWER, &power) == -1)
		err(1, "ioctl: apm");

	close(fd);

	printf("Battery state: %s\n", b_state(power.battery_state));
	printf("AC: %s\n", ac_state(power.ac_state));
	printf("charge capacity: %hhu%%\n", power.battery_life);
	printf("estimated minutes left: %d\n", power.minutes_left);
	printf("\nunknown properties:\n");
	printf("spare1 = %hhu\n", power.spare1);
	printf("spare2[0] = %d\n", power.spare2[0]);
	printf("spare2[1] = %d\n", power.spare2[1]);
	printf("spare2[2] = %d\n", power.spare2[2]);
	printf("spare2[3] = %d\n", power.spare2[3]);
	printf("spare2[4] = %d\n", power.spare2[4]);
	printf("spare2[5] = %d\n", power.spare2[5]);

	return 0;
}
