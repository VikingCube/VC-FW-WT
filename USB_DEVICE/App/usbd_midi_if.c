/**
  ******************************************************************************
  * @file    usbd_midi_if.c
  * @author  Sam Kent
  * @brief   USB MIDI Access Layer
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usbd_midi_if.h"

/** @addtogroup STM32_USB_DEVICE_LIBRARY
  * @{
  */


/** @defgroup USBD_MIDI
  * @brief usbd core module
  * @{
  */

/** @defgroup USBD_MIDI_Private_TypesDefinitions
  * @{
  */
/**
  * @}
  */


/** @defgroup USBD_MIDI_Private_Defines
  * @{
  */
/**
  * @}
  */


/** @defgroup USBD_MIDI_Private_Macros
  * @{
  */

/**
  * @}
  */


/** @defgroup USBD_MIDI_Private_FunctionPrototypes
  * @{
  */

static int8_t MIDI_Init     (USBD_HandleTypeDef *pdev, uint8_t cfgidx);
static int8_t MIDI_DeInit   (USBD_HandleTypeDef *pdev, uint8_t cfgidx);
static int8_t MIDI_Receive  (uint8_t* pbuf, uint32_t length);
static int8_t MIDI_Send     (uint8_t* pbuf, uint32_t length);

USBD_MIDI_ItfTypeDef USBD_MIDI_fops =
{
  MIDI_Init,
  MIDI_DeInit,
  MIDI_Receive,
  MIDI_Send
};

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  MIDI_Init
  *         Initializes the MIDI media low layer
  * @param  None
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t MIDI_Init(USBD_HandleTypeDef *pdev, uint8_t cfgidx)
{
  /*
     Add your initialization code here
  */
  return (0);
}

/**
  * @brief  MIDI_DeInit
  *         DeInitializes the MIDI media low layer
  * @param  None
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t MIDI_DeInit(USBD_HandleTypeDef *pdev, uint8_t cfgidx)
{
  /*
     Add your deinitialization code here
  */
  return (0);
}

/**
  * @brief  MIDI_Send
  *
  * @param  buffer: bufferfer of data to be received
  * @param  length: Number of data received (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t MIDI_Send (uint8_t* buffer, uint32_t length)
{
  uint8_t ret = USBD_OK;

  USBD_MIDI_SetTxBuffer(&hUsbDeviceFS, buffer, length);

  ret = USBD_MIDI_TransmitPacket(&hUsbDeviceFS);

  return (ret);
}

/**
  * @brief  MIDI_Receive
  *
  * @param  buffer: bufferfer of data to be received
  * @param  length: Number of data received (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t MIDI_Receive (uint8_t* buffer, uint32_t length) //TODO DEBUG This never gets called.
{
  uint8_t ret = USBD_OK;
  if (length < 4) {
  	  return ret;
  }
  uint8_t chan = buffer[1] & 0x0f;
  uint8_t msgtype = buffer[1] & 0xf0;
  uint8_t b1 =  buffer[2]; //Note ?
  uint8_t b2 =  buffer[3]; //Velocity ? --> TODO: Pass it to note on - calculate it into ADSR.
  //uint16_t b = ((b2 & 0x7f) << 7) | (b1 & 0x7f);

  //TODO how to give the date up to the user level?

  if (msgtype == 0x90) { //NOTE ON
	  if (chan == 0x00) {
		  	  HAL_TIM_Base_Stop(&htim2);
	  		  htim2.Init.Period = midi_to_cnt[b1];
	  		  if (HAL_TIM_Base_Init(&htim2) != HAL_OK) { Error_Handler(); }
	  		  HAL_TIM_Base_Start(&htim2);
	  		  adsr_note_on(0, b2);
	  }
	  if (chan == 0x01) {
		  HAL_TIM_Base_Stop(&htim4);
		  htim4.Init.Period = midi_to_cnt[b1];
		  if (HAL_TIM_Base_Init(&htim4) != HAL_OK) { Error_Handler(); }
		  HAL_TIM_Base_Start(&htim4);
		  adsr_note_on(1, b2);
	  }
  } else if (msgtype == 0x80) { //NOTE OFF
	  if (chan < 0x02) {
		  adsr_note_off(chan);
	  }
  }
  return ret;
}

void MIDI_note_on(uint8_t note, uint8_t velocity) {
    uint8_t b[4];
    b[0] = 0x0B;
    b[1] = 0x90;
    b[2] = note;
    b[3] = velocity;

    MIDI_Send(b, 4);

}

void MIDI_note_off(uint8_t note, uint8_t velocity) {
    uint8_t b[4];
    b[0] = 0x0B;
    b[1] = 0x80;
    b[2] = note;
    b[3] = velocity;

    MIDI_Send(b, 4);

}

void MIDI_cc_update(uint8_t channel , uint8_t controler_number, uint8_t controller_value) {
    uint8_t b[4];
    b[0] = 0x0B;
    b[1] = 0xB0 | channel;
    b[2] = controler_number;
    b[3] = controller_value;

    MIDI_Send(b, 4);

}
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
