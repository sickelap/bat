
TODO to populate structure:

from batt_sys.h
```c
typedef struct battery {
    int battery_num; // got that
    /* path to battery dir */
    gchar *path; // crap
    /* sysfs file contents */
    int charge_now; // mAh
    int energy_now; // mWh
    int current_now; // mAh
    int power_now; // mWh
    int voltage_now; // V (current voltage or voltage?)
    int charge_full_design; // mAh
    int energy_full_design; // mWh
    int charge_full; // mAh
    int energy_full; // mWh
    /* extra info */
    int seconds; // calculate using max capacity and discharge rate
    int percentage; // calculate using current and max
    char *state; // ?
    //const char *poststr;
    //const char *capacity_unit;
    int type_battery; // ?
} battery;
```

