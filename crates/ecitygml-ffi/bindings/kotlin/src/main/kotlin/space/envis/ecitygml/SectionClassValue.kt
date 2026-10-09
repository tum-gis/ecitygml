package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface SectionClassValueLib: Library {
    fun ecitygml_SectionClassValue_destroy(handle: Pointer)
    fun ecitygml_SectionClassValue_code(handle: Pointer): Pointer
    fun ecitygml_SectionClassValue_value(handle: Pointer): Slice
}
/** The `class` property of a Section.
*/
class SectionClassValue internal constructor (
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

    private class SectionClassValueCleaner(val handle: Pointer, val lib: SectionClassValueLib) : Runnable {
        override fun run() {
            lib.ecitygml_SectionClassValue_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, SectionClassValue.SectionClassValueCleaner(handle, SectionClassValue.lib));
    }

    companion object {
        internal val libClass: Class<SectionClassValueLib> = SectionClassValueLib::class.java
        internal val lib: SectionClassValueLib = Native.load("ecitygml_ffi", libClass)
    }
    
    fun code(): Code {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_SectionClassValue_code(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal 
        val returnOpaque = Code(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun value(): String {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_SectionClassValue_value(handle);
            return PrimitiveArrayTools.getUtf8(returnVal)
    }

}