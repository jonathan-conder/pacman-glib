// This file was generated by the Gtk# code generator.
// Any changes made will be lost if regenerated.

namespace PackageKit {

	using System;
	using System.Runtime.InteropServices;

#region Autogenerated code
	public class Network {

		[DllImport("libpackagekit-glib.dll")]
		static extern IntPtr pk_network_enum_to_string(int network);

		public static string EnumToText(PackageKit.NetworkEnum network) {
			IntPtr raw_ret = pk_network_enum_to_string((int) network);
			string ret = GLib.Marshaller.Utf8PtrToString (raw_ret);
			return ret;
		}

		[DllImport("libpackagekit-glib.dll")]
		static extern int pk_network_enum_from_string(IntPtr network);

		public static PackageKit.NetworkEnum EnumFromText(string network) {
			IntPtr native_network = GLib.Marshaller.StringToPtrGStrdup (network);
			int raw_ret = pk_network_enum_from_string(native_network);
			PackageKit.NetworkEnum ret = (PackageKit.NetworkEnum) raw_ret;
			GLib.Marshaller.Free (native_network);
			return ret;
		}

#endregion
	}
}
