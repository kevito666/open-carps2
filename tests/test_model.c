#include "open_carps2/model.h"

#include <assert.h>
#include <stdio.h>

int main(void) {
    assert(oc2_model_count() == 7);
    assert(oc2_model_at(7) == NULL);
    assert(oc2_find_model(NULL) == NULL);
    assert(oc2_find_model("lbp6040") != NULL);
    assert(oc2_find_model("LBP6040")->priority == 0);
    assert(oc2_find_model("LBP7110C")->color == OC2_COLOR);
    assert(oc2_find_model("LBP123456") == NULL);
    const oc2_model *out[4] = {NULL};
    assert(oc2_match_usb(0x04a9, 0x2795, out, 4) == 2);
    assert(out[0] && out[1]);
    assert(oc2_match_usb(0x04a9, 0x2796, out, 4) == 2);
    assert(oc2_match_usb(0, 0, out, 4) == 0);
    assert(oc2_match_usb(0x04a9, 0x9999, out, 4) == 0);
    assert(oc2_match_usb(0x04a9, 0x2795, NULL, 0) == 2);
    assert(oc2_match_usb(0x04a9, 0x2795, out, 1) == 2);
    puts("PASS: model database and USB candidate lookup");
    return 0;
}
