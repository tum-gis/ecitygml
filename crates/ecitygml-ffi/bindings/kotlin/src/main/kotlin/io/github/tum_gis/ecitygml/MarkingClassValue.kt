package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface MarkingClassValueLib: Library {
    fun ecitygml_MarkingClassValue_destroy(handle: Pointer)
    fun ecitygml_MarkingClassValue_code(handle: Pointer): Pointer
    fun ecitygml_MarkingClassValue_value(handle: Pointer): Slice
}
/** The `class` property of a Marking.
*/
class MarkingClassValue internal constructor (
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

    private class MarkingClassValueCleaner(val handle: Pointer, val lib: MarkingClassValueLib) : Runnable {
        override fun run() {
            lib.ecitygml_MarkingClassValue_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, MarkingClassValue.MarkingClassValueCleaner(handle, MarkingClassValue.lib));
    }

    companion object {
        internal val libClass: Class<MarkingClassValueLib> = MarkingClassValueLib::class.java
        internal val lib: MarkingClassValueLib = Native.load("ecitygml_ffi", libClass)
    }
    
    fun code(): Code {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_MarkingClassValue_code(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal 
        val returnOpaque = Code(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun value(): String {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_MarkingClassValue_value(handle);
            return PrimitiveArrayTools.getUtf8(returnVal)
    }

}