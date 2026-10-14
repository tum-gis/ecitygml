package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface RoadFunctionValueLib: Library {
    fun ecitygml_RoadFunctionValue_destroy(handle: Pointer)
    fun ecitygml_RoadFunctionValue_code(handle: Pointer): Pointer
    fun ecitygml_RoadFunctionValue_value(handle: Pointer): Slice
}
/** The `function` property of a Road.
*/
class RoadFunctionValue internal constructor (
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

    private class RoadFunctionValueCleaner(val handle: Pointer, val lib: RoadFunctionValueLib) : Runnable {
        override fun run() {
            lib.ecitygml_RoadFunctionValue_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, RoadFunctionValue.RoadFunctionValueCleaner(handle, RoadFunctionValue.lib));
    }

    companion object {
        internal val libClass: Class<RoadFunctionValueLib> = RoadFunctionValueLib::class.java
        internal val lib: RoadFunctionValueLib = Native.load("ecitygml_ffi", libClass)
    }
    
    fun code(): Code {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_RoadFunctionValue_code(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal 
        val returnOpaque = Code(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun value(): String {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_RoadFunctionValue_value(handle);
            return PrimitiveArrayTools.getUtf8(returnVal)
    }

}