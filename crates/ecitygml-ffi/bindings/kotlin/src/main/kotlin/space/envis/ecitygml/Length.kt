package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface LengthLib: Library {
    fun ecitygml_Length_destroy(handle: Pointer)
    fun ecitygml_Length_value(handle: Pointer): Double
    fun ecitygml_Length_uom(handle: Pointer): Slice
}
/** A length with its unit of measure, borrowed from a city model.
*/
class Length internal constructor (
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

    private class LengthCleaner(val handle: Pointer, val lib: LengthLib) : Runnable {
        override fun run() {
            lib.ecitygml_Length_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, Length.LengthCleaner(handle, Length.lib));
    }

    companion object {
        internal val libClass: Class<LengthLib> = LengthLib::class.java
        internal val lib: LengthLib = Native.load("ecitygml_ffi", libClass)
    }
    
    fun value(): Double {
        
        val returnVal = lib.ecitygml_Length_value(handle);
        return (returnVal)
    }
    
    /** Unit of measure (`uom`), e.g. `m`.
    */
    fun uom(): String {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Length_uom(handle);
            return PrimitiveArrayTools.getUtf8(returnVal)
    }

}