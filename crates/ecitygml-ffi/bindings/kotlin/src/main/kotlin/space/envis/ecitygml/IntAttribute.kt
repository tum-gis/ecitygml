package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface IntAttributeLib: Library {
    fun ecitygml_IntAttribute_destroy(handle: Pointer)
    fun ecitygml_IntAttribute_name(handle: Pointer): Slice
    fun ecitygml_IntAttribute_value(handle: Pointer): Long
}
/** A generic attribute with an integer value, borrowed from a city model.
*/
class IntAttribute internal constructor (
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

    private class IntAttributeCleaner(val handle: Pointer, val lib: IntAttributeLib) : Runnable {
        override fun run() {
            lib.ecitygml_IntAttribute_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, IntAttribute.IntAttributeCleaner(handle, IntAttribute.lib));
    }

    companion object {
        internal val libClass: Class<IntAttributeLib> = IntAttributeLib::class.java
        internal val lib: IntAttributeLib = Native.load("ecitygml_ffi", libClass)
    }
    
    fun name(): String {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_IntAttribute_name(handle);
            return PrimitiveArrayTools.getUtf8(returnVal)
    }
    
    fun value(): Long {
        
        val returnVal = lib.ecitygml_IntAttribute_value(handle);
        return (returnVal)
    }

}