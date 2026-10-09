package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface TunnelUsageValueIteratorLib: Library {
    fun ecitygml_TunnelUsageValueIterator_destroy(handle: Pointer)
    fun ecitygml_TunnelUsageValueIterator_next(handle: Pointer): Pointer?
}
typealias TunnelUsageValueIteratorIteratorItem = TunnelUsageValue?
/** Iterates over a list of code-list values, borrowed from a city model.
*/
class TunnelUsageValueIterator internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal val aEdges: List<Any?>,
    internal var owned: Boolean,
): Iterator<TunnelUsageValue?> {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class TunnelUsageValueIteratorCleaner(val handle: Pointer, val lib: TunnelUsageValueIteratorLib) : Runnable {
        override fun run() {
            lib.ecitygml_TunnelUsageValueIterator_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, TunnelUsageValueIterator.TunnelUsageValueIteratorCleaner(handle, TunnelUsageValueIterator.lib));
    }

    companion object {
        internal val libClass: Class<TunnelUsageValueIteratorLib> = TunnelUsageValueIteratorLib::class.java
        internal val lib: TunnelUsageValueIteratorLib = Native.load("ecitygml_ffi", libClass)
    }
    
    internal fun nextInternal(): TunnelUsageValue? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_TunnelUsageValueIterator_next(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = TunnelUsageValue(handle, selfEdges, false)
        return returnOpaque
    }

    var iterVal = nextInternal()

    override fun hasNext(): Boolean {
       return iterVal != null
    }

    override fun next(): TunnelUsageValue?{
        val returnVal = iterVal
        if (returnVal == null) {
            throw NoSuchElementException()
        } else {
            iterVal = nextInternal()
            return returnVal
        }
    }

}