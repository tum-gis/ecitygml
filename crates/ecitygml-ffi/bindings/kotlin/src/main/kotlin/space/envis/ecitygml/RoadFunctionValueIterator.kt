package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface RoadFunctionValueIteratorLib: Library {
    fun ecitygml_RoadFunctionValueIterator_destroy(handle: Pointer)
    fun ecitygml_RoadFunctionValueIterator_next(handle: Pointer): Pointer?
}
typealias RoadFunctionValueIteratorIteratorItem = RoadFunctionValue?
/** Iterates over a list of code-list values, borrowed from a city model.
*/
class RoadFunctionValueIterator internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal val aEdges: List<Any?>,
    internal var owned: Boolean,
): Iterator<RoadFunctionValue?> {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class RoadFunctionValueIteratorCleaner(val handle: Pointer, val lib: RoadFunctionValueIteratorLib) : Runnable {
        override fun run() {
            lib.ecitygml_RoadFunctionValueIterator_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, RoadFunctionValueIterator.RoadFunctionValueIteratorCleaner(handle, RoadFunctionValueIterator.lib));
    }

    companion object {
        internal val libClass: Class<RoadFunctionValueIteratorLib> = RoadFunctionValueIteratorLib::class.java
        internal val lib: RoadFunctionValueIteratorLib = Native.load("ecitygml_ffi", libClass)
    }
    
    internal fun nextInternal(): RoadFunctionValue? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_RoadFunctionValueIterator_next(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = RoadFunctionValue(handle, selfEdges, false)
        return returnOpaque
    }

    var iterVal = nextInternal()

    override fun hasNext(): Boolean {
       return iterVal != null
    }

    override fun next(): RoadFunctionValue?{
        val returnVal = iterVal
        if (returnVal == null) {
            throw NoSuchElementException()
        } else {
            iterVal = nextInternal()
            return returnVal
        }
    }

}