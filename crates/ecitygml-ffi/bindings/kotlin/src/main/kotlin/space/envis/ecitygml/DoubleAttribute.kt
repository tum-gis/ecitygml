package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface DoubleAttributeLib: Library {
    fun ecitygml_DoubleAttribute_destroy(handle: Pointer)
    fun ecitygml_DoubleAttribute_name(handle: Pointer): Slice
    fun ecitygml_DoubleAttribute_value(handle: Pointer): Double
}
/** A generic attribute with a floating-point value, borrowed from a city model.
*/
class DoubleAttribute internal constructor (
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

    private class DoubleAttributeCleaner(val handle: Pointer, val lib: DoubleAttributeLib) : Runnable {
        override fun run() {
            lib.ecitygml_DoubleAttribute_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, DoubleAttribute.DoubleAttributeCleaner(handle, DoubleAttribute.lib));
    }

    companion object {
        internal val libClass: Class<DoubleAttributeLib> = DoubleAttributeLib::class.java
        internal val lib: DoubleAttributeLib = Native.load("ecitygml_ffi", libClass)
    }
    
    fun name(): String {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_DoubleAttribute_name(handle);
            return PrimitiveArrayTools.getUtf8(returnVal)
    }
    
    fun value(): Double {
        
        val returnVal = lib.ecitygml_DoubleAttribute_value(handle);
        return (returnVal)
    }

}