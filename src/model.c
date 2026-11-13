#include "open_carps2/model.h"

#include <ctype.h>

/* Entries denote research targets only, not a functioning driver. */
static const oc2_model models[] = {
    {"LBP6040", 0, OC2_MONO,  0x04a9, 0x2795, OC2_TARGET_UNTESTED},
    {"LBP6030", 1, OC2_MONO,  0x04a9, 0x2795, OC2_TARGET_UNTESTED},
    {"LBP6230", 2, OC2_MONO,  0x04a9, 0x2796, OC2_TARGET_UNTESTED},
    {"LBP6240", 2, OC2_MONO,  0x04a9, 0x2796, OC2_TARGET_UNTESTED},
    {"LBP8100", 3, OC2_MONO,  0x0000, 0x0000, OC2_TARGET_UNTESTED},
    {"LBP7100C",4, OC2_COLOR, 0x0000, 0x0000, OC2_TARGET_UNTESTED},
    {"LBP7110C",4, OC2_COLOR, 0x0000, 0x0000, OC2_TARGET_UNTESTED},
};

size_t oc2_model_count(void) {
    return sizeof(models) / sizeof(models[0]);
}

const oc2_model *oc2_model_at(size_t index) {
    if (index >= oc2_model_count()) return NULL;
    return &models[index];
}

static int ascii_case_equal(const char *a, const char *b) {
    if (!a || !b) return 0;
    for (; *a && *b; ++a, ++b) {
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b)) return 0;
    }
    return *a == '\0' && *b == '\0';
}

const oc2_model *oc2_find_model(const char *name) {
    for (size_t i = 0; i < oc2_model_count(); ++i) {
        if (ascii_case_equal(name, models[i].name)) return &models[i];
    }
    return NULL;
}

size_t oc2_match_usb(uint16_t vendor, uint16_t product,
                     const oc2_model **matches, size_t capacity) {
    if (vendor == 0 || product == 0) return 0;
    size_t found = 0;
    for (size_t i = 0; i < oc2_model_count(); ++i) {
        if (models[i].usb_vendor != vendor || models[i].usb_product != product) continue;
        if (matches && found < capacity) matches[found] = &models[i];
        ++found;
    }
    return found;
}
