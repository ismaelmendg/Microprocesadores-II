#include "fsl_tpm.h"
void TPM_PWM(TPM_Type *base,
                            tpm_chnl_t chnlNumber,
                            tpm_pwm_mode_t currentPwmMode,
                            uint8_t dutyCyclePercent)
{
    assert(chnlNumber < FSL_FEATURE_TPM_CHANNEL_COUNTn(base));
#if defined(FSL_FEATURE_TPM_HAS_COMBINE) && FSL_FEATURE_TPM_HAS_COMBINE
    if(currentPwmMode == kTPM_CombinedPwm)
    {
        assert(FSL_FEATURE_TPM_COMBINE_HAS_EFFECTn(base));
    }
#endif

    uint16_t cnv, mod;

    mod = base->MOD;
#if defined(FSL_FEATURE_TPM_HAS_COMBINE) && FSL_FEATURE_TPM_HAS_COMBINE
    if (currentPwmMode == kTPM_CombinedPwm)
    {
        uint16_t cnvFirstEdge;

        /* This check is added for combined mode as the channel number should be the pair number */
        if (chnlNumber >= (FSL_FEATURE_TPM_CHANNEL_COUNTn(base) / 2))
        {
            return;
        }
        cnv = (mod * dutyCyclePercent) / 100;
        cnvFirstEdge = base->CONTROLS[chnlNumber * 2].CnV;
        /* For 100% duty cycle */
        if (cnv >= mod)
        {
            cnv = mod + 1;
        }
        base->CONTROLS[(chnlNumber * 2) + 1].CnV = cnvFirstEdge + cnv;
    }
    else
    {
#endif
        cnv = (mod * dutyCyclePercent) / 100;
        /* For 100% duty cycle */
        if (cnv >= mod)
        {
            cnv = mod + 1;
        }
        base->CONTROLS[chnlNumber].CnV = cnv;
#if defined(FSL_FEATURE_TPM_HAS_COMBINE) && FSL_FEATURE_TPM_HAS_COMBINE
    }
#endif
}
