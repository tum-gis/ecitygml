package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface AbstractSurfacePatchKindLib: Library {
    fun ecitygml_AbstractSurfacePatchKind_destroy(handle: Pointer)
    fun ecitygml_AbstractSurfacePatchKind_triangulate(handle: Pointer): ResultPointerPointer
    fun ecitygml_AbstractSurfacePatchKind_area_3d(handle: Pointer): ResultDoublePointer
    fun ecitygml_AbstractSurfacePatchKind_points(handle: Pointer): Pointer
    fun ecitygml_AbstractSurfacePatchKind_compute_envelope(handle: Pointer): Pointer?
}
/** A surface patch of any type, borrowed from a city model; convert it with
*`PolygonPatch::try_from` or `Triangle::try_from`. Patches aren't GML objects (no `gml:id`).
*/
class AbstractSurfacePatchKind internal constructor (
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

    private class AbstractSurfacePatchKindCleaner(val handle: Pointer, val lib: AbstractSurfacePatchKindLib) : Runnable {
        override fun run() {
            lib.ecitygml_AbstractSurfacePatchKind_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, AbstractSurfacePatchKind.AbstractSurfacePatchKindCleaner(handle, AbstractSurfacePatchKind.lib));
    }

    companion object {
        internal val libClass: Class<AbstractSurfacePatchKindLib> = AbstractSurfacePatchKindLib::class.java
        internal val lib: AbstractSurfacePatchKindLib = Native.load("ecitygml_ffi", libClass)
    }
    
    /** Triangulates the geometry (Rust: `Triangulate::triangulate`). Members that fail to
    *triangulate are listed in `Triangulation::skipped`; as in egml, members that are only an
    *`xlink:href` are left out without such an entry.
    */
    fun triangulate(): Result<Triangulation> {
        
        val returnVal = lib.ecitygml_AbstractSurfacePatchKind_triangulate(handle);
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
    
    fun area3d(): Result<Double> {
        
        val returnVal = lib.ecitygml_AbstractSurfacePatchKind_area_3d(handle);
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
    
    /** The patch's positions.
    */
    fun points(): DirectPositionIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AbstractSurfacePatchKind_points(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = DirectPositionIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    /** Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).
    */
    fun computeEnvelope(): Envelope? {
        
        val returnVal = lib.ecitygml_AbstractSurfacePatchKind_compute_envelope(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal ?: return null
        val returnOpaque = Envelope(handle, selfEdges, true)
        return returnOpaque
    }

}