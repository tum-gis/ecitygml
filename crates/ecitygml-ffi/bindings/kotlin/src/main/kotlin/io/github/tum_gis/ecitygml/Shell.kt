package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface ShellLib: Library {
    fun ecitygml_Shell_destroy(handle: Pointer)
    fun ecitygml_Shell_id(handle: Pointer): Pointer?
    fun ecitygml_Shell_names(handle: Pointer): Pointer
    fun ecitygml_Shell_triangulate(handle: Pointer): ResultPointerPointer
    fun ecitygml_Shell_try_from(surface: Pointer): Pointer?
    fun ecitygml_Shell_members(handle: Pointer): Pointer
    fun ecitygml_Shell_points(handle: Pointer): Pointer
    fun ecitygml_Shell_area_3d(handle: Pointer): ResultDoublePointer
    fun ecitygml_Shell_volume_3d(handle: Pointer): ResultDoublePointer
    fun ecitygml_Shell_compute_envelope(handle: Pointer): Pointer?
}
/** A shell (closed surface), borrowed from a city model.
*/
class Shell internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal var owned: Boolean,
)  {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class ShellCleaner(val handle: Pointer, val lib: ShellLib) : Runnable {
        override fun run() {
            lib.ecitygml_Shell_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, Shell.ShellCleaner(handle, Shell.lib));
    }

    companion object {
        internal val libClass: Class<ShellLib> = ShellLib::class.java
        internal val lib: ShellLib = Native.load("ecitygml_ffi", libClass)
        @JvmStatic
        
        /** The surface as a shell, or none if it is another type (Rust: `Shell::try_from`, which
        *takes the surface by value).
        */
        fun tryFrom(surface: AbstractSurfaceKind): Shell? {
            // This lifetime edge depends on lifetimes: 'a
            val aEdges: MutableList<Any> = mutableListOf(surface);
            
            val returnVal = lib.ecitygml_Shell_try_from(surface.handle);
            val selfEdges: List<Any> = listOf(surface)
            val handle = returnVal ?: return null
            val returnOpaque = Shell(handle, selfEdges, false)
            return returnOpaque
        }
    }
    
    /** The object's `gml:id`, if it has one.
    */
    fun id(): Id? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Shell_id(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = Id(handle, selfEdges, false)
        return returnOpaque
    }
    
    /** The object's `gml:name`s.
    */
    fun names(): CodeIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Shell_names(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = CodeIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    /** Triangulates the geometry (Rust: `Triangulate::triangulate`). Members that fail to
    *triangulate are listed in `Triangulation::skipped`; as in egml, members that are only an
    *`xlink:href` are left out without such an entry.
    */
    fun triangulate(): Result<Triangulation> {
        
        val returnVal = lib.ecitygml_Shell_triangulate(handle);
        val nativeOkVal = returnVal.getNativeOk();
        if (nativeOkVal != null) {
            val selfEdges: List<Any> = listOf()
            val handle = nativeOkVal 
            val returnOpaque = Triangulation(handle, selfEdges, true)
            return returnOpaque.ok()
        } else {
            val selfEdges: List<Any> = listOf()
            val handle = returnVal.getNativeErr()!! 
            val returnOpaque = Error(handle, selfEdges, true)
            return returnOpaque.err()
        }
    }
    
    /** The surface members (`gml:surfaceMember`).
    */
    fun members(): AbstractSurfacePropertyIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Shell_members(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = AbstractSurfacePropertyIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    /** All positions of the inline members.
    */
    fun points(): DirectPositionIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Shell_points(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = DirectPositionIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    fun area3d(): Result<Double> {
        
        val returnVal = lib.ecitygml_Shell_area_3d(handle);
        val nativeOkVal = returnVal.getNativeOk();
        if (nativeOkVal != null) {
            return (nativeOkVal).ok()
        } else {
            val selfEdges: List<Any> = listOf()
            val handle = returnVal.getNativeErr()!! 
            val returnOpaque = Error(handle, selfEdges, true)
            return returnOpaque.err()
        }
    }
    
    /** Enclosed volume; fails with `UnresolvedReference` if a member is only an `xlink:href`.
    */
    fun volume3d(): Result<Double> {
        
        val returnVal = lib.ecitygml_Shell_volume_3d(handle);
        val nativeOkVal = returnVal.getNativeOk();
        if (nativeOkVal != null) {
            return (nativeOkVal).ok()
        } else {
            val selfEdges: List<Any> = listOf()
            val handle = returnVal.getNativeErr()!! 
            val returnOpaque = Error(handle, selfEdges, true)
            return returnOpaque.err()
        }
    }
    
    /** Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).
    */
    fun computeEnvelope(): Envelope? {
        
        val returnVal = lib.ecitygml_Shell_compute_envelope(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal ?: return null
        val returnOpaque = Envelope(handle, selfEdges, true)
        return returnOpaque
    }

}