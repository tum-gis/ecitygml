package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface GenericAttributeKindLib: Library {
    fun ecitygml_GenericAttributeKind_destroy(handle: Pointer)
    fun ecitygml_GenericAttributeKind_name(handle: Pointer): Slice
    fun ecitygml_GenericAttributeKind_as_string(handle: Pointer): Pointer?
    fun ecitygml_GenericAttributeKind_as_int(handle: Pointer): Pointer?
    fun ecitygml_GenericAttributeKind_as_double(handle: Pointer): Pointer?
}
/** A generic attribute of any kind, borrowed from a city model; get its value with `as_string`,
*`as_int`, `as_double`, `MeasureAttribute::try_from` or `GenericAttributeSet::try_from`.
*/
class GenericAttributeKind internal constructor (
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

    private class GenericAttributeKindCleaner(val handle: Pointer, val lib: GenericAttributeKindLib) : Runnable {
        override fun run() {
            lib.ecitygml_GenericAttributeKind_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, GenericAttributeKind.GenericAttributeKindCleaner(handle, GenericAttributeKind.lib));
    }

    companion object {
        internal val libClass: Class<GenericAttributeKindLib> = GenericAttributeKindLib::class.java
        internal val lib: GenericAttributeKindLib = Native.load("ecitygml_ffi", libClass)
    }
    
    fun name(): String {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_GenericAttributeKind_name(handle);
            return PrimitiveArrayTools.getUtf8(returnVal)
    }
    
    fun asString(): StringAttribute? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_GenericAttributeKind_as_string(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = StringAttribute(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun asInt(): IntAttribute? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_GenericAttributeKind_as_int(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = IntAttribute(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun asDouble(): DoubleAttribute? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_GenericAttributeKind_as_double(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = DoubleAttribute(handle, selfEdges, false)
        return returnOpaque
    }

}