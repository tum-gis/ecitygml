package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface MultiCurveLib: Library {
    fun ecitygml_MultiCurve_destroy(handle: Pointer)
    fun ecitygml_MultiCurve_id(handle: Pointer): Pointer?
    fun ecitygml_MultiCurve_names(handle: Pointer): Pointer
    fun ecitygml_MultiCurve_try_from(geometry: Pointer): Pointer?
    fun ecitygml_MultiCurve_curve_member(handle: Pointer): Pointer
    fun ecitygml_MultiCurve_length_3d(handle: Pointer): ResultDoublePointer
    fun ecitygml_MultiCurve_compute_envelope(handle: Pointer): Pointer?
}
/** A multi curve, borrowed from a city model.
*/
class MultiCurve internal constructor (
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

    private class MultiCurveCleaner(val handle: Pointer, val lib: MultiCurveLib) : Runnable {
        override fun run() {
            lib.ecitygml_MultiCurve_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, MultiCurve.MultiCurveCleaner(handle, MultiCurve.lib));
    }

    companion object {
        internal val libClass: Class<MultiCurveLib> = MultiCurveLib::class.java
        internal val lib: MultiCurveLib = Native.load("ecitygml_ffi", libClass)
        @JvmStatic
        
        /** The geometry as a `MultiCurve`, or none if it is another type (Rust: nested
        *`AbstractGeometryKind` variants).
        */
        fun tryFrom(geometry: AbstractGeometryKind): MultiCurve? {
            // This lifetime edge depends on lifetimes: 'a
            val aEdges: MutableList<Any> = mutableListOf(geometry);
            
            val returnVal = lib.ecitygml_MultiCurve_try_from(geometry.handle);
            val selfEdges: List<Any> = listOf(geometry)
            val handle = returnVal ?: return null
            val returnOpaque = MultiCurve(handle, selfEdges, false)
            return returnOpaque
        }
    }
    
    /** The object's `gml:id`, if it has one.
    */
    fun id(): Id? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_MultiCurve_id(handle);
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
        
        val returnVal = lib.ecitygml_MultiCurve_names(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = CodeIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    /** The curve members (`gml:curveMember`).
    */
    fun curveMember(): AbstractCurvePropertyIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_MultiCurve_curve_member(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = AbstractCurvePropertyIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    /** Sum of the members' lengths; fails with `UnresolvedReference` if a member is only an
    *`xlink:href`.
    */
    fun length3d(): Result<Double> {
        
        val returnVal = lib.ecitygml_MultiCurve_length_3d(handle);
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
        
        val returnVal = lib.ecitygml_MultiCurve_compute_envelope(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal ?: return null
        val returnOpaque = Envelope(handle, selfEdges, true)
        return returnOpaque
    }

}