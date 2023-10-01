/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "err_code.h"
#include "hw_intf.h"
#include "imu_public.h"
#include "imu_madgwick.h"
#include "bldc_motor.h"
/* USER CODE END Includes */
/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */
/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */
/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */
/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
imu_handle_t imu_handle = NULL;
imu_madgwick_handle_t imu_madgwick_handle = NULL;
bldc_motor_handle_t motor_front_left = NULL;
bldc_motor_handle_t motor_front_right = NULL;
bldc_motor_handle_t motor_back_left = NULL;
bldc_motor_handle_t motor_back_right = NULL;
/* USER CODE END PV */
/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
err_code_t SystemIMU_Config(void);
err_code_t SystemIMUFilter_Config(void);
err_code_t SystemMotor_Config(void);
/* USER CODE END PFP */
/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */
/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
    /* USER CODE BEGIN 1 */

    /* USER CODE END 1 */
    /* MCU Configuration--------------------------------------------------------*/
    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();
    /* USER CODE BEGIN Init */

    /* USER CODE END Init */
    /* Configure the system clock */
    SystemClock_Config();
    SystemIMUFilter_Config();
    /* USER CODE BEGIN SysInit */

    /* USER CODE END SysInit */
    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_DMA_Init();
    MX_TIM1_Init();
    MX_SPI1_Init();
    /* USER CODE BEGIN 2 */
    SystemIMU_Config();
    /* USER CODE END 2 */
    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1)
    {
        /* USER CODE END WHILE */
        /* USER CODE BEGIN 3 */
    }
    /* USER CODE END 3 */
}
/**
    * @brief System Clock Configuration
    * @retval None
    */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    /** Configure the main internal regulator output voltage
    */
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
    /** Initializes the RCC Oscillators according to the specified parameters
    * in the RCC_OscInitTypeDef structure.
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 4;
    RCC_OscInitStruct.PLL.PLLN = 168;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 4;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }
    /** Initializes the CPU, AHB and APB buses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                  | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
    {
        Error_Handler();
    }
}
/* USER CODE BEGIN 4 */
err_code_t SystemIMU_Config(void)
{
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

    return ERR_CODE_SUCCESS;
}

err_code_t SystemIMUFilter_Config(void)
{
    imu_madgwick_handle = imu_madgwick_init();

    imu_madgwick_cfg_t imu_madgwick_cfg = {
        .beta = 0.1f,
        .sample_freq = 50.0f
    };
    imu_madgwick_set_config(imu_madgwick_handle, imu_madgwick_cfg);

    imu_madgwick_config(imu_madgwick_handle);

    return ERR_CODE_SUCCESS;
}

err_code_t SystemMotor_Config(void)
{
    return ERR_CODE_SUCCESS;
}
/* USER CODE END 4 */
/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1)
    {
    }
    /* USER CODE END Error_Handler_Debug */
}
#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
