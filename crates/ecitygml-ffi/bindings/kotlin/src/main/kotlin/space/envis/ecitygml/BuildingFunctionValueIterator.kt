package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface BuildingFunctionValueIteratorLib: Library {
    fun ecitygml_BuildingFunctionValueIterator_destroy(handle: Pointer)
    fun ecitygml_BuildingFunctionValueIterator_next(handle: Pointer): Pointer?
}
typealias BuildingFunctionValueIteratorIteratorItem = BuildingFunctionValue?
/** Iterates over a list of code-list values, borrowed from a city model.
*/
class BuildingFunctionValueIterator internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal val aEdges: List<Any?>,
    internal var owned: Boolean,
): Iterator<BuildingFunctionValue?> {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class BuildingFunctionValueIteratorCleaner(val handle: Pointer, val lib: BuildingFunctionValueIteratorLib) : Runnable {
        override fun run() {
            lib.ecitygml_BuildingFunctionValueIterator_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, BuildingFunctionValueIterator.BuildingFunctionValueIteratorCleaner(handle, BuildingFunctionValueIterator.lib));
    }

    companion object {
        internal val libClass: Class<BuildingFunctionValueIteratorLib> = BuildingFunctionValueIteratorLib::class.java
        internal val lib: BuildingFunctionValueIteratorLib = Native.load("ecitygml_ffi", libClass)
    }
    
    internal fun nextInternal(): BuildingFunctionValue? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_BuildingFunctionValueIterator_next(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = BuildingFunctionValue(handle, selfEdges, false)
        return returnOpaque
    }

    var iterVal = nextInternal()

    override fun hasNext(): Boolean {
       return iterVal != null
    }

    override fun next(): BuildingFunctionValue?{
        val returnVal = iterVal
        if (returnVal == null) {
            throw NoSuchElementException()
        } else {
            iterVal = nextInternal()
            return returnVal
        }
    }

}