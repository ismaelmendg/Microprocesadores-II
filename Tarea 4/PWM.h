#include "fsl_tpm.h"
#ifndef PWM_H_
#define PWM_H_

void TPM_PWM(TPM_Type *base,
                            tpm_chnl_t chnlNumber,
                            tpm_pwm_mode_t currentPwmMode,
                            uint8_t dutyCyclePercent);

#endif /* PWM_H_ */
