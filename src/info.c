#include "open_carps2/model.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void usage(FILE *output, const char *program) {
    fprintf(output, "Usage: %s --list | --model NAME | --match-usb VID:PID | --version\n", program);
    fputs("Research tool only. No CARPS2 encoder or printer transport is implemented.\n", output);
}

static void print_model(const oc2_model *model) {
    printf("%-9s P%u %-6s TARGET/UNTESTED", model->name, model->priority,
           model->color == OC2_COLOR ? "color" : "mono");
    if (model->usb_vendor && model->usb_product)
        printf(" USB=%04x:%04x (candidate)", model->usb_vendor, model->usb_product);
    else fputs(" USB=unknown", stdout);
    putchar('\n');
}

static int parse_usb(const char *value, unsigned *vendor, unsigned *product) {
    if (!value || strlen(value) != 9 || value[4] != ':') return 0;
    char left[5] = {0}, right[5] = {0};
    memcpy(left, value, 4);
    memcpy(right, value + 5, 4);
    for (size_t i = 0; i < 4; ++i) {
        if (!((left[i] >= '0' && left[i] <= '9') ||
              (left[i] >= 'a' && left[i] <= 'f') ||
              (left[i] >= 'A' && left[i] <= 'F'))) return 0;
        if (!((right[i] >= '0' && right[i] <= '9') ||
              (right[i] >= 'a' && right[i] <= 'f') ||
              (right[i] >= 'A' && right[i] <= 'F'))) return 0;
    }
    errno = 0;
    char *end = NULL;
    unsigned long a = strtoul(left, &end, 16);
    if (errno || *end != '\0' || a > 65535UL) return 0;
    errno = 0;
    unsigned long b = strtoul(right, &end, 16);
    if (errno || *end != '\0' || b > 65535UL) return 0;
    *vendor = (unsigned)a;
    *product = (unsigned)b;
    return 1;
}

int main(int argc, char **argv) {
    if (argc == 2 && strcmp(argv[1], "--version") == 0) {
        puts("open-carps2 0.0.1-dev (non-printing research tools)");
        return 0;
    }
    if (argc == 2 && strcmp(argv[1], "--list") == 0) {
        for (size_t i = 0; i < oc2_model_count(); ++i) print_model(oc2_model_at(i));
        return 0;
    }
    if (argc == 3 && strcmp(argv[1], "--model") == 0) {
        const oc2_model *model = oc2_find_model(argv[2]);
        if (!model) { fprintf(stderr, "Unknown target model: %s\n", argv[2]); return 2; }
        print_model(model);
        return 0;
    }
    if (argc == 3 && strcmp(argv[1], "--match-usb") == 0) {
        unsigned vendor = 0, product = 0;
        if (!parse_usb(argv[2], &vendor, &product)) {
            fputs("Expected VID:PID as four hexadecimal digits each, e.g. 04a9:2795\n", stderr);
            return 2;
        }
        const oc2_model *matches[16];
        size_t found = oc2_match_usb((uint16_t)vendor, (uint16_t)product, matches, 16);
        if (!found) {
            puts("No known model candidates. Unknown does not imply incompatible.");
            return 1;
        }
        puts("USB candidates (NOT verified print support):");
        for (size_t i = 0; i < found && i < 16; ++i) print_model(matches[i]);
        return 0;
    }
    usage(argc == 2 && strcmp(argv[1], "--help") == 0 ? stdout : stderr, argv[0]);
    return argc == 2 && strcmp(argv[1], "--help") == 0 ? 0 : 2;
}
