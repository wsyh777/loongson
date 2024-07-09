#ifndef _LS1C102_I2C_H
#define _LS1C102_I2C_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @˵����I2C�ӿں궨��
 *
 */
typedef struct
{
  volatile uint8_t PRERL;			/* ��Ƶֵ���ֽڼĴ��� */
  volatile uint8_t PRERH;			/* ��Ƶֵ���ֽڼĴ��� */
  volatile uint8_t CTRL;			/* ���ƼĴ��� */
  volatile uint8_t DR;				/* ���ݼĴ��� */
  volatile uint8_t CR_SR;			/* ����Ĵ��� �� ״̬�Ĵ��� */
  volatile uint8_t BLTOP;			/* ��������ʱ��Ĵ��� */
  volatile uint8_t RESERVED0;		/* �����ֽ�  */
  volatile uint8_t SADDR;			/* ��ģʽ��ַ�Ĵ��� */
} I2C_TypeDef;

#define I2C                 ((I2C_TypeDef *) I2C_BASE)

typedef struct
{
	uint32_t I2C_ClockSpeed;         /*!< Specifies the clock frequency.
                                        This parameter must be set to a value lower than 400kHz */

	uint8_t I2C_Mode;                /*!< Specifies the I2C mode.
                                        This parameter can be a value of @ref I2C_mode */

	uint8_t I2C_OwnAddress1;         /*!< Specifies the first device own address.
                                        This parameter can be a 7-bit or 10-bit address. */

	uint8_t I2C_BuslockCheckEn;    	 /*!< Set the I2C buslock check function*/


	uint8_t I2C_SlvAutoresetEn;		 /*!< Set the I2C autoreset check function*/

}I2C_InitTypeDef;

#define IS_I2C_ALL_PERIPH(PERIPH) ((PERIPH) == I2C)

#define IS_I2C_CLEAR_FLAG(FLAG) (((FLAG) & 0x01) == 0x01)
/** @defgroup I2C_mode
  * @{
  */
#define IS_I2C_CLOCK_SPEED(SPEED) (((SPEED) >= 0x1) && ((SPEED) <= 400000))

#define IS_I2C_OWN_ADDRESS1(ADDRESS1) ((ADDRESS1) <= 0x3FF)

#define I2C_Mode_Slave            ((uint8_t)0x00)
#define I2C_Mode_Master           ((uint8_t)0x20)

#define IS_I2C_MODE(MODE) (((MODE) == I2C_Mode_Slave) || \
						   ((MODE) == I2C_Mode_Master))
/**
  * @}
  */
#define I2C_Buslock_Check_Enable                  ((uint8_t)0x02)
#define I2C_Buslock_Check_Disable                 ((uint8_t)0x00)
#define IS_I2C_BUSLOCK_CHECK_EN(STATE) (((STATE) == I2C_Buslock_Check_Enable) || \
										((STATE) == I2C_Buslock_Check_Disable))

#define I2C_Slv_Autoreset_Enable                  ((uint8_t)0x01)
#define I2C_Slv_Autoreset_Disable                 ((uint8_t)0x00)
#define IS_I2C_SLV_AUTORESET_EN(STATE) (((STATE) == I2C_Slv_Autoreset_Enable) || \
										((STATE) == I2C_Slv_Autoreset_Disable))

/** @defgroup I2C_transfer_direction
  * @{
  */
#define I2C_Direction_Transmitter       ((uint8_t)0x00)
#define I2C_Direction_Receiver          ((uint8_t)0x01)
#define IS_I2C_DIRECTION(DIRECTION) (((DIRECTION) == I2C_Direction_Transmitter) || \
										((DIRECTION) == I2C_Direction_Receiver))

#define  I2C_ACK      					((uint8_t)0x00)
#define  I2C_NACK         				((uint8_t)0x08)
#define IS_I2C_ACK(ACK) 	(((ACK) == I2C_ACK) ||  ((DIRECTION) == I2C_NACK))

#define I2C_STOP      					((uint8_t)0x40)
#define I2C_NSTOP         				((uint8_t)0x00)
#define IS_I2C_STOP(STOP) 	(((STOP) == I2C_STOP) ||  ((DIRECTION) == I2C_NSTOP))

/**
 *@ I2C_STATE_Flags
 */
#define I2C_STATE_RxACK                     ((uint8_t)0x80)  /* �յ���Ӧ��λ�� 0��ʾ�յ�Ӧ��1��ʾ�յ�NACK */
#define I2C_STATE_BUSY                      ((uint8_t)0x40)  /* ����æ��־ */
#define I2C_STATE_AL                        ((uint8_t)0x20)  /* ʧȥ�ٲã�1��ʾ���豸ʧȥ���߿���Ȩ  */
#define I2C_STATE_Slave_Addressed           ((uint8_t)0x10)  /* ��Ѱַ��1��ʾ��Ϊ���豸ʱ�ѱ�Ѱַ�ɹ�  */
#define I2C_STATE_Slave_Rw                  ((uint8_t)0x08)  /* ���豸��д��0��ʾ���� ��1��ʾ��д */
#define I2C_STATE_Buslock                   ((uint8_t)0x04)  /* ����������1��ʾ���߳������� */
#define I2C_STATE_TIP                       ((uint8_t)0x02)  /* ������У�1��ʾ���豸��Ч�����ڴ��� */
#define I2C_STATE_IF                        ((uint8_t)0x01)  /* �жϱ�־λ��1��ʾ������һ���ֽڻ����豸ʧȥ�ٲ� */

/** @defgroup I2C_registers
  * @{
  */
#define IS_I2C_GET_STATUS(I2C_STATUS)  (((I2C_STATUS) == I2C_STATE_RxACK) || \
										((I2C_STATUS) == I2C_STATE_BUSY) || \
										((I2C_STATUS) == I2C_STATE_AL) || \
										((I2C_STATUS) == I2C_STATE_Slave_Addressed) || \
										((I2C_STATUS) == I2C_STATE_Slave_Rw) || \
										((I2C_STATUS) == I2C_STATE_Buslock) || \
										((I2C_STATUS) == I2C_STATE_TIP) || \
										((I2C_STATUS) == I2C_STATE_IF))

#define I2C_Register_PRERL				((uint8_t)0x00)
#define I2C_Register_PRERH				((uint8_t)0x01)
#define I2C_Register_CTR				((uint8_t)0x02)
#define I2C_Register_DR					((uint8_t)0x03)
#define I2C_Register_SR					((uint8_t)0x04)
#define I2C_Register_BLTOP				((uint8_t)0x05)
#define I2C_Register_SADDR				((uint8_t)0x07)

#define IS_I2C_REGISTER(REGISTER) (((REGISTER) == I2C_Register_PRERL) || \
                                   ((REGISTER) == I2C_Register_PRERH) || \
                                   ((REGISTER) == I2C_Register_CTR) || \
                                   ((REGISTER) == I2C_Register_DR) || \
                                   ((REGISTER) == I2C_Register_SR) || \
                                   ((REGISTER) == I2C_Register_BLTOP) || \
                                   ((REGISTER) == I2C_Register_BLTOP))

#define IRQ_I2C         	((uint8_t)0x02)
//#define I2C_RXACK			((uint8_t)0x00)
//#define I2C_BUSY			((uint8_t)0x01)
//#define I2C_AL			((uint8_t)0x02)
//#define I2C_SLV_ADDR		((uint8_t)0x03)
//#define I2C_SLV_RW		((uint8_t)0x04)
//#define I2C_BUS_LOCK		((uint8_t)0x05)
//#define I2C_TIP			((uint8_t)0x07)
//#define I2C_IF			((uint8_t)0x07)

// I2C ��ʼ��
void I2C_Init(I2C_InitTypeDef* I2C_InitStruct);
void I2C_StructInit(I2C_InitTypeDef* I2C_InitStruct);
// I2C ��ʼ��

// I2C ʱ��
void I2C_GenerateSTART(FunctionalState NewState);	 // I2C���豸����start�ź�
void I2C_GenerateSTOP(FunctionalState NewState);     // I2C���豸����stop�ź�
void I2C_AcknowledgeConfig(FunctionalState NewState);// I2C���豸����ack�ź�
void I2C_SendData(uint8_t Data);					 // I2C��������
void I2C_ReceiveData(FunctionalState ACK, FunctionalState STOP); // I2C��������
void I2C_Send7bitAddress(uint8_t Address, uint8_t I2C_Direction);// I2C���ʹ��豸��ַ
void I2C_wait();									 // I2C�ȴ��������
void I2C_Unlock();									 // I2C�����������
void I2C_BUSY();									 // I2C�ȴ����߿���
// I2C ʱ��

// I2C �ж�
void I2C_ITConfig(FunctionalState NewState);		 // I2C�ж�����
void I2C_ITCmd(FunctionalState NewState);			 // I2C�жϿ���
void I2C_ClearIT();									 // I2C����жϱ�־
void I2C_ClearFlag(uint8_t I2C_FLAG);				 // I2C����Ĵ���״̬
ITStatus I2C_GetStatus(uint8_t I2C_STATUS);			 // I2C��ȡ״̬
// I2C �ж�

uint8_t I2C_ReadRegister(uint8_t I2C_Register);		 // I2C��ȡ�Ĵ�����ֵ

#ifdef __cplusplus
}
#endif

#endif // _LS1C102_I2C_H