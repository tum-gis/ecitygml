package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface LinearRingLib: Library {
    fun ecitygml_LinearRing_destroy(handle: Pointer)
    fun ecitygml_LinearRing_id(handle: Pointer): Pointer?
    fun ecitygml_LinearRing_names(handle: Pointer): Pointer
    fun ecitygml_LinearRing_try_from(ring: Pointer): Pointer?
    fun ecitygml_LinearRing_points(handle: Pointer): Pointer
    fun ecitygml_LinearRing_length_3d(handle: Pointer): Double
    fun ecitygml_LinearRing_area_3d(handle: Pointer): Double
    fun ecitygml_LinearRing_compute_envelope(handle: Pointer): Pointer?
}
/** A linear ring, borrowed from a city model.
*/
class LinearRing internal constructor (
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

    private class LinearRingCleaner(val handle: Pointer, val lib: LinearRingLib) : Runnable {
        override fun run() {
            lib.ecitygml_LinearRing_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, LinearRing.LinearRingCleaner(handle, LinearRing.lib));
    }

    companion object {
        internal val libClass: Class<LinearRingLib> = LinearRingLib::class.java
        internal val lib: LinearRingLib = Native.load("ecitygml_ffi", libClass)
        @JvmStatic
        
        /** The ring as a linear ring, or none if it is another type (Rust: `LinearRing::try_from`,
        *which takes the ring by value). Follows nested rings (`AbstractRingKind::AbstractRingKind`).
        */
        fun tryFrom(ring: AbstractRingKind): LinearRing? {
            // This lifetime edge depends on lifetimes: 'a
            val aEdges: MutableList<Any> = mutableListOf(ring);
            
            val returnVal = lib.ecitygml_LinearRing_try_from(ring.handle);
            val selfEdges: List<Any> = listOf(ring)
            val handle = returnVal ?: return null
            val returnOpaque = LinearRing(handle, selfEdges, false)
            return returnOpaque
        }
    }
    
    /** The object's `gml:id`, if it has one.
    */
    fun id(): Id? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_LinearRing_id(handle);
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
        
        val returnVal = lib.ecitygml_LinearRing_names(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = CodeIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    /** The positions, without the repeated closing position.
    */
    fun points(): DirectPositionIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_LinearRing_points(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = DirectPositionIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    fun length3d(): Double {
        
        val returnVal = lib.ecitygml_LinearRing_length_3d(handle);
        return (returnVal)
    }
    
    fun area3d(): Double {
        
        val returnVal = lib.ecitygml_LinearRing_area_3d(handle);
        return (returnVal)
    }
    
    /** Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).
    */
    fun computeEnvelope(): Envelope? {
        
        val returnVal = lib.ecitygml_LinearRing_compute_envelope(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal ?: return null
        val returnOpaque = Envelope(handle, selfEdges, true)
        return returnOpaque
    }

}