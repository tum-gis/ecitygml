package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface AbstractCurveKindLib: Library {
    fun ecitygml_AbstractCurveKind_destroy(handle: Pointer)
    fun ecitygml_AbstractCurveKind_id(handle: Pointer): Pointer?
    fun ecitygml_AbstractCurveKind_names(handle: Pointer): Pointer
    fun ecitygml_AbstractCurveKind_try_from(geometry: Pointer): Pointer?
    fun ecitygml_AbstractCurveKind_geometry_type(handle: Pointer): Int
    fun ecitygml_AbstractCurveKind_length_3d(handle: Pointer): Double
    fun ecitygml_AbstractCurveKind_compute_envelope(handle: Pointer): Pointer?
}
/** A curve of any type, borrowed from a city model; convert it with e.g. `LineString::try_from`.
*Rings: `AbstractRingKind::try_from`.
*/
class AbstractCurveKind internal constructor (
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

    private class AbstractCurveKindCleaner(val handle: Pointer, val lib: AbstractCurveKindLib) : Runnable {
        override fun run() {
            lib.ecitygml_AbstractCurveKind_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, AbstractCurveKind.AbstractCurveKindCleaner(handle, AbstractCurveKind.lib));
    }

    companion object {
        internal val libClass: Class<AbstractCurveKindLib> = AbstractCurveKindLib::class.java
        internal val lib: AbstractCurveKindLib = Native.load("ecitygml_ffi", libClass)
        @JvmStatic
        
        /** The geometry as an `AbstractCurveKind`, or none if it is another type (Rust: nested
        *`AbstractGeometryKind` variants).
        */
        fun tryFrom(geometry: AbstractGeometryKind): AbstractCurveKind? {
            // This lifetime edge depends on lifetimes: 'a
            val aEdges: MutableList<Any> = mutableListOf(geometry);
            
            val returnVal = lib.ecitygml_AbstractCurveKind_try_from(geometry.handle);
            val selfEdges: List<Any> = listOf(geometry)
            val handle = returnVal ?: return null
            val returnOpaque = AbstractCurveKind(handle, selfEdges, false)
            return returnOpaque
        }
    }
    
    /** The object's `gml:id`, if it has one.
    */
    fun id(): Id? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AbstractCurveKind_id(handle);
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
        
        val returnVal = lib.ecitygml_AbstractCurveKind_names(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = CodeIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    fun geometryType(): GeometryType {
        
        val returnVal = lib.ecitygml_AbstractCurveKind_geometry_type(handle);
        return (GeometryType.fromNative(returnVal))
    }
    
    fun length3d(): Double {
        
        val returnVal = lib.ecitygml_AbstractCurveKind_length_3d(handle);
        return (returnVal)
    }
    
    /** Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).
    */
    fun computeEnvelope(): Envelope? {
        
        val returnVal = lib.ecitygml_AbstractCurveKind_compute_envelope(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal ?: return null
        val returnOpaque = Envelope(handle, selfEdges, true)
        return returnOpaque
    }

}