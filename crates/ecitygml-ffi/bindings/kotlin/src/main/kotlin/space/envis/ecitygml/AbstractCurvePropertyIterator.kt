package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface AbstractCurvePropertyIteratorLib: Library {
    fun ecitygml_AbstractCurvePropertyIterator_destroy(handle: Pointer)
    fun ecitygml_AbstractCurvePropertyIterator_next(handle: Pointer): Pointer?
}
typealias AbstractCurvePropertyIteratorIteratorItem = AbstractCurveProperty?
/** Iterates over curve properties, borrowed from a city model.
*/
class AbstractCurvePropertyIterator internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal val aEdges: List<Any?>,
    internal var owned: Boolean,
): Iterator<AbstractCurveProperty?> {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class AbstractCurvePropertyIteratorCleaner(val handle: Pointer, val lib: AbstractCurvePropertyIteratorLib) : Runnable {
        override fun run() {
            lib.ecitygml_AbstractCurvePropertyIterator_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, AbstractCurvePropertyIterator.AbstractCurvePropertyIteratorCleaner(handle, AbstractCurvePropertyIterator.lib));
    }

    companion object {
        internal val libClass: Class<AbstractCurvePropertyIteratorLib> = AbstractCurvePropertyIteratorLib::class.java
        internal val lib: AbstractCurvePropertyIteratorLib = Native.load("ecitygml_ffi", libClass)
    }
    
    internal fun nextInternal(): AbstractCurveProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AbstractCurvePropertyIterator_next(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = AbstractCurveProperty(handle, selfEdges, false)
        return returnOpaque
    }

    var iterVal = nextInternal()

    override fun hasNext(): Boolean {
       return iterVal != null
    }

    override fun next(): AbstractCurveProperty?{
        val returnVal = iterVal
        if (returnVal == null) {
            throw NoSuchElementException()
        } else {
            iterVal = nextInternal()
            return returnVal
        }
    }

}