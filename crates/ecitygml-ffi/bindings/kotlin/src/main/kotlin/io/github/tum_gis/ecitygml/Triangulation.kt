package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface TriangulationLib: Library {
    fun ecitygml_Triangulation_destroy(handle: Pointer)
    fun ecitygml_Triangulation_surface(handle: Pointer): Pointer
    fun ecitygml_Triangulation_has_skipped(handle: Pointer): Byte
    fun ecitygml_Triangulation_skipped(handle: Pointer): Pointer
}
/** A triangulated surface and the members that couldn't be triangulated.
*/
class Triangulation internal constructor (
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

    private class TriangulationCleaner(val handle: Pointer, val lib: TriangulationLib) : Runnable {
        override fun run() {
            lib.ecitygml_Triangulation_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, Triangulation.TriangulationCleaner(handle, Triangulation.lib));
    }

    companion object {
        internal val libClass: Class<TriangulationLib> = TriangulationLib::class.java
        internal val lib: TriangulationLib = Native.load("ecitygml_ffi", libClass)
    }
    
    fun surface(): TriangulatedSurface {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Triangulation_surface(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal 
        val returnOpaque = TriangulatedSurface(handle, selfEdges, false)
        return returnOpaque
    }
    
    /** Whether some members couldn't be triangulated.
    */
    fun hasSkipped(): Boolean {
        
        val returnVal = lib.ecitygml_Triangulation_has_skipped(handle);
        return (returnVal > 0)
    }
    
    /** Why members couldn't be triangulated, one error each.
    */
    fun skipped(): TriangulationSkippedIterator {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_Triangulation_skipped(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal 
        val returnOpaque = TriangulationSkippedIterator(handle, selfEdges, aEdges, true)
        return returnOpaque
    }

}