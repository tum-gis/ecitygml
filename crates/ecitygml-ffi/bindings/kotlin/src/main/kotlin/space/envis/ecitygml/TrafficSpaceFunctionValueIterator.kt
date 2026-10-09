package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface TrafficSpaceFunctionValueIteratorLib: Library {
    fun ecitygml_TrafficSpaceFunctionValueIterator_destroy(handle: Pointer)
    fun ecitygml_TrafficSpaceFunctionValueIterator_next(handle: Pointer): Pointer?
}
typealias TrafficSpaceFunctionValueIteratorIteratorItem = TrafficSpaceFunctionValue?
/** Iterates over a list of code-list values, borrowed from a city model.
*/
class TrafficSpaceFunctionValueIterator internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal val aEdges: List<Any?>,
    internal var owned: Boolean,
): Iterator<TrafficSpaceFunctionValue?> {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class TrafficSpaceFunctionValueIteratorCleaner(val handle: Pointer, val lib: TrafficSpaceFunctionValueIteratorLib) : Runnable {
        override fun run() {
            lib.ecitygml_TrafficSpaceFunctionValueIterator_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, TrafficSpaceFunctionValueIterator.TrafficSpaceFunctionValueIteratorCleaner(handle, TrafficSpaceFunctionValueIterator.lib));
    }

    companion object {
        internal val libClass: Class<TrafficSpaceFunctionValueIteratorLib> = TrafficSpaceFunctionValueIteratorLib::class.java
        internal val lib: TrafficSpaceFunctionValueIteratorLib = Native.load("ecitygml_ffi", libClass)
    }
    
    internal fun nextInternal(): TrafficSpaceFunctionValue? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_TrafficSpaceFunctionValueIterator_next(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = TrafficSpaceFunctionValue(handle, selfEdges, false)
        return returnOpaque
    }

    var iterVal = nextInternal()

    override fun hasNext(): Boolean {
       return iterVal != null
    }

    override fun next(): TrafficSpaceFunctionValue?{
        val returnVal = iterVal
        if (returnVal == null) {
            throw NoSuchElementException()
        } else {
            iterVal = nextInternal()
            return returnVal
        }
    }

}