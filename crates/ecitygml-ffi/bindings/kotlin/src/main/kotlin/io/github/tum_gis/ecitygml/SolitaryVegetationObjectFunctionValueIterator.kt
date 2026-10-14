package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface SolitaryVegetationObjectFunctionValueIteratorLib: Library {
    fun ecitygml_SolitaryVegetationObjectFunctionValueIterator_destroy(handle: Pointer)
    fun ecitygml_SolitaryVegetationObjectFunctionValueIterator_next(handle: Pointer): Pointer?
}
typealias SolitaryVegetationObjectFunctionValueIteratorIteratorItem = SolitaryVegetationObjectFunctionValue?
/** Iterates over a list of code-list values, borrowed from a city model.
*/
class SolitaryVegetationObjectFunctionValueIterator internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal val aEdges: List<Any?>,
    internal var owned: Boolean,
): Iterator<SolitaryVegetationObjectFunctionValue?> {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class SolitaryVegetationObjectFunctionValueIteratorCleaner(val handle: Pointer, val lib: SolitaryVegetationObjectFunctionValueIteratorLib) : Runnable {
        override fun run() {
            lib.ecitygml_SolitaryVegetationObjectFunctionValueIterator_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, SolitaryVegetationObjectFunctionValueIterator.SolitaryVegetationObjectFunctionValueIteratorCleaner(handle, SolitaryVegetationObjectFunctionValueIterator.lib));
    }

    companion object {
        internal val libClass: Class<SolitaryVegetationObjectFunctionValueIteratorLib> = SolitaryVegetationObjectFunctionValueIteratorLib::class.java
        internal val lib: SolitaryVegetationObjectFunctionValueIteratorLib = Native.load("ecitygml_ffi", libClass)
    }
    
    internal fun nextInternal(): SolitaryVegetationObjectFunctionValue? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_SolitaryVegetationObjectFunctionValueIterator_next(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = SolitaryVegetationObjectFunctionValue(handle, selfEdges, false)
        return returnOpaque
    }

    var iterVal = nextInternal()

    override fun hasNext(): Boolean {
       return iterVal != null
    }

    override fun next(): SolitaryVegetationObjectFunctionValue?{
        val returnVal = iterVal
        if (returnVal == null) {
            throw NoSuchElementException()
        } else {
            iterVal = nextInternal()
            return returnVal
        }
    }

}