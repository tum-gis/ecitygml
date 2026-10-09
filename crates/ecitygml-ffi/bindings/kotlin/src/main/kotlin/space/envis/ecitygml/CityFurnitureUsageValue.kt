package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface CityFurnitureUsageValueLib: Library {
    fun ecitygml_CityFurnitureUsageValue_destroy(handle: Pointer)
    fun ecitygml_CityFurnitureUsageValue_code(handle: Pointer): Pointer
    fun ecitygml_CityFurnitureUsageValue_value(handle: Pointer): Slice
}
/** The `usage` property of a CityFurniture.
*/
class CityFurnitureUsageValue internal constructor (
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

    private class CityFurnitureUsageValueCleaner(val handle: Pointer, val lib: CityFurnitureUsageValueLib) : Runnable {
        override fun run() {
            lib.ecitygml_CityFurnitureUsageValue_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, CityFurnitureUsageValue.CityFurnitureUsageValueCleaner(handle, CityFurnitureUsageValue.lib));
    }

    companion object {
        internal val libClass: Class<CityFurnitureUsageValueLib> = CityFurnitureUsageValueLib::class.java
        internal val lib: CityFurnitureUsageValueLib = Native.load("ecitygml_ffi", libClass)
    }
    
    fun code(): Code {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_CityFurnitureUsageValue_code(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal 
        val returnOpaque = Code(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun value(): String {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_CityFurnitureUsageValue_value(handle);
            return PrimitiveArrayTools.getUtf8(returnVal)
    }

}