package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface AuxiliaryTrafficAreaFunctionValueLib: Library {
    fun ecitygml_AuxiliaryTrafficAreaFunctionValue_destroy(handle: Pointer)
    fun ecitygml_AuxiliaryTrafficAreaFunctionValue_code(handle: Pointer): Pointer
    fun ecitygml_AuxiliaryTrafficAreaFunctionValue_value(handle: Pointer): Slice
}
/** The `function` property of an AuxiliaryTrafficArea.
*/
class AuxiliaryTrafficAreaFunctionValue internal constructor (
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

    private class AuxiliaryTrafficAreaFunctionValueCleaner(val handle: Pointer, val lib: AuxiliaryTrafficAreaFunctionValueLib) : Runnable {
        override fun run() {
            lib.ecitygml_AuxiliaryTrafficAreaFunctionValue_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, AuxiliaryTrafficAreaFunctionValue.AuxiliaryTrafficAreaFunctionValueCleaner(handle, AuxiliaryTrafficAreaFunctionValue.lib));
    }

    companion object {
        internal val libClass: Class<AuxiliaryTrafficAreaFunctionValueLib> = AuxiliaryTrafficAreaFunctionValueLib::class.java
        internal val lib: AuxiliaryTrafficAreaFunctionValueLib = Native.load("ecitygml_ffi", libClass)
    }
    
    fun code(): Code {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AuxiliaryTrafficAreaFunctionValue_code(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal 
        val returnOpaque = Code(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun value(): String {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AuxiliaryTrafficAreaFunctionValue_value(handle);
            return PrimitiveArrayTools.getUtf8(returnVal)
    }

}