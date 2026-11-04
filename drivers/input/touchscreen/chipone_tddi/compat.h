#ifndef _FTS_COMPAT_H_
#define _FTS_COMPAT_H_

#include <linux/gpio/consumer.h>
#include <linux/gpio.h>
#include <linux/of.h>
#include <linux/string.h>

static inline int of_get_named_gpio_flags(struct device_node *np, const char *propname, int index, unsigned int *flags)
{
    struct gpio_desc *desc;
    char con_id[64];
    char *p;
    int gpio;

    strncpy(con_id, propname, sizeof(con_id) - 1);
    con_id[sizeof(con_id) - 1] = '\0';
    p = strstr(con_id, "-gpio");
    if (p) *p = '\0';

    desc = fwnode_gpiod_get_index(of_fwnode_handle(np), con_id, index, GPIOD_ASIS, "fts");
    if (IS_ERR(desc) && strncmp(con_id, "focaltech,", 10) == 0) {
        desc = fwnode_gpiod_get_index(of_fwnode_handle(np), con_id + 10, index, GPIOD_ASIS, "fts");
    }
    if (IS_ERR(desc))
        return PTR_ERR(desc);

    gpio = desc_to_gpio(desc);
    gpiod_put(desc);
    return gpio;
}

static inline int of_get_named_gpio(struct device_node *np, const char *propname, int index)
{
    return of_get_named_gpio_flags(np, propname, index, NULL);
}

#endif
