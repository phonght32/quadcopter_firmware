#include "periph_motor.h"
#include "hw_intf.h"
#include "bldc_motor.h"

bldc_motor_handle_t motorfl_handle = NULL;
bldc_motor_handle_t motorfr_handle = NULL;
bldc_motor_handle_t motorbl_handle = NULL;
bldc_motor_handle_t motorbr_handle = NULL;

err_code_t periph_motor_init(void)
{
    motorfl_handle = bldc_motor_init();
    bldc_motor_cfg_t motorfl_cfg = {
        .kv = 3800,
        .set_pwm = hw_intf_motorfl_set_pwm,
        .start = hw_intf_motorfl_start,
        .stop = hw_intf_motorfl_stop
    };
    bldc_motor_set_config(motorfl_handle, motorfl_cfg);
    bldc_motor_config(motorfl_handle);

    motorfr_handle = bldc_motor_init();
    bldc_motor_cfg_t motorfr_cfg = {
        .kv = 3800,
        .set_pwm = hw_intf_motorfr_set_pwm,
        .start = hw_intf_motorfr_start,
        .stop = hw_intf_motorfr_stop
    };
    bldc_motor_set_config(motorfr_handle, motorfr_cfg);
    bldc_motor_config(motorfr_handle);

    motorbl_handle = bldc_motor_init();
    bldc_motor_cfg_t motorbl_cfg = {
        .kv = 3800,
        .set_pwm = hw_intf_motorbl_set_pwm,
        .start = hw_intf_motorbl_start,
        .stop = hw_intf_motorbl_stop
    };
    bldc_motor_set_config(motorbl_handle, motorbl_cfg);
    bldc_motor_config(motorbl_handle);

    motorbr_handle = bldc_motor_init();
    bldc_motor_cfg_t motorbr_cfg = {
        .kv = 3800,
        .set_pwm = hw_intf_motorbr_set_pwm,
        .start = hw_intf_motorbr_start,
        .stop = hw_intf_motorbr_stop
    };
    bldc_motor_set_config(motorbr_handle, motorbr_cfg);
    bldc_motor_config(motorbr_handle);

    return ERR_CODE_SUCCESS;
}