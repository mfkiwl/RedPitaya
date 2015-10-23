/**
 * $Id: $
 *
 * @brief Red Pitaya library Generate module interface
 *
 * @Author Red Pitaya
 *
 * (c) Red Pitaya  http://www.redpitaya.com
 *
 * This part of code is written in C programming language.
 * Please visit http://en.wikipedia.org/wiki/C_(programming_language)
 * for more details on the language used herein.
 */
#ifndef __GENERATE_H
#define __GENERATE_H

#include "redpitaya/rp.h"

#define LEVEL_MAX               1.0         // V
#define AMPLITUDE_MAX           1.0         // V
#define ARBITRARY_MIN          -1.0         // V
#define ARBITRARY_MAX           1.0         // V
#define OFFSET_MAX              2.0         // V
#define FREQUENCY_MIN           0           // Hz
#define FREQUENCY_MAX           62.5e6      // Hz
#define PHASE_MIN              -360         // deg
#define PHASE_MAX               360         // deg
#define DUTY_CYCLE_MIN          0           // %
#define DUTY_CYCLE_MAX          100         // %
#define BURST_COUNT_MIN        -1
#define BURST_COUNT_MAX         50000
#define BURST_REPETITIONS_MIN   1
#define BURST_REPETITIONS_MAX   50000
#define BURST_PERIOD_MIN        1           // us
#define BURST_PERIOD_MAX        500000000   // us
#define DAC_FREQUENCY           125e6       // Hz

#define BUFFER_LENGTH           (16 * 1024)
#define CHA_DATA_OFFSET         0x10000
#define CHB_DATA_OFFSET         0x20000
#define DATA_BIT_LENGTH         14
#define MICRO                   1e6

// Base Generate address
#define GENERATE_BASE_ADDR      0x40200000
#define GENERATE_BASE_SIZE      0x00030000

typedef struct ch_properties {
    uint32_t amplitudeScale     :14;
    uint32_t                    :2;
    uint32_t amplitudeOffset    :14;
    uint32_t                    :2;
    uint32_t counterWrap;
    uint32_t startOffset;
    uint32_t counterStep;
    uint32_t                    :2;
    uint32_t buffReadPointer    :14;
    uint32_t                    :16;
    uint32_t cyclesInOneBurst;
    uint32_t burstRepetitions;
    uint32_t delayBetweenBurstRepetitions;
} ch_properties_t;

typedef struct generate_control_s {
    uint32_t AtriggerSelector   :4;
    uint32_t ASM_WrapPointer    :1;
    uint32_t                    :1;
    uint32_t ASM_reset          :1;
    uint32_t AsetOutputTo0      :1;
    uint32_t AgatedBursts       :1;
    uint32_t                    :7;

    uint32_t BtriggerSelector   :4;
    uint32_t BSM_WrapPointer    :1;
    uint32_t                    :1;
    uint32_t BSM_reset          :1;
    uint32_t BsetOutputTo0      :1;
    uint32_t BgatedBursts       :1;
    uint32_t                    :7;

    ch_properties_t properties_ch[2];
} generate_control_t;

int generate_Init();
int generate_Release();

int generate_setAmplitude(rp_channel_t channel, float amplitude);
int generate_getAmplitude(rp_channel_t channel, float *amplitude);
int generate_setDCOffset(rp_channel_t channel, float offset);
int generate_getDCOffset(rp_channel_t channel, float *offset);
int generate_setFrequency(rp_channel_t channel, float frequency);
int generate_getFrequency(rp_channel_t channel, float *frequency);
int generate_setWrapCounter(rp_channel_t channel, uint32_t size);
int generate_setTriggerSource(rp_channel_t channel, unsigned short value);
int generate_getTriggerSource(rp_channel_t channel, uint32_t *value);
int generate_setGatedBurst(rp_channel_t channel, uint32_t value);
int generate_getGatedBurst(rp_channel_t channel, uint32_t *value);
int generate_setBurstCount(rp_channel_t channel, uint32_t num);
int generate_getBurstCount(rp_channel_t channel, uint32_t *num);
int generate_setBurstRepetitions(rp_channel_t channel, uint32_t repetitions);
int generate_getBurstRepetitions(rp_channel_t channel, uint32_t *repetitions);
int generate_setBurstDelay(rp_channel_t channel, uint32_t delay);
int generate_getBurstDelay(rp_channel_t channel, uint32_t *delay);

int generate_simultaneousTrigger();
int generate_Synchronise();

int generate_writeData(rp_channel_t channel, float *data, uint32_t start, uint32_t length);

#endif //__GENERATE_H
