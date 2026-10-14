package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface RoadClassValueLib: Library {
    fun ecitygml_RoadClassValue_destroy(handle: Pointer)
    fun ecitygml_RoadClassValue_code(handle: Pointer): Pointer
    fun ecitygml_RoadClassValue_value(handle: Pointer): Slice
}
/** The `class` property of a Road.
*/
class RoadClassValue internal constructor (
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

    private class RoadClassValueCleaner(val handle: Pointer, val lib: RoadClassValueLib) : Runnable {
        override fun run() {
            lib.ecitygml_RoadClassValue_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, RoadClassValue.RoadClassValueCleaner(handle, RoadClassValue.lib));
    }

    companion object {
        internal val libClass: Class<RoadClassValueLib> = RoadClassValueLib::class.java
        internal val lib: RoadClassValueLib = Native.load("ecitygml_ffi", libClass)
    }
    
    fun code(): Code {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_RoadClassValue_code(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal 
        val returnOpaque = Code(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun value(): String {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_RoadClassValue_value(handle);
            return PrimitiveArrayTools.getUtf8(returnVal)
    }

}