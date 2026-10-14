package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface SpeciesValueLib: Library {
    fun ecitygml_SpeciesValue_destroy(handle: Pointer)
    fun ecitygml_SpeciesValue_code(handle: Pointer): Pointer
    fun ecitygml_SpeciesValue_value(handle: Pointer): Slice
}
/** The `species` property of a SolitaryVegetationObject.
*/
class SpeciesValue internal constructor (
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

    private class SpeciesValueCleaner(val handle: Pointer, val lib: SpeciesValueLib) : Runnable {
        override fun run() {
            lib.ecitygml_SpeciesValue_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, SpeciesValue.SpeciesValueCleaner(handle, SpeciesValue.lib));
    }

    companion object {
        internal val libClass: Class<SpeciesValueLib> = SpeciesValueLib::class.java
        internal val lib: SpeciesValueLib = Native.load("ecitygml_ffi", libClass)
    }
    
    fun code(): Code {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_SpeciesValue_code(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal 
        val returnOpaque = Code(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun value(): String {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_SpeciesValue_value(handle);
            return PrimitiveArrayTools.getUtf8(returnVal)
    }

}