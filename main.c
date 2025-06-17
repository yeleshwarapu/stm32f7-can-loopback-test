#include "main.h"
#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_can.h"
#include <string.h>

CAN_HandleTypeDef hcan1;
CAN_TxHeaderTypeDef TxHeader;
CAN_RxHeaderTypeDef RxHeader;
uint8_t TxData[8] = {0xAA, 0x55, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
uint8_t RxData[8];
uint32_t TxMailbox;

int main(void) {
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_CAN1_Init();

  CAN_FilterTypeDef filter;
  filter.FilterIdHigh = 0;
  filter.FilterIdLow = 0;
  filter.FilterMaskIdHigh = 0;
  filter.FilterMaskIdLow = 0;
  filter.FilterFIFOAssignment = CAN_RX_FIFO0;
  filter.FilterBank = 0;
  filter.FilterMode = CAN_FILTERMODE_IDMASK;
  filter.FilterScale = CAN_FILTERSCALE_32BIT;
  filter.FilterActivation = ENABLE;
  HAL_CAN_ConfigFilter(&hcan1, &filter);

  HAL_CAN_Start(&hcan1);

  TxHeader.StdId = 0x123;
  TxHeader.ExtId = 0;
  TxHeader.RTR = CAN_RTR_DATA;
  TxHeader.IDE = CAN_ID_STD;
  TxHeader.DLC = 8;
  TxHeader.TransmitGlobalTime = DISABLE;

  while (1) {
    if (HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox) == HAL_OK) {
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET); // LED ON
    }

    if (HAL_CAN_GetRxFifoFillLevel(&hcan1, CAN_RX_FIFO0) > 0) {
      HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &RxHeader, RxData);
      if (RxHeader.StdId == 0x123 && memcmp(TxData, RxData, 8) == 0) {
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0); // Toggle LED
        HAL_Delay(500);
      }
    }
    HAL_Delay(1000);
  }
}
