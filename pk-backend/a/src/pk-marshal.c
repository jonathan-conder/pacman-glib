#include "pk-marshal.h"

#include	<glib-object.h>


#ifdef G_ENABLE_DEBUG
#define g_marshal_value_peek_boolean(v)  g_value_get_boolean (v)
#define g_marshal_value_peek_char(v)     g_value_get_char (v)
#define g_marshal_value_peek_uchar(v)    g_value_get_uchar (v)
#define g_marshal_value_peek_int(v)      g_value_get_int (v)
#define g_marshal_value_peek_uint(v)     g_value_get_uint (v)
#define g_marshal_value_peek_long(v)     g_value_get_long (v)
#define g_marshal_value_peek_ulong(v)    g_value_get_ulong (v)
#define g_marshal_value_peek_int64(v)    g_value_get_int64 (v)
#define g_marshal_value_peek_uint64(v)   g_value_get_uint64 (v)
#define g_marshal_value_peek_enum(v)     g_value_get_enum (v)
#define g_marshal_value_peek_flags(v)    g_value_get_flags (v)
#define g_marshal_value_peek_float(v)    g_value_get_float (v)
#define g_marshal_value_peek_double(v)   g_value_get_double (v)
#define g_marshal_value_peek_string(v)   (char*) g_value_get_string (v)
#define g_marshal_value_peek_param(v)    g_value_get_param (v)
#define g_marshal_value_peek_boxed(v)    g_value_get_boxed (v)
#define g_marshal_value_peek_pointer(v)  g_value_get_pointer (v)
#define g_marshal_value_peek_object(v)   g_value_get_object (v)
#else /* !G_ENABLE_DEBUG */
/* WARNING: This code accesses GValues directly, which is UNSUPPORTED API.
 *          Do not access GValues directly in your code. Instead, use the
 *          g_value_get_*() functions
 */
#define g_marshal_value_peek_boolean(v)  (v)->data[0].v_int
#define g_marshal_value_peek_char(v)     (v)->data[0].v_int
#define g_marshal_value_peek_uchar(v)    (v)->data[0].v_uint
#define g_marshal_value_peek_int(v)      (v)->data[0].v_int
#define g_marshal_value_peek_uint(v)     (v)->data[0].v_uint
#define g_marshal_value_peek_long(v)     (v)->data[0].v_long
#define g_marshal_value_peek_ulong(v)    (v)->data[0].v_ulong
#define g_marshal_value_peek_int64(v)    (v)->data[0].v_int64
#define g_marshal_value_peek_uint64(v)   (v)->data[0].v_uint64
#define g_marshal_value_peek_enum(v)     (v)->data[0].v_long
#define g_marshal_value_peek_flags(v)    (v)->data[0].v_ulong
#define g_marshal_value_peek_float(v)    (v)->data[0].v_float
#define g_marshal_value_peek_double(v)   (v)->data[0].v_double
#define g_marshal_value_peek_string(v)   (v)->data[0].v_pointer
#define g_marshal_value_peek_param(v)    (v)->data[0].v_pointer
#define g_marshal_value_peek_boxed(v)    (v)->data[0].v_pointer
#define g_marshal_value_peek_pointer(v)  (v)->data[0].v_pointer
#define g_marshal_value_peek_object(v)   (v)->data[0].v_pointer
#endif /* !G_ENABLE_DEBUG */


/* VOID:UINT,STRING,STRING (pk-marshal.list:1) */
void
pk_marshal_VOID__UINT_STRING_STRING (GClosure     *closure,
                                     GValue       *return_value G_GNUC_UNUSED,
                                     guint         n_param_values,
                                     const GValue *param_values,
                                     gpointer      invocation_hint G_GNUC_UNUSED,
                                     gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__UINT_STRING_STRING) (gpointer     data1,
                                                         guint        arg_1,
                                                         gpointer     arg_2,
                                                         gpointer     arg_3,
                                                         gpointer     data2);
  register GMarshalFunc_VOID__UINT_STRING_STRING callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 4);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__UINT_STRING_STRING) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_uint (param_values + 1),
            g_marshal_value_peek_string (param_values + 2),
            g_marshal_value_peek_string (param_values + 3),
            data2);
}

/* VOID:UINT,STRING (pk-marshal.list:2) */
void
pk_marshal_VOID__UINT_STRING (GClosure     *closure,
                              GValue       *return_value G_GNUC_UNUSED,
                              guint         n_param_values,
                              const GValue *param_values,
                              gpointer      invocation_hint G_GNUC_UNUSED,
                              gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__UINT_STRING) (gpointer     data1,
                                                  guint        arg_1,
                                                  gpointer     arg_2,
                                                  gpointer     data2);
  register GMarshalFunc_VOID__UINT_STRING callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 3);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__UINT_STRING) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_uint (param_values + 1),
            g_marshal_value_peek_string (param_values + 2),
            data2);
}

/* VOID:UINT,STRING,UINT (pk-marshal.list:3) */
void
pk_marshal_VOID__UINT_STRING_UINT (GClosure     *closure,
                                   GValue       *return_value G_GNUC_UNUSED,
                                   guint         n_param_values,
                                   const GValue *param_values,
                                   gpointer      invocation_hint G_GNUC_UNUSED,
                                   gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__UINT_STRING_UINT) (gpointer     data1,
                                                       guint        arg_1,
                                                       gpointer     arg_2,
                                                       guint        arg_3,
                                                       gpointer     data2);
  register GMarshalFunc_VOID__UINT_STRING_UINT callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 4);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__UINT_STRING_UINT) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_uint (param_values + 1),
            g_marshal_value_peek_string (param_values + 2),
            g_marshal_value_peek_uint (param_values + 3),
            data2);
}

/* VOID:UINT,UINT (pk-marshal.list:4) */
void
pk_marshal_VOID__UINT_UINT (GClosure     *closure,
                            GValue       *return_value G_GNUC_UNUSED,
                            guint         n_param_values,
                            const GValue *param_values,
                            gpointer      invocation_hint G_GNUC_UNUSED,
                            gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__UINT_UINT) (gpointer     data1,
                                                guint        arg_1,
                                                guint        arg_2,
                                                gpointer     data2);
  register GMarshalFunc_VOID__UINT_UINT callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 3);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__UINT_UINT) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_uint (param_values + 1),
            g_marshal_value_peek_uint (param_values + 2),
            data2);
}

/* VOID:UINT,UINT,UINT,UINT (pk-marshal.list:5) */
void
pk_marshal_VOID__UINT_UINT_UINT_UINT (GClosure     *closure,
                                      GValue       *return_value G_GNUC_UNUSED,
                                      guint         n_param_values,
                                      const GValue *param_values,
                                      gpointer      invocation_hint G_GNUC_UNUSED,
                                      gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__UINT_UINT_UINT_UINT) (gpointer     data1,
                                                          guint        arg_1,
                                                          guint        arg_2,
                                                          guint        arg_3,
                                                          guint        arg_4,
                                                          gpointer     data2);
  register GMarshalFunc_VOID__UINT_UINT_UINT_UINT callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 5);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__UINT_UINT_UINT_UINT) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_uint (param_values + 1),
            g_marshal_value_peek_uint (param_values + 2),
            g_marshal_value_peek_uint (param_values + 3),
            g_marshal_value_peek_uint (param_values + 4),
            data2);
}

/* VOID:STRING,UINT,UINT,UINT,UINT (pk-marshal.list:6) */
void
pk_marshal_VOID__STRING_UINT_UINT_UINT_UINT (GClosure     *closure,
                                             GValue       *return_value G_GNUC_UNUSED,
                                             guint         n_param_values,
                                             const GValue *param_values,
                                             gpointer      invocation_hint G_GNUC_UNUSED,
                                             gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__STRING_UINT_UINT_UINT_UINT) (gpointer     data1,
                                                                 gpointer     arg_1,
                                                                 guint        arg_2,
                                                                 guint        arg_3,
                                                                 guint        arg_4,
                                                                 guint        arg_5,
                                                                 gpointer     data2);
  register GMarshalFunc_VOID__STRING_UINT_UINT_UINT_UINT callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 6);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__STRING_UINT_UINT_UINT_UINT) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_string (param_values + 1),
            g_marshal_value_peek_uint (param_values + 2),
            g_marshal_value_peek_uint (param_values + 3),
            g_marshal_value_peek_uint (param_values + 4),
            g_marshal_value_peek_uint (param_values + 5),
            data2);
}

/* VOID:STRING (pk-marshal.list:7) */

/* VOID:STRING,BOOL (pk-marshal.list:8) */
void
pk_marshal_VOID__STRING_BOOLEAN (GClosure     *closure,
                                 GValue       *return_value G_GNUC_UNUSED,
                                 guint         n_param_values,
                                 const GValue *param_values,
                                 gpointer      invocation_hint G_GNUC_UNUSED,
                                 gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__STRING_BOOLEAN) (gpointer     data1,
                                                     gpointer     arg_1,
                                                     gboolean     arg_2,
                                                     gpointer     data2);
  register GMarshalFunc_VOID__STRING_BOOLEAN callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 3);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__STRING_BOOLEAN) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_string (param_values + 1),
            g_marshal_value_peek_boolean (param_values + 2),
            data2);
}

/* VOID:STRING,UINT (pk-marshal.list:9) */
void
pk_marshal_VOID__STRING_UINT (GClosure     *closure,
                              GValue       *return_value G_GNUC_UNUSED,
                              guint         n_param_values,
                              const GValue *param_values,
                              gpointer      invocation_hint G_GNUC_UNUSED,
                              gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__STRING_UINT) (gpointer     data1,
                                                  gpointer     arg_1,
                                                  guint        arg_2,
                                                  gpointer     data2);
  register GMarshalFunc_VOID__STRING_UINT callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 3);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__STRING_UINT) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_string (param_values + 1),
            g_marshal_value_peek_uint (param_values + 2),
            data2);
}

/* VOID:STRING,STRING,UINT (pk-marshal.list:10) */
void
pk_marshal_VOID__STRING_STRING_UINT (GClosure     *closure,
                                     GValue       *return_value G_GNUC_UNUSED,
                                     guint         n_param_values,
                                     const GValue *param_values,
                                     gpointer      invocation_hint G_GNUC_UNUSED,
                                     gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__STRING_STRING_UINT) (gpointer     data1,
                                                         gpointer     arg_1,
                                                         gpointer     arg_2,
                                                         guint        arg_3,
                                                         gpointer     data2);
  register GMarshalFunc_VOID__STRING_STRING_UINT callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 4);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__STRING_STRING_UINT) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_string (param_values + 1),
            g_marshal_value_peek_string (param_values + 2),
            g_marshal_value_peek_uint (param_values + 3),
            data2);
}

/* VOID:STRING,UINT,STRING,STRING (pk-marshal.list:11) */
void
pk_marshal_VOID__STRING_UINT_STRING_STRING (GClosure     *closure,
                                            GValue       *return_value G_GNUC_UNUSED,
                                            guint         n_param_values,
                                            const GValue *param_values,
                                            gpointer      invocation_hint G_GNUC_UNUSED,
                                            gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__STRING_UINT_STRING_STRING) (gpointer     data1,
                                                                gpointer     arg_1,
                                                                guint        arg_2,
                                                                gpointer     arg_3,
                                                                gpointer     arg_4,
                                                                gpointer     data2);
  register GMarshalFunc_VOID__STRING_UINT_STRING_STRING callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 5);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__STRING_UINT_STRING_STRING) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_string (param_values + 1),
            g_marshal_value_peek_uint (param_values + 2),
            g_marshal_value_peek_string (param_values + 3),
            g_marshal_value_peek_string (param_values + 4),
            data2);
}

/* VOID:STRING,STRING (pk-marshal.list:12) */
void
pk_marshal_VOID__STRING_STRING (GClosure     *closure,
                                GValue       *return_value G_GNUC_UNUSED,
                                guint         n_param_values,
                                const GValue *param_values,
                                gpointer      invocation_hint G_GNUC_UNUSED,
                                gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__STRING_STRING) (gpointer     data1,
                                                    gpointer     arg_1,
                                                    gpointer     arg_2,
                                                    gpointer     data2);
  register GMarshalFunc_VOID__STRING_STRING callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 3);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__STRING_STRING) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_string (param_values + 1),
            g_marshal_value_peek_string (param_values + 2),
            data2);
}

/* VOID:STRING,STRING,STRING (pk-marshal.list:13) */
void
pk_marshal_VOID__STRING_STRING_STRING (GClosure     *closure,
                                       GValue       *return_value G_GNUC_UNUSED,
                                       guint         n_param_values,
                                       const GValue *param_values,
                                       gpointer      invocation_hint G_GNUC_UNUSED,
                                       gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__STRING_STRING_STRING) (gpointer     data1,
                                                           gpointer     arg_1,
                                                           gpointer     arg_2,
                                                           gpointer     arg_3,
                                                           gpointer     data2);
  register GMarshalFunc_VOID__STRING_STRING_STRING callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 4);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__STRING_STRING_STRING) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_string (param_values + 1),
            g_marshal_value_peek_string (param_values + 2),
            g_marshal_value_peek_string (param_values + 3),
            data2);
}

/* VOID:STRING,STRING,STRING,STRING (pk-marshal.list:14) */
void
pk_marshal_VOID__STRING_STRING_STRING_STRING (GClosure     *closure,
                                              GValue       *return_value G_GNUC_UNUSED,
                                              guint         n_param_values,
                                              const GValue *param_values,
                                              gpointer      invocation_hint G_GNUC_UNUSED,
                                              gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__STRING_STRING_STRING_STRING) (gpointer     data1,
                                                                  gpointer     arg_1,
                                                                  gpointer     arg_2,
                                                                  gpointer     arg_3,
                                                                  gpointer     arg_4,
                                                                  gpointer     data2);
  register GMarshalFunc_VOID__STRING_STRING_STRING_STRING callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 5);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__STRING_STRING_STRING_STRING) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_string (param_values + 1),
            g_marshal_value_peek_string (param_values + 2),
            g_marshal_value_peek_string (param_values + 3),
            g_marshal_value_peek_string (param_values + 4),
            data2);
}

/* VOID:STRING,STRING,STRING,STRING,STRING (pk-marshal.list:15) */
void
pk_marshal_VOID__STRING_STRING_STRING_STRING_STRING (GClosure     *closure,
                                                     GValue       *return_value G_GNUC_UNUSED,
                                                     guint         n_param_values,
                                                     const GValue *param_values,
                                                     gpointer      invocation_hint G_GNUC_UNUSED,
                                                     gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__STRING_STRING_STRING_STRING_STRING) (gpointer     data1,
                                                                         gpointer     arg_1,
                                                                         gpointer     arg_2,
                                                                         gpointer     arg_3,
                                                                         gpointer     arg_4,
                                                                         gpointer     arg_5,
                                                                         gpointer     data2);
  register GMarshalFunc_VOID__STRING_STRING_STRING_STRING_STRING callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 6);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__STRING_STRING_STRING_STRING_STRING) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_string (param_values + 1),
            g_marshal_value_peek_string (param_values + 2),
            g_marshal_value_peek_string (param_values + 3),
            g_marshal_value_peek_string (param_values + 4),
            g_marshal_value_peek_string (param_values + 5),
            data2);
}

/* VOID:STRING,STRING,STRING,STRING,STRING,STRING (pk-marshal.list:16) */
void
pk_marshal_VOID__STRING_STRING_STRING_STRING_STRING_STRING (GClosure     *closure,
                                                            GValue       *return_value G_GNUC_UNUSED,
                                                            guint         n_param_values,
                                                            const GValue *param_values,
                                                            gpointer      invocation_hint G_GNUC_UNUSED,
                                                            gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__STRING_STRING_STRING_STRING_STRING_STRING) (gpointer     data1,
                                                                                gpointer     arg_1,
                                                                                gpointer     arg_2,
                                                                                gpointer     arg_3,
                                                                                gpointer     arg_4,
                                                                                gpointer     arg_5,
                                                                                gpointer     arg_6,
                                                                                gpointer     data2);
  register GMarshalFunc_VOID__STRING_STRING_STRING_STRING_STRING_STRING callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 7);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__STRING_STRING_STRING_STRING_STRING_STRING) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_string (param_values + 1),
            g_marshal_value_peek_string (param_values + 2),
            g_marshal_value_peek_string (param_values + 3),
            g_marshal_value_peek_string (param_values + 4),
            g_marshal_value_peek_string (param_values + 5),
            g_marshal_value_peek_string (param_values + 6),
            data2);
}

/* VOID:STRING,STRING,STRING,STRING,STRING,STRING,STRING,STRING,STRING (pk-marshal.list:17) */
void
pk_marshal_VOID__STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING (GClosure     *closure,
                                                                                 GValue       *return_value G_GNUC_UNUSED,
                                                                                 guint         n_param_values,
                                                                                 const GValue *param_values,
                                                                                 gpointer      invocation_hint G_GNUC_UNUSED,
                                                                                 gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING) (gpointer     data1,
                                                                                                     gpointer     arg_1,
                                                                                                     gpointer     arg_2,
                                                                                                     gpointer     arg_3,
                                                                                                     gpointer     arg_4,
                                                                                                     gpointer     arg_5,
                                                                                                     gpointer     arg_6,
                                                                                                     gpointer     arg_7,
                                                                                                     gpointer     arg_8,
                                                                                                     gpointer     arg_9,
                                                                                                     gpointer     data2);
  register GMarshalFunc_VOID__STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 10);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_string (param_values + 1),
            g_marshal_value_peek_string (param_values + 2),
            g_marshal_value_peek_string (param_values + 3),
            g_marshal_value_peek_string (param_values + 4),
            g_marshal_value_peek_string (param_values + 5),
            g_marshal_value_peek_string (param_values + 6),
            g_marshal_value_peek_string (param_values + 7),
            g_marshal_value_peek_string (param_values + 8),
            g_marshal_value_peek_string (param_values + 9),
            data2);
}

/* VOID:STRING,STRING,STRING,STRING,STRING,STRING,STRING,STRING,STRING,STRING (pk-marshal.list:18) */
void
pk_marshal_VOID__STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING (GClosure     *closure,
                                                                                        GValue       *return_value G_GNUC_UNUSED,
                                                                                        guint         n_param_values,
                                                                                        const GValue *param_values,
                                                                                        gpointer      invocation_hint G_GNUC_UNUSED,
                                                                                        gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING) (gpointer     data1,
                                                                                                            gpointer     arg_1,
                                                                                                            gpointer     arg_2,
                                                                                                            gpointer     arg_3,
                                                                                                            gpointer     arg_4,
                                                                                                            gpointer     arg_5,
                                                                                                            gpointer     arg_6,
                                                                                                            gpointer     arg_7,
                                                                                                            gpointer     arg_8,
                                                                                                            gpointer     arg_9,
                                                                                                            gpointer     arg_10,
                                                                                                            gpointer     data2);
  register GMarshalFunc_VOID__STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 11);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_string (param_values + 1),
            g_marshal_value_peek_string (param_values + 2),
            g_marshal_value_peek_string (param_values + 3),
            g_marshal_value_peek_string (param_values + 4),
            g_marshal_value_peek_string (param_values + 5),
            g_marshal_value_peek_string (param_values + 6),
            g_marshal_value_peek_string (param_values + 7),
            g_marshal_value_peek_string (param_values + 8),
            g_marshal_value_peek_string (param_values + 9),
            g_marshal_value_peek_string (param_values + 10),
            data2);
}

/* VOID:STRING,STRING,STRING,STRING,STRING,STRING,STRING,STRING,STRING,STRING,STRING (pk-marshal.list:19) */
void
pk_marshal_VOID__STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING (GClosure     *closure,
                                                                                               GValue       *return_value G_GNUC_UNUSED,
                                                                                               guint         n_param_values,
                                                                                               const GValue *param_values,
                                                                                               gpointer      invocation_hint G_GNUC_UNUSED,
                                                                                               gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING) (gpointer     data1,
                                                                                                                   gpointer     arg_1,
                                                                                                                   gpointer     arg_2,
                                                                                                                   gpointer     arg_3,
                                                                                                                   gpointer     arg_4,
                                                                                                                   gpointer     arg_5,
                                                                                                                   gpointer     arg_6,
                                                                                                                   gpointer     arg_7,
                                                                                                                   gpointer     arg_8,
                                                                                                                   gpointer     arg_9,
                                                                                                                   gpointer     arg_10,
                                                                                                                   gpointer     arg_11,
                                                                                                                   gpointer     data2);
  register GMarshalFunc_VOID__STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 12);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_string (param_values + 1),
            g_marshal_value_peek_string (param_values + 2),
            g_marshal_value_peek_string (param_values + 3),
            g_marshal_value_peek_string (param_values + 4),
            g_marshal_value_peek_string (param_values + 5),
            g_marshal_value_peek_string (param_values + 6),
            g_marshal_value_peek_string (param_values + 7),
            g_marshal_value_peek_string (param_values + 8),
            g_marshal_value_peek_string (param_values + 9),
            g_marshal_value_peek_string (param_values + 10),
            g_marshal_value_peek_string (param_values + 11),
            data2);
}

/* VOID:STRING,STRING,STRING,STRING,STRING,STRING,STRING,STRING,STRING,STRING,STRING,STRING (pk-marshal.list:20) */
void
pk_marshal_VOID__STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING (GClosure     *closure,
                                                                                                      GValue       *return_value G_GNUC_UNUSED,
                                                                                                      guint         n_param_values,
                                                                                                      const GValue *param_values,
                                                                                                      gpointer      invocation_hint G_GNUC_UNUSED,
                                                                                                      gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING) (gpointer     data1,
                                                                                                                          gpointer     arg_1,
                                                                                                                          gpointer     arg_2,
                                                                                                                          gpointer     arg_3,
                                                                                                                          gpointer     arg_4,
                                                                                                                          gpointer     arg_5,
                                                                                                                          gpointer     arg_6,
                                                                                                                          gpointer     arg_7,
                                                                                                                          gpointer     arg_8,
                                                                                                                          gpointer     arg_9,
                                                                                                                          gpointer     arg_10,
                                                                                                                          gpointer     arg_11,
                                                                                                                          gpointer     arg_12,
                                                                                                                          gpointer     data2);
  register GMarshalFunc_VOID__STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 13);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_string (param_values + 1),
            g_marshal_value_peek_string (param_values + 2),
            g_marshal_value_peek_string (param_values + 3),
            g_marshal_value_peek_string (param_values + 4),
            g_marshal_value_peek_string (param_values + 5),
            g_marshal_value_peek_string (param_values + 6),
            g_marshal_value_peek_string (param_values + 7),
            g_marshal_value_peek_string (param_values + 8),
            g_marshal_value_peek_string (param_values + 9),
            g_marshal_value_peek_string (param_values + 10),
            g_marshal_value_peek_string (param_values + 11),
            g_marshal_value_peek_string (param_values + 12),
            data2);
}

/* VOID:STRING,STRING,STRING,STRING,STRING,STRING,STRING,STRING (pk-marshal.list:21) */
void
pk_marshal_VOID__STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING (GClosure     *closure,
                                                                          GValue       *return_value G_GNUC_UNUSED,
                                                                          guint         n_param_values,
                                                                          const GValue *param_values,
                                                                          gpointer      invocation_hint G_GNUC_UNUSED,
                                                                          gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING) (gpointer     data1,
                                                                                              gpointer     arg_1,
                                                                                              gpointer     arg_2,
                                                                                              gpointer     arg_3,
                                                                                              gpointer     arg_4,
                                                                                              gpointer     arg_5,
                                                                                              gpointer     arg_6,
                                                                                              gpointer     arg_7,
                                                                                              gpointer     arg_8,
                                                                                              gpointer     data2);
  register GMarshalFunc_VOID__STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 9);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_string (param_values + 1),
            g_marshal_value_peek_string (param_values + 2),
            g_marshal_value_peek_string (param_values + 3),
            g_marshal_value_peek_string (param_values + 4),
            g_marshal_value_peek_string (param_values + 5),
            g_marshal_value_peek_string (param_values + 6),
            g_marshal_value_peek_string (param_values + 7),
            g_marshal_value_peek_string (param_values + 8),
            data2);
}

/* VOID:STRING,STRING,STRING,STRING,STRING,STRING,UINT,STRING (pk-marshal.list:22) */
void
pk_marshal_VOID__STRING_STRING_STRING_STRING_STRING_STRING_UINT_STRING (GClosure     *closure,
                                                                        GValue       *return_value G_GNUC_UNUSED,
                                                                        guint         n_param_values,
                                                                        const GValue *param_values,
                                                                        gpointer      invocation_hint G_GNUC_UNUSED,
                                                                        gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__STRING_STRING_STRING_STRING_STRING_STRING_UINT_STRING) (gpointer     data1,
                                                                                            gpointer     arg_1,
                                                                                            gpointer     arg_2,
                                                                                            gpointer     arg_3,
                                                                                            gpointer     arg_4,
                                                                                            gpointer     arg_5,
                                                                                            gpointer     arg_6,
                                                                                            guint        arg_7,
                                                                                            gpointer     arg_8,
                                                                                            gpointer     data2);
  register GMarshalFunc_VOID__STRING_STRING_STRING_STRING_STRING_STRING_UINT_STRING callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 9);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__STRING_STRING_STRING_STRING_STRING_STRING_UINT_STRING) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_string (param_values + 1),
            g_marshal_value_peek_string (param_values + 2),
            g_marshal_value_peek_string (param_values + 3),
            g_marshal_value_peek_string (param_values + 4),
            g_marshal_value_peek_string (param_values + 5),
            g_marshal_value_peek_string (param_values + 6),
            g_marshal_value_peek_uint (param_values + 7),
            g_marshal_value_peek_string (param_values + 8),
            data2);
}

/* VOID:STRING,STRING,STRING,STRING,STRING,STRING,STRING (pk-marshal.list:23) */
void
pk_marshal_VOID__STRING_STRING_STRING_STRING_STRING_STRING_STRING (GClosure     *closure,
                                                                   GValue       *return_value G_GNUC_UNUSED,
                                                                   guint         n_param_values,
                                                                   const GValue *param_values,
                                                                   gpointer      invocation_hint G_GNUC_UNUSED,
                                                                   gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__STRING_STRING_STRING_STRING_STRING_STRING_STRING) (gpointer     data1,
                                                                                       gpointer     arg_1,
                                                                                       gpointer     arg_2,
                                                                                       gpointer     arg_3,
                                                                                       gpointer     arg_4,
                                                                                       gpointer     arg_5,
                                                                                       gpointer     arg_6,
                                                                                       gpointer     arg_7,
                                                                                       gpointer     data2);
  register GMarshalFunc_VOID__STRING_STRING_STRING_STRING_STRING_STRING_STRING callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 8);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__STRING_STRING_STRING_STRING_STRING_STRING_STRING) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_string (param_values + 1),
            g_marshal_value_peek_string (param_values + 2),
            g_marshal_value_peek_string (param_values + 3),
            g_marshal_value_peek_string (param_values + 4),
            g_marshal_value_peek_string (param_values + 5),
            g_marshal_value_peek_string (param_values + 6),
            g_marshal_value_peek_string (param_values + 7),
            data2);
}

/* VOID:STRING,STRING,STRING,STRING,STRING,STRING,STRING,UINT (pk-marshal.list:24) */
void
pk_marshal_VOID__STRING_STRING_STRING_STRING_STRING_STRING_STRING_UINT (GClosure     *closure,
                                                                        GValue       *return_value G_GNUC_UNUSED,
                                                                        guint         n_param_values,
                                                                        const GValue *param_values,
                                                                        gpointer      invocation_hint G_GNUC_UNUSED,
                                                                        gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__STRING_STRING_STRING_STRING_STRING_STRING_STRING_UINT) (gpointer     data1,
                                                                                            gpointer     arg_1,
                                                                                            gpointer     arg_2,
                                                                                            gpointer     arg_3,
                                                                                            gpointer     arg_4,
                                                                                            gpointer     arg_5,
                                                                                            gpointer     arg_6,
                                                                                            gpointer     arg_7,
                                                                                            guint        arg_8,
                                                                                            gpointer     data2);
  register GMarshalFunc_VOID__STRING_STRING_STRING_STRING_STRING_STRING_STRING_UINT callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 9);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__STRING_STRING_STRING_STRING_STRING_STRING_STRING_UINT) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_string (param_values + 1),
            g_marshal_value_peek_string (param_values + 2),
            g_marshal_value_peek_string (param_values + 3),
            g_marshal_value_peek_string (param_values + 4),
            g_marshal_value_peek_string (param_values + 5),
            g_marshal_value_peek_string (param_values + 6),
            g_marshal_value_peek_string (param_values + 7),
            g_marshal_value_peek_uint (param_values + 8),
            data2);
}

/* VOID:STRING,STRING,UINT,STRING,STRING,UINT64 (pk-marshal.list:25) */
void
pk_marshal_VOID__STRING_STRING_UINT_STRING_STRING_UINT64 (GClosure     *closure,
                                                          GValue       *return_value G_GNUC_UNUSED,
                                                          guint         n_param_values,
                                                          const GValue *param_values,
                                                          gpointer      invocation_hint G_GNUC_UNUSED,
                                                          gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__STRING_STRING_UINT_STRING_STRING_UINT64) (gpointer     data1,
                                                                              gpointer     arg_1,
                                                                              gpointer     arg_2,
                                                                              guint        arg_3,
                                                                              gpointer     arg_4,
                                                                              gpointer     arg_5,
                                                                              guint64      arg_6,
                                                                              gpointer     data2);
  register GMarshalFunc_VOID__STRING_STRING_UINT_STRING_STRING_UINT64 callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 7);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__STRING_STRING_UINT_STRING_STRING_UINT64) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_string (param_values + 1),
            g_marshal_value_peek_string (param_values + 2),
            g_marshal_value_peek_uint (param_values + 3),
            g_marshal_value_peek_string (param_values + 4),
            g_marshal_value_peek_string (param_values + 5),
            g_marshal_value_peek_uint64 (param_values + 6),
            data2);
}

/* VOID:STRING,STRING,STRING,STRING,STRING,STRING,UINT64 (pk-marshal.list:26) */
void
pk_marshal_VOID__STRING_STRING_STRING_STRING_STRING_STRING_UINT64 (GClosure     *closure,
                                                                   GValue       *return_value G_GNUC_UNUSED,
                                                                   guint         n_param_values,
                                                                   const GValue *param_values,
                                                                   gpointer      invocation_hint G_GNUC_UNUSED,
                                                                   gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__STRING_STRING_STRING_STRING_STRING_STRING_UINT64) (gpointer     data1,
                                                                                       gpointer     arg_1,
                                                                                       gpointer     arg_2,
                                                                                       gpointer     arg_3,
                                                                                       gpointer     arg_4,
                                                                                       gpointer     arg_5,
                                                                                       gpointer     arg_6,
                                                                                       guint64      arg_7,
                                                                                       gpointer     data2);
  register GMarshalFunc_VOID__STRING_STRING_STRING_STRING_STRING_STRING_UINT64 callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 8);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__STRING_STRING_STRING_STRING_STRING_STRING_UINT64) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_string (param_values + 1),
            g_marshal_value_peek_string (param_values + 2),
            g_marshal_value_peek_string (param_values + 3),
            g_marshal_value_peek_string (param_values + 4),
            g_marshal_value_peek_string (param_values + 5),
            g_marshal_value_peek_string (param_values + 6),
            g_marshal_value_peek_uint64 (param_values + 7),
            data2);
}

/* VOID:STRING,STRING,STRING,STRING,STRING,UINT64 (pk-marshal.list:27) */
void
pk_marshal_VOID__STRING_STRING_STRING_STRING_STRING_UINT64 (GClosure     *closure,
                                                            GValue       *return_value G_GNUC_UNUSED,
                                                            guint         n_param_values,
                                                            const GValue *param_values,
                                                            gpointer      invocation_hint G_GNUC_UNUSED,
                                                            gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__STRING_STRING_STRING_STRING_STRING_UINT64) (gpointer     data1,
                                                                                gpointer     arg_1,
                                                                                gpointer     arg_2,
                                                                                gpointer     arg_3,
                                                                                gpointer     arg_4,
                                                                                gpointer     arg_5,
                                                                                guint64      arg_6,
                                                                                gpointer     data2);
  register GMarshalFunc_VOID__STRING_STRING_STRING_STRING_STRING_UINT64 callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 7);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__STRING_STRING_STRING_STRING_STRING_UINT64) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_string (param_values + 1),
            g_marshal_value_peek_string (param_values + 2),
            g_marshal_value_peek_string (param_values + 3),
            g_marshal_value_peek_string (param_values + 4),
            g_marshal_value_peek_string (param_values + 5),
            g_marshal_value_peek_uint64 (param_values + 6),
            data2);
}

/* VOID:STRING,STRING,STRING,STRING,STRING,STRING,UINT (pk-marshal.list:28) */
void
pk_marshal_VOID__STRING_STRING_STRING_STRING_STRING_STRING_UINT (GClosure     *closure,
                                                                 GValue       *return_value G_GNUC_UNUSED,
                                                                 guint         n_param_values,
                                                                 const GValue *param_values,
                                                                 gpointer      invocation_hint G_GNUC_UNUSED,
                                                                 gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__STRING_STRING_STRING_STRING_STRING_STRING_UINT) (gpointer     data1,
                                                                                     gpointer     arg_1,
                                                                                     gpointer     arg_2,
                                                                                     gpointer     arg_3,
                                                                                     gpointer     arg_4,
                                                                                     gpointer     arg_5,
                                                                                     gpointer     arg_6,
                                                                                     guint        arg_7,
                                                                                     gpointer     data2);
  register GMarshalFunc_VOID__STRING_STRING_STRING_STRING_STRING_STRING_UINT callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 8);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__STRING_STRING_STRING_STRING_STRING_STRING_UINT) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_string (param_values + 1),
            g_marshal_value_peek_string (param_values + 2),
            g_marshal_value_peek_string (param_values + 3),
            g_marshal_value_peek_string (param_values + 4),
            g_marshal_value_peek_string (param_values + 5),
            g_marshal_value_peek_string (param_values + 6),
            g_marshal_value_peek_uint (param_values + 7),
            data2);
}

/* VOID:STRING,STRING,BOOL (pk-marshal.list:29) */
void
pk_marshal_VOID__STRING_STRING_BOOLEAN (GClosure     *closure,
                                        GValue       *return_value G_GNUC_UNUSED,
                                        guint         n_param_values,
                                        const GValue *param_values,
                                        gpointer      invocation_hint G_GNUC_UNUSED,
                                        gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__STRING_STRING_BOOLEAN) (gpointer     data1,
                                                            gpointer     arg_1,
                                                            gpointer     arg_2,
                                                            gboolean     arg_3,
                                                            gpointer     data2);
  register GMarshalFunc_VOID__STRING_STRING_BOOLEAN callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 4);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__STRING_STRING_BOOLEAN) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_string (param_values + 1),
            g_marshal_value_peek_string (param_values + 2),
            g_marshal_value_peek_boolean (param_values + 3),
            data2);
}

/* VOID:STRING,STRING,STRING,BOOL (pk-marshal.list:30) */
void
pk_marshal_VOID__STRING_STRING_STRING_BOOLEAN (GClosure     *closure,
                                               GValue       *return_value G_GNUC_UNUSED,
                                               guint         n_param_values,
                                               const GValue *param_values,
                                               gpointer      invocation_hint G_GNUC_UNUSED,
                                               gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__STRING_STRING_STRING_BOOLEAN) (gpointer     data1,
                                                                   gpointer     arg_1,
                                                                   gpointer     arg_2,
                                                                   gpointer     arg_3,
                                                                   gboolean     arg_4,
                                                                   gpointer     data2);
  register GMarshalFunc_VOID__STRING_STRING_STRING_BOOLEAN callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 5);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__STRING_STRING_STRING_BOOLEAN) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_string (param_values + 1),
            g_marshal_value_peek_string (param_values + 2),
            g_marshal_value_peek_string (param_values + 3),
            g_marshal_value_peek_boolean (param_values + 4),
            data2);
}

/* VOID:STRING,UINT,STRING,STRING (pk-marshal.list:31) */

/* VOID:STRING,STRING,UINT,UINT,UINT (pk-marshal.list:32) */
void
pk_marshal_VOID__STRING_STRING_UINT_UINT_UINT (GClosure     *closure,
                                               GValue       *return_value G_GNUC_UNUSED,
                                               guint         n_param_values,
                                               const GValue *param_values,
                                               gpointer      invocation_hint G_GNUC_UNUSED,
                                               gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__STRING_STRING_UINT_UINT_UINT) (gpointer     data1,
                                                                   gpointer     arg_1,
                                                                   gpointer     arg_2,
                                                                   guint        arg_3,
                                                                   guint        arg_4,
                                                                   guint        arg_5,
                                                                   gpointer     data2);
  register GMarshalFunc_VOID__STRING_STRING_UINT_UINT_UINT callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 6);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__STRING_STRING_UINT_UINT_UINT) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_string (param_values + 1),
            g_marshal_value_peek_string (param_values + 2),
            g_marshal_value_peek_uint (param_values + 3),
            g_marshal_value_peek_uint (param_values + 4),
            g_marshal_value_peek_uint (param_values + 5),
            data2);
}

/* VOID:STRING,STRING,BOOL,UINT,UINT,STRING,UINT,STRING (pk-marshal.list:33) */
void
pk_marshal_VOID__STRING_STRING_BOOLEAN_UINT_UINT_STRING_UINT_STRING (GClosure     *closure,
                                                                     GValue       *return_value G_GNUC_UNUSED,
                                                                     guint         n_param_values,
                                                                     const GValue *param_values,
                                                                     gpointer      invocation_hint G_GNUC_UNUSED,
                                                                     gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__STRING_STRING_BOOLEAN_UINT_UINT_STRING_UINT_STRING) (gpointer     data1,
                                                                                         gpointer     arg_1,
                                                                                         gpointer     arg_2,
                                                                                         gboolean     arg_3,
                                                                                         guint        arg_4,
                                                                                         guint        arg_5,
                                                                                         gpointer     arg_6,
                                                                                         guint        arg_7,
                                                                                         gpointer     arg_8,
                                                                                         gpointer     data2);
  register GMarshalFunc_VOID__STRING_STRING_BOOLEAN_UINT_UINT_STRING_UINT_STRING callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 9);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__STRING_STRING_BOOLEAN_UINT_UINT_STRING_UINT_STRING) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_string (param_values + 1),
            g_marshal_value_peek_string (param_values + 2),
            g_marshal_value_peek_boolean (param_values + 3),
            g_marshal_value_peek_uint (param_values + 4),
            g_marshal_value_peek_uint (param_values + 5),
            g_marshal_value_peek_string (param_values + 6),
            g_marshal_value_peek_uint (param_values + 7),
            g_marshal_value_peek_string (param_values + 8),
            data2);
}

/* VOID:STRING,STRING,STRING,BOOL,STRING,UINT,STRING,UINT,STRING (pk-marshal.list:34) */
void
pk_marshal_VOID__STRING_STRING_STRING_BOOLEAN_STRING_UINT_STRING_UINT_STRING (GClosure     *closure,
                                                                              GValue       *return_value G_GNUC_UNUSED,
                                                                              guint         n_param_values,
                                                                              const GValue *param_values,
                                                                              gpointer      invocation_hint G_GNUC_UNUSED,
                                                                              gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__STRING_STRING_STRING_BOOLEAN_STRING_UINT_STRING_UINT_STRING) (gpointer     data1,
                                                                                                  gpointer     arg_1,
                                                                                                  gpointer     arg_2,
                                                                                                  gpointer     arg_3,
                                                                                                  gboolean     arg_4,
                                                                                                  gpointer     arg_5,
                                                                                                  guint        arg_6,
                                                                                                  gpointer     arg_7,
                                                                                                  guint        arg_8,
                                                                                                  gpointer     arg_9,
                                                                                                  gpointer     data2);
  register GMarshalFunc_VOID__STRING_STRING_STRING_BOOLEAN_STRING_UINT_STRING_UINT_STRING callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 10);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__STRING_STRING_STRING_BOOLEAN_STRING_UINT_STRING_UINT_STRING) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_string (param_values + 1),
            g_marshal_value_peek_string (param_values + 2),
            g_marshal_value_peek_string (param_values + 3),
            g_marshal_value_peek_boolean (param_values + 4),
            g_marshal_value_peek_string (param_values + 5),
            g_marshal_value_peek_uint (param_values + 6),
            g_marshal_value_peek_string (param_values + 7),
            g_marshal_value_peek_uint (param_values + 8),
            g_marshal_value_peek_string (param_values + 9),
            data2);
}

/* VOID:STRING,STRING,BOOL,STRING,UINT,STRING,UINT,STRING (pk-marshal.list:35) */
void
pk_marshal_VOID__STRING_STRING_BOOLEAN_STRING_UINT_STRING_UINT_STRING (GClosure     *closure,
                                                                       GValue       *return_value G_GNUC_UNUSED,
                                                                       guint         n_param_values,
                                                                       const GValue *param_values,
                                                                       gpointer      invocation_hint G_GNUC_UNUSED,
                                                                       gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__STRING_STRING_BOOLEAN_STRING_UINT_STRING_UINT_STRING) (gpointer     data1,
                                                                                           gpointer     arg_1,
                                                                                           gpointer     arg_2,
                                                                                           gboolean     arg_3,
                                                                                           gpointer     arg_4,
                                                                                           guint        arg_5,
                                                                                           gpointer     arg_6,
                                                                                           guint        arg_7,
                                                                                           gpointer     arg_8,
                                                                                           gpointer     data2);
  register GMarshalFunc_VOID__STRING_STRING_BOOLEAN_STRING_UINT_STRING_UINT_STRING callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 9);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__STRING_STRING_BOOLEAN_STRING_UINT_STRING_UINT_STRING) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_string (param_values + 1),
            g_marshal_value_peek_string (param_values + 2),
            g_marshal_value_peek_boolean (param_values + 3),
            g_marshal_value_peek_string (param_values + 4),
            g_marshal_value_peek_uint (param_values + 5),
            g_marshal_value_peek_string (param_values + 6),
            g_marshal_value_peek_uint (param_values + 7),
            g_marshal_value_peek_string (param_values + 8),
            data2);
}

/* VOID:POINTER,UINT,STRING (pk-marshal.list:36) */
void
pk_marshal_VOID__POINTER_UINT_STRING (GClosure     *closure,
                                      GValue       *return_value G_GNUC_UNUSED,
                                      guint         n_param_values,
                                      const GValue *param_values,
                                      gpointer      invocation_hint G_GNUC_UNUSED,
                                      gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__POINTER_UINT_STRING) (gpointer     data1,
                                                          gpointer     arg_1,
                                                          guint        arg_2,
                                                          gpointer     arg_3,
                                                          gpointer     data2);
  register GMarshalFunc_VOID__POINTER_UINT_STRING callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 4);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__POINTER_UINT_STRING) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_pointer (param_values + 1),
            g_marshal_value_peek_uint (param_values + 2),
            g_marshal_value_peek_string (param_values + 3),
            data2);
}

/* VOID:POINTER,UINT,UINT (pk-marshal.list:37) */
void
pk_marshal_VOID__POINTER_UINT_UINT (GClosure     *closure,
                                    GValue       *return_value G_GNUC_UNUSED,
                                    guint         n_param_values,
                                    const GValue *param_values,
                                    gpointer      invocation_hint G_GNUC_UNUSED,
                                    gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__POINTER_UINT_UINT) (gpointer     data1,
                                                        gpointer     arg_1,
                                                        guint        arg_2,
                                                        guint        arg_3,
                                                        gpointer     data2);
  register GMarshalFunc_VOID__POINTER_UINT_UINT callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 4);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__POINTER_UINT_UINT) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_pointer (param_values + 1),
            g_marshal_value_peek_uint (param_values + 2),
            g_marshal_value_peek_uint (param_values + 3),
            data2);
}

/* VOID:STRING,BOXED (pk-marshal.list:38) */
void
pk_marshal_VOID__STRING_BOXED (GClosure     *closure,
                               GValue       *return_value G_GNUC_UNUSED,
                               guint         n_param_values,
                               const GValue *param_values,
                               gpointer      invocation_hint G_GNUC_UNUSED,
                               gpointer      marshal_data)
{
  typedef void (*GMarshalFunc_VOID__STRING_BOXED) (gpointer     data1,
                                                   gpointer     arg_1,
                                                   gpointer     arg_2,
                                                   gpointer     data2);
  register GMarshalFunc_VOID__STRING_BOXED callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;

  g_return_if_fail (n_param_values == 3);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_VOID__STRING_BOXED) (marshal_data ? marshal_data : cc->callback);

  callback (data1,
            g_marshal_value_peek_string (param_values + 1),
            g_marshal_value_peek_boxed (param_values + 2),
            data2);
}

