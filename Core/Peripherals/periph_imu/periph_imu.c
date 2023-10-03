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
        .mpu_type = MPU_TYPE_MPU6050,
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

    // mpu6500_cfg_t mpu6500_cfg = {
    //     .clksel = MPU6500_CLKSEL_AUTO,
    //     .dlpf_cfg = MPU6500_41ACEL_42GYRO_BW_HZ,
    //     .sleep_mode = MPU6500_DISABLE_SLEEP_MODE,
    //     .gfs_sel = MPU6500_GFS_SEL_2000,
    //     .afs_sel = MPU6500_AFS_SEL_8G,
    //     .read_bytes = hw_intf_mpu6500_read_bytes,
    //     .write_bytes = hw_intf_mpu6500_write_bytes
    // };
    // imu_config_mpu6500(imu_handle, mpu6500_cfg);

    // ak8963_cfg_t ak8963_cfg = {
    //     .opr_mode = AK8963_MODE_CONT_MEASUREMENT_2,
    //     .mfs_sel = AK8963_MFS_16BIT,
    //     .read_bytes = hw_intf_ak8963_read_bytes,
    //     .write_bytes = hw_intf_ak8963_write_bytes
    // };
    // imu_config_ak8963(imu_handle, ak8963_cfg);

    mpu6050_cfg_t mpu6050_cfg = {
        .clksel = MPU6050_CLKSEL_X_GYRO_REF,
        .dlpf_cfg = MPU6050_44ACCEL_42GYRO_BW_HZ,
        .sleep_mode = MPU6050_DISABLE_SLEEP_MODE,
        .gfs_sel = MPU6050_GFS_SEL_2000,
        .afs_sel = MPU6050_AFS_SEL_8G,
        .read_bytes = hw_intf_mpu6050_read_bytes,
        .write_bytes = hw_intf_mpu6050_write_bytes
    };
    imu_config_mpu6050(imu_handle, mpu6050_cfg);

    imu_config(imu_handle);

    /* Config madgwick filter */
    imu_madgwick_handle = imu_madgwick_init();

    imu_madgwick_cfg_t imu_madgwick_cfg = {
        .beta = 0.1f,
        .sample_freq = 1000.0f
    };
    imu_madgwick_set_config(imu_madgwick_handle, imu_madgwick_cfg);

    imu_madgwick_config(imu_madgwick_handle);

    return ERR_CODE_SUCCESS;
}

err_code_t periph_imu_update_quat(void)
{
    float accel_x, accel_y, accel_z;
    float gyro_x, gyro_y, gyro_z;

    imu_get_accel_scale(imu_handle, &accel_x, &accel_y, &accel_z);
    imu_get_gyro_scale(imu_handle, &gyro_x, &gyro_y, &gyro_z);

    imu_madgwick_update_6dof(imu_madgwick_handle, gyro_x, gyro_y, gyro_z, accel_x, accel_y, accel_z);

    return ERR_CODE_SUCCESS;
}

err_code_t periph_imu_get_quat(float *q0, float *q1, float *q2, float* q3)
{
    imu_madgwick_quat_t quat_data;

    imu_madgwick_get_quaternion(imu_madgwick_handle, &quat_data);

    *q0 = quat_data.q0;
    *q1 = quat_data.q1;
    *q2 = quat_data.q2;
    *q3 = quat_data.q3;

    return ERR_CODE_SUCCESS;
}
