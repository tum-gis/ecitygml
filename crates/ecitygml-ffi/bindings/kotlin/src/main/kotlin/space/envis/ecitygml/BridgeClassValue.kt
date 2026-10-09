package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface BridgeClassValueLib: Library {
    fun ecitygml_BridgeClassValue_destroy(handle: Pointer)
    fun ecitygml_BridgeClassValue_code(handle: Pointer): Pointer
    fun ecitygml_BridgeClassValue_value(handle: Pointer): Slice
}
/** The `class` property of a Bridge or BridgePart.
*/
class BridgeClassValue internal constructor (
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

    private class BridgeClassValueCleaner(val handle: Pointer, val lib: BridgeClassValueLib) : Runnable {
        override fun run() {
            lib.ecitygml_BridgeClassValue_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, BridgeClassValue.BridgeClassValueCleaner(handle, BridgeClassValue.lib));
    }

    companion object {
        internal val libClass: Class<BridgeClassValueLib> = BridgeClassValueLib::class.java
        internal val lib: BridgeClassValueLib = Native.load("ecitygml_ffi", libClass)
    }
    
    fun code(): Code {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_BridgeClassValue_code(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal 
        val returnOpaque = Code(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun value(): String {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_BridgeClassValue_value(handle);
            return PrimitiveArrayTools.getUtf8(returnVal)
    }

}