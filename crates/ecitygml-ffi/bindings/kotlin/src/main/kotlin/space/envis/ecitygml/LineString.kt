package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface LineStringLib: Library {
    fun ecitygml_LineString_destroy(handle: Pointer)
    fun ecitygml_LineString_id(handle: Pointer): Pointer?
    fun ecitygml_LineString_names(handle: Pointer): Pointer
    fun ecitygml_LineString_try_from(curve: Pointer): Pointer?
    fun ecitygml_LineString_points(handle: Pointer): Pointer
    fun ecitygml_LineString_length_3d(handle: Pointer): Double
    fun ecitygml_LineString_compute_envelope(handle: Pointer): Pointer?
}
/** A line string, borrowed from a city model.
*/
class LineString internal constructor (
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

    private class LineStringCleaner(val handle: Pointer, val lib: LineStringLib) : Runnable {
        override fun run() {
            lib.ecitygml_LineString_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, LineString.LineStringCleaner(handle, LineString.lib));
    }

    companion object {
        internal val libClass: Class<LineStringLib> = LineStringLib::class.java
        internal val lib: LineStringLib = Native.load("ecitygml_ffi", libClass)
        @JvmStatic
        
        /** The curve as a line string, or none if it is another type (Rust: `LineString::try_from`,
        *which takes the curve by value).
        */
        fun tryFrom(curve: AbstractCurveKind): LineString? {
            // This lifetime edge depends on lifetimes: 'a
            val aEdges: MutableList<Any> = mutableListOf(curve);
            
            val returnVal = lib.ecitygml_LineString_try_from(curve.handle);
            val selfEdges: List<Any> = listOf(curve)
            val handle = returnVal ?: return null
            val returnOpaque = LineString(handle, selfEdges, false)
            return returnOpaque
        }
    }
    
    /** The object's `gml:id`, if it has one.
    */
    fun id(): Id? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_LineString_id(handle);
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
        
        val returnVal = lib.ecitygml_LineString_names(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = CodeIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    /** The positions (`gml:posList`).
    */
    fun points(): DirectPositionIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_LineString_points(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = DirectPositionIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }
    
    fun length3d(): Double {
        
        val returnVal = lib.ecitygml_LineString_length_3d(handle);
        return (returnVal)
    }
    
    /** Envelope computed from the geometry (Rust: `ComputeEnvelope::compute_envelope`).
    */
    fun computeEnvelope(): Envelope? {
        
        val returnVal = lib.ecitygml_LineString_compute_envelope(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal ?: return null
        val returnOpaque = Envelope(handle, selfEdges, true)
        return returnOpaque
    }

}