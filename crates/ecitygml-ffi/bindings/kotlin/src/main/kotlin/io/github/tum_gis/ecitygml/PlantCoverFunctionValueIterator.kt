package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface PlantCoverFunctionValueIteratorLib: Library {
    fun ecitygml_PlantCoverFunctionValueIterator_destroy(handle: Pointer)
    fun ecitygml_PlantCoverFunctionValueIterator_next(handle: Pointer): Pointer?
}
typealias PlantCoverFunctionValueIteratorIteratorItem = PlantCoverFunctionValue?
/** Iterates over a list of code-list values, borrowed from a city model.
*/
class PlantCoverFunctionValueIterator internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal val aEdges: List<Any?>,
    internal var owned: Boolean,
): Iterator<PlantCoverFunctionValue?> {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class PlantCoverFunctionValueIteratorCleaner(val handle: Pointer, val lib: PlantCoverFunctionValueIteratorLib) : Runnable {
        override fun run() {
            lib.ecitygml_PlantCoverFunctionValueIterator_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, PlantCoverFunctionValueIterator.PlantCoverFunctionValueIteratorCleaner(handle, PlantCoverFunctionValueIterator.lib));
    }

    companion object {
        internal val libClass: Class<PlantCoverFunctionValueIteratorLib> = PlantCoverFunctionValueIteratorLib::class.java
        internal val lib: PlantCoverFunctionValueIteratorLib = Native.load("ecitygml_ffi", libClass)
    }
    
    internal fun nextInternal(): PlantCoverFunctionValue? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_PlantCoverFunctionValueIterator_next(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = PlantCoverFunctionValue(handle, selfEdges, false)
        return returnOpaque
    }

    var iterVal = nextInternal()

    override fun hasNext(): Boolean {
       return iterVal != null
    }

    override fun next(): PlantCoverFunctionValue?{
        val returnVal = iterVal
        if (returnVal == null) {
            throw NoSuchElementException()
        } else {
            iterVal = nextInternal()
            return returnVal
        }
    }

}