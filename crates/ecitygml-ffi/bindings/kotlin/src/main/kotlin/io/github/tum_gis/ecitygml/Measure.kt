package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface MeasureLib: Library {
    fun ecitygml_Measure_destroy(handle: Pointer)
    fun ecitygml_Measure_value(handle: Pointer): Double
    fun ecitygml_Measure_uom(handle: Pointer): Slice
}
/** A numeric value with its unit of measure, borrowed from a city model.
*/
class Measure internal constructor (
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

    private class MeasureCleaner(val handle: Pointer, val lib: MeasureLib) : Runnable {
        override fun run() {
            lib.ecitygml_Measure_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, Measure.MeasureCleaner(handle, Measure.lib));
    }

    companion object {
        internal val libClass: Class<MeasureLib> = MeasureLib::class.java
        internal val lib: MeasureLib = Native.load("ecitygml_ffi", libClass)
    }
    
    fun value(): Double {
        
        val returnVal = lib.ecitygml_Measure_value(handle);
        return (returnVal)
    }
    
    /** Unit of measure (`uom`), e.g. `m2`.
    */
    fun uom(): String {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Measure_uom(handle);
            return PrimitiveArrayTools.getUtf8(returnVal)
    }

}