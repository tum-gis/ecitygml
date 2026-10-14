package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface AbstractReliefComponentPropertyIteratorLib: Library {
    fun ecitygml_AbstractReliefComponentPropertyIterator_destroy(handle: Pointer)
    fun ecitygml_AbstractReliefComponentPropertyIterator_next(handle: Pointer): Pointer?
}
typealias AbstractReliefComponentPropertyIteratorIteratorItem = AbstractReliefComponentProperty?
/** Iterates over relief component properties, borrowed from a city model.
*/
class AbstractReliefComponentPropertyIterator internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal val aEdges: List<Any?>,
    internal var owned: Boolean,
): Iterator<AbstractReliefComponentProperty?> {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class AbstractReliefComponentPropertyIteratorCleaner(val handle: Pointer, val lib: AbstractReliefComponentPropertyIteratorLib) : Runnable {
        override fun run() {
            lib.ecitygml_AbstractReliefComponentPropertyIterator_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, AbstractReliefComponentPropertyIterator.AbstractReliefComponentPropertyIteratorCleaner(handle, AbstractReliefComponentPropertyIterator.lib));
    }

    companion object {
        internal val libClass: Class<AbstractReliefComponentPropertyIteratorLib> = AbstractReliefComponentPropertyIteratorLib::class.java
        internal val lib: AbstractReliefComponentPropertyIteratorLib = Native.load("ecitygml_ffi", libClass)
    }
    
    internal fun nextInternal(): AbstractReliefComponentProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AbstractReliefComponentPropertyIterator_next(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = AbstractReliefComponentProperty(handle, selfEdges, false)
        return returnOpaque
    }

    var iterVal = nextInternal()

    override fun hasNext(): Boolean {
       return iterVal != null
    }

    override fun next(): AbstractReliefComponentProperty?{
        val returnVal = iterVal
        if (returnVal == null) {
            throw NoSuchElementException()
        } else {
            iterVal = nextInternal()
            return returnVal
        }
    }

}