/*
 * duty.h
 *
 *  Created on: 12 ago. 2021
 *      Author: Ismae
 */

#ifndef DUTY_H_
#define DUTY_H_

void TPM_PWM(TPM_Type *base,
                            tpm_chnl_t chnlNumber,
                            tpm_pwm_mode_t currentPwmMode,
                            uint8_t dutyCyclePercent);


#endif /* DUTY_H_ */
