package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface AbstractRingKindLib: Library {
    fun ecitygml_AbstractRingKind_destroy(handle: Pointer)
    fun ecitygml_AbstractRingKind_id(handle: Pointer): Pointer?
    fun ecitygml_AbstractRingKind_names(handle: Pointer): Pointer
    fun ecitygml_AbstractRingKind_try_from(curve: Pointer): Pointer?
    fun ecitygml_AbstractRingKind_geometry_type(handle: Pointer): Int
    fun ecitygml_AbstractRingKind_points(handle: Pointer): Pointer
    fun ecitygml_AbstractRingKind_length_3d(handle: Pointer): Double
    fun ecitygml_AbstractRingKind_area_3d(handle: Pointer): Double
    fun ecitygml_AbstractRingKind_compute_envelope(handle: Pointer): Pointer?
}
/** A ring of any type, borrowed from a city model; convert it with `LinearRing::try_from`.
*/
class AbstractRingKind internal constructor (
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

    private class AbstractRingKindCleaner(val handle: Pointer, val lib: AbstractRingKindLib) : Runnable {
        override fun run() {
            lib.ecitygml_AbstractRingKind_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, AbstractRingKind.AbstractRingKindCleaner(handle, AbstractRingKind.lib));
    }

    companion object {
        internal val libClass: Class<AbstractRingKindLib> = AbstractRingKindLib::class.java
        internal val lib: AbstractRingKindLib = Native.load("ecitygml_ffi", libClass)
        @JvmStatic
        
        /** The curve as a ring, or none if it is another type (Rust: `AbstractRingKind::try_from`,
        *which takes the curve by value).
        */
        fun tryFrom(curve: AbstractCurveKind): AbstractRingKind? {
            // This lifetime edge depends on lifetimes: 'a
            val aEdges: MutableList<Any> = mutableListOf(curve);
            
            val returnVal = lib.ecitygml_AbstractRingKind_try_from(curve.handle);
            val selfEdges: List<Any> = listOf(curve)
            val handle = returnVal ?: return null
            val returnOpaque = AbstractRingKind(handle, selfEdges, false)
            return returnOpaque
        }
    }
    
    /** The object's `gml:id`, if it has one.
    */
    fun id(): Id? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AbstractRingKind_id(handle);
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
        
        val returnVal = lib.ecitygml_AbstractRingKind_names(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = CodeIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    fun geometryType(): GeometryType {
        
        val returnVal = lib.ecitygml_AbstractRingKind_geometry_type(handle);
        return (GeometryType.fromNative(returnVal))
    }
    
    /** The positions, without the repeated closing position.
    */
    fun points(): DirectPositionIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AbstractRingKind_points(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = DirectPositionIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    fun length3d(): Double {
        
        val returnVal = lib.ecitygml_AbstractRingKind_length_3d(handle);
        return (returnVal)
    }
    
    fun area3d(): Double {
        
        val returnVal = lib.ecitygml_AbstractRingKind_area_3d(handle);
        return (returnVal)
    }
    
    /** Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).
    */
    fun computeEnvelope(): Envelope? {
        
        val returnVal = lib.ecitygml_AbstractRingKind_compute_envelope(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal ?: return null
        val returnOpaque = Envelope(handle, selfEdges, true)
        return returnOpaque
    }

}