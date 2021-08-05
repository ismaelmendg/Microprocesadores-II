/*
 * dutycycle.h
 *
 *  Created on: 17 jul. 2021
 *      Author: Ismae
 */

#ifndef DUTYCYCLE_H_
#define DUTYCYCLE_H_
void TPM_PWM(TPM_Type *base,
                            tpm_chnl_t chnlNumber,
                            tpm_pwm_mode_t currentPwmMode,
                            uint8_t dutyCyclePercent);


#endif /* DUTYCYCLE_H_ */
