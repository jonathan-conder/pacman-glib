// This file was generated by the Gtk# code generator.
// Any changes made will be lost if regenerated.

namespace PackageKit {

	using System;
	using System.Collections;
	using System.Runtime.InteropServices;

#region Autogenerated code
	public class UpdateDetailObj : GLib.Opaque {

		[DllImport("libpackagekit-glib.dll")]
		static extern IntPtr pk_update_detail_obj_copy(IntPtr raw);

		public PackageKit.UpdateDetailObj Copy() {
			IntPtr raw_ret = pk_update_detail_obj_copy(Handle);
			PackageKit.UpdateDetailObj ret = raw_ret == IntPtr.Zero ? null : (PackageKit.UpdateDetailObj) GLib.Opaque.GetOpaque (raw_ret, typeof (PackageKit.UpdateDetailObj), true);
			return ret;
		}

		[DllImport("libpackagekit-glib.dll")]
		static extern bool pk_update_detail_obj_free(IntPtr raw);

		public bool Free() {
			bool raw_ret = pk_update_detail_obj_free(Handle);
			bool ret = raw_ret;
			return ret;
		}

		public UpdateDetailObj(IntPtr raw) : base(raw) {}

		[DllImport("libpackagekit-glib.dll")]
		static extern IntPtr pk_update_detail_obj_new();

		public UpdateDetailObj () 
		{
			Raw = pk_update_detail_obj_new();
		}

#endregion
	}
}
