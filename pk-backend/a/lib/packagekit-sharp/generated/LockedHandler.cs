// This file was generated by the Gtk# code generator.
// Any changes made will be lost if regenerated.

namespace PackageKit {

	using System;

	public delegate void LockedHandler(object o, LockedArgs args);

	public class LockedArgs : GLib.SignalArgs {
		public bool IsLocked{
			get {
				return (bool) Args[0];
			}
		}

	}
}
