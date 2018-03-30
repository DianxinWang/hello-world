//TODO CHECK THE GPIO STATE OF ENABLE


#include "motor.h"


Motor::Motor(Motor_InitTypeDef MotEnc)
{	
	m_Mhtim = MotEnc.Mhtim;
	m_outA = MotEnc.Channel1;
	m_outB = MotEnc.Channel2;
	m_dutyratio = 0;
	m_MGPIOx = MotEnc.MGPIOx;
	m_MGPIO_Pin = MotEnc.MGPIO_Pin;
	m_Ehtim = MotEnc.Ehtim;
	m_EGPIOx = MotEnc.EGPIOx;
	m_EGPIO_Pin = MotEnc.EGPIO_Pin;
	m_SampleFrequence = 1000;
	pid_init(&m_pid);
	pid_set_gains(&m_pid, 1, 0, 0);
};

void Motor::enable()
{
	HAL_GPIO_WritePin(m_MGPIOx, m_MGPIO_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(m_EGPIOx, m_EGPIO_Pin, GPIO_PIN_SET);
	HAL_TIM_Encoder_Start(m_Ehtim, TIM_CHANNEL_ALL);
}
void Motor::disable()
{
	HAL_GPIO_WritePin(m_MGPIOx, m_MGPIO_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(m_EGPIOx, m_EGPIO_Pin, GPIO_PIN_RESET);
	HAL_TIM_Encoder_Stop(m_Ehtim, TIM_CHANNEL_ALL);
}

void Motor::start()
{
	if(m_dutyratio >=0) 
		forward(m_dutyratio);
	else	
		backward(-m_dutyratio);
}

void Motor::forward(int8_t dutyratio)
{
	m_dutyratio = dutyratio;
	setPWM(m_outA, dutyratio);
	setPWM(m_outB, 0);
}

void Motor::backward(int8_t dutyratio)
{
	m_dutyratio = dutyratio;
	setPWM(m_outA, 0);
	setPWM(m_outB, dutyratio);
}

void Motor::brake()
{
	setPWM(m_outA, 0);
	setPWM(m_outB, 0);
}

void Motor::setPWM(uint32_t Channel,uint8_t value)  
{     
    uint32_t period=m_Mhtim->Init.Period+1;  
    uint32_t pluse=(value * period)/100;   
    __HAL_TIM_SET_COMPARE(m_Mhtim, Channel, pluse);  
    HAL_TIM_PWM_Start(m_Mhtim, Channel);
}

int8_t Motor::getDutyRatio()
{
	return m_dutyratio;
}

void Motor::getEncoderValue()
{
	m_EncValue = (int16_t)(__HAL_TIM_GET_COUNTER(m_Ehtim));
}

void Motor::setDutyratio(int8_t dutyratio)
{
	m_dutyratio = dutyratio;
}

void Motor::pid_process(int16_t setvalue)
{
	this->getEncoderValue();
	m_dutyratio = ::pid_process(&m_pid, m_EncValue - setvalue);
	if(m_dutyratio > 100) m_dutyratio = 100;
	else if(m_dutyratio < -100) m_dutyratio = -100;
}