package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface DirectPositionIteratorLib: Library {
    fun ecitygml_DirectPositionIterator_destroy(handle: Pointer)
    fun ecitygml_DirectPositionIterator_next(handle: Pointer): Pointer?
}
typealias DirectPositionIteratorIteratorItem = DirectPosition?
/** Iterates over positions, borrowed from a city model.
*/
class DirectPositionIterator internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal val aEdges: List<Any?>,
    internal var owned: Boolean,
): Iterator<DirectPosition?> {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class DirectPositionIteratorCleaner(val handle: Pointer, val lib: DirectPositionIteratorLib) : Runnable {
        override fun run() {
            lib.ecitygml_DirectPositionIterator_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, DirectPositionIterator.DirectPositionIteratorCleaner(handle, DirectPositionIterator.lib));
    }

    companion object {
        internal val libClass: Class<DirectPositionIteratorLib> = DirectPositionIteratorLib::class.java
        internal val lib: DirectPositionIteratorLib = Native.load("ecitygml_ffi", libClass)
    }
    
    internal fun nextInternal(): DirectPosition? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_DirectPositionIterator_next(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = DirectPosition(handle, selfEdges, false)
        return returnOpaque
    }

    var iterVal = nextInternal()

    override fun hasNext(): Boolean {
       return iterVal != null
    }

    override fun next(): DirectPosition?{
        val returnVal = iterVal
        if (returnVal == null) {
            throw NoSuchElementException()
        } else {
            iterVal = nextInternal()
            return returnVal
        }
    }

}