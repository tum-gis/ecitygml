package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface TrafficAreaFunctionValueLib: Library {
    fun ecitygml_TrafficAreaFunctionValue_destroy(handle: Pointer)
    fun ecitygml_TrafficAreaFunctionValue_code(handle: Pointer): Pointer
    fun ecitygml_TrafficAreaFunctionValue_value(handle: Pointer): Slice
}
/** The `function` property of a TrafficArea.
*/
class TrafficAreaFunctionValue internal constructor (
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

    private class TrafficAreaFunctionValueCleaner(val handle: Pointer, val lib: TrafficAreaFunctionValueLib) : Runnable {
        override fun run() {
            lib.ecitygml_TrafficAreaFunctionValue_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, TrafficAreaFunctionValue.TrafficAreaFunctionValueCleaner(handle, TrafficAreaFunctionValue.lib));
    }

    companion object {
        internal val libClass: Class<TrafficAreaFunctionValueLib> = TrafficAreaFunctionValueLib::class.java
        internal val lib: TrafficAreaFunctionValueLib = Native.load("ecitygml_ffi", libClass)
    }
    
    fun code(): Code {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_TrafficAreaFunctionValue_code(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal 
        val returnOpaque = Code(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun value(): String {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_TrafficAreaFunctionValue_value(handle);
            return PrimitiveArrayTools.getUtf8(returnVal)
    }

}