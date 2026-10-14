package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface BridgeFunctionValueIteratorLib: Library {
    fun ecitygml_BridgeFunctionValueIterator_destroy(handle: Pointer)
    fun ecitygml_BridgeFunctionValueIterator_next(handle: Pointer): Pointer?
}
typealias BridgeFunctionValueIteratorIteratorItem = BridgeFunctionValue?
/** Iterates over a list of code-list values, borrowed from a city model.
*/
class BridgeFunctionValueIterator internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal val aEdges: List<Any?>,
    internal var owned: Boolean,
): Iterator<BridgeFunctionValue?> {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class BridgeFunctionValueIteratorCleaner(val handle: Pointer, val lib: BridgeFunctionValueIteratorLib) : Runnable {
        override fun run() {
            lib.ecitygml_BridgeFunctionValueIterator_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, BridgeFunctionValueIterator.BridgeFunctionValueIteratorCleaner(handle, BridgeFunctionValueIterator.lib));
    }

    companion object {
        internal val libClass: Class<BridgeFunctionValueIteratorLib> = BridgeFunctionValueIteratorLib::class.java
        internal val lib: BridgeFunctionValueIteratorLib = Native.load("ecitygml_ffi", libClass)
    }
    
    internal fun nextInternal(): BridgeFunctionValue? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_BridgeFunctionValueIterator_next(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = BridgeFunctionValue(handle, selfEdges, false)
        return returnOpaque
    }

    var iterVal = nextInternal()

    override fun hasNext(): Boolean {
       return iterVal != null
    }

    override fun next(): BridgeFunctionValue?{
        val returnVal = iterVal
        if (returnVal == null) {
            throw NoSuchElementException()
        } else {
            iterVal = nextInternal()
            return returnVal
        }
    }

}