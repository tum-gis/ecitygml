package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface RoofTypeValueLib: Library {
    fun ecitygml_RoofTypeValue_destroy(handle: Pointer)
    fun ecitygml_RoofTypeValue_code(handle: Pointer): Pointer
    fun ecitygml_RoofTypeValue_value(handle: Pointer): Slice
}
/** The `roofType` property of a Building or BuildingPart.
*/
class RoofTypeValue internal constructor (
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

    private class RoofTypeValueCleaner(val handle: Pointer, val lib: RoofTypeValueLib) : Runnable {
        override fun run() {
            lib.ecitygml_RoofTypeValue_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, RoofTypeValue.RoofTypeValueCleaner(handle, RoofTypeValue.lib));
    }

    companion object {
        internal val libClass: Class<RoofTypeValueLib> = RoofTypeValueLib::class.java
        internal val lib: RoofTypeValueLib = Native.load("ecitygml_ffi", libClass)
    }
    
    fun code(): Code {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_RoofTypeValue_code(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal 
        val returnOpaque = Code(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun value(): String {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_RoofTypeValue_value(handle);
            return PrimitiveArrayTools.getUtf8(returnVal)
    }

}