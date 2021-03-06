#ifndef __MOTOR_H__
#define __MOTOR_H__

#ifdef __cplusplus
  extern "C" {
#endif

#include "stm32F4xx_hal.h" 
#include "stm32f4xx_hal_tim.h"
#include "pid.h"

typedef struct Motor_Init
{
	TIM_HandleTypeDef *Mhtim;
	uint32_t 				Channel1; 
	uint32_t 				Channel2; 
	GPIO_TypeDef 			*MGPIOx; 
	uint16_t 				MGPIO_Pin;
	TIM_HandleTypeDef *Ehtim; 
	GPIO_TypeDef 			*EGPIOx; //Todo delete
	uint16_t 				EGPIO_Pin;
	bool						Rotate_Direction;
}Motor_InitTypeDef;


class Motor
{
public:
	Motor(Motor_InitTypeDef MotEnc);
	~Motor(void);
	
public:
	void enable();
	void disable();
	void start();
	void forward(int8_t dutyratio);
	void backward(int8_t dutyratio);
	void brake();
	void setDutyratio(int8_t dutyratio);
	void getEncoderValue();
	void setTrace(int16_t setvalue);
	void setInterval();
	void setInteLimit(float intelimit);
	int8_t getDutyRatio();
private:
	void setPWM(uint32_t Channel,uint8_t value);
public:
	void pid_process();
private:
	TIM_HandleTypeDef 		*m_Mhtim;
	uint32_t 				m_outA;
	uint32_t 				m_outB;
	GPIO_TypeDef 			*m_MGPIOx;
	uint16_t 				m_MGPIO_Pin;
	TIM_HandleTypeDef 		*m_Ehtim;
	GPIO_TypeDef 			*m_EGPIOx; 
	uint16_t 				m_EGPIO_Pin;
	int8_t  				m_dutyratio;
  bool 						m_Rotate_Direction;
/*
 * These varialbes are intended for PID motion control
 */
public:
	static uint16_t	m_interval;
	pid_ctrl_t      m_pid;
	int16_t 				m_EncValue;
	float					  m_trace;
};

#ifdef __cplusplus
}
#endif
#endif
