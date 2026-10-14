package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface PolygonPatchLib: Library {
    fun ecitygml_PolygonPatch_destroy(handle: Pointer)
    fun ecitygml_PolygonPatch_triangulate(handle: Pointer): ResultPointerPointer
    fun ecitygml_PolygonPatch_try_from(patch: Pointer): Pointer?
    fun ecitygml_PolygonPatch_exterior(handle: Pointer): Pointer?
    fun ecitygml_PolygonPatch_interior(handle: Pointer): Pointer
    fun ecitygml_PolygonPatch_area_3d(handle: Pointer): ResultDoublePointer
    fun ecitygml_PolygonPatch_points(handle: Pointer): Pointer
    fun ecitygml_PolygonPatch_compute_envelope(handle: Pointer): Pointer?
}
/** A polygon patch, borrowed from a city model.
*/
class PolygonPatch internal constructor (
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

    private class PolygonPatchCleaner(val handle: Pointer, val lib: PolygonPatchLib) : Runnable {
        override fun run() {
            lib.ecitygml_PolygonPatch_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, PolygonPatch.PolygonPatchCleaner(handle, PolygonPatch.lib));
    }

    companion object {
        internal val libClass: Class<PolygonPatchLib> = PolygonPatchLib::class.java
        internal val lib: PolygonPatchLib = Native.load("ecitygml_ffi", libClass)
        @JvmStatic
        
        /** The patch as a polygon patch, or none if it is another type (Rust: `PolygonPatch::try_from`, which
        *takes the patch by value).
        */
        fun tryFrom(patch: AbstractSurfacePatchKind): PolygonPatch? {
            // This lifetime edge depends on lifetimes: 'a
            val aEdges: MutableList<Any> = mutableListOf(patch);
            
            val returnVal = lib.ecitygml_PolygonPatch_try_from(patch.handle);
            val selfEdges: List<Any> = listOf(patch)
            val handle = returnVal ?: return null
            val returnOpaque = PolygonPatch(handle, selfEdges, false)
            return returnOpaque
        }
    }
    
    /** Triangulates the geometry (Rust: `Triangulate::triangulate`). Members that fail to
    *triangulate are listed in `Triangulation::skipped`; as in egml, members that are only an
    *`xlink:href` are left out without such an entry.
    */
    fun triangulate(): Result<Triangulation> {
        
        val returnVal = lib.ecitygml_PolygonPatch_triangulate(handle);
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
    
    fun exterior(): AbstractRingKind? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_PolygonPatch_exterior(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = AbstractRingKind(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun interior(): AbstractRingKindIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_PolygonPatch_interior(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = AbstractRingKindIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    /** Exterior area minus the holes; fails if the patch has no exterior ring.
    */
    fun area3d(): Result<Double> {
        
        val returnVal = lib.ecitygml_PolygonPatch_area_3d(handle);
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
    
    /** All positions of the exterior and interior rings.
    */
    fun points(): DirectPositionIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_PolygonPatch_points(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = DirectPositionIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    /** Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).
    */
    fun computeEnvelope(): Envelope? {
        
        val returnVal = lib.ecitygml_PolygonPatch_compute_envelope(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal ?: return null
        val returnOpaque = Envelope(handle, selfEdges, true)
        return returnOpaque
    }

}