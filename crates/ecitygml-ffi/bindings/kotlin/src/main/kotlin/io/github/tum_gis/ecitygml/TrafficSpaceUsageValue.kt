package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface TrafficSpaceUsageValueLib: Library {
    fun ecitygml_TrafficSpaceUsageValue_destroy(handle: Pointer)
    fun ecitygml_TrafficSpaceUsageValue_code(handle: Pointer): Pointer
    fun ecitygml_TrafficSpaceUsageValue_value(handle: Pointer): Slice
}
/** The `usage` property of a TrafficSpace.
*/
class TrafficSpaceUsageValue internal constructor (
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

    private class TrafficSpaceUsageValueCleaner(val handle: Pointer, val lib: TrafficSpaceUsageValueLib) : Runnable {
        override fun run() {
            lib.ecitygml_TrafficSpaceUsageValue_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, TrafficSpaceUsageValue.TrafficSpaceUsageValueCleaner(handle, TrafficSpaceUsageValue.lib));
    }

    companion object {
        internal val libClass: Class<TrafficSpaceUsageValueLib> = TrafficSpaceUsageValueLib::class.java
        internal val lib: TrafficSpaceUsageValueLib = Native.load("ecitygml_ffi", libClass)
    }
    
    fun code(): Code {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_TrafficSpaceUsageValue_code(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal 
        val returnOpaque = Code(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun value(): String {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_TrafficSpaceUsageValue_value(handle);
            return PrimitiveArrayTools.getUtf8(returnVal)
    }

}