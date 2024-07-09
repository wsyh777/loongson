#include "ls1c102_i2c.h"
#include "ls1c102.h"

/* I2C START mask */
#define I2C_START_Set           ((uint8_t)0x80)
#define I2C_START_Reset         ((uint8_t)0x7F)

/* I2C STOP mask */
#define I2C_STOP_Set            ((uint8_t)0x40)
#define I2C_STOP_Reset          ((uint8_t)0xBF)

/* I2C ACK mask */
#define I2C_ACK_Set             ((uint8_t)0x08)
#define I2C_ACK_Reset           ((uint8_t)0xF7)

/* I2C ADD0 mask */
#define I2C_ADD0_Set            ((uint8_t)0x01)
#define I2C_ADD0_Reset          ((uint8_t)0xFE)

#define FLAG_Mask               ((uint8_t)0xFF)
#define ITEN_Mask               ((uint8_t)0x40)

static inline void I2C_delay_restart(void)
{
    for(volatile int j = 100; j; j--){
        ;
    }
}


/**
  * @brief  Fills each I2C_InitStruct member with its default value.
  * @param  I2C_InitStruct: pointer to an I2C_InitTypeDef structure which will be initialized.
  * @retval None
  */
void I2C_StructInit(I2C_InitTypeDef* I2C_InitStruct)
{
    /*---------------- Reset I2C init structure parameters values ----------------*/
    /* initialize the I2C_ClockSpeed member */
    I2C_InitStruct->I2C_ClockSpeed = 100000;// IIC ��׼����100k����������400k��
    //I2C_InitStruct->I2C_ClockSpeed = 400000;// not feasible
    
    /* Initialize the I2C_Mode member */
    I2C_InitStruct->I2C_Mode = I2C_Mode_Master;
    //I2C_InitStruct->I2C_Mode = I2C_Mode_Slave;

    /* Initialize the I2C_OwnAddress1 member */
    //I2C_InitStruct->I2C_OwnAddress1 = 0x2A;// initial ��// ��Ϊ���豸ʱ����Ŵӻ���ַ����Ϊ���豸ʱӦ��û��
    
    /* Initialize the I2C_Buslock Check */
    I2C_InitStruct->I2C_BuslockCheckEn = I2C_Buslock_Check_Enable;// ��������״̬���ʹ��

    /* Initialize the I2C_Slave_Autoreset */
    I2C_InitStruct->I2C_SlvAutoresetEn = I2C_Slv_Autoreset_Disable;// ��������ʱ���豸�Զ���λ״̬��ʧ�ܡ���Ϊ���豸ʱӦ��û��
}

/**
  * @brief  Initializes the I2C peripheral according to the specified
  * 		parameters in the I2C_InitStruct .
  * @param  I2C: select the I2C peripheral.
  *         This parameter can be I2C.
  * @param  I2C_InitStruct:  pointer to an I2C_InitTypeDef structure
  *         that contains the configuration information for the specified I2C peripheral.
  * @retval None
  */
void I2C_Init(I2C_InitTypeDef* I2C_InitStruct)
{
	uint32_t tmp = 0;
	uint32_t pclk1 = 8000000;// 8MHz ʱ��

	/* Check the parameters */
	/*---------------------------- I2C Configuration ------------------------*/
	I2C->CTRL = 0x20;// ѡ����ģʽ�����ʷ�Ƶ�Ĵ���

	tmp = pclk1 / I2C_InitStruct->I2C_ClockSpeed;

	tmp = (tmp >> 2) - 1;

	I2C->PRERL = tmp;// 8MHzʱ�ӣ����ʹ�õ���100k����Ƶϵ��Ϊ80�����Ե��ֽڼĴ����͹��ˣ����ֽڼĴ���Ϊ0��
	I2C->PRERH = tmp >> 8;

	/* Enable the selected I2C peripheral */
	//I2C->CTRL = 0x80 | (I2C_InitStruct->I2C_Mode) | (I2C_InitStruct->I2C_BuslockCheckEn)
		//| (I2C_InitStruct->I2C_SlvAutoresetEn);// initial
	I2C->CTRL = 0x80 | (I2C_InitStruct->I2C_Mode) | (I2C_InitStruct->I2C_BuslockCheckEn);
    // ģ�鹤��ʹ�ܡ�ѡ����ģʽ��
    
	if (I2C_InitStruct->I2C_BuslockCheckEn)
	{
		I2C->CR_SR = 0x04;// ִ����������ʱ�ָ�����������
	}
	//I2C->SADDR = I2C_InitStruct->I2C_OwnAddress1;// ��Ϊ���豸ʱ����Ŵӻ���ַ����Ϊ���豸ʱӦ��û��

	I2C_wait();
}

/**
  * @brief  Generates I2C communication START condition.
  * @param  I2C: select the I2C peripheral.
  *   		This parameter can be I2C.
  * @param  NewState: new state of the I2C START condition generation.
  *   	    This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void I2C_GenerateSTART(FunctionalState NewState)
{
    if (NewState != DISABLE)
    {
		/* Generate a START condition */
		I2C->CR_SR |= I2C_START_Set;
    }
    else
    {
		/* Disable the START condition generation */
		I2C->CR_SR &= I2C_START_Reset;
    }

    //I2C_delay_restart();
}

/**
  * @brief  Generates I2C communication STOP condition.
  * @param  I2C: select the I2C peripheral.
  *   	    This parameter can be I2C.
  * @param  NewState: new state of the I2C STOP condition generation.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void I2C_GenerateSTOP(FunctionalState NewState)
{
    if (NewState != DISABLE)
    {
		/* Generate a STOP condition */
		I2C->CR_SR |= I2C_STOP_Set;
    }
    else
    {
		/* Disable the STOP condition generation */
		I2C->CR_SR &= I2C_STOP_Reset;
    }

    I2C_delay_restart();
}

/**
  * @brief  Enables or disables the specified I2C acknowledge feature.
  * @param  I2C: select the I2C peripheral.
  *   	    This parameter can be I2C.
  * @param  NewState: new state of the I2C Acknowledgement.
  *   	    This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void I2C_AcknowledgeConfig(FunctionalState NewState)
{
    if (NewState != DISABLE)
    {
		/* Enable the acknowledgement */
		I2C->CR_SR |= I2C_ACK_Set;
    }
    else
    {
		/* Disable the acknowledgement */
		I2C->CR_SR &= I2C_ACK_Reset;
    }
}

/**
  * @brief  Sends a data byte through the I2C peripheral.
  * @param  I2C: select the I2C peripheral.
  *         This parameter can be I2C.
  * @param  Data: Byte to be transmitted.
  * @retval None
  */
void I2C_SendData(uint8_t Data)
{
  	/* Write in the DR register the data to be sent */
	I2C_Unlock();

	I2C->DR = Data;
	I2C->CR_SR = 0x10;
}

/**
  * @brief  Returns the most recent received data by the I2C peripheral.
  * @param  I2C: select the I2C peripheral.
  *         This parameter can be I2C.
  * @retval The value of the received data.
  */
void I2C_ReceiveData(FunctionalState ACK, FunctionalState STOP)
{
    I2C_Unlock();

  	/* Return the data in the DR register */
    I2C->CR_SR = 0x20 | ACK | STOP;// ��ȡ I2C->DR �е�����
	return;
}

/**
  * @brief  Sends a Address byte through the I2C peripheral.
  * @param  I2C: select the I2C peripheral.
  *   	    This parameter can be I2C.
  * @param  Address: Address to be transmitted.
  * @param  I2C_Direction: set the direction of the I2C next byte transfer.
  *   		This parameter can be I2C_Direction_Transmitter or I2C_Direction_Receiver.
  * @retval None
  */
void I2C_Send7bitAddress(uint8_t Address, uint8_t I2C_Direction)
{
	/* Test on the direction to set/reset the read/write bit */
	I2C_Unlock();

	if (I2C_Direction != I2C_Direction_Transmitter)
	{
		/* Set the address bit0 for read */
		Address |= I2C_ADD0_Set;
			printk("\r\n receive addr 0x%02x\r\n", Address);
	}
	else
	{
		/* Reset the address bit0 for write */
		Address &= I2C_ADD0_Reset;// 0xFE = 0b1111_1110
			printk("\r\n trans addr 0x%02x\r\n", Address);
	}
	I2C->DR = Address;
	I2C->CR_SR = 0x90;// 0x90 ��ʾ���Ϳ�ʼ�źź�д�ź�
	/* Send the address */
}

/**
  * @brief  Wait for the Master's transmission is completed.
  * @param  I2C: select the I2C peripheral.
  *   		This parameter can be I2C.
  * @retval None
  */
void I2C_wait()
{
	uint8_t temp;
	temp = I2C->CR_SR;
    while (temp & 0x02)// �ȴ��������
    {
		temp = I2C->CR_SR;
    }
}

/**
  * @brief  Wait for the bus until it is idle.
  * @param  I2C: select the I2C peripheral.
  *   		This parameter can be I2C.
  * @retval None
  */
void I2C_BUSY()
{
	uint8_t temp;
	temp = I2C->CR_SR;
    while (temp & 0x40)// �ȴ����߿���
    {
		temp = I2C->CR_SR;
    }
}

/**
  * @brief  Check for buslock and recover it if so.
  * @param  I2C: select the I2C peripheral.
  *         This parameter can be I2C.
  * @retval None
  */
void I2C_Unlock()
{
	uint8_t temp;
	temp = I2C-> CR_SR;
    if (temp & 0x04)// ����������������� if
    {
		I2C->CR_SR |= 0x04;// �����������
    }
}

/**
  * @brief  Reads the specified I2C register and returns its value.
  * @param  I2C: select the I2C peripheral.
  *   		This parameter can be I2C.
  * @param  I2C_Register: specifies the register to read.
  *   		This parameter can be one of the following values:
  * 		@arg    I2C_Register_PRERL:  PRERL register.
  * 		@arg    I2C_Register_PRERH:  PRERH register.
  * 		@arg    I2C_Register_CTRL:	 CTR register.
  * 		@arg    I2C_Register_DR:	 DR register.
  * 		@arg    I2C_Register_SR:	 SR register.
  * 		@arg    I2C_Register_BLTOP:  BLTOP register.
  * 		@arg    I2C_Register_SADDR:  SADDR register.
  * @retval The value of the read register.
  */
uint8_t I2C_ReadRegister(uint8_t I2C_Register)
{
	__IO uint32_t tmp = 0;

	tmp = (uint32_t) I2C;
	tmp += I2C_Register;

	/* Return the selected register value */
	return (*(__IO uint8_t *) tmp);
}

/**
 * brief�� Enables or disables the specified I2C interrupts.
 * @param  I2C: Select the I2c peripheral.
 *   	   This parameter can be I2C.
 * @param  NewState: new state of the specified I2C interrupt.
 *         This parameter can be: ENABLE or DISABLE.
 * @retval None
 */
void I2C_ITConfig(FunctionalState NewState)
{
    if (NewState != DISABLE)
    {
		/* Enable the selected I2C interrupts */
		I2C->CTRL |= 0X40;
    }
    else
    {
		/* Disable the selected I2C interrupts */
		I2C->CTRL &= (uint8_t)~0X40;
    }
}

/**
 * brief�� Enables or disables the specified I2C interrupts.
 * @param  I2C: Select the I2c peripheral.
 *         This parameter can be I2C.
 * @param  NewState: new state of the specified I2C interrupt.
 *         This parameter can be: ENABLE or DISABLE.
 * @retval None
 */
void I2C_ITCmd(FunctionalState NewState)
{
	/* set the interrupt */
	(NewState != DISABLE) ? (INT_EN  |= IRQ_I2C) : (INT_EN  &= ~(IRQ_I2C));
}

/**
  * @brief  Clears the I2C's interrupt pending bits.
  * @param  I2C: select the I2C peripheral.
  *   		This parameter can be I2C.
  * @retval None
  */
void I2C_ClearIT()
{
	I2C->CR_SR = 0x01;// IIC ����Ĵ��� CR �е��ж����λ��1
	SET_BIT(INT_CLR, IRQ_I2C);// INTC �жϿ������е� IIC ���ж����λ��1
}

/**
  * @brief  Clears the I2C's flags.
  * @param  I2C: select the I2C peripheral.
  *   		This parameter can be I2C.
  * @param  I2C_FLAG: specifies the flag to clear.
  *   		This parameter can be any combination of the following values:
  *     	@arg I2C_FLAG_IT: SMBus Alert flag
  * @retval None
  */
void I2C_ClearFlag(uint8_t I2C_FLAG)// �ú���������� I2C_FLAG ����ȷ���������ò���ȷ
{
	uint8_t flagpos = 0;

	/* Get the I2C flag position */
	flagpos = I2C_FLAG & FLAG_Mask;

	/* Clear the selected I2C flag */
	I2C->CR_SR = (uint8_t)~flagpos;
}

/**
  * @brief  GET the I2C Status.
  * @param  I2C: select the I2C peripheral.
  *   		This parameter can be I2C.
  * @param  I2C_IT: check the interrupt flag.
  *   		This parameter can be I2C_STATE_IF.
  * @retval The new state of I2C_IT (SET or RESET).
  */
ITStatus I2C_GetStatus(uint8_t I2C_STATUS)
{
	ITStatus bitstatus = RESET;

	/* Get bit[7:0] of the flag */
	I2C_STATUS &= FLAG_Mask;

	/* Check the status of the I2C interrupt flag */
	if (((I2C->CR_SR & I2C_STATUS) != (uint8_t)RESET))// ������һ���ֽڻ����豸��ʧ�ٲ�ʱ���� if
	{
		/* I2C_IT is set */
		bitstatus = SET;
	}
	else
	{
		/* I2C_IT is reset */
		bitstatus = RESET;
	}
	/* Return the I2C_IT status */
	return  bitstatus;
}