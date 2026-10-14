package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface StringAttributeLib: Library {
    fun ecitygml_StringAttribute_destroy(handle: Pointer)
    fun ecitygml_StringAttribute_name(handle: Pointer): Slice
    fun ecitygml_StringAttribute_value(handle: Pointer): Slice
}
/** A generic attribute with a text value, borrowed from a city model.
*/
class StringAttribute internal constructor (
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

    private class StringAttributeCleaner(val handle: Pointer, val lib: StringAttributeLib) : Runnable {
        override fun run() {
            lib.ecitygml_StringAttribute_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, StringAttribute.StringAttributeCleaner(handle, StringAttribute.lib));
    }

    companion object {
        internal val libClass: Class<StringAttributeLib> = StringAttributeLib::class.java
        internal val lib: StringAttributeLib = Native.load("ecitygml_ffi", libClass)
    }
    
    fun name(): String {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_StringAttribute_name(handle);
            return PrimitiveArrayTools.getUtf8(returnVal)
    }
    
    fun value(): String {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_StringAttribute_value(handle);
            return PrimitiveArrayTools.getUtf8(returnVal)
    }

}