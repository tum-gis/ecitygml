package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface GenericAttributeSetLib: Library {
    fun ecitygml_GenericAttributeSet_destroy(handle: Pointer)
    fun ecitygml_GenericAttributeSet_try_from(attribute: Pointer): Pointer?
    fun ecitygml_GenericAttributeSet_name(handle: Pointer): Slice
    fun ecitygml_GenericAttributeSet_generic_attributes(handle: Pointer): Pointer
}
/** A named set of generic attributes, borrowed from a city model.
*/
class GenericAttributeSet internal constructor (
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

    private class GenericAttributeSetCleaner(val handle: Pointer, val lib: GenericAttributeSetLib) : Runnable {
        override fun run() {
            lib.ecitygml_GenericAttributeSet_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, GenericAttributeSet.GenericAttributeSetCleaner(handle, GenericAttributeSet.lib));
    }

    companion object {
        internal val libClass: Class<GenericAttributeSetLib> = GenericAttributeSetLib::class.java
        internal val lib: GenericAttributeSetLib = Native.load("ecitygml_ffi", libClass)
        @JvmStatic
        
        /** The attribute as a set, or none if it is another kind (Rust has no `as_set`; it matches
        *`GenericAttributeKind::GenericAttributeSet`).
        */
        fun tryFrom(attribute: GenericAttributeKind): GenericAttributeSet? {
            // This lifetime edge depends on lifetimes: 'a
            val aEdges: MutableList<Any> = mutableListOf(attribute);
            
            val returnVal = lib.ecitygml_GenericAttributeSet_try_from(attribute.handle);
            val selfEdges: List<Any> = listOf(attribute)
            val handle = returnVal ?: return null
            val returnOpaque = GenericAttributeSet(handle, selfEdges, false)
            return returnOpaque
        }
    }
    
    fun name(): String {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_GenericAttributeSet_name(handle);
            return PrimitiveArrayTools.getUtf8(returnVal)
    }
    
    fun genericAttributes(): GenericAttributeKindIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_GenericAttributeSet_generic_attributes(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = GenericAttributeKindIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }

}