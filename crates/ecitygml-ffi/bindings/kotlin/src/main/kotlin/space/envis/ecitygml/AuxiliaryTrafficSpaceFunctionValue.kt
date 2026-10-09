package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface AuxiliaryTrafficSpaceFunctionValueLib: Library {
    fun ecitygml_AuxiliaryTrafficSpaceFunctionValue_destroy(handle: Pointer)
    fun ecitygml_AuxiliaryTrafficSpaceFunctionValue_code(handle: Pointer): Pointer
    fun ecitygml_AuxiliaryTrafficSpaceFunctionValue_value(handle: Pointer): Slice
}
/** The `function` property of an AuxiliaryTrafficSpace.
*/
class AuxiliaryTrafficSpaceFunctionValue internal constructor (
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

    private class AuxiliaryTrafficSpaceFunctionValueCleaner(val handle: Pointer, val lib: AuxiliaryTrafficSpaceFunctionValueLib) : Runnable {
        override fun run() {
            lib.ecitygml_AuxiliaryTrafficSpaceFunctionValue_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, AuxiliaryTrafficSpaceFunctionValue.AuxiliaryTrafficSpaceFunctionValueCleaner(handle, AuxiliaryTrafficSpaceFunctionValue.lib));
    }

    companion object {
        internal val libClass: Class<AuxiliaryTrafficSpaceFunctionValueLib> = AuxiliaryTrafficSpaceFunctionValueLib::class.java
        internal val lib: AuxiliaryTrafficSpaceFunctionValueLib = Native.load("ecitygml_ffi", libClass)
    }
    
    fun code(): Code {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AuxiliaryTrafficSpaceFunctionValue_code(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal 
        val returnOpaque = Code(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun value(): String {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AuxiliaryTrafficSpaceFunctionValue_value(handle);
            return PrimitiveArrayTools.getUtf8(returnVal)
    }

}