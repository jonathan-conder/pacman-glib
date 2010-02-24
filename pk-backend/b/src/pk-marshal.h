
#ifndef __pk_marshal_MARSHAL_H__
#define __pk_marshal_MARSHAL_H__

#include	<glib-object.h>

G_BEGIN_DECLS

/* VOID:UINT,STRING,STRING (pk-marshal.list:1) */
extern void pk_marshal_VOID__UINT_STRING_STRING (GClosure     *closure,
                                                 GValue       *return_value,
                                                 guint         n_param_values,
                                                 const GValue *param_values,
                                                 gpointer      invocation_hint,
                                                 gpointer      marshal_data);

/* VOID:UINT,STRING (pk-marshal.list:2) */
extern void pk_marshal_VOID__UINT_STRING (GClosure     *closure,
                                          GValue       *return_value,
                                          guint         n_param_values,
                                          const GValue *param_values,
                                          gpointer      invocation_hint,
                                          gpointer      marshal_data);

/* VOID:UINT,STRING,UINT (pk-marshal.list:3) */
extern void pk_marshal_VOID__UINT_STRING_UINT (GClosure     *closure,
                                               GValue       *return_value,
                                               guint         n_param_values,
                                               const GValue *param_values,
                                               gpointer      invocation_hint,
                                               gpointer      marshal_data);

/* VOID:UINT,UINT (pk-marshal.list:4) */
extern void pk_marshal_VOID__UINT_UINT (GClosure     *closure,
                                        GValue       *return_value,
                                        guint         n_param_values,
                                        const GValue *param_values,
                                        gpointer      invocation_hint,
                                        gpointer      marshal_data);

/* VOID:UINT,UINT,UINT,UINT (pk-marshal.list:5) */
extern void pk_marshal_VOID__UINT_UINT_UINT_UINT (GClosure     *closure,
                                                  GValue       *return_value,
                                                  guint         n_param_values,
                                                  const GValue *param_values,
                                                  gpointer      invocation_hint,
                                                  gpointer      marshal_data);

/* VOID:STRING,UINT,UINT,UINT,UINT (pk-marshal.list:6) */
extern void pk_marshal_VOID__STRING_UINT_UINT_UINT_UINT (GClosure     *closure,
                                                         GValue       *return_value,
                                                         guint         n_param_values,
                                                         const GValue *param_values,
                                                         gpointer      invocation_hint,
                                                         gpointer      marshal_data);

/* VOID:STRING (pk-marshal.list:7) */
#define pk_marshal_VOID__STRING	g_cclosure_marshal_VOID__STRING

/* VOID:STRING,BOOL (pk-marshal.list:8) */
extern void pk_marshal_VOID__STRING_BOOLEAN (GClosure     *closure,
                                             GValue       *return_value,
                                             guint         n_param_values,
                                             const GValue *param_values,
                                             gpointer      invocation_hint,
                                             gpointer      marshal_data);
#define pk_marshal_VOID__STRING_BOOL	pk_marshal_VOID__STRING_BOOLEAN

/* VOID:STRING,UINT (pk-marshal.list:9) */
extern void pk_marshal_VOID__STRING_UINT (GClosure     *closure,
                                          GValue       *return_value,
                                          guint         n_param_values,
                                          const GValue *param_values,
                                          gpointer      invocation_hint,
                                          gpointer      marshal_data);

/* VOID:STRING,STRING,UINT (pk-marshal.list:10) */
extern void pk_marshal_VOID__STRING_STRING_UINT (GClosure     *closure,
                                                 GValue       *return_value,
                                                 guint         n_param_values,
                                                 const GValue *param_values,
                                                 gpointer      invocation_hint,
                                                 gpointer      marshal_data);

/* VOID:STRING,UINT,STRING,STRING (pk-marshal.list:11) */
extern void pk_marshal_VOID__STRING_UINT_STRING_STRING (GClosure     *closure,
                                                        GValue       *return_value,
                                                        guint         n_param_values,
                                                        const GValue *param_values,
                                                        gpointer      invocation_hint,
                                                        gpointer      marshal_data);

/* VOID:STRING,STRING (pk-marshal.list:12) */
extern void pk_marshal_VOID__STRING_STRING (GClosure     *closure,
                                            GValue       *return_value,
                                            guint         n_param_values,
                                            const GValue *param_values,
                                            gpointer      invocation_hint,
                                            gpointer      marshal_data);

/* VOID:STRING,STRING,STRING (pk-marshal.list:13) */
extern void pk_marshal_VOID__STRING_STRING_STRING (GClosure     *closure,
                                                   GValue       *return_value,
                                                   guint         n_param_values,
                                                   const GValue *param_values,
                                                   gpointer      invocation_hint,
                                                   gpointer      marshal_data);

/* VOID:STRING,STRING,STRING,STRING (pk-marshal.list:14) */
extern void pk_marshal_VOID__STRING_STRING_STRING_STRING (GClosure     *closure,
                                                          GValue       *return_value,
                                                          guint         n_param_values,
                                                          const GValue *param_values,
                                                          gpointer      invocation_hint,
                                                          gpointer      marshal_data);

/* VOID:STRING,STRING,STRING,STRING,STRING (pk-marshal.list:15) */
extern void pk_marshal_VOID__STRING_STRING_STRING_STRING_STRING (GClosure     *closure,
                                                                 GValue       *return_value,
                                                                 guint         n_param_values,
                                                                 const GValue *param_values,
                                                                 gpointer      invocation_hint,
                                                                 gpointer      marshal_data);

/* VOID:STRING,STRING,STRING,STRING,STRING,STRING (pk-marshal.list:16) */
extern void pk_marshal_VOID__STRING_STRING_STRING_STRING_STRING_STRING (GClosure     *closure,
                                                                        GValue       *return_value,
                                                                        guint         n_param_values,
                                                                        const GValue *param_values,
                                                                        gpointer      invocation_hint,
                                                                        gpointer      marshal_data);

/* VOID:STRING,STRING,STRING,STRING,STRING,STRING,STRING,STRING,STRING (pk-marshal.list:17) */
extern void pk_marshal_VOID__STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING (GClosure     *closure,
                                                                                             GValue       *return_value,
                                                                                             guint         n_param_values,
                                                                                             const GValue *param_values,
                                                                                             gpointer      invocation_hint,
                                                                                             gpointer      marshal_data);

/* VOID:STRING,STRING,STRING,STRING,STRING,STRING,STRING,STRING,STRING,STRING (pk-marshal.list:18) */
extern void pk_marshal_VOID__STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING (GClosure     *closure,
                                                                                                    GValue       *return_value,
                                                                                                    guint         n_param_values,
                                                                                                    const GValue *param_values,
                                                                                                    gpointer      invocation_hint,
                                                                                                    gpointer      marshal_data);

/* VOID:STRING,STRING,STRING,STRING,STRING,STRING,STRING,STRING,STRING,STRING,STRING (pk-marshal.list:19) */
extern void pk_marshal_VOID__STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING (GClosure     *closure,
                                                                                                           GValue       *return_value,
                                                                                                           guint         n_param_values,
                                                                                                           const GValue *param_values,
                                                                                                           gpointer      invocation_hint,
                                                                                                           gpointer      marshal_data);

/* VOID:STRING,STRING,STRING,STRING,STRING,STRING,STRING,STRING,STRING,STRING,STRING,STRING (pk-marshal.list:20) */
extern void pk_marshal_VOID__STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING (GClosure     *closure,
                                                                                                                  GValue       *return_value,
                                                                                                                  guint         n_param_values,
                                                                                                                  const GValue *param_values,
                                                                                                                  gpointer      invocation_hint,
                                                                                                                  gpointer      marshal_data);

/* VOID:STRING,STRING,STRING,STRING,STRING,STRING,STRING,STRING (pk-marshal.list:21) */
extern void pk_marshal_VOID__STRING_STRING_STRING_STRING_STRING_STRING_STRING_STRING (GClosure     *closure,
                                                                                      GValue       *return_value,
                                                                                      guint         n_param_values,
                                                                                      const GValue *param_values,
                                                                                      gpointer      invocation_hint,
                                                                                      gpointer      marshal_data);

/* VOID:STRING,STRING,STRING,STRING,STRING,STRING,UINT,STRING (pk-marshal.list:22) */
extern void pk_marshal_VOID__STRING_STRING_STRING_STRING_STRING_STRING_UINT_STRING (GClosure     *closure,
                                                                                    GValue       *return_value,
                                                                                    guint         n_param_values,
                                                                                    const GValue *param_values,
                                                                                    gpointer      invocation_hint,
                                                                                    gpointer      marshal_data);

/* VOID:STRING,STRING,STRING,STRING,STRING,STRING,STRING (pk-marshal.list:23) */
extern void pk_marshal_VOID__STRING_STRING_STRING_STRING_STRING_STRING_STRING (GClosure     *closure,
                                                                               GValue       *return_value,
                                                                               guint         n_param_values,
                                                                               const GValue *param_values,
                                                                               gpointer      invocation_hint,
                                                                               gpointer      marshal_data);

/* VOID:STRING,STRING,STRING,STRING,STRING,STRING,STRING,UINT (pk-marshal.list:24) */
extern void pk_marshal_VOID__STRING_STRING_STRING_STRING_STRING_STRING_STRING_UINT (GClosure     *closure,
                                                                                    GValue       *return_value,
                                                                                    guint         n_param_values,
                                                                                    const GValue *param_values,
                                                                                    gpointer      invocation_hint,
                                                                                    gpointer      marshal_data);

/* VOID:STRING,STRING,UINT,STRING,STRING,UINT64 (pk-marshal.list:25) */
extern void pk_marshal_VOID__STRING_STRING_UINT_STRING_STRING_UINT64 (GClosure     *closure,
                                                                      GValue       *return_value,
                                                                      guint         n_param_values,
                                                                      const GValue *param_values,
                                                                      gpointer      invocation_hint,
                                                                      gpointer      marshal_data);

/* VOID:STRING,STRING,STRING,STRING,STRING,STRING,UINT64 (pk-marshal.list:26) */
extern void pk_marshal_VOID__STRING_STRING_STRING_STRING_STRING_STRING_UINT64 (GClosure     *closure,
                                                                               GValue       *return_value,
                                                                               guint         n_param_values,
                                                                               const GValue *param_values,
                                                                               gpointer      invocation_hint,
                                                                               gpointer      marshal_data);

/* VOID:STRING,STRING,STRING,STRING,STRING,UINT64 (pk-marshal.list:27) */
extern void pk_marshal_VOID__STRING_STRING_STRING_STRING_STRING_UINT64 (GClosure     *closure,
                                                                        GValue       *return_value,
                                                                        guint         n_param_values,
                                                                        const GValue *param_values,
                                                                        gpointer      invocation_hint,
                                                                        gpointer      marshal_data);

/* VOID:STRING,STRING,STRING,STRING,STRING,STRING,UINT (pk-marshal.list:28) */
extern void pk_marshal_VOID__STRING_STRING_STRING_STRING_STRING_STRING_UINT (GClosure     *closure,
                                                                             GValue       *return_value,
                                                                             guint         n_param_values,
                                                                             const GValue *param_values,
                                                                             gpointer      invocation_hint,
                                                                             gpointer      marshal_data);

/* VOID:STRING,STRING,BOOL (pk-marshal.list:29) */
extern void pk_marshal_VOID__STRING_STRING_BOOLEAN (GClosure     *closure,
                                                    GValue       *return_value,
                                                    guint         n_param_values,
                                                    const GValue *param_values,
                                                    gpointer      invocation_hint,
                                                    gpointer      marshal_data);
#define pk_marshal_VOID__STRING_STRING_BOOL	pk_marshal_VOID__STRING_STRING_BOOLEAN

/* VOID:STRING,STRING,STRING,BOOL (pk-marshal.list:30) */
extern void pk_marshal_VOID__STRING_STRING_STRING_BOOLEAN (GClosure     *closure,
                                                           GValue       *return_value,
                                                           guint         n_param_values,
                                                           const GValue *param_values,
                                                           gpointer      invocation_hint,
                                                           gpointer      marshal_data);
#define pk_marshal_VOID__STRING_STRING_STRING_BOOL	pk_marshal_VOID__STRING_STRING_STRING_BOOLEAN

/* VOID:STRING,UINT,STRING,STRING (pk-marshal.list:31) */

/* VOID:STRING,STRING,UINT,UINT,UINT (pk-marshal.list:32) */
extern void pk_marshal_VOID__STRING_STRING_UINT_UINT_UINT (GClosure     *closure,
                                                           GValue       *return_value,
                                                           guint         n_param_values,
                                                           const GValue *param_values,
                                                           gpointer      invocation_hint,
                                                           gpointer      marshal_data);

/* VOID:STRING,STRING,BOOL,UINT,UINT,STRING,UINT,STRING (pk-marshal.list:33) */
extern void pk_marshal_VOID__STRING_STRING_BOOLEAN_UINT_UINT_STRING_UINT_STRING (GClosure     *closure,
                                                                                 GValue       *return_value,
                                                                                 guint         n_param_values,
                                                                                 const GValue *param_values,
                                                                                 gpointer      invocation_hint,
                                                                                 gpointer      marshal_data);
#define pk_marshal_VOID__STRING_STRING_BOOL_UINT_UINT_STRING_UINT_STRING	pk_marshal_VOID__STRING_STRING_BOOLEAN_UINT_UINT_STRING_UINT_STRING

/* VOID:STRING,STRING,STRING,BOOL,STRING,UINT,STRING,UINT,STRING (pk-marshal.list:34) */
extern void pk_marshal_VOID__STRING_STRING_STRING_BOOLEAN_STRING_UINT_STRING_UINT_STRING (GClosure     *closure,
                                                                                          GValue       *return_value,
                                                                                          guint         n_param_values,
                                                                                          const GValue *param_values,
                                                                                          gpointer      invocation_hint,
                                                                                          gpointer      marshal_data);
#define pk_marshal_VOID__STRING_STRING_STRING_BOOL_STRING_UINT_STRING_UINT_STRING	pk_marshal_VOID__STRING_STRING_STRING_BOOLEAN_STRING_UINT_STRING_UINT_STRING

/* VOID:STRING,STRING,BOOL,STRING,UINT,STRING,UINT,STRING (pk-marshal.list:35) */
extern void pk_marshal_VOID__STRING_STRING_BOOLEAN_STRING_UINT_STRING_UINT_STRING (GClosure     *closure,
                                                                                   GValue       *return_value,
                                                                                   guint         n_param_values,
                                                                                   const GValue *param_values,
                                                                                   gpointer      invocation_hint,
                                                                                   gpointer      marshal_data);
#define pk_marshal_VOID__STRING_STRING_BOOL_STRING_UINT_STRING_UINT_STRING	pk_marshal_VOID__STRING_STRING_BOOLEAN_STRING_UINT_STRING_UINT_STRING

/* VOID:POINTER,UINT,STRING (pk-marshal.list:36) */
extern void pk_marshal_VOID__POINTER_UINT_STRING (GClosure     *closure,
                                                  GValue       *return_value,
                                                  guint         n_param_values,
                                                  const GValue *param_values,
                                                  gpointer      invocation_hint,
                                                  gpointer      marshal_data);

/* VOID:POINTER,UINT,UINT (pk-marshal.list:37) */
extern void pk_marshal_VOID__POINTER_UINT_UINT (GClosure     *closure,
                                                GValue       *return_value,
                                                guint         n_param_values,
                                                const GValue *param_values,
                                                gpointer      invocation_hint,
                                                gpointer      marshal_data);

/* VOID:STRING,BOXED (pk-marshal.list:38) */
extern void pk_marshal_VOID__STRING_BOXED (GClosure     *closure,
                                           GValue       *return_value,
                                           guint         n_param_values,
                                           const GValue *param_values,
                                           gpointer      invocation_hint,
                                           gpointer      marshal_data);

G_END_DECLS

#endif /* __pk_marshal_MARSHAL_H__ */

