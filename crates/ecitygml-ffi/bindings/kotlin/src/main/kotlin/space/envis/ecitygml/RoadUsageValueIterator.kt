package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface RoadUsageValueIteratorLib: Library {
    fun ecitygml_RoadUsageValueIterator_destroy(handle: Pointer)
    fun ecitygml_RoadUsageValueIterator_next(handle: Pointer): Pointer?
}
typealias RoadUsageValueIteratorIteratorItem = RoadUsageValue?
/** Iterates over a list of code-list values, borrowed from a city model.
*/
class RoadUsageValueIterator internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal val aEdges: List<Any?>,
    internal var owned: Boolean,
): Iterator<RoadUsageValue?> {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class RoadUsageValueIteratorCleaner(val handle: Pointer, val lib: RoadUsageValueIteratorLib) : Runnable {
        override fun run() {
            lib.ecitygml_RoadUsageValueIterator_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, RoadUsageValueIterator.RoadUsageValueIteratorCleaner(handle, RoadUsageValueIterator.lib));
    }

    companion object {
        internal val libClass: Class<RoadUsageValueIteratorLib> = RoadUsageValueIteratorLib::class.java
        internal val lib: RoadUsageValueIteratorLib = Native.load("ecitygml_ffi", libClass)
    }
    
    internal fun nextInternal(): RoadUsageValue? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_RoadUsageValueIterator_next(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = RoadUsageValue(handle, selfEdges, false)
        return returnOpaque
    }

    var iterVal = nextInternal()

    override fun hasNext(): Boolean {
       return iterVal != null
    }

    override fun next(): RoadUsageValue?{
        val returnVal = iterVal
        if (returnVal == null) {
            throw NoSuchElementException()
        } else {
            iterVal = nextInternal()
            return returnVal
        }
    }

}