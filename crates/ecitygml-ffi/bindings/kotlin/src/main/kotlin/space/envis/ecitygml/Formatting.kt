package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface FormattingLib: Library {
    fun ecitygml_Formatting_destroy(handle: Pointer)
    fun ecitygml_Formatting_compact(): Pointer
    fun ecitygml_Formatting_new_line(): Pointer
    fun ecitygml_Formatting_indent(char: FFIUint8, size: FFISizet): Pointer
}
/** How written GML is laid out. Rust's enum variant `Indent` carries data, which Diplomat enums
*can't, so each variant is a named constructor.
*/
class Formatting internal constructor (
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

    private class FormattingCleaner(val handle: Pointer, val lib: FormattingLib) : Runnable {
        override fun run() {
            lib.ecitygml_Formatting_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, Formatting.FormattingCleaner(handle, Formatting.lib));
    }

    companion object {
        internal val libClass: Class<FormattingLib> = FormattingLib::class.java
        internal val lib: FormattingLib = Native.load("ecitygml_ffi", libClass)
        @JvmStatic
        
        /** All elements on a single line, without whitespace between them.
        */
        fun compact(): Formatting {
            
            val returnVal = lib.ecitygml_Formatting_compact();
            val selfEdges: List<Any> = listOf()
            val handle = returnVal 
            val returnOpaque = Formatting(handle, selfEdges, true)
            return returnOpaque
        }
        @JvmStatic
        
        /** Each element on its own line, without indentation (the default).
        */
        fun newLine(): Formatting {
            
            val returnVal = lib.ecitygml_Formatting_new_line();
            val selfEdges: List<Any> = listOf()
            val handle = returnVal 
            val returnOpaque = Formatting(handle, selfEdges, true)
            return returnOpaque
        }
        @JvmStatic
        
        /** Each element on its own line, indented by `size` repetitions of the byte `char`, e.g.
        *`b' '` and 2.
        */
        fun indent(char: UByte, size: ULong): Formatting {
            
            val returnVal = lib.ecitygml_Formatting_indent(FFIUint8(char), FFISizet(size));
            val selfEdges: List<Any> = listOf()
            val handle = returnVal 
            val returnOpaque = Formatting(handle, selfEdges, true)
            return returnOpaque
        }
    }

}