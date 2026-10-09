package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface BridgePartPropertyIteratorLib: Library {
    fun ecitygml_BridgePartPropertyIterator_destroy(handle: Pointer)
    fun ecitygml_BridgePartPropertyIterator_next(handle: Pointer): Pointer?
}
typealias BridgePartPropertyIteratorIteratorItem = BridgePartProperty?
/** Iterates over bridge part properties, borrowed from a city model.
*/
class BridgePartPropertyIterator internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal val aEdges: List<Any?>,
    internal var owned: Boolean,
): Iterator<BridgePartProperty?> {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class BridgePartPropertyIteratorCleaner(val handle: Pointer, val lib: BridgePartPropertyIteratorLib) : Runnable {
        override fun run() {
            lib.ecitygml_BridgePartPropertyIterator_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, BridgePartPropertyIterator.BridgePartPropertyIteratorCleaner(handle, BridgePartPropertyIterator.lib));
    }

    companion object {
        internal val libClass: Class<BridgePartPropertyIteratorLib> = BridgePartPropertyIteratorLib::class.java
        internal val lib: BridgePartPropertyIteratorLib = Native.load("ecitygml_ffi", libClass)
    }
    
    internal fun nextInternal(): BridgePartProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_BridgePartPropertyIterator_next(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = BridgePartProperty(handle, selfEdges, false)
        return returnOpaque
    }

    var iterVal = nextInternal()

    override fun hasNext(): Boolean {
       return iterVal != null
    }

    override fun next(): BridgePartProperty?{
        val returnVal = iterVal
        if (returnVal == null) {
            throw NoSuchElementException()
        } else {
            iterVal = nextInternal()
            return returnVal
        }
    }

}