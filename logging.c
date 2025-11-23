#include "sd_card.h"
#include "ff.h"
#include "f_util.h"

const char *logfile = "0:/sensorlogs.csv";

void setup_fs(void)
{
    bool sd_bool = sd_init_driver();

    FATFS fs;
    FRESULT fr = f_mount(&fs, "", 1);

    if (fr != FR_OK)
    {
        while (1)
        {
            printf("f_mount error: %s (%d)\n", FRESULT_str(fr), fr);
        }
        return;
    }
    // sd_init_driver();
    // sd_card_t *sd = sd_get_by_drive_prefix("0:/");

    // FRESULT fr = f_mount(&sd->state.fatfs, sd_get_drive_prefix(sd), 1);
    // if (fr == FR_OK)
    // {
    //     printf("Successfully mounted SD Card file-system.");
    // }
    // else
    // {
    //     while (1)
    //     {
    //         printf("Mount failed: %d\n", fr);
    //     }
    // }
}

void write_log(char *msg)
{
    uint32_t timestamp = to_ms_since_boot(get_absolute_time());
    char buffer[256];

    sprintf(buffer, "%u::%s", timestamp, msg);

    FIL file;
    FRESULT fr = f_open(&file, logfile, FA_WRITE | FA_OPEN_APPEND);

    if (fr == FR_OK)
    {
        UINT bw;
        fr = f_write(&file, buffer, strlen(buffer), &bw);
        if (fr != FR_OK)
        {
            printf("Log file was opened, but failed to write log.");
        }

        f_close(&file);
    }
    else
    {
        printf("Failed to open log file: %d\n", fr);
    }
}