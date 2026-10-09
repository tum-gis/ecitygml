package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface PlantCoverUsageValueLib: Library {
    fun ecitygml_PlantCoverUsageValue_destroy(handle: Pointer)
    fun ecitygml_PlantCoverUsageValue_code(handle: Pointer): Pointer
    fun ecitygml_PlantCoverUsageValue_value(handle: Pointer): Slice
}
/** The `usage` property of a PlantCover.
*/
class PlantCoverUsageValue internal constructor (
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

    private class PlantCoverUsageValueCleaner(val handle: Pointer, val lib: PlantCoverUsageValueLib) : Runnable {
        override fun run() {
            lib.ecitygml_PlantCoverUsageValue_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, PlantCoverUsageValue.PlantCoverUsageValueCleaner(handle, PlantCoverUsageValue.lib));
    }

    companion object {
        internal val libClass: Class<PlantCoverUsageValueLib> = PlantCoverUsageValueLib::class.java
        internal val lib: PlantCoverUsageValueLib = Native.load("ecitygml_ffi", libClass)
    }
    
    fun code(): Code {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_PlantCoverUsageValue_code(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal 
        val returnOpaque = Code(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun value(): String {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_PlantCoverUsageValue_value(handle);
            return PrimitiveArrayTools.getUtf8(returnVal)
    }

}