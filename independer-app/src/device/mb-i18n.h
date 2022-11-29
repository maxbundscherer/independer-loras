#define PROP_GERMAN 1
#define PROP_ENGLISH 2

const String TEMPLATE_WEBSITE_URL = "a-sdr.org/independer";

#if i18n == PROP_GERMAN
#include "device/i18n/german.h"
#elif i18n == PROP_ENGLISH
#include "device/i18n/english.h"
#else
#include "device/i18n/english.h"
#endif