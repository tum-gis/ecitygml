package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface TrafficSpaceUsageValueIteratorLib: Library {
    fun ecitygml_TrafficSpaceUsageValueIterator_destroy(handle: Pointer)
    fun ecitygml_TrafficSpaceUsageValueIterator_next(handle: Pointer): Pointer?
}
typealias TrafficSpaceUsageValueIteratorIteratorItem = TrafficSpaceUsageValue?
/** Iterates over a list of code-list values, borrowed from a city model.
*/
class TrafficSpaceUsageValueIterator internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal val aEdges: List<Any?>,
    internal var owned: Boolean,
): Iterator<TrafficSpaceUsageValue?> {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class TrafficSpaceUsageValueIteratorCleaner(val handle: Pointer, val lib: TrafficSpaceUsageValueIteratorLib) : Runnable {
        override fun run() {
            lib.ecitygml_TrafficSpaceUsageValueIterator_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, TrafficSpaceUsageValueIterator.TrafficSpaceUsageValueIteratorCleaner(handle, TrafficSpaceUsageValueIterator.lib));
    }

    companion object {
        internal val libClass: Class<TrafficSpaceUsageValueIteratorLib> = TrafficSpaceUsageValueIteratorLib::class.java
        internal val lib: TrafficSpaceUsageValueIteratorLib = Native.load("ecitygml_ffi", libClass)
    }
    
    internal fun nextInternal(): TrafficSpaceUsageValue? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_TrafficSpaceUsageValueIterator_next(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = TrafficSpaceUsageValue(handle, selfEdges, false)
        return returnOpaque
    }

    var iterVal = nextInternal()

    override fun hasNext(): Boolean {
       return iterVal != null
    }

    override fun next(): TrafficSpaceUsageValue?{
        val returnVal = iterVal
        if (returnVal == null) {
            throw NoSuchElementException()
        } else {
            iterVal = nextInternal()
            return returnVal
        }
    }

}