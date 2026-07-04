/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "cmsis_os.h"
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <math.h>
#include "ai_platform.h"
#include "network_1.h"
#include "network_1_data.h"
#include "usbd_hid.h"
// Silence the conflicting duplicate 'bool' definitions between stdbool and the ToF library
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmacro-redefined"
#include "VL53L0X.h"
#pragma GCC diagnostic pop
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
I2C_HandleTypeDef hi2c2;

UART_HandleTypeDef huart1;

extern USBD_HandleTypeDef hUsbDeviceFS;
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* USER CODE BEGIN PV */
// Global AI Engine Handle Structures
static ai_handle network_handle = AI_HANDLE_NULL;
ai_buffer ai_input[AI_NETWORK_1_IN_NUM];
ai_buffer ai_output[AI_NETWORK_1_OUT_NUM];

AI_ALIGNED(32)
static ai_u8 activations_buffer[AI_NETWORK_1_DATA_ACTIVATIONS_SIZE];

// App Shared Memory Layout arrays
static ai_float ai_input_features[30];
static ai_float prediction_outputs[30];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C2_Init(void);
static void MX_USART1_UART_Init(void);
void StartDefaultTask(void *argument);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
#ifdef __GNUC__
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

PUTCHAR_PROTOTYPE
{
  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
  return ch;
}

void AI_Model_Init(void) {
    ai_error err;
    ai_network_report report;

    // 1. Instantiate the neural network execution runtime
    err = ai_network_1_create(&network_handle, AI_NETWORK_1_DATA_CONFIG);
    if (err.type != AI_ERROR_NONE) {
        printf("Error: Network creation failed! Type: %d, Code: %d\r\n", err.type, err.code);
        while(1);
    }

    // 2. Map structural weights using modern structured designated initialization flags
    const ai_network_params params = {
        .params = AI_NETWORK_1_DATA_WEIGHTS(ai_network_1_data_weights_get()),
        .activations = AI_NETWORK_1_DATA_ACTIVATIONS(activations_buffer)
    };

    // 3. Initialize the internal layer parameters
    if (!ai_network_1_init(network_handle, &params)) {
        printf("Error: Network layer internal config initialization failed!\r\n");
        while(1);
    }

    // 4. Retrieve exact IO array metadata structures safely using the API report interface
    if (!ai_network_1_get_info(network_handle, &report)) {
        printf("Error: Failed to safely query model runtime info report!\r\n");
        while(1);
    }

    // 5. Clone structural settings over to input/output descriptors
    ai_input[0] = report.inputs[0];
    ai_output[0] = report.outputs[0];

    // 6. Bind live feature arrays safely to execution memory pointers
    ai_input[0].data = AI_HANDLE_PTR(ai_input_features);
    ai_output[0].data = AI_HANDLE_PTR(prediction_outputs);

    printf("LSTM Neural Network Engine Ready!\r\n");
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C2_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  printf("Initializing VL53L0X Sensor...\r\n");

  // Initialize the VL53L0X handle on I2C2
  initVL53L0X(1, &hi2c2);

  // Load recommended optical budget parameters for optimal sampling
  setSignalRateLimit(200);
  setVcselPulsePeriod(VcselPeriodPreRange, 10);
  setVcselPulsePeriod(VcselPeriodFinalRange, 14);
  setMeasurementTimingBudget(300 * 1000UL);

  printf("Sensor Setup Ready!\r\n");

  // Run our updated context model parser pipeline setup
  AI_Model_Init();
  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */

  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1)
  {

  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */


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
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE|RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 60;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }

  /** Enable MSI Auto calibration
  */
  HAL_RCCEx_EnableMSIPLLMode();
}

/**
  * @brief I2C2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C2_Init(void)
{

  /* USER CODE BEGIN I2C2_Init 0 */

  /* USER CODE END I2C2_Init 0 */

  /* USER CODE BEGIN I2C2_Init 1 */

  /* USER CODE END I2C2_Init 1 */
  hi2c2.Instance = I2C2;
  hi2c2.Init.Timing = 0x30A175AB;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c2, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c2, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C2_Init 2 */

  /* USER CODE END I2C2_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);

  /*Configure GPIO pin : PB14 */
  GPIO_InitStruct.Pin = GPIO_PIN_14;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PC6 */
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* init code for USB_DEVICE */
  MX_USB_DEVICE_Init();

  /* USER CODE BEGIN 5 */
  #define WINDOW_SIZE 30
  #define SAMPLE_DELAY_MS 30
  #define TOF_MAX_RANGE 1200

  // --- Local Task Memory Buffers ---
  uint16_t raw_samples[WINDOW_SIZE];
  char csv_buffer[256];
  char text_buffer[128];
  uint8_t mouse_report[4] = {0, 0, 0, 0}; // 8-byte USB HID standard keyboard buffer
  statInfo_t_VL53L0X distanceStr;

  printf("\r\n--- Starting I2C2 Bus Scan inside RTOS ---\r\n");
  HAL_StatusTypeDef scan_result;
  for (uint16_t i = 1; i < 128; i++) {
      scan_result = HAL_I2C_IsDeviceReady(&hi2c2, (uint16_t)(i << 1), 3, 10);
      if (scan_result == HAL_OK) {
          printf("Found Device! 7-bit Addr: 0x%02X | HAL 8-bit Addr: 0x%02X\r\n", i, (i << 1));
      }
  }
  printf("--- Scan Complete ---\r\n\r\n");

  /* Infinite loop */
  for(;;)
  {
      // Check if User Button is pressed (Active Low)
      if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET)
      {
          osDelay(200); // Debounce delay (RTOS-friendly)

          // Turn onboard LED ON to signal capturing motion
          HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);

          // 1. Capture 30 steps of physical data
          for (int i = 0; i < WINDOW_SIZE; i++)
          {
              uint16_t distance = readRangeSingleMillimeters(&distanceStr);

              if (distance == 0 || distance > TOF_MAX_RANGE) {
                  distance = TOF_MAX_RANGE;
              }

              raw_samples[i] = distance;
              osDelay(SAMPLE_DELAY_MS); // Yield CPU smoothly to allow context switching
          }

          // Recording finished: Turn LED back OFF
          HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);

          // 2. Pre-process and scale the sensor inputs properly using raw_samples
          for (int i = 0; i < 30; i++)
          {
              // Convert raw mm (0 to 1200) into a decimal range (0.0 to 1.0)
              ai_input_features[i] = (float)raw_samples[i] / 1200.0f;
          }

          // Format and Transmit raw telemetry row over UART for debugging
          int offset = 0;
          for (int i = 0; i < WINDOW_SIZE; i++)
          {
              offset += snprintf(csv_buffer + offset, sizeof(csv_buffer) - offset, "%d,", raw_samples[i]);
          }
          csv_buffer[offset - 1] = '\r';
          csv_buffer[offset] = '\n';
          csv_buffer[offset + 1] = '\0';
          HAL_UART_Transmit(&huart1, (uint8_t*)csv_buffer, strlen(csv_buffer), 200);

          // 3. Run TinyML LSTM Model Inference Pass
          ai_i32 batch_run = ai_network_1_run(network_handle, &ai_input[0], &ai_output[0]);

          if (batch_run > 0)
                    {
                        // Calculate the trend slope from the model predictions
                        float start_trend = 0.0f;
                        float end_trend = 0.0f;
                        for (int i = 0; i < 10; i++) {
                            start_trend += prediction_outputs[i];
                            end_trend += prediction_outputs[20 + i];
                        }
                        start_trend /= 10.0f;
                        end_trend /= 10.0f;
                        float slope = end_trend - start_trend;

                        char motion_label[20] = "STATIC";

                        // Filter out the 1200 noise spikes to find the true gesture direction
                        float first_half_sum = 0.0f;
                        float second_half_sum = 0.0f;
                        int first_half_valid_count = 0;
                        int second_half_valid_count = 0;
                        int absolute_min = 1200;

                        for (int i = 0; i < 30; i++) {
                            // Track absolute closest point to confirm hand presence
                            if (raw_samples[i] < absolute_min) {
                                absolute_min = raw_samples[i];
                            }

                            // Ignore the 1200 out-of-range sensor readings for direction calculation
                            if (raw_samples[i] < 1000) {
                                if (i < 15) {
                                    first_half_sum += raw_samples[i];
                                    first_half_valid_count++;
                                } else {
                                    second_half_sum += raw_samples[i];
                                    second_half_valid_count++;
                                }
                            }
                        }

                        // Only trigger if an object was legitimately closer than 700mm
                        if (absolute_min < 700 && first_half_valid_count > 2 && second_half_valid_count > 2)
                        {
                            float first_half_avg = first_half_sum / first_half_valid_count;
                            float second_half_avg = second_half_sum / second_half_valid_count;

                            // Clear previous mouse frame values
                            // Clear the report frame before assigning values
                            memset(mouse_report, 0, 4);

                                                // CASE 1: Left Swipe -> Move Cursor Left
                                                if (first_half_avg > second_half_avg)
                                                {
                                                    mouse_report[1] = (uint8_t)-60; // Load X-axis movement
                                                    USBD_HID_SendReport(&hUsbDeviceFS, mouse_report, 4);

                                                    osDelay(1); // Ultra-low latency delay

                                                    memset(mouse_report, 0, 4); // Clear frame
                                                    USBD_HID_SendReport(&hUsbDeviceFS, mouse_report, 4); // Stop movement

                                                    // FIX: NATIVE UART TRANSMIT PLACED AFTER THE MOUSE CLEAR TO PRESERVE TIMING
                                                    HAL_UART_Transmit(&huart1, (uint8_t*)"\r\n[ACTION] Left Swipe Detected!\r\n", 33, 10);
                                                }
                                                // CASE 2: Right Swipe -> Trigger Right Click Alone
                                                else if (second_half_avg > first_half_avg)
                                                {
                                                    mouse_report[0] = 0x02; // 0x02 tells the PC: "Right Mouse Button Pressed"
                                                    mouse_report[1] = 0;    // 0 tells the PC: "Do NOT move the cursor coordinates"
                                                    USBD_HID_SendReport(&hUsbDeviceFS, mouse_report, 4);

                                                    // Keep the button held for 10ms for OS registration
                                                    osDelay(10);

                                                    memset(mouse_report, 0, 4); // 0x00 tells the PC: "All Buttons Released"
                                                    USBD_HID_SendReport(&hUsbDeviceFS, mouse_report, 4);

                                                    // FIX: NATIVE UART TRANSMIT PLACED AFTER THE MOUSE RELEASE
                                                    HAL_UART_Transmit(&huart1, (uint8_t*)"\r\n[ACTION] Right Click Triggered!\r\n", 35, 10);
                                                }
                                            }

                                        else
                                        {
                                            ai_error runtime_err = ai_network_1_get_error(network_handle);
                                            snprintf(text_buffer, sizeof(text_buffer), "--> Inference Failed! Code: %d\r\n", runtime_err.code);
                                            HAL_UART_Transmit(&huart1, (uint8_t*)text_buffer, strlen(text_buffer), 200);
                                        }

                                        // Kept at a tight 5ms to balance live streaming logs and mouse reactivity
                                        osDelay(3);
                                    }
  /* USER CODE END 5 */
}}}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1)
  {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
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
