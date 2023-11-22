#include "imu.h"
#include "imu_madgwick.h"
#include "periph_imu.h"
#include "hw_intf.h"

imu_handle_t imu_handle = NULL;
imu_madgwick_handle_t imu_madgwick_handle = NULL;

err_code_t periph_imu_init(void)
{
    /* Config MPU6500 and AK8963 */
    imu_handle = imu_init();
    if (imu_handle == NULL)
    {
        return ERR_CODE_NULL_PTR;
    }

    err_code_t err_ret;

    imu_cfg_t imu_cfg = {
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
        .mag_soft_iron_bias_z = 0,
        .func_delay = HAL_Delay,
        .mpu6050_read_bytes = hw_intf_mpu6050_read_bytes,
        .mpu6050_write_bytes = hw_intf_mpu6050_write_bytes
    };
    err_ret = imu_set_config(imu_handle, imu_cfg);
    if (err_ret != ERR_CODE_SUCCESS)
    {
        return err_ret;
    }

    err_ret = imu_config(imu_handle);
    if (err_ret != ERR_CODE_SUCCESS)
    {
        return err_ret;
    }

    /* Config madgwick filter */
    imu_madgwick_handle = imu_madgwick_init();
    if (imu_madgwick_handle == NULL)
    {
        return err_ret;
    }

    imu_madgwick_cfg_t imu_madgwick_cfg = {
        .beta = 0.1f,
        .sample_freq = 200.0f
    };
    err_ret = imu_madgwick_set_config(imu_madgwick_handle, imu_madgwick_cfg);
    if (err_ret != ERR_CODE_SUCCESS)
    {
        return err_ret;
    }

    err_ret = imu_madgwick_config(imu_madgwick_handle);
    if (err_ret != ERR_CODE_SUCCESS)
    {
        return err_ret;
    }

    return ERR_CODE_SUCCESS;
}

err_code_t periph_imu_update_quat(void)
{
    if ((imu_handle == NULL) || (imu_madgwick_handle == NULL))
    {
        return ERR_CODE_NULL_PTR;
    }

    err_code_t err_ret;
    float accel_x, accel_y, accel_z;
    float gyro_x, gyro_y, gyro_z;

    err_ret = imu_get_accel_scale(imu_handle, &accel_x, &accel_y, &accel_z);
    if (err_ret != ERR_CODE_SUCCESS)
    {
        return err_ret;
    }

    err_ret = imu_get_gyro_scale(imu_handle, &gyro_x, &gyro_y, &gyro_z);
    if (err_ret != ERR_CODE_SUCCESS)
    {
        return err_ret;
    }

    err_ret = imu_madgwick_update_6dof(imu_madgwick_handle, gyro_x, gyro_y, gyro_z, accel_x, accel_y, accel_z);
    if (err_ret != ERR_CODE_SUCCESS)
    {
        return err_ret;
    }

    return ERR_CODE_SUCCESS;
}

err_code_t periph_imu_get_quat(float *q0, float *q1, float *q2, float* q3)
{
    if (imu_madgwick_handle == NULL)
    {
        return ERR_CODE_NULL_PTR;
    }

    err_code_t err_ret;
    imu_madgwick_quat_t quat_data;

    err_ret = imu_madgwick_get_quaternion(imu_madgwick_handle, &quat_data);
    if (err_ret != ERR_CODE_SUCCESS)
    {
        return err_ret;
    }

    *q0 = quat_data.q0;
    *q1 = quat_data.q1;
    *q2 = quat_data.q2;
    *q3 = quat_data.q3;

    return ERR_CODE_SUCCESS;
}
