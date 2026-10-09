package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface SectionPropertyIteratorLib: Library {
    fun ecitygml_SectionPropertyIterator_destroy(handle: Pointer)
    fun ecitygml_SectionPropertyIterator_next(handle: Pointer): Pointer?
}
typealias SectionPropertyIteratorIteratorItem = SectionProperty?
/** Iterates over section properties, borrowed from a city model.
*/
class SectionPropertyIterator internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal val aEdges: List<Any?>,
    internal var owned: Boolean,
): Iterator<SectionProperty?> {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class SectionPropertyIteratorCleaner(val handle: Pointer, val lib: SectionPropertyIteratorLib) : Runnable {
        override fun run() {
            lib.ecitygml_SectionPropertyIterator_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, SectionPropertyIterator.SectionPropertyIteratorCleaner(handle, SectionPropertyIterator.lib));
    }

    companion object {
        internal val libClass: Class<SectionPropertyIteratorLib> = SectionPropertyIteratorLib::class.java
        internal val lib: SectionPropertyIteratorLib = Native.load("ecitygml_ffi", libClass)
    }
    
    internal fun nextInternal(): SectionProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_SectionPropertyIterator_next(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = SectionProperty(handle, selfEdges, false)
        return returnOpaque
    }

    var iterVal = nextInternal()

    override fun hasNext(): Boolean {
       return iterVal != null
    }

    override fun next(): SectionProperty?{
        val returnVal = iterVal
        if (returnVal == null) {
            throw NoSuchElementException()
        } else {
            iterVal = nextInternal()
            return returnVal
        }
    }

}