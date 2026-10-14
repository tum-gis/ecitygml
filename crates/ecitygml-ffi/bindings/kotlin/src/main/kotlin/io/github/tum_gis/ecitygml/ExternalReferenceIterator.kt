package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface ExternalReferenceIteratorLib: Library {
    fun ecitygml_ExternalReferenceIterator_destroy(handle: Pointer)
    fun ecitygml_ExternalReferenceIterator_next(handle: Pointer): Pointer?
}
typealias ExternalReferenceIteratorIteratorItem = ExternalReference?
/** Iterates over external references, borrowed from a city model.
*/
class ExternalReferenceIterator internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal val aEdges: List<Any?>,
    internal var owned: Boolean,
): Iterator<ExternalReference?> {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class ExternalReferenceIteratorCleaner(val handle: Pointer, val lib: ExternalReferenceIteratorLib) : Runnable {
        override fun run() {
            lib.ecitygml_ExternalReferenceIterator_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, ExternalReferenceIterator.ExternalReferenceIteratorCleaner(handle, ExternalReferenceIterator.lib));
    }

    companion object {
        internal val libClass: Class<ExternalReferenceIteratorLib> = ExternalReferenceIteratorLib::class.java
        internal val lib: ExternalReferenceIteratorLib = Native.load("ecitygml_ffi", libClass)
    }
    
    internal fun nextInternal(): ExternalReference? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_ExternalReferenceIterator_next(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = ExternalReference(handle, selfEdges, false)
        return returnOpaque
    }

    var iterVal = nextInternal()

    override fun hasNext(): Boolean {
       return iterVal != null
    }

    override fun next(): ExternalReference?{
        val returnVal = iterVal
        if (returnVal == null) {
            throw NoSuchElementException()
        } else {
            iterVal = nextInternal()
            return returnVal
        }
    }

}