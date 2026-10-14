package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface BuildingSubdivisionUsageValueIteratorLib: Library {
    fun ecitygml_BuildingSubdivisionUsageValueIterator_destroy(handle: Pointer)
    fun ecitygml_BuildingSubdivisionUsageValueIterator_next(handle: Pointer): Pointer?
}
typealias BuildingSubdivisionUsageValueIteratorIteratorItem = BuildingSubdivisionUsageValue?
/** Iterates over a list of code-list values, borrowed from a city model.
*/
class BuildingSubdivisionUsageValueIterator internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal val aEdges: List<Any?>,
    internal var owned: Boolean,
): Iterator<BuildingSubdivisionUsageValue?> {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class BuildingSubdivisionUsageValueIteratorCleaner(val handle: Pointer, val lib: BuildingSubdivisionUsageValueIteratorLib) : Runnable {
        override fun run() {
            lib.ecitygml_BuildingSubdivisionUsageValueIterator_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, BuildingSubdivisionUsageValueIterator.BuildingSubdivisionUsageValueIteratorCleaner(handle, BuildingSubdivisionUsageValueIterator.lib));
    }

    companion object {
        internal val libClass: Class<BuildingSubdivisionUsageValueIteratorLib> = BuildingSubdivisionUsageValueIteratorLib::class.java
        internal val lib: BuildingSubdivisionUsageValueIteratorLib = Native.load("ecitygml_ffi", libClass)
    }
    
    internal fun nextInternal(): BuildingSubdivisionUsageValue? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_BuildingSubdivisionUsageValueIterator_next(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = BuildingSubdivisionUsageValue(handle, selfEdges, false)
        return returnOpaque
    }

    var iterVal = nextInternal()

    override fun hasNext(): Boolean {
       return iterVal != null
    }

    override fun next(): BuildingSubdivisionUsageValue?{
        val returnVal = iterVal
        if (returnVal == null) {
            throw NoSuchElementException()
        } else {
            iterVal = nextInternal()
            return returnVal
        }
    }

}