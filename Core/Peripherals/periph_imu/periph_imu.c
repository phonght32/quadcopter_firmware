#include "imu_public.h"
#include "imu_madgwick.h"
#include "periph_imu.h"
#include "hw_intf.h"

imu_handle_t imu_handle = NULL;
imu_madgwick_handle_t imu_madgwick_handle = NULL;

err_code_t periph_imu_init(void)
{
	/* Config MPU6500 and AK8963 */
	imu_handle = imu_init();

    imu_cfg_t imu_cfg = {
        .mpu_type = MPU_TYPE_MPU6500 | MPU_TYPE_AK8963,
        .accel_bias_x = 0,
        .accel_bias_y = 0,
        .accel_bias_z = 0,
        .gyro_bias_x = 0,
        .gyro_bias_y = 0,
        .gyro_bias_z = 0,
        .mag_hard_iron_bias_x = 0,
        .mag_hard_iron_bias_y = 0,
        .mag_hard_iron_bias_z = 0,
        .mag_soft_iron_bias_x = 0,
        .mag_soft_iron_bias_y = 0,
        .mag_soft_iron_bias_z = 0
    };
    imu_set_config(imu_handle, imu_cfg);

    mpu6500_cfg_t mpu6500_cfg = {
        .clksel = MPU6500_CLKSEL_AUTO,
        .dlpf_cfg = MPU6500_41ACEL_42GYRO_BW_HZ,
        .sleep_mode = MPU6500_DISABLE_SLEEP_MODE,
        .gfs_sel = MPU6500_GFS_SEL_2000,
        .afs_sel = MPU6500_AFS_SEL_8G,
        .read_bytes = hw_intf_mpu6500_read_bytes,
        .write_bytes = hw_intf_mpu6500_write_bytes
    };
    imu_config_mpu6500(imu_handle, mpu6500_cfg);

    ak8963_cfg_t ak8963_cfg = {
        .opr_mode = AK8963_MODE_CONT_MEASUREMENT_2,
        .mfs_sel = AK8963_MFS_16BIT,
        .read_bytes = hw_intf_ak8963_read_bytes,
        .write_bytes = hw_intf_ak8963_write_bytes
    };
    imu_config_ak8963(imu_handle, ak8963_cfg);

    imu_config(imu_handle);

    /* Config madgwick filter */
    imu_madgwick_handle = imu_madgwick_init();

    imu_madgwick_cfg_t imu_madgwick_cfg = {
        .beta = 0.1f,
        .sample_freq = 50.0f
    };
    imu_madgwick_set_config(imu_madgwick_handle, imu_madgwick_cfg);

    imu_madgwick_config(imu_madgwick_handle);

    return ERR_CODE_SUCCESS;
}
