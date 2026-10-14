package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface OccupancyLib: Library {
    fun ecitygml_Occupancy_destroy(handle: Pointer)
    fun ecitygml_Occupancy_number_of_occupants(handle: Pointer): Long
    fun ecitygml_Occupancy_interval(handle: Pointer): Pointer?
    fun ecitygml_Occupancy_occupant_type(handle: Pointer): Pointer?
}
/** The number of occupants of a feature, borrowed from a city model.
*/
class Occupancy internal constructor (
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

    private class OccupancyCleaner(val handle: Pointer, val lib: OccupancyLib) : Runnable {
        override fun run() {
            lib.ecitygml_Occupancy_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, Occupancy.OccupancyCleaner(handle, Occupancy.lib));
    }

    companion object {
        internal val libClass: Class<OccupancyLib> = OccupancyLib::class.java
        internal val lib: OccupancyLib = Native.load("ecitygml_ffi", libClass)
    }
    
    fun numberOfOccupants(): Long {
        
        val returnVal = lib.ecitygml_Occupancy_number_of_occupants(handle);
        return (returnVal)
    }
    
    fun interval(): IntervalValue? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Occupancy_interval(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = IntervalValue(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun occupantType(): OccupantTypeValue? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Occupancy_occupant_type(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = OccupantTypeValue(handle, selfEdges, false)
        return returnOpaque
    }

}