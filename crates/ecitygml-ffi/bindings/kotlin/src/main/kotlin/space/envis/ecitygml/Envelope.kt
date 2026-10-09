package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface EnvelopeLib: Library {
    fun ecitygml_Envelope_destroy(handle: Pointer)
    fun ecitygml_Envelope_lower_corner(handle: Pointer): Pointer
    fun ecitygml_Envelope_upper_corner(handle: Pointer): Pointer
    fun ecitygml_Envelope_size_x(handle: Pointer): Double
    fun ecitygml_Envelope_size_y(handle: Pointer): Double
    fun ecitygml_Envelope_size_z(handle: Pointer): Double
    fun ecitygml_Envelope_volume(handle: Pointer): Double
    fun ecitygml_Envelope_contains(handle: Pointer, point: Pointer): Byte
}
/** An axis-aligned bounding box, borrowed from a city model.
*/
class Envelope internal constructor (
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

    private class EnvelopeCleaner(val handle: Pointer, val lib: EnvelopeLib) : Runnable {
        override fun run() {
            lib.ecitygml_Envelope_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, Envelope.EnvelopeCleaner(handle, Envelope.lib));
    }

    companion object {
        internal val libClass: Class<EnvelopeLib> = EnvelopeLib::class.java
        internal val lib: EnvelopeLib = Native.load("ecitygml_ffi", libClass)
    }
    
    fun lowerCorner(): DirectPosition {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Envelope_lower_corner(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal 
        val returnOpaque = DirectPosition(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun upperCorner(): DirectPosition {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Envelope_upper_corner(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal 
        val returnOpaque = DirectPosition(handle, selfEdges, false)
        return returnOpaque
    }
    
    /** Extent along the x axis.
    */
    fun sizeX(): Double {
        
        val returnVal = lib.ecitygml_Envelope_size_x(handle);
        return (returnVal)
    }
    
    /** Extent along the y axis.
    */
    fun sizeY(): Double {
        
        val returnVal = lib.ecitygml_Envelope_size_y(handle);
        return (returnVal)
    }
    
    /** Extent along the z axis.
    */
    fun sizeZ(): Double {
        
        val returnVal = lib.ecitygml_Envelope_size_z(handle);
        return (returnVal)
    }
    
    /** Volume of the box (`size_x * size_y * size_z`); `0.0` if an extent is zero.
    */
    fun volume(): Double {
        
        val returnVal = lib.ecitygml_Envelope_volume(handle);
        return (returnVal)
    }
    
    /** Whether `point` lies inside or on the boundary of the box.
    */
    fun contains(point: DirectPosition): Boolean {
        
        val returnVal = lib.ecitygml_Envelope_contains(handle, point.handle);
        return (returnVal > 0)
    }

}