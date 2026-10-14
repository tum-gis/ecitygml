package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface BridgeUsageValueLib: Library {
    fun ecitygml_BridgeUsageValue_destroy(handle: Pointer)
    fun ecitygml_BridgeUsageValue_code(handle: Pointer): Pointer
    fun ecitygml_BridgeUsageValue_value(handle: Pointer): Slice
}
/** The `usage` property of a Bridge or BridgePart.
*/
class BridgeUsageValue internal constructor (
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

    private class BridgeUsageValueCleaner(val handle: Pointer, val lib: BridgeUsageValueLib) : Runnable {
        override fun run() {
            lib.ecitygml_BridgeUsageValue_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, BridgeUsageValue.BridgeUsageValueCleaner(handle, BridgeUsageValue.lib));
    }

    companion object {
        internal val libClass: Class<BridgeUsageValueLib> = BridgeUsageValueLib::class.java
        internal val lib: BridgeUsageValueLib = Native.load("ecitygml_ffi", libClass)
    }
    
    fun code(): Code {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_BridgeUsageValue_code(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal 
        val returnOpaque = Code(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun value(): String {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_BridgeUsageValue_value(handle);
            return PrimitiveArrayTools.getUtf8(returnVal)
    }

}