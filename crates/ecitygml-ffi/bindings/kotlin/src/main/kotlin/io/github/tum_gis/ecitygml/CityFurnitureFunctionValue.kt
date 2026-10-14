package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface CityFurnitureFunctionValueLib: Library {
    fun ecitygml_CityFurnitureFunctionValue_destroy(handle: Pointer)
    fun ecitygml_CityFurnitureFunctionValue_code(handle: Pointer): Pointer
    fun ecitygml_CityFurnitureFunctionValue_value(handle: Pointer): Slice
}
/** The `function` property of a CityFurniture.
*/
class CityFurnitureFunctionValue internal constructor (
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

    private class CityFurnitureFunctionValueCleaner(val handle: Pointer, val lib: CityFurnitureFunctionValueLib) : Runnable {
        override fun run() {
            lib.ecitygml_CityFurnitureFunctionValue_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, CityFurnitureFunctionValue.CityFurnitureFunctionValueCleaner(handle, CityFurnitureFunctionValue.lib));
    }

    companion object {
        internal val libClass: Class<CityFurnitureFunctionValueLib> = CityFurnitureFunctionValueLib::class.java
        internal val lib: CityFurnitureFunctionValueLib = Native.load("ecitygml_ffi", libClass)
    }
    
    fun code(): Code {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_CityFurnitureFunctionValue_code(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal 
        val returnOpaque = Code(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun value(): String {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_CityFurnitureFunctionValue_value(handle);
            return PrimitiveArrayTools.getUtf8(returnVal)
    }

}