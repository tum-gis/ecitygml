package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface IntervalValueLib: Library {
    fun ecitygml_IntervalValue_destroy(handle: Pointer)
    fun ecitygml_IntervalValue_code(handle: Pointer): Pointer
    fun ecitygml_IntervalValue_value(handle: Pointer): Slice
}
/** The `interval` property of an Occupancy.
*/
class IntervalValue internal constructor (
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

    private class IntervalValueCleaner(val handle: Pointer, val lib: IntervalValueLib) : Runnable {
        override fun run() {
            lib.ecitygml_IntervalValue_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, IntervalValue.IntervalValueCleaner(handle, IntervalValue.lib));
    }

    companion object {
        internal val libClass: Class<IntervalValueLib> = IntervalValueLib::class.java
        internal val lib: IntervalValueLib = Native.load("ecitygml_ffi", libClass)
    }
    
    fun code(): Code {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_IntervalValue_code(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal 
        val returnOpaque = Code(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun value(): String {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_IntervalValue_value(handle);
            return PrimitiveArrayTools.getUtf8(returnVal)
    }

}