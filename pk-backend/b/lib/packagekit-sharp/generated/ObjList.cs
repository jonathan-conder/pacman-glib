// This file was generated by the Gtk# code generator.
// Any changes made will be lost if regenerated.

namespace PackageKit {

	using System;
	using System.Collections;
	using System.Runtime.InteropServices;

#region Autogenerated code
	public class ObjList : GLib.Object {

		[Obsolete]
		protected ObjList(GLib.GType gtype) : base(gtype) {}
		public ObjList(IntPtr raw) : base(raw) {}

		[DllImport("libpackagekit-glib.dll")]
		static extern IntPtr pk_obj_list_new();

		public ObjList () : base (IntPtr.Zero)
		{
			if (GetType () != typeof (ObjList)) {
				CreateNativeObject (new string [0], new GLib.Value[0]);
				return;
			}
			Raw = pk_obj_list_new();
		}

		[DllImport("libpackagekit-glib.dll")]
		static extern bool pk_obj_list_remove_index(IntPtr raw, uint index);

		public bool RemoveIndex(uint index) {
			bool raw_ret = pk_obj_list_remove_index(Handle, index);
			bool ret = raw_ret;
			return ret;
		}

		[DllImport("libpackagekit-glib.dll")]
		static extern void pk_obj_list_add_list(IntPtr raw, IntPtr data);

		public void AddList(PackageKit.ObjList data) {
			pk_obj_list_add_list(Handle, data == null ? IntPtr.Zero : data.Handle);
		}

		[DllImport("libpackagekit-glib.dll")]
		static extern void pk_obj_list_add_strv(IntPtr raw, IntPtr data);

		public void AddStrv(IntPtr data) {
			pk_obj_list_add_strv(Handle, data);
		}

		[DllImport("libpackagekit-glib.dll")]
		static extern void pk_obj_list_set_compare(IntPtr raw, PackageKitSharp.ObjListCompareFuncNative func);

		public PackageKit.ObjListCompareFunc Compare { 
			set {
				PackageKitSharp.ObjListCompareFuncWrapper value_wrapper = new PackageKitSharp.ObjListCompareFuncWrapper (value);
				pk_obj_list_set_compare(Handle, value_wrapper.NativeDelegate);
			}
		}

		[DllImport("libpackagekit-glib.dll")]
		static extern IntPtr pk_obj_list_to_string(IntPtr raw);

		public override string ToString() {
			IntPtr raw_ret = pk_obj_list_to_string(Handle);
			string ret = GLib.Marshaller.PtrToStringGFree(raw_ret);
			return ret;
		}

		[DllImport("libpackagekit-glib.dll")]
		static extern bool pk_obj_list_from_file(IntPtr raw, IntPtr filename);

		public bool FromFile(string filename) {
			IntPtr native_filename = GLib.Marshaller.StringToPtrGStrdup (filename);
			bool raw_ret = pk_obj_list_from_file(Handle, native_filename);
			bool ret = raw_ret;
			GLib.Marshaller.Free (native_filename);
			return ret;
		}

		[DllImport("libpackagekit-glib.dll")]
		static extern void pk_obj_list_set_copy(IntPtr raw, PackageKitSharp.ObjListCopyFuncNative func);

		public PackageKit.ObjListCopyFunc Copy { 
			set {
				PackageKitSharp.ObjListCopyFuncWrapper value_wrapper = new PackageKitSharp.ObjListCopyFuncWrapper (value);
				pk_obj_list_set_copy(Handle, value_wrapper.NativeDelegate);
			}
		}

		[DllImport("libpackagekit-glib.dll")]
		static extern bool pk_obj_list_exists(IntPtr raw, IntPtr data);

		public bool Exists(IntPtr data) {
			bool raw_ret = pk_obj_list_exists(Handle, data);
			bool ret = raw_ret;
			return ret;
		}

		[DllImport("libpackagekit-glib.dll")]
		static extern void pk_obj_list_set_free(IntPtr raw, PackageKitSharp.ObjListFreeFuncNative func);

		public PackageKit.ObjListFreeFunc Free { 
			set {
				PackageKitSharp.ObjListFreeFuncWrapper value_wrapper = new PackageKitSharp.ObjListFreeFuncWrapper (value);
				pk_obj_list_set_free(Handle, value_wrapper.NativeDelegate);
			}
		}

		[DllImport("libpackagekit-glib.dll")]
		static extern void pk_obj_list_remove_duplicate(IntPtr raw);

		public void RemoveDuplicate() {
			pk_obj_list_remove_duplicate(Handle);
		}

		[DllImport("libpackagekit-glib.dll")]
		static extern void pk_obj_list_print(IntPtr raw);

		public void Print() {
			pk_obj_list_print(Handle);
		}

		[DllImport("libpackagekit-glib.dll")]
		static extern void pk_obj_list_set_new(IntPtr raw, PackageKitSharp.ObjListNewFuncNative func);

		public PackageKit.ObjListNewFunc New { 
			set {
				PackageKitSharp.ObjListNewFuncWrapper value_wrapper = new PackageKitSharp.ObjListNewFuncWrapper (value);
				pk_obj_list_set_new(Handle, value_wrapper.NativeDelegate);
			}
		}

		[DllImport("libpackagekit-glib.dll")]
		static extern void pk_obj_list_set_equal(IntPtr raw, PackageKitSharp.ObjListEqualFuncNative func);

		public PackageKit.ObjListEqualFunc Equal { 
			set {
				PackageKitSharp.ObjListEqualFuncWrapper value_wrapper = new PackageKitSharp.ObjListEqualFuncWrapper (value);
				pk_obj_list_set_equal(Handle, value_wrapper.NativeDelegate);
			}
		}

		[DllImport("libpackagekit-glib.dll")]
		static extern bool pk_obj_list_to_file(IntPtr raw, IntPtr filename);

		public bool ToFile(string filename) {
			IntPtr native_filename = GLib.Marshaller.StringToPtrGStrdup (filename);
			bool raw_ret = pk_obj_list_to_file(Handle, native_filename);
			bool ret = raw_ret;
			GLib.Marshaller.Free (native_filename);
			return ret;
		}

		[DllImport("libpackagekit-glib.dll")]
		static extern IntPtr pk_obj_list_get_array(IntPtr raw);

		public GLib.PtrArray Array { 
			get {
				IntPtr raw_ret = pk_obj_list_get_array(Handle);
				GLib.PtrArray ret = new GLib.PtrArray(raw_ret);
				return ret;
			}
		}

		[DllImport("libpackagekit-glib.dll")]
		static extern void pk_obj_list_set_from_string(IntPtr raw, PackageKitSharp.ObjListFromStringFuncNative func);

		public PackageKit.ObjListFromStringFunc FromString { 
			set {
				PackageKitSharp.ObjListFromStringFuncWrapper value_wrapper = new PackageKitSharp.ObjListFromStringFuncWrapper (value);
				pk_obj_list_set_from_string(Handle, value_wrapper.NativeDelegate);
			}
		}

		[DllImport("libpackagekit-glib.dll")]
		static extern void pk_obj_list_remove_list(IntPtr raw, IntPtr data);

		public void RemoveList(PackageKit.ObjList data) {
			pk_obj_list_remove_list(Handle, data == null ? IntPtr.Zero : data.Handle);
		}

		[DllImport("libpackagekit-glib.dll")]
		static extern void pk_obj_list_add(IntPtr raw, IntPtr data);

		public void Add(IntPtr data) {
			pk_obj_list_add(Handle, data);
		}

		[DllImport("libpackagekit-glib.dll")]
		static extern void pk_obj_list_set_to_string(IntPtr raw, PackageKitSharp.ObjListToStringFuncNative func);

		public PackageKit.ObjListToStringFunc ToStringFunc { 
			set {
				PackageKitSharp.ObjListToStringFuncWrapper value_wrapper = new PackageKitSharp.ObjListToStringFuncWrapper (value);
				pk_obj_list_set_to_string(Handle, value_wrapper.NativeDelegate);
			}
		}

		[DllImport("libpackagekit-glib.dll")]
		static extern bool pk_obj_list_remove(IntPtr raw, IntPtr data);

		public bool Remove(IntPtr data) {
			bool raw_ret = pk_obj_list_remove(Handle, data);
			bool ret = raw_ret;
			return ret;
		}

		[DllImport("libpackagekit-glib.dll")]
		static extern void pk_obj_list_add_array(IntPtr raw, IntPtr data);

		public void AddArray(GLib.PtrArray data) {
			pk_obj_list_add_array(Handle, data == null ? IntPtr.Zero : data.Handle);
		}

		[DllImport("libpackagekit-glib.dll")]
		static extern IntPtr pk_obj_list_get_type();

		public static new GLib.GType GType { 
			get {
				IntPtr raw_ret = pk_obj_list_get_type();
				GLib.GType ret = new GLib.GType(raw_ret);
				return ret;
			}
		}

		[DllImport("libpackagekit-glib.dll")]
		static extern void pk_obj_list_clear(IntPtr raw);

		public void Clear() {
			pk_obj_list_clear(Handle);
		}


		static ObjList ()
		{
			GtkSharp.PackagekitSharp.ObjectManager.Initialize ();
		}
#endregion
	}
}
