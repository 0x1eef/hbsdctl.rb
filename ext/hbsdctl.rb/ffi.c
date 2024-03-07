#include <libhbsdcontrol.h>
#include <ruby.h>
#include "include/ffi.h"

/**
 * BSD::Control::FFI.available_features
 **/
VALUE
ffi_available_features(VALUE self)
{
  const struct pax_feature_entry *entry = &pax_features[0];
  VALUE rb_mBSD = rb_const_get(rb_cObject, rb_intern("BSD")),
    rb_mControl = rb_const_get(rb_mBSD, rb_intern("Control")),
    rb_cFeature = rb_const_get(rb_mControl, rb_intern("Feature")),
    features = rb_ary_new(),
    feature = 0;

  while (entry->feature != NULL)
  {
    feature = rb_funcall(
      rb_cFeature,
      rb_intern("new"),
      3,
      rb_str_new2(entry->feature),
      rb_str_new2(entry->extattr[1]),
      rb_str_new2(entry->extattr[0])
      );
    rb_ary_push(features, feature);
    entry++;
  }
  return (features);
}


/**
 * BSD::Control::FFI.reset!
 **/
VALUE
ffi_reset(VALUE self, VALUE rb_feature, VALUE rb_path)
{
  VALUE rb_enable_flag, rb_disable_flag;
  char *enable_flag, *disable_flag, *path;
  int r;

  rb_enable_flag = rb_funcall(rb_feature, rb_intern("enable"), 0);
  rb_disable_flag = rb_funcall(rb_feature, rb_intern("disable"), 0);
  Check_Type(rb_path, T_STRING);
  Check_Type(rb_enable_flag, T_STRING);
  Check_Type(rb_disable_flag, T_STRING);
  path = RSTRING_PTR(rb_path);
  enable_flag = RSTRING_PTR(rb_enable_flag);
  disable_flag = RSTRING_PTR(rb_disable_flag);
  r = hbsdcontrol_extattr_rm_attr(path, disable_flag);
  r &= hbsdcontrol_extattr_rm_attr(path, enable_flag);
  return (r == 0 ? Qtrue : Qfalse);
}


/**
 * BSD::Control::FFI.library_version
 **/
VALUE
ffi_library_version(VALUE self)
{
  const char *ver;
  ver = hbsdcontrol_get_version();
  return (rb_str_new2(ver));
}
