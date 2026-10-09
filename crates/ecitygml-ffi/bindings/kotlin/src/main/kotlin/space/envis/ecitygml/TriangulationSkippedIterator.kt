package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface TriangulationSkippedIteratorLib: Library {
    fun ecitygml_TriangulationSkippedIterator_destroy(handle: Pointer)
    fun ecitygml_TriangulationSkippedIterator_next(handle: Pointer): Pointer?
}
typealias TriangulationSkippedIteratorIteratorItem = Error?
/** Iterates over the errors of skipped members, borrowed from a triangulation.
*/
class TriangulationSkippedIterator internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal val aEdges: List<Any?>,
    internal var owned: Boolean,
): Iterator<Error?> {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class TriangulationSkippedIteratorCleaner(val handle: Pointer, val lib: TriangulationSkippedIteratorLib) : Runnable {
        override fun run() {
            lib.ecitygml_TriangulationSkippedIterator_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, TriangulationSkippedIterator.TriangulationSkippedIteratorCleaner(handle, TriangulationSkippedIterator.lib));
    }

    companion object {
        internal val libClass: Class<TriangulationSkippedIteratorLib> = TriangulationSkippedIteratorLib::class.java
        internal val lib: TriangulationSkippedIteratorLib = Native.load("ecitygml_ffi", libClass)
    }
    
    internal fun nextInternal(): Error? {
        
        val returnVal = lib.ecitygml_TriangulationSkippedIterator_next(handle);
        val selfEdges: List<Any> = listOf()
        val handle = returnVal ?: return null
        val returnOpaque = Error(handle, selfEdges, true)
        return returnOpaque
    }

    var iterVal = nextInternal()

    override fun hasNext(): Boolean {
       return iterVal != null
    }

    override fun next(): Error?{
        val returnVal = iterVal
        if (returnVal == null) {
            throw NoSuchElementException()
        } else {
            iterVal = nextInternal()
            return returnVal
        }
    }

}