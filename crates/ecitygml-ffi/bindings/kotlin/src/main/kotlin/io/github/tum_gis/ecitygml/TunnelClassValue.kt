package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface TunnelClassValueLib: Library {
    fun ecitygml_TunnelClassValue_destroy(handle: Pointer)
    fun ecitygml_TunnelClassValue_code(handle: Pointer): Pointer
    fun ecitygml_TunnelClassValue_value(handle: Pointer): Slice
}
/** The `class` property of a Tunnel or TunnelPart.
*/
class TunnelClassValue internal constructor (
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

    private class TunnelClassValueCleaner(val handle: Pointer, val lib: TunnelClassValueLib) : Runnable {
        override fun run() {
            lib.ecitygml_TunnelClassValue_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, TunnelClassValue.TunnelClassValueCleaner(handle, TunnelClassValue.lib));
    }

    companion object {
        internal val libClass: Class<TunnelClassValueLib> = TunnelClassValueLib::class.java
        internal val lib: TunnelClassValueLib = Native.load("ecitygml_ffi", libClass)
    }
    
    fun code(): Code {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_TunnelClassValue_code(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal 
        val returnOpaque = Code(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun value(): String {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_TunnelClassValue_value(handle);
            return PrimitiveArrayTools.getUtf8(returnVal)
    }

}