package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface PointLib: Library {
    fun ecitygml_Point_destroy(handle: Pointer)
    fun ecitygml_Point_id(handle: Pointer): Pointer?
    fun ecitygml_Point_names(handle: Pointer): Pointer
    fun ecitygml_Point_try_from(geometry: Pointer): Pointer?
    fun ecitygml_Point_pos(handle: Pointer): Pointer
    fun ecitygml_Point_compute_envelope(handle: Pointer): Pointer?
}
/** A point, borrowed from a city model.
*/
class Point internal constructor (
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

    private class PointCleaner(val handle: Pointer, val lib: PointLib) : Runnable {
        override fun run() {
            lib.ecitygml_Point_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, Point.PointCleaner(handle, Point.lib));
    }

    companion object {
        internal val libClass: Class<PointLib> = PointLib::class.java
        internal val lib: PointLib = Native.load("ecitygml_ffi", libClass)
        @JvmStatic
        
        /** The geometry as a `Point`, or none if it is another type (Rust: nested
        *`AbstractGeometryKind` variants).
        */
        fun tryFrom(geometry: AbstractGeometryKind): Point? {
            // This lifetime edge depends on lifetimes: 'a
            val aEdges: MutableList<Any> = mutableListOf(geometry);
            
            val returnVal = lib.ecitygml_Point_try_from(geometry.handle);
            val selfEdges: List<Any> = listOf(geometry)
            val handle = returnVal ?: return null
            val returnOpaque = Point(handle, selfEdges, false)
            return returnOpaque
        }
    }
    
    /** The object's `gml:id`, if it has one.
    */
    fun id(): Id? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Point_id(handle);
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
        
        val returnVal = lib.ecitygml_Point_names(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = CodeIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    /** The position (`gml:pos`).
    */
    fun pos(): DirectPosition {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Point_pos(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal 
        val returnOpaque = DirectPosition(handle, selfEdges, false)
        return returnOpaque
    }
    
    /** Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).
    */
    fun computeEnvelope(): Envelope? {
        
        val returnVal = lib.ecitygml_Point_compute_envelope(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal ?: return null
        val returnOpaque = Envelope(handle, selfEdges, true)
        return returnOpaque
    }

}