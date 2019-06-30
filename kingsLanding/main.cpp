// Discoery Board Datasheet: https://www.st.com/content/ccc/resource/technical/document/user_manual/f0/14/c1/b9/95/6d/40/4d/DM00190424.pdf/files/DM00190424.pdf/jcr:content/translations/en.DM00190424.pdf
// STM32F746xx Datasheet: https://www.st.com/resource/en/datasheet/DM00166116.pdf
// STM32F74xxx Full Reference Manual: https://www.st.com/content/ccc/resource/technical/document/reference_manual/c5/cf/ef/52/c0/f1/4b/fa/DM00124865.pdf/files/DM00124865.pdf/jcr:content/translations/en.DM00124865.pdf

#include <stm32f7xx_hal.h>

UART_HandleTypeDef uart6;  // Uart Pins: RX-PC6/D1 TX-PC7/D0
UART_HandleTypeDef uart1;  // Uart Pins: Connected through STLink

#ifdef __cplusplus
extern "C"
#endif
  
void SysTick_Handler(void);
void SystemClock_Config(void);
void Init_Green_Led(void);
void Init_Uart6(void);
void Init_STLink_Uart(void);


int main(void)
{
  SCB_EnableICache();
  SCB_EnableDCache();
  HAL_Init();
  SystemClock_Config();
  Init_Green_Led();
  Init_Uart6();
  Init_STLink_Uart();
  
  HAL_Delay(100);
  
  while (1)
  {
    HAL_Delay(500);
    HAL_GPIO_WritePin(GPIOI, GPIO_PIN_1, GPIO_PIN_RESET);
    HAL_Delay(500);
    HAL_GPIO_WritePin(GPIOI, GPIO_PIN_1, GPIO_PIN_SET);
    
    uint8_t onlineMessage[15] = "uart6 online\r\n";
    HAL_UART_Transmit(&uart6, onlineMessage, 15, 100);
    uint8_t onlineMessage2[15] = "uart1 online\r\n";
    HAL_UART_Transmit(&uart1, onlineMessage2, 15, 100);   
  }
}


void Init_Green_Led(void)
{
  // Init Green Led Pin
  __HAL_RCC_GPIOI_CLK_ENABLE();
  GPIO_InitTypeDef GPIO_InitStruct = { 0 };
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);
}

void Init_Uart6(void)
{
  // Init Uart6 Pins
  __HAL_RCC_GPIOC_CLK_ENABLE();
  GPIO_InitTypeDef GPIO_InitStruct = { 0 };
  GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF8_USART6;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct); 

  // Init Uart6
  __HAL_RCC_USART6_CLK_ENABLE();
  uart6.Instance = USART6;
  uart6.Init.BaudRate = 115200;
  uart6.Init.WordLength = UART_WORDLENGTH_8B;
  uart6.Init.StopBits = UART_STOPBITS_1;
  uart6.Init.Parity = UART_PARITY_NONE;
  uart6.Init.Mode = UART_MODE_TX_RX;
  uart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  uart6.Init.OverSampling = UART_OVERSAMPLING_16;
  uart6.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  uart6.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  HAL_UART_Init(&uart6);
}

void Init_STLink_Uart(void)
{
  // Init Uart1 Pins
  __HAL_RCC_GPIOB_CLK_ENABLE();
  GPIO_InitTypeDef GPIO_InitStruct = { 0 };
  GPIO_InitStruct.Pin = GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  
  __HAL_RCC_GPIOA_CLK_ENABLE();
  GPIO_InitStruct.Pin = GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  // Enable Uart1
  __HAL_RCC_USART1_CLK_ENABLE();
  uart1.Instance = USART1;
  uart1.Init.BaudRate = 115200;
  uart1.Init.WordLength = UART_WORDLENGTH_8B;
  uart1.Init.StopBits = UART_STOPBITS_1;
  uart1.Init.Parity = UART_PARITY_NONE;
  uart1.Init.Mode = UART_MODE_TX_RX;
  uart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  uart1.Init.OverSampling = UART_OVERSAMPLING_16;
  uart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  uart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  HAL_UART_Init(&uart1);
}



// Setup clock to run @ 216 MHz
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
  RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 216;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  HAL_PWREx_EnableOverDrive();

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7);
  
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

// Increment SysTick - Neccesary for "HAL_Delay" to run correctly
void SysTick_Handler(void)
{
  HAL_IncTick();
  HAL_SYSTICK_IRQHandler();
}
