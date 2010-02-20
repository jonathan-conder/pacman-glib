namespace Pacman {
	[Compact]
	[CCode (dup_function = "pacman_list_copy", free_function = "pacman_list_free")]
	public class List<G> {
		public List ();
		[ReturnsModifiedPointer ()]
		public void add (owned G item);
		[ReturnsModifiedPointer ()]
		public void add_sorted (owned G item, GLib.CompareFunc func);
		[ReturnsModifiedPointer ()]
		public void concat (owned Pacman.List<G> second);
		public Pacman.List<unowned G> copy ();
		public Pacman.List<unowned G> diff (Pacman.List<G> rhs, GLib.CompareFunc func);
		public unowned G? find (G needle, GLib.CompareFunc func);
		public unowned G? find_direct (G needle);
		public void free_contents (GLib.DestroyNotify func);
		public unowned G @get ();
		public uint length ();
		public unowned Pacman.List<G> next ();
		public unowned Pacman.List<G> nth (uint n);
		[ReturnsModifiedPointer ()]
		public void remove (G needle, GLib.CompareFunc func, out G removed);
		[ReturnsModifiedPointer ()]
		public void remove_direct (G needle, out G removed);
		public Pacman.List<unowned G> remove_duplicates ();
		public Pacman.List<unowned G> reverse ();
		public void @set (G item);
		[ReturnsModifiedPointer ()]
		public void sort (GLib.CompareFunc func);
	}
}
