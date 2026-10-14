package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface TrafficAreaFunctionValueIteratorLib: Library {
    fun ecitygml_TrafficAreaFunctionValueIterator_destroy(handle: Pointer)
    fun ecitygml_TrafficAreaFunctionValueIterator_next(handle: Pointer): Pointer?
}
typealias TrafficAreaFunctionValueIteratorIteratorItem = TrafficAreaFunctionValue?
/** Iterates over a list of code-list values, borrowed from a city model.
*/
class TrafficAreaFunctionValueIterator internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal val aEdges: List<Any?>,
    internal var owned: Boolean,
): Iterator<TrafficAreaFunctionValue?> {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class TrafficAreaFunctionValueIteratorCleaner(val handle: Pointer, val lib: TrafficAreaFunctionValueIteratorLib) : Runnable {
        override fun run() {
            lib.ecitygml_TrafficAreaFunctionValueIterator_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, TrafficAreaFunctionValueIterator.TrafficAreaFunctionValueIteratorCleaner(handle, TrafficAreaFunctionValueIterator.lib));
    }

    companion object {
        internal val libClass: Class<TrafficAreaFunctionValueIteratorLib> = TrafficAreaFunctionValueIteratorLib::class.java
        internal val lib: TrafficAreaFunctionValueIteratorLib = Native.load("ecitygml_ffi", libClass)
    }
    
    internal fun nextInternal(): TrafficAreaFunctionValue? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_TrafficAreaFunctionValueIterator_next(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = TrafficAreaFunctionValue(handle, selfEdges, false)
        return returnOpaque
    }

    var iterVal = nextInternal()

    override fun hasNext(): Boolean {
       return iterVal != null
    }

    override fun next(): TrafficAreaFunctionValue?{
        val returnVal = iterVal
        if (returnVal == null) {
            throw NoSuchElementException()
        } else {
            iterVal = nextInternal()
            return returnVal
        }
    }

}