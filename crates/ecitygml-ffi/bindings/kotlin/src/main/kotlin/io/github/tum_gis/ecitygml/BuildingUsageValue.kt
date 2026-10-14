package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface BuildingUsageValueLib: Library {
    fun ecitygml_BuildingUsageValue_destroy(handle: Pointer)
    fun ecitygml_BuildingUsageValue_code(handle: Pointer): Pointer
    fun ecitygml_BuildingUsageValue_value(handle: Pointer): Slice
}
/** The `usage` property of a Building or BuildingPart.
*/
class BuildingUsageValue internal constructor (
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

    private class BuildingUsageValueCleaner(val handle: Pointer, val lib: BuildingUsageValueLib) : Runnable {
        override fun run() {
            lib.ecitygml_BuildingUsageValue_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, BuildingUsageValue.BuildingUsageValueCleaner(handle, BuildingUsageValue.lib));
    }

    companion object {
        internal val libClass: Class<BuildingUsageValueLib> = BuildingUsageValueLib::class.java
        internal val lib: BuildingUsageValueLib = Native.load("ecitygml_ffi", libClass)
    }
    
    fun code(): Code {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_BuildingUsageValue_code(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal 
        val returnOpaque = Code(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun value(): String {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_BuildingUsageValue_value(handle);
            return PrimitiveArrayTools.getUtf8(returnVal)
    }

}