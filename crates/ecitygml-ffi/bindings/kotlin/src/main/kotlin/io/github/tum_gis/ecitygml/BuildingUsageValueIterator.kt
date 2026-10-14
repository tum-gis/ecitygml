package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface BuildingUsageValueIteratorLib: Library {
    fun ecitygml_BuildingUsageValueIterator_destroy(handle: Pointer)
    fun ecitygml_BuildingUsageValueIterator_next(handle: Pointer): Pointer?
}
typealias BuildingUsageValueIteratorIteratorItem = BuildingUsageValue?
/** Iterates over a list of code-list values, borrowed from a city model.
*/
class BuildingUsageValueIterator internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal val aEdges: List<Any?>,
    internal var owned: Boolean,
): Iterator<BuildingUsageValue?> {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class BuildingUsageValueIteratorCleaner(val handle: Pointer, val lib: BuildingUsageValueIteratorLib) : Runnable {
        override fun run() {
            lib.ecitygml_BuildingUsageValueIterator_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, BuildingUsageValueIterator.BuildingUsageValueIteratorCleaner(handle, BuildingUsageValueIterator.lib));
    }

    companion object {
        internal val libClass: Class<BuildingUsageValueIteratorLib> = BuildingUsageValueIteratorLib::class.java
        internal val lib: BuildingUsageValueIteratorLib = Native.load("ecitygml_ffi", libClass)
    }
    
    internal fun nextInternal(): BuildingUsageValue? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_BuildingUsageValueIterator_next(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = BuildingUsageValue(handle, selfEdges, false)
        return returnOpaque
    }

    var iterVal = nextInternal()

    override fun hasNext(): Boolean {
       return iterVal != null
    }

    override fun next(): BuildingUsageValue?{
        val returnVal = iterVal
        if (returnVal == null) {
            throw NoSuchElementException()
        } else {
            iterVal = nextInternal()
            return returnVal
        }
    }

}