package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface AuxiliaryTrafficAreaUsageValueLib: Library {
    fun ecitygml_AuxiliaryTrafficAreaUsageValue_destroy(handle: Pointer)
    fun ecitygml_AuxiliaryTrafficAreaUsageValue_code(handle: Pointer): Pointer
    fun ecitygml_AuxiliaryTrafficAreaUsageValue_value(handle: Pointer): Slice
}
/** The `usage` property of an AuxiliaryTrafficArea.
*/
class AuxiliaryTrafficAreaUsageValue internal constructor (
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

    private class AuxiliaryTrafficAreaUsageValueCleaner(val handle: Pointer, val lib: AuxiliaryTrafficAreaUsageValueLib) : Runnable {
        override fun run() {
            lib.ecitygml_AuxiliaryTrafficAreaUsageValue_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, AuxiliaryTrafficAreaUsageValue.AuxiliaryTrafficAreaUsageValueCleaner(handle, AuxiliaryTrafficAreaUsageValue.lib));
    }

    companion object {
        internal val libClass: Class<AuxiliaryTrafficAreaUsageValueLib> = AuxiliaryTrafficAreaUsageValueLib::class.java
        internal val lib: AuxiliaryTrafficAreaUsageValueLib = Native.load("ecitygml_ffi", libClass)
    }
    
    fun code(): Code {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AuxiliaryTrafficAreaUsageValue_code(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal 
        val returnOpaque = Code(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun value(): String {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AuxiliaryTrafficAreaUsageValue_value(handle);
            return PrimitiveArrayTools.getUtf8(returnVal)
    }

}