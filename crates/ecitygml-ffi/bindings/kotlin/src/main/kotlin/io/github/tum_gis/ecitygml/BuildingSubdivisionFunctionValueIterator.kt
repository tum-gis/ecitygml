package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface BuildingSubdivisionFunctionValueIteratorLib: Library {
    fun ecitygml_BuildingSubdivisionFunctionValueIterator_destroy(handle: Pointer)
    fun ecitygml_BuildingSubdivisionFunctionValueIterator_next(handle: Pointer): Pointer?
}
typealias BuildingSubdivisionFunctionValueIteratorIteratorItem = BuildingSubdivisionFunctionValue?
/** Iterates over a list of code-list values, borrowed from a city model.
*/
class BuildingSubdivisionFunctionValueIterator internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal val aEdges: List<Any?>,
    internal var owned: Boolean,
): Iterator<BuildingSubdivisionFunctionValue?> {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class BuildingSubdivisionFunctionValueIteratorCleaner(val handle: Pointer, val lib: BuildingSubdivisionFunctionValueIteratorLib) : Runnable {
        override fun run() {
            lib.ecitygml_BuildingSubdivisionFunctionValueIterator_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, BuildingSubdivisionFunctionValueIterator.BuildingSubdivisionFunctionValueIteratorCleaner(handle, BuildingSubdivisionFunctionValueIterator.lib));
    }

    companion object {
        internal val libClass: Class<BuildingSubdivisionFunctionValueIteratorLib> = BuildingSubdivisionFunctionValueIteratorLib::class.java
        internal val lib: BuildingSubdivisionFunctionValueIteratorLib = Native.load("ecitygml_ffi", libClass)
    }
    
    internal fun nextInternal(): BuildingSubdivisionFunctionValue? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_BuildingSubdivisionFunctionValueIterator_next(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = BuildingSubdivisionFunctionValue(handle, selfEdges, false)
        return returnOpaque
    }

    var iterVal = nextInternal()

    override fun hasNext(): Boolean {
       return iterVal != null
    }

    override fun next(): BuildingSubdivisionFunctionValue?{
        val returnVal = iterVal
        if (returnVal == null) {
            throw NoSuchElementException()
        } else {
            iterVal = nextInternal()
            return returnVal
        }
    }

}