package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface TrafficAreaUsageValueIteratorLib: Library {
    fun ecitygml_TrafficAreaUsageValueIterator_destroy(handle: Pointer)
    fun ecitygml_TrafficAreaUsageValueIterator_next(handle: Pointer): Pointer?
}
typealias TrafficAreaUsageValueIteratorIteratorItem = TrafficAreaUsageValue?
/** Iterates over a list of code-list values, borrowed from a city model.
*/
class TrafficAreaUsageValueIterator internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal val aEdges: List<Any?>,
    internal var owned: Boolean,
): Iterator<TrafficAreaUsageValue?> {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class TrafficAreaUsageValueIteratorCleaner(val handle: Pointer, val lib: TrafficAreaUsageValueIteratorLib) : Runnable {
        override fun run() {
            lib.ecitygml_TrafficAreaUsageValueIterator_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, TrafficAreaUsageValueIterator.TrafficAreaUsageValueIteratorCleaner(handle, TrafficAreaUsageValueIterator.lib));
    }

    companion object {
        internal val libClass: Class<TrafficAreaUsageValueIteratorLib> = TrafficAreaUsageValueIteratorLib::class.java
        internal val lib: TrafficAreaUsageValueIteratorLib = Native.load("ecitygml_ffi", libClass)
    }
    
    internal fun nextInternal(): TrafficAreaUsageValue? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_TrafficAreaUsageValueIterator_next(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = TrafficAreaUsageValue(handle, selfEdges, false)
        return returnOpaque
    }

    var iterVal = nextInternal()

    override fun hasNext(): Boolean {
       return iterVal != null
    }

    override fun next(): TrafficAreaUsageValue?{
        val returnVal = iterVal
        if (returnVal == null) {
            throw NoSuchElementException()
        } else {
            iterVal = nextInternal()
            return returnVal
        }
    }

}