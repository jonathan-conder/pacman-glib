// This file was generated by the Gtk# code generator.
// Any changes made will be lost if regenerated.

namespace PackageKit {

	using System;

	public delegate void RequireRestartHandler(object o, RequireRestartArgs args);

	public class RequireRestartArgs : GLib.SignalArgs {
		public PackageKit.RestartEnum Restart{
			get {
				return (PackageKit.RestartEnum) Args[0];
			}
		}

		public PackageKit.PackageId Id{
			get {
				return (PackageKit.PackageId) Args[1];
			}
		}

	}
}
