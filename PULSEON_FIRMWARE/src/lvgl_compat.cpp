#include <lvgl.h>

extern "C" void lv_obj_set_name_static(lv_obj_t * obj, const char * name)
{
    (void)obj;
    (void)name;
}

extern "C" void lv_obj_set_name(lv_obj_t * obj, const char * name)
{
    (void)obj;
    (void)name;
}

extern "C" lv_obj_t * lv_obj_find_by_name(
    lv_obj_t * parent,
    const char * name)
{
    (void)parent;
    (void)name;

    return nullptr;
}

extern "C" void lv_label_set_translation_tag(
    lv_obj_t * label,
    const char * translation_tag)
{
    (void)label;
    (void)translation_tag;
}

extern "C" void lv_translation_add_static(
    const char * const * languages,
    const char * const * tags,
    const char * const * texts)
{
    (void)languages;
    (void)tags;
    (void)texts;
}

extern "C" void lv_translation_set_language(const char * language)
{
    (void)language;
}
