package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface BridgeUsageValueIteratorLib: Library {
    fun ecitygml_BridgeUsageValueIterator_destroy(handle: Pointer)
    fun ecitygml_BridgeUsageValueIterator_next(handle: Pointer): Pointer?
}
typealias BridgeUsageValueIteratorIteratorItem = BridgeUsageValue?
/** Iterates over a list of code-list values, borrowed from a city model.
*/
class BridgeUsageValueIterator internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal val aEdges: List<Any?>,
    internal var owned: Boolean,
): Iterator<BridgeUsageValue?> {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class BridgeUsageValueIteratorCleaner(val handle: Pointer, val lib: BridgeUsageValueIteratorLib) : Runnable {
        override fun run() {
            lib.ecitygml_BridgeUsageValueIterator_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, BridgeUsageValueIterator.BridgeUsageValueIteratorCleaner(handle, BridgeUsageValueIterator.lib));
    }

    companion object {
        internal val libClass: Class<BridgeUsageValueIteratorLib> = BridgeUsageValueIteratorLib::class.java
        internal val lib: BridgeUsageValueIteratorLib = Native.load("ecitygml_ffi", libClass)
    }
    
    internal fun nextInternal(): BridgeUsageValue? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_BridgeUsageValueIterator_next(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = BridgeUsageValue(handle, selfEdges, false)
        return returnOpaque
    }

    var iterVal = nextInternal()

    override fun hasNext(): Boolean {
       return iterVal != null
    }

    override fun next(): BridgeUsageValue?{
        val returnVal = iterVal
        if (returnVal == null) {
            throw NoSuchElementException()
        } else {
            iterVal = nextInternal()
            return returnVal
        }
    }

}