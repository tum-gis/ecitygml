package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface CodeLib: Library {
    fun ecitygml_Code_destroy(handle: Pointer)
    fun ecitygml_Code_value(handle: Pointer): Slice
    fun ecitygml_Code_code_space(handle: Pointer): OptionSlice
}
/** A code-list value with an optional code space, borrowed from a city model.
*/
class Code internal constructor (
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

    private class CodeCleaner(val handle: Pointer, val lib: CodeLib) : Runnable {
        override fun run() {
            lib.ecitygml_Code_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, Code.CodeCleaner(handle, Code.lib));
    }

    companion object {
        internal val libClass: Class<CodeLib> = CodeLib::class.java
        internal val lib: CodeLib = Native.load("ecitygml_ffi", libClass)
    }
    
    fun value(): String {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Code_value(handle);
            return PrimitiveArrayTools.getUtf8(returnVal)
    }
    
    fun codeSpace(): String? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Code_code_space(handle);
        
        val intermediateOption = returnVal.option() ?: return null
            return PrimitiveArrayTools.getUtf8(intermediateOption)
                                
    }

}