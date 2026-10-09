package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface MeasureAttributeLib: Library {
    fun ecitygml_MeasureAttribute_destroy(handle: Pointer)
    fun ecitygml_MeasureAttribute_try_from(attribute: Pointer): Pointer?
    fun ecitygml_MeasureAttribute_name(handle: Pointer): Slice
    fun ecitygml_MeasureAttribute_value(handle: Pointer): Pointer
}
/** A generic attribute with a value and unit of measure, borrowed from a city model.
*/
class MeasureAttribute internal constructor (
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

    private class MeasureAttributeCleaner(val handle: Pointer, val lib: MeasureAttributeLib) : Runnable {
        override fun run() {
            lib.ecitygml_MeasureAttribute_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, MeasureAttribute.MeasureAttributeCleaner(handle, MeasureAttribute.lib));
    }

    companion object {
        internal val libClass: Class<MeasureAttributeLib> = MeasureAttributeLib::class.java
        internal val lib: MeasureAttributeLib = Native.load("ecitygml_ffi", libClass)
        @JvmStatic
        
        /** The attribute as a measure attribute, or none if it is another kind (Rust has no
        *`as_measure`; it matches `GenericAttributeKind::MeasureAttribute`).
        */
        fun tryFrom(attribute: GenericAttributeKind): MeasureAttribute? {
            // This lifetime edge depends on lifetimes: 'a
            val aEdges: MutableList<Any> = mutableListOf(attribute);
            
            val returnVal = lib.ecitygml_MeasureAttribute_try_from(attribute.handle);
            val selfEdges: List<Any> = listOf(attribute)
            val handle = returnVal ?: return null
            val returnOpaque = MeasureAttribute(handle, selfEdges, false)
            return returnOpaque
        }
    }
    
    fun name(): String {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_MeasureAttribute_name(handle);
            return PrimitiveArrayTools.getUtf8(returnVal)
    }
    
    fun value(): Measure {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_MeasureAttribute_value(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal 
        val returnOpaque = Measure(handle, selfEdges, false)
        return returnOpaque
    }

}