#pragma once

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

void lv_obj_set_name_static(lv_obj_t * obj, const char * name);

void lv_obj_set_name(lv_obj_t * obj, const char * name);
void lv_label_set_translation_tag(lv_obj_t * label, const char * translation_tag);

lv_obj_t * lv_obj_find_by_name(
    lv_obj_t * parent,
    const char * name
);

void lv_translation_add_static(
    const char * const * languages,
    const char * const * tags,
    const char * const * texts
);

void lv_translation_set_language(const char * language);

#ifdef __cplusplus
}
#endif
