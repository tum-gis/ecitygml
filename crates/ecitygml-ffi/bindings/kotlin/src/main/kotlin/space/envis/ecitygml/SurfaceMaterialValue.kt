package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface SurfaceMaterialValueLib: Library {
    fun ecitygml_SurfaceMaterialValue_destroy(handle: Pointer)
    fun ecitygml_SurfaceMaterialValue_code(handle: Pointer): Pointer
    fun ecitygml_SurfaceMaterialValue_value(handle: Pointer): Slice
}
/** The `surfaceMaterial` property of a TrafficArea or AuxiliaryTrafficArea.
*/
class SurfaceMaterialValue internal constructor (
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

    private class SurfaceMaterialValueCleaner(val handle: Pointer, val lib: SurfaceMaterialValueLib) : Runnable {
        override fun run() {
            lib.ecitygml_SurfaceMaterialValue_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, SurfaceMaterialValue.SurfaceMaterialValueCleaner(handle, SurfaceMaterialValue.lib));
    }

    companion object {
        internal val libClass: Class<SurfaceMaterialValueLib> = SurfaceMaterialValueLib::class.java
        internal val lib: SurfaceMaterialValueLib = Native.load("ecitygml_ffi", libClass)
    }
    
    fun code(): Code {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_SurfaceMaterialValue_code(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal 
        val returnOpaque = Code(handle, selfEdges, false)
        return returnOpaque
    }
    
    fun value(): String {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_SurfaceMaterialValue_value(handle);
            return PrimitiveArrayTools.getUtf8(returnVal)
    }

}