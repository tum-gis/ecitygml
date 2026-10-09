package space.envis.ecitygml;
import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface AuxiliaryTrafficSpaceFunctionValueIteratorLib: Library {
    fun ecitygml_AuxiliaryTrafficSpaceFunctionValueIterator_destroy(handle: Pointer)
    fun ecitygml_AuxiliaryTrafficSpaceFunctionValueIterator_next(handle: Pointer): Pointer?
}
typealias AuxiliaryTrafficSpaceFunctionValueIteratorIteratorItem = AuxiliaryTrafficSpaceFunctionValue?
/** Iterates over a list of code-list values, borrowed from a city model.
*/
class AuxiliaryTrafficSpaceFunctionValueIterator internal constructor (
    internal val handle: Pointer,
    // These ensure that anything that is borrowed is kept alive and not cleaned
    // up by the garbage collector.
    internal val selfEdges: List<Any>,
    internal val aEdges: List<Any?>,
    internal var owned: Boolean,
): Iterator<AuxiliaryTrafficSpaceFunctionValue?> {

    init {
        if (this.owned) {
            this.registerCleaner()
        }
    }

    private class AuxiliaryTrafficSpaceFunctionValueIteratorCleaner(val handle: Pointer, val lib: AuxiliaryTrafficSpaceFunctionValueIteratorLib) : Runnable {
        override fun run() {
            lib.ecitygml_AuxiliaryTrafficSpaceFunctionValueIterator_destroy(handle)
        }
    }
    private fun registerCleaner() {
        CLEANER.register(this, AuxiliaryTrafficSpaceFunctionValueIterator.AuxiliaryTrafficSpaceFunctionValueIteratorCleaner(handle, AuxiliaryTrafficSpaceFunctionValueIterator.lib));
    }

    companion object {
        internal val libClass: Class<AuxiliaryTrafficSpaceFunctionValueIteratorLib> = AuxiliaryTrafficSpaceFunctionValueIteratorLib::class.java
        internal val lib: AuxiliaryTrafficSpaceFunctionValueIteratorLib = Native.load("ecitygml_ffi", libClass)
    }
    
    internal fun nextInternal(): AuxiliaryTrafficSpaceFunctionValue? {
        // This lifetime edge depends on lifetimes: 'a
        val aEdges: MutableList<Any> = mutableListOf(this);
        
        val returnVal = lib.ecitygml_AuxiliaryTrafficSpaceFunctionValueIterator_next(handle);
        val selfEdges: List<Any> = listOf(this)
        val handle = returnVal ?: return null
        val returnOpaque = AuxiliaryTrafficSpaceFunctionValue(handle, selfEdges, false)
        return returnOpaque
    }

    var iterVal = nextInternal()

    override fun hasNext(): Boolean {
       return iterVal != null
    }

    override fun next(): AuxiliaryTrafficSpaceFunctionValue?{
        val returnVal = iterVal
        if (returnVal == null) {
            throw NoSuchElementException()
        } else {
            iterVal = nextInternal()
            return returnVal
        }
    }

}