package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface AbstractSpaceBoundaryPropertyIteratorLib: Library {
    fun ecitygml_AbstractSpaceBoundaryPropertyIterator_destroy(handle: Pointer)
    fun ecitygml_AbstractSpaceBoundaryPropertyIterator_next(handle: Pointer): Pointer?
}
typealias AbstractSpaceBoundaryPropertyIteratorIteratorItem = AbstractSpaceBoundaryProperty?
/** Iterates over space boundary properties, borrowed from a city model.
*/
class AbstractSpaceBoundaryPropertyIterator internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal val aEdges: List<Any?>,
    internal var owned: Boolean,
): Iterator<AbstractSpaceBoundaryProperty?> {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class AbstractSpaceBoundaryPropertyIteratorCleaner(val handle: Pointer, val lib: AbstractSpaceBoundaryPropertyIteratorLib) : Runnable {
        override fun run() {
            lib.ecitygml_AbstractSpaceBoundaryPropertyIterator_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, AbstractSpaceBoundaryPropertyIterator.AbstractSpaceBoundaryPropertyIteratorCleaner(handle, AbstractSpaceBoundaryPropertyIterator.lib));
    }

    companion object {
        internal val libClass: Class<AbstractSpaceBoundaryPropertyIteratorLib> = AbstractSpaceBoundaryPropertyIteratorLib::class.java
        internal val lib: AbstractSpaceBoundaryPropertyIteratorLib = Native.load("ecitygml_ffi", libClass)
    }
    
    internal fun nextInternal(): AbstractSpaceBoundaryProperty? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AbstractSpaceBoundaryPropertyIterator_next(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = AbstractSpaceBoundaryProperty(handle, selfEdges, false)
        return returnOpaque
    }

    var iterVal = nextInternal()

    override fun hasNext(): Boolean {
       return iterVal != null
    }

    override fun next(): AbstractSpaceBoundaryProperty?{
        val returnVal = iterVal
        if (returnVal == null) {
            throw NoSuchElementException()
        } else {
            iterVal = nextInternal()
            return returnVal
        }
    }

}