package io.github.tum_gis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface CodeIteratorLib: Library {
    fun ecitygml_CodeIterator_destroy(handle: Pointer)
    fun ecitygml_CodeIterator_next(handle: Pointer): Pointer?
}
typealias CodeIteratorIteratorItem = Code?
/** Iterates over a list of codes (e.g. `gml:name`s), borrowed from a city model.
*/
class CodeIterator internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal val aEdges: List<Any?>,
    internal var owned: Boolean,
): Iterator<Code?> {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class CodeIteratorCleaner(val handle: Pointer, val lib: CodeIteratorLib) : Runnable {
        override fun run() {
            lib.ecitygml_CodeIterator_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, CodeIterator.CodeIteratorCleaner(handle, CodeIterator.lib));
    }

    companion object {
        internal val libClass: Class<CodeIteratorLib> = CodeIteratorLib::class.java
        internal val lib: CodeIteratorLib = Native.load("ecitygml_ffi", libClass)
    }
    
    internal fun nextInternal(): Code? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_CodeIterator_next(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = Code(handle, selfEdges, false)
        return returnOpaque
    }

    var iterVal = nextInternal()

    override fun hasNext(): Boolean {
       return iterVal != null
    }

    override fun next(): Code?{
        val returnVal = iterVal
        if (returnVal == null) {
            throw NoSuchElementException()
        } else {
            iterVal = nextInternal()
            return returnVal
        }
    }

}