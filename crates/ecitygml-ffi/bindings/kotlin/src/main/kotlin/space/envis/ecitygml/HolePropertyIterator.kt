package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface HolePropertyIteratorLib: Library {
    fun ecitygml_HolePropertyIterator_destroy(handle: Pointer)
    fun ecitygml_HolePropertyIterator_next(handle: Pointer): Pointer?
}
typealias HolePropertyIteratorIteratorItem = HoleProperty?
/** Iterates over hole properties, borrowed from a city model.
*/
class HolePropertyIterator internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal val aEdges: List<Any?>,
    internal var owned: Boolean,
): Iterator<HoleProperty?> {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class HolePropertyIteratorCleaner(val handle: Pointer, val lib: HolePropertyIteratorLib) : Runnable {
        override fun run() {
            lib.ecitygml_HolePropertyIterator_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, HolePropertyIterator.HolePropertyIteratorCleaner(handle, HolePropertyIterator.lib));
    }

    companion object {
        internal val libClass: Class<HolePropertyIteratorLib> = HolePropertyIteratorLib::class.java
        internal val lib: HolePropertyIteratorLib = Native.load("ecitygml_ffi", libClass)
    }
    
    internal fun nextInternal(): HoleProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_HolePropertyIterator_next(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = HoleProperty(handle, selfEdges, false)
        return returnOpaque
    }

    var iterVal = nextInternal()

    override fun hasNext(): Boolean {
       return iterVal != null
    }

    override fun next(): HoleProperty?{
        val returnVal = iterVal
        if (returnVal == null) {
            throw NoSuchElementException()
        } else {
            iterVal = nextInternal()
            return returnVal
        }
    }

}