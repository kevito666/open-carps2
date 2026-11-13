#ifndef OPEN_CARPS2_MODEL_H
#define OPEN_CARPS2_MODEL_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    OC2_MONO = 0,
    OC2_COLOR = 1
} oc2_color_mode;

typedef enum {
    OC2_TARGET_UNTESTED = 0
} oc2_support_status;

typedef struct {
    const char *name;
    unsigned priority;
    oc2_color_mode color;
    /* Zero indicates unknown ID, NOT a USB match. */
    uint16_t usb_vendor;
    uint16_t usb_product;
    oc2_support_status status;
} oc2_model;

size_t oc2_model_count(void);
const oc2_model *oc2_model_at(size_t index);
const oc2_model *oc2_find_model(const char *name);
/* Returns number of matching candidates; fills up to capacity entries. */
size_t oc2_match_usb(uint16_t vendor, uint16_t product,
                     const oc2_model **matches, size_t capacity);

#ifdef __cplusplus
}
#endif
#endif
