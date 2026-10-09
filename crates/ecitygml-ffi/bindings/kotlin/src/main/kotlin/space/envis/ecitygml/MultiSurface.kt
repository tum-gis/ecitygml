package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface MultiSurfaceLib: Library {
    fun ecitygml_MultiSurface_destroy(handle: Pointer)
    fun ecitygml_MultiSurface_id(handle: Pointer): Pointer?
    fun ecitygml_MultiSurface_names(handle: Pointer): Pointer
    fun ecitygml_MultiSurface_triangulate(handle: Pointer): ResultPointerPointer
    fun ecitygml_MultiSurface_try_from(geometry: Pointer): Pointer?
    fun ecitygml_MultiSurface_surface_member(handle: Pointer): Pointer
    fun ecitygml_MultiSurface_area_3d(handle: Pointer): ResultDoublePointer
    fun ecitygml_MultiSurface_points(handle: Pointer): Pointer
    fun ecitygml_MultiSurface_compute_envelope(handle: Pointer): Pointer?
}
/** A multi surface, borrowed from a city model.
*/
class MultiSurface internal constructor (
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

    private class MultiSurfaceCleaner(val handle: Pointer, val lib: MultiSurfaceLib) : Runnable {
        override fun run() {
            lib.ecitygml_MultiSurface_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, MultiSurface.MultiSurfaceCleaner(handle, MultiSurface.lib));
    }

    companion object {
        internal val libClass: Class<MultiSurfaceLib> = MultiSurfaceLib::class.java
        internal val lib: MultiSurfaceLib = Native.load("ecitygml_ffi", libClass)
        @JvmStatic
        
        /** The geometry as a `MultiSurface`, or none if it is another type (Rust: nested
        *`AbstractGeometryKind` variants).
        */
        fun tryFrom(geometry: AbstractGeometryKind): MultiSurface? {
            // This lifetime edge depends on lifetimes: 'a
            val aEdges: MutableList<Any> = mutableListOf(geometry);
            
            val returnVal = lib.ecitygml_MultiSurface_try_from(geometry.handle);
            val selfEdges: List<Any> = listOf(geometry)
            val handle = returnVal ?: return null
            val returnOpaque = MultiSurface(handle, selfEdges, false)
            return returnOpaque
        }
    }
    
    /** The object's `gml:id`, if it has one.
    */
    fun id(): Id? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_MultiSurface_id(handle);
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
        
        val returnVal = lib.ecitygml_MultiSurface_names(handle);
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
        
        val returnVal = lib.ecitygml_MultiSurface_triangulate(handle);
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
    fun surfaceMember(): AbstractSurfacePropertyIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_MultiSurface_surface_member(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = AbstractSurfacePropertyIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    /** Sum of the members' areas; fails with `UnresolvedReference` if a member is only an
    *`xlink:href`.
    */
    fun area3d(): Result<Double> {
        
        val returnVal = lib.ecitygml_MultiSurface_area_3d(handle);
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
    
    /** All positions of the inline members.
    */
    fun points(): DirectPositionIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_MultiSurface_points(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = DirectPositionIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    /** Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).
    */
    fun computeEnvelope(): Envelope? {
        
        val returnVal = lib.ecitygml_MultiSurface_compute_envelope(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal ?: return null
        val returnOpaque = Envelope(handle, selfEdges, true)
        return returnOpaque
    }

}